package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.PrgState;
import Domain.Types.Type;
import Exceptions.StmtException;

public class NopStmt implements IStatement {
    @Override
    public PrgState execute(PrgState state) throws StmtException {
        return state;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException {
        return typeEnvironment;
    }

    @Override
    public String toString(){
        return "";
    }
}
