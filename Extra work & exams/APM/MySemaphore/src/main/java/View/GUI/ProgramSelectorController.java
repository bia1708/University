package View.GUI;

import Controller.Controller;
import Domain.Statements.IStatement;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;
import View.CLI.Examples;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;

public class ProgramSelectorController {
    @FXML
    private ListView<IStatement> examples;
    private Controller controller;
    private final ProgramWatchController watchController;

    public ProgramSelectorController(Controller controller, ProgramWatchController watchController) {
        this.controller = controller;
        this.watchController = watchController;
    }

    @FXML
    void initialize() {
        examples.setItems(FXCollections.observableArrayList(Examples.getExamples()));
        examples.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        examples.getSelectionModel().selectedItemProperty().addListener(
                (observable, oldValue, newValue) -> {
                    try {
//                        PrgState state = new PrgState(newValue);
//                        IRepository repository = new Repository("log.txt");
//                        Controller controller = new Controller(repository);
//                        try {
//                            controller.runTypeChecker();
//                            repository.addState(state);
//                            this.controller = controller;
//                        } catch (ExprException | StmtException | ADTException e) {
//                            throw new RuntimeException(e);
                        this.controller.setProgram(newValue);
                    } catch (ExprException | StmtException | ADTException e) {
                        throw new RuntimeException(e);
                    } finally {
                        watchController.setController(controller);
                        watchController.refresh();
                    }
                }
        );
    }

}
