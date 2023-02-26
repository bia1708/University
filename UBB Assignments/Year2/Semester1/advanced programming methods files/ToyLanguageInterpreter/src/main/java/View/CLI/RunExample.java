package View.CLI;

import Controller.Controller;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

public class RunExample extends Command{
    private final Controller controller;

    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }


    @Override
    public void execute() {
        try{
            controller.allSteps();
        }
        catch (ExprException | StmtException | ADTException error) {
            System.out.println(error.getMessage());
        }
    }
}
