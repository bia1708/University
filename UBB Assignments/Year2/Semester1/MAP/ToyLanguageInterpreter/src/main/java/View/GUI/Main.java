package View.GUI;

import Controller.Controller;
import Repository.IRepository;
import Repository.Repository;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.net.URL;

public class Main extends Application {
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage selectorStage) throws Exception {
        // each repo gets a different file when selected

        Stage programWatchStage = new Stage();
        FXMLLoader programWatchLoader = new FXMLLoader(getClass().getResource("/ProgramWatch.fxml"));
        ProgramWatchController programWatchController = new ProgramWatchController();
        programWatchLoader.setController(programWatchController);

        Scene programWatchScene = programWatchLoader.load();
        programWatchStage.setScene(programWatchScene);
        programWatchStage.setTitle("Program Watch");
        programWatchStage.show();


        FXMLLoader programSelectorLoader = new FXMLLoader(getClass().getResource("/ProgramSelector.fxml"));
        programSelectorLoader.setController(new ProgramSelectorController(programWatchController));

        Scene programSelectorScene = programSelectorLoader.load();
        selectorStage.setScene(programSelectorScene);
        selectorStage.setTitle("Program Selector");
        selectorStage.show();
    }
}
