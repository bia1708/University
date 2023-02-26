import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;



public class Main {
    public static void main(String[] args) throws ExprException, StmtException, ADTException {
//        View.CLI.View UI = new View.CLI.View();
//        UI.main(args);

        View.GUI.Main.main(args);
    }
}
