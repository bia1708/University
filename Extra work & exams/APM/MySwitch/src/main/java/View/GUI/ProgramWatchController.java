package View.GUI;

import Controller.Controller;
import Domain.PrgState;
import Domain.Statements.IStatement;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.value.ChangeListener;
import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Pair;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

public class ProgramWatchController {
    private Controller controller;
    private final ChangeListener<Integer> programStatesListSelectHandler = (observable, oldValue, newValue) -> refresh();
    @FXML
    private ResourceBundle resources;
    @FXML
    private URL location;
    @FXML
    private ListView<String> filesList;
    @FXML
    private TableView<Pair<Integer, Value>> heapTable;
    @FXML
    private TableColumn<Pair<Integer, Value>, Integer> heapTableAddressColumn;
    @FXML
    private TableColumn<Pair<Integer, Value>, String> heapTableValueColumn;
    @FXML
    private TextField numberOfProgramStates;
    @FXML
    private Button oneStepButton;
    @FXML
    private ListView<String> outList;
    @FXML
    private ListView<Integer> programStatesList;
    @FXML
    private ListView<IStatement> stackList;
    @FXML
    private TableView<Pair<String, Value>> symbolsTable;
    @FXML
    private TableColumn<Pair<String, Value>, String> symbolsTableValueColumn;
    @FXML
    private TableColumn<Pair<String, Value>, String> symbolsTableVariableNameColumn;

    public ProgramWatchController(Controller controller) {
        this.controller = controller;
    }

    public void setController(Controller controller){
        this.controller = controller;
    }

    @FXML
    void initialize() {
        symbolsTableValueColumn.setCellValueFactory(pair -> new SimpleStringProperty(pair.getValue().getValue().toString()));
        symbolsTableVariableNameColumn.setCellValueFactory(pair -> new SimpleStringProperty(pair.getValue().getKey()));
        heapTableValueColumn.setCellValueFactory(pair -> new SimpleStringProperty(pair.getValue().getValue().toString()));
        heapTableAddressColumn.setCellValueFactory(pair -> new SimpleIntegerProperty(pair.getValue().getKey()).asObject());

        programStatesList.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);

        oneStepButton.setOnAction(this::handleOneStepButtonClick);
        programStatesList.getSelectionModel().selectedItemProperty().addListener(programStatesListSelectHandler);
    }

    void handleOneStepButtonClick(ActionEvent event){
        if (controller == null) {
            return;
        }
        try {
            controller.oneStepAll();
        } catch (ExprException | StmtException | ADTException e){
            System.out.println(e.toString());
        }
        refresh();
    }

    void refresh() {
        programStatesList.getSelectionModel().selectedItemProperty().removeListener(programStatesListSelectHandler);
        clearAllWindows();
        if (controller.getProgramStates().isEmpty()) {
            return;
        }
        Integer programStateIdInt = programStatesList.getSelectionModel().getSelectedItem();
        if (programStateIdInt == null) {
            programStateIdInt = controller.getProgramStates().get(0).getStateID();
            programStatesList.getSelectionModel().select(0);
        }
        final int programStateId = programStateIdInt;
        PrgState programState = controller.getProgramStates().stream()
                .filter(p -> p.getStateID() == programStateId).findFirst().get();

        // Program States List
        programStatesList.setItems(FXCollections.observableArrayList(
                controller.getProgramStates().stream().map(PrgState::getStateID).toList()
        ));

        // Stack List
        List<IStatement> stack = new ArrayList<>(programState.getStack().toList());
        stackList.setItems(FXCollections.observableArrayList(stack));
        oneStepButton.setDisable(stack.isEmpty());

        // Symbols Table
        symbolsTable.setItems(FXCollections.observableArrayList(
                programState.getSymTable().entrySet().stream().map(entry -> new Pair<>(entry.getKey(), entry.getValue())).toList()
        ));

        // Heap Table
        heapTable.setItems(FXCollections.observableArrayList(
                programState.getHeap().entrySet().stream().map(entry -> new Pair<>(entry.getKey(), entry.getValue())).toList()
        ));

        // Out List
        outList.setItems(FXCollections.observableArrayList(
                programState.getOutConsole().getList().stream().map(Value::toString).toList()
        ));

        // File List
        filesList.setItems(FXCollections.observableArrayList(
                programState.getFileTable().entrySet().stream().map(entry -> entry.getKey().toString()).toList()
        ));

        // Number of programs
        numberOfProgramStates.setText(String.valueOf(controller.getProgramStates().size()));
        refreshAllWindows();
        programStatesList.getSelectionModel().selectedItemProperty().addListener(programStatesListSelectHandler);
    }

    private void refreshAllWindows() {
        programStatesList.refresh();
        stackList.refresh();
        symbolsTable.refresh();
        heapTable.refresh();
        outList.refresh();
        filesList.refresh();
    }

    private void clearAllWindows() {
        programStatesList.getItems().clear();
        stackList.getItems().clear();
        symbolsTable.getItems().clear();
        heapTable.getItems().clear();
        outList.getItems().clear();
        filesList.getItems().clear();
        oneStepButton.setDisable(true);
    }
}
