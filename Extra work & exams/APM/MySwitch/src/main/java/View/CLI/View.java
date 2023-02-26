package View.CLI;

import Controller.Controller;
import Domain.PrgState;
import Domain.Statements.IStatement;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;
import Repository.IRepository;
import Repository.Repository;

public class View {
    Controller controller;

    public void main(String[] args) throws ExprException, StmtException, ADTException {
        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));

        IStatement[] examples = Examples.getExamples();
        for (int i = 0; i < examples.length; i++) {
            IStatement statement = examples[i];
            PrgState programState = new PrgState(statement);
            IRepository repository = new Repository("log" + (i + 1) + ".txt");
            Controller controller = new Controller(repository);
            controller.runTypeChecker();
            repository.addState(programState);
            menu.addCommand(new RunExample(Integer.toString(i + 1), statement.toString(), controller));
        }
        menu.show();
    }
}
