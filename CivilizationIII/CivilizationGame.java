package runner;

import java.util.Optional;
import controller.GameController;
import model.Civilization;
import view.StartScreen;
import view.GameScreen;
import view.GridFX;
import view.CivEnum;
import model.QinDynasty;
import model.RomanEmpire;
import model.Egypt;
import model.Bandit;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;
import javafx.scene.control.Label;
import javafx.scene.control.TextInputDialog;
import javafx.event.EventHandler;
import javafx.scene.control.ListView;
import java.util.NoSuchElementException;

/**
 * Created by Tian-Yo Yang on 11/11/2016.
 */
public class CivilizationGame extends Application {

    /**
     * this method is called upon running/launching the application
     * this method should display a scene on the stage
     */
    private Stage window;
    private Button button1;
    private Scene scene1, scene2;
    private Scene scene = null;
    private Label label1, label2;
    private EventHandler handler;
    private StartScreen startScreen = new StartScreen();
    private GameScreen gameScreen;
    private Civilization playerCivilization;


    @Override
    public void start(Stage primaryStage) {

        //Sets up the first scene or StartScreen
        window = primaryStage;
        scene1 = new Scene(startScreen);
        window.setScene(scene1);
        startScreen.getStartButton().setOnAction(e -> {
                window.setScene(startGame());
            });

        window.show();
    }


    /**
     * This is the main method that launches the javafx application
     */
    public static void main(String[] args) {
        launch(args);

    }
    /**
    * This method is responsible for setting the scene to the corresponding
    * layout.
    * and returning the scene.
    * @return Scene
    */

    public Scene startGame() {

        //Town Name with dialog box
        TextInputDialog dialog = new TextInputDialog("Town Name");
        dialog.setTitle("A New Settlement");
        dialog.setHeaderText("You have built a Settlement!");
        dialog.setContentText("Enter the Name of your first town");
        Optional<String> result = dialog.showAndWait();
        try {
            if (result.isPresent()) {
                System.out.println("Town Name: " + result.get());
            }

            //Gets name of selected enum element which is civilization
            ListView<CivEnum> pCivList = startScreen.getCivList();
            CivEnum pCivE = pCivList.getSelectionModel().getSelectedItem();
            String civName = pCivE.toString();
            if (civName == CivEnum.ANCIENT_EGYPT.toString()) {
                playerCivilization = new Egypt();
            } else if (civName == CivEnum.QIN_DYNASTY.toString()) {
                playerCivilization = new QinDynasty();
            } else if (civName == CivEnum.ROMAN_EMPIRE.toString()) {
                playerCivilization = new RomanEmpire();
            }

                //Sets Civilization in GameController
            GameController.setCivilization(playerCivilization);
            System.out.println(GameController.getCivilization().getName());

            GridFX.getMap().putSettlement(result.get(),
                playerCivilization, 5, 5);

            GridFX.getMap().addEnemies(new Bandit(), 1);
            GridFX grid = GridFX.getInstance();

            gameScreen = new GameScreen();
            gameScreen.setCenter(grid);
            gameScreen.update();
            scene = new Scene(gameScreen);
            window.setMaximized(true);
            window.show();

            return scene;
        } catch (NoSuchElementException e) {
            e.getMessage();
        }
        return scene1;
    }



}
