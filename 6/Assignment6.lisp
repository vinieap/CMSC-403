; 1. myList function
; Returns a list containing (4 (7 22) "art" ("math (8) 99) 100)
(defun myList ()
  (list 4 '(7 22) "art" '("math" (8) 99) 100)
)

; 2. leapYear function
; Returns an ordered list of all leap years between 1800 and 2019
(defun leapYear ()
  ; Creates new label to calculate leap years
  (labels ((createList (currentYear retList)
          ; Check if the year is on or past 2019, returns all leap years if true
    (cond ((<= 2019 currentYear) retList)
          ; Check conditions for if it is NOT a leap year
          ((and (/= (mod currentYear 400) 0) (= (mod currentYear 100) 0) (= (mod currentYear 4) 0)) (createList (+ 4 currentYear) retList))
          ; Else it must be a leap year and add it to the list
          (T (createList (+ 4 currentYear) (append retList (list currentYear)))))
          ))
    ; Create the list
    (createList 1800 '())
  )
)

; 3. union function
; Returns the union of two lists without duplicates
(defun union- (list1 list2 &optional retList)
  ; Create label to loop and check if element is already in the list
  (labels ((alreadyInList (element searchList)
                  ; If list is empty then element is not in list and return false
            (cond ((null searchList) NIL)
                  ; If element is equal to element in list then return true
                  ((eql element (car searchList)) T)
                  ; Continue going through list if not equal and not empty
                  (T (alreadyInList element (cdr searchList)))
            )
          ))
          ; Check if both lists are empty, return the final unioned list
    (cond ((and (null list1) (null list2)) retList)
          ; Check if only the first list is empty
          ((null list1) (union- list1 (cdr list2) (if (alreadyInList (car list2) retList) retList (append retList (list (car list2))))))
          ; Check if only the second list is empty
          ((null list2) (union- (cdr list1) list2 (if (alreadyInList (car list1) retList) retList (append retList (list (car list1))))))
          ; Go through list 1 until end
          (T (union- (cdr list1) list2 (if (alreadyInList (car list1) retList) retList (append retList (list (car list1))))))
    )
  )
)

; 4. avg function
; Returns the average of a list of numbers
(defun avg (numbers)
          ; Check if list is empty
	(cond ((= (length numbers) 0) NIL)
        (T
          ; Create label to loop through list and calculate average
          (labels ((avr (sum size l1)
          ; If list is empty then divide sum by size and return average
          (cond ((= (length l1) 0) (/ sum size))
                ; If not empty then add first element to sum and 1 to size and recurse
                ((avr (+ sum (car l1)) (+ size 1) (cdr l1)))
          )
        ))
        ; Start calculating average
        (avr 0 0 numbers)
      )
    )
  )
)

; 5. isType function
; Returns if a value is the date type given
(defun isType (dataType)
  ; Checks dataType with the data type sent to the anonymous function
	(function (lambda (otherDataType) (typep otherDataType dataType)))
)

; 6. taxCalculator function
; Returns tax
(defun taxCalculator (limit rate values &optional retList)
        ; Check if values is empty, return final tax list
  (cond ((= (length values) 0) retList)
        ; If value > limit then call taxCalculator and append rate * value to retList
        ((< limit (car values)) (taxCalculator limit rate (cdr values) (append retList (list (* rate (car values))))))
        ; Else value <= limit and call taxCalculator and append original value to retList
        (T (taxCalculator limit rate (cdr values) (append retList (list (car values)))))
  )
)

; 7. clean function
; Returns cleaned up list
(defun clean (aFunc aList)
        ; Check if the list of empty
  (cond ((null aList) NIL)
        ; If the element is a list itself then go into that list and clean it
        ((consp (car aList)) (cons (clean aFunc (car aList)) (clean aFunc (cdr aList))))
        ; Call the aFunc with the element and if it is true then create new cons cell
        ((funcall aFunc (car aList)) (cons (car aList) (clean aFunc (cdr aList))))
        ; Go to next element
        (T (clean aFunc (cdr aList)))
  )
)

; 8. threeWayBranch macro
; Creates new macro
(defmacro threeWayBranch (x y toExecute)
  ; Create label to loop through execution sublist
  (labels ((execute (executeList)
                  ; Check if executeList is empty
            (cond ((= 0 (length executeList)) NIL)
                  ; Evaluate statement and go to next element in list
                  (T (progn (eval (car executeList)) (execute (cdr executeList))))
            )
          ))
          ; Check if sublist 1 needs to be evaluated
    (cond ((< x y) (execute (car toExecute)))
          ; Check if sublist 2 needs to be evaluated
          ((> x y) (execute (car (cdr toExecute))))
          ; Check if sublist 3 needs to be evaluated
          (T (execute (car (cdr (cdr toExecute)))))
    )
  )
)
