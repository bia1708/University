package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyStack;
import Domain.PrgState;
import Domain.Types.Type;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

public class CompStmt implements IStatement {
    IStatement first;
    IStatement snd;

    public CompStmt(IStatement first, IStatement snd) {
        this.first = first;
        this.snd = snd;
    }

    @Override
    public PrgState execute(PrgState state)  throws StmtException {
        IMyStack<IStatement> stack = state.getStack();
        stack.push(this.snd);
        stack.push(this.first);
        state.setExeStack(stack);
        return state;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        return this.snd.typecheck(this.first.typecheck(typeEnvironment));
    }

    @Override
    public String toString() {
        return "(" + this.first.toString() + ";" + this.snd.toString() + ")";
    }
}
