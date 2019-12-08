public class FoodBankPatrons {


    public static void main(String[] args) {
        //Create FoodBank, FoodProducer, and FoodConsumer(s)
        FoodBank fb = new FoodBank();
        Thread prod = new FoodProducer(fb);
        Thread cons1 = new FoodConsumer(fb);
        Thread cons2 = new FoodConsumer(fb);
        Thread cons3 = new FoodConsumer(fb);

        //Start threads
        prod.start();
        cons1.start();
        cons2.start();
        cons3.start();
    }
}