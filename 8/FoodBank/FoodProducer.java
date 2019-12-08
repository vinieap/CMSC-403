import java.util.Random;

public class FoodProducer extends Thread {
    
    FoodBank bank;

    FoodProducer(FoodBank bank) {
        this.bank = bank; //Initialize FoodProducer
    }

    public void run() {
        Random r = new Random();
        while(true) {
            try { 
                bank.giveFood(r.nextInt(100) + 1); //Give 1-100 items of food to FoodBank
                sleep(100); //Sleep for 0.1 seconds
            } catch(InterruptedException e) {}
        }
    }
}