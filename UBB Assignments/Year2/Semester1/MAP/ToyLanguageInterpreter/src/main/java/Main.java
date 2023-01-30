import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;
//import View.CLI.View;


public class Main {
    public static void main(String[] args) throws ExprException, StmtException, ADTException {
//        View UI = new View();

        View.GUI.Main.main(args);
    }
}
