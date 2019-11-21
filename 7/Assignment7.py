import tkinter  #Canvas
import sys      #Argument
import rectpack #Rectangle Packer

class CustomCanvas:
    #CustomClass constructor
    def __init__(self, height, width):
        self.parent = tkinter.Tk() #Create new tkinter window
        self.canvas = tkinter.Canvas(self.parent, height=height, width=width) #Create new canvas in that window
        self.canvas.pack() #Pack the canvas

    def draw(self, rects):
        count = 1 #Labelling, not necessary but helpful
        for rect in rects: #Loop through all the rectangles and draw the rectangle and add a label number to it
            self.canvas.create_rectangle(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, outline="black", fill="purple")
            self.canvas.create_text(rect.x + rect.width/2, rect.y + rect.height/2, text=count)
            count = count + 1
        self.parent.mainloop() #Loop until window is closed

class Rectangle:
    #Rectangle constructor
    def __init__(self, height, width, x=0, y=0):
        self.height = int(height)
        self.width = int(width)
        self.x = x
        self.y = y

def pack(allRect, canvasSize):
    packer = rectpack.newPacker() #Create new packer object
    for rect in allRect: #Loop through rectangles and add it to the packer
        packer.add_rect(rect.width, rect.height)
    packer.add_bin(int(canvasSize[0]), int(canvasSize[1])) #Add a canvas size bin to the packer
    packer.pack() #Pack the rectangles
    returnRectangles = []

    for rect in packer.rect_list(): #Loop through packed rectangles and add it to return list
        #rect[4] = height, rect[3] = width, rect[1] = x, rect[2] = y
        returnRectangles.append(Rectangle(rect[4], rect[3], rect[1], rect[2]))
        
    return returnRectangles #Return new list of packed rectangles

def main():
    path = sys.argv[1] #Get input file path

    with open(path) as f: #Loop through file and get canvas size and all rectangle sizes
        size = (f.readline().split(','))
        rectangles = [Rectangle(*l.split(','), 0, 0) for l in f]

    newRectangles = pack(rectangles, size) #Call pack to get packed rectangles on canvas
    CustomCanvas(*size).draw(newRectangles) #Draw the rectangles to the canvas

if __name__ == "__main__": #Run as standalone file
    main()
