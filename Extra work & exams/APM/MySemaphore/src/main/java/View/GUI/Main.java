package View.GUI;

import Controller.Controller;
import Repository.IRepository;
import Repository.Repository;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage selectorStage) throws Exception {
        IRepository repo = new Repository("log.txt");
        Controller controller = new Controller(repo);

        Stage programWatchStage = new Stage();
        FXMLLoader programWatchLoader = new FXMLLoader(getClass().getResource("/ProgramWatch.fxml"));
        ProgramWatchController programWatchController = new ProgramWatchController(controller);
        programWatchLoader.setController(programWatchController);

        Scene programWatchScene = programWatchLoader.load();
        programWatchStage.setScene(programWatchScene);
        programWatchStage.setTitle("Program Watch");
        programWatchStage.show();


        FXMLLoader programSelectorLoader = new FXMLLoader(getClass().getResource("/ProgramSelector.fxml"));
        programSelectorLoader.setController(new ProgramSelectorController(controller, programWatchController));

        Scene programSelectorScene = programSelectorLoader.load();
        selectorStage.setScene(programSelectorScene);
        selectorStage.setTitle("Program Selector");
        selectorStage.show();
    }
}
