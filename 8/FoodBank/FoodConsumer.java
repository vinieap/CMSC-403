import java.util.Random;

public class FoodConsumer extends Thread {

    FoodBank bank;

    FoodConsumer(FoodBank bank) {
        this.bank = bank; //Initialize FoodConsumer
    }

    @Override
    public void run() {
        Random r = new Random();
        while(true) {
            try { 
                bank.takeFood(r.nextInt(100) + 1); //Take away 1-100 food items
                sleep(100); //Sleep for 0.1 seconds
            } catch(InterruptedException e) {}
        }
    }
}