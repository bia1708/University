package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.PrgState;
import Domain.Types.Type;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.MyException;
import Exceptions.StmtException;

public abstract interface IStatement {
    //which is the execution method for a statement.
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException, MyException;

    IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException;
}
