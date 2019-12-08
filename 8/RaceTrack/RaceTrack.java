//Imports
import javafx.application.Application;
import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType; 
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.util.Random; 


public class RaceTrack extends Application {
    
    private boolean started = false; //Tracks if race is ongoing or not
    
    private ImageView view1; //Car Images
    private ImageView view2;
    private ImageView view3;

    private Thread thread1; //Car Threads
    private Thread thread2;
    private Thread thread3;

    @Override
    public void start(Stage stage) {
        //Initialize Stage and Add to Components to Pane
        stage.setTitle("Richmond Raceway");
        stage.setResizable(false);
        Pane pane = new Pane();
        pane = createRacetrack(pane);
        pane = createRacecars(pane);
        pane = createButtons(pane);

        //Create new scene with pane
        Scene scene = new Scene(pane, 500, 200);
        stage.setScene(scene);
        stage.show(); //Show GUI
    }

    private Pane createRacetrack(Pane p) {
        //Create racetracks
        Rectangle r1 = new Rectangle(57, 70, 400, 16);
        Rectangle r2 = new Rectangle(57, 110, 400, 16);
        Rectangle r3 = new Rectangle(57, 150, 400, 16);

        //Color racetracks
        r1.setFill(Color.LIGHTGRAY);
        r2.setFill(Color.LIGHTGRAY);
        r3.setFill(Color.LIGHTGRAY);

        //Add racetracks to pane
        p.getChildren().addAll(r1, r2, r3);

        return p;
    }

    private void alert(int winner) {
        //Popup Alert with Winner
        Alert a = new Alert(AlertType.INFORMATION);
        a.setContentText("Car " + winner + " Wins!");
        a.show();
    }

    private void start() {
        //Start race
        Random r = new Random();

        Task task1 = new Task<Void>() {
            @Override
            public Void call() {
                while(true && started) {
                    //Check if finished
                    if(view1.getX() >= 396) {
                        started = false; //Stop race
                        Platform.runLater(() -> alert(1)); //Show Alert
                        break;
                    }
                    //Progress on track
                    Platform.runLater(() -> view1.setX(view1.getX() + r.nextInt(10)));
                    try {
                        Thread.sleep(50);
                    } catch(InterruptedException e) {
                        break;
                    }
                }
                return null;
            }
        };

        Task task2 = new Task<Void>() {
            @Override
            public Void call() {
                while(true && started) {
                    //Check if finished
                    if(view2.getX() >= 396) {
                        started = false; //Stop race
                        Platform.runLater(() -> alert(2)); //Show Alert
                        break;
                    }
                    //Progress on track
                    Platform.runLater(() -> view2.setX(view2.getX() + r.nextInt(10)));
                    try {
                        Thread.sleep(50);
                    } catch(InterruptedException e) {
                        break;
                    }
                }
                return null;
            }
        };

        Task task3 = new Task<Void>() {
            @Override
            public Void call() {
                while(true && started) {
                    //Check if finished
                    if(view3.getX() >= 396) {
                        started = false; //Stop race
                        Platform.runLater(() -> alert(3)); //Show Alert
                        break;
                    }
                    //Progress on track
                    Platform.runLater(() -> view3.setX(view3.getX() + r.nextInt(10)));
                    try {
                        Thread.sleep(50);
                    } catch(InterruptedException e) {
                        break;
                    }
                }
                return null;
            }
        };

        //Assign tasks to threads
        thread1 = new Thread(task1);
        thread2 = new Thread(task2);
        thread3 = new Thread(task3);

        //Safe exiting
        thread1.setDaemon(true);
        thread2.setDaemon(true);
        thread3.setDaemon(true);


        //Start race
        thread1.start();
        thread2.start();
        thread3.start();
    }

    private void reset() {
        started = false; //Stop race

        //Set racecars back to original positions
        view1.setX(0);
        view2.setX(0);
        view3.setX(0);
    }

    private Pane createButtons(Pane p) {
        //Create buttons
        Button start = new Button("Start");
        Button pause = new Button("Pause");
        Button reset = new Button("Reset");

        //Set max size for buttons
        start.setMaxSize(75, 25);
        pause.setMaxSize(75, 25);
        reset.setMaxSize(75, 25);

        p.getChildren().addAll(start, pause, reset); //Add buttons to pane

        //Place buttons in correct places
        start.relocate(100, 15);
        pause.relocate(237.5, 15);
        reset.relocate(375, 15);

        //Event listener on start button press
        start.setOnAction((event) -> {
            if(started) { //If started then do nothing
                return;
            }

            started = true; //Set start of race to true
            start(); //Start race
        });

        pause.setOnAction((event) -> {
            if(!started && thread1 != null && thread2 != null && thread3 != null) { //If race has not started or one of the threads is not initialized then do nothing
                return;
            }
            started = false; //Stop race
        });

        reset.setOnAction((event) -> {
            reset(); //Reset race
        });

        return p;
    }

    private Pane createRacecars(Pane p) {
        //Create image objects with racecar image
        Image racecar1 = new Image("/sportive-car.png");
        Image racecar2 = new Image("/sportive-car.png");
        Image racecar3 = new Image("/sportive-car.png");

        //Create an ImageView of each image to move and relocate
        view1 = new ImageView(racecar1);
        view2 = new ImageView(racecar2);
        view3 = new ImageView(racecar3);

        //Set racecar starting positions
        view1.relocate(25, 60);
        view2.relocate(25, 100);
        view3.relocate(25, 140);

        p.getChildren().addAll(view1, view2, view3); //Add racecars to pane

        return p;
    }

    public static void main(String[] args) {
        launch(); //Start Application
    }
}