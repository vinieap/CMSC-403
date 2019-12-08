import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

public class FoodBank {
    
    int food;
    private final ReentrantLock lock = new ReentrantLock(); //Lock
    private final Condition foodLow = lock.newCondition(); //Check if food is too low for taking

    FoodBank() {
        this.food = 0; //Initalize FoodBank with zero food
    }

    public void giveFood(int food) {
        lock.lock(); //Lock object to give food
        try {
            this.food += food; //Add food
            System.out.println("Giving " + food + " items of food, the balance is now " + this.food + " items");
            foodLow.signalAll(); //Signal to awaiting conditions that food has been added
        } finally {
            lock.unlock(); //Unlock object
        }
    }

    public void takeFood(int food) throws InterruptedException {
        lock.lock(); //Lock object to take away food
        try {
            while(food > this.food) { //Check if food requested is more than food available
                System.out.println("Waiting to get " + food + " items of food");
                foodLow.await(); //Wait for more food to be produced
            }
            this.food -= food; //Take away food
            System.out.println("Taking " + food + " items of food, the balance is now " + this.food + " items");
        } finally {
            lock.unlock(); //Unlock object
        }
    }
}