package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyList;
import Domain.ADT.IMyStack;
import Domain.Expressions.Expression;
import Domain.PrgState;
import Domain.Types.Type;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

public class PrintStmt implements IStatement {
    Expression exp;

    public PrintStmt(Expression exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyStack<IStatement> stack = state.getStack();
        IMyList<Value> outConsole = state.getOutConsole();
        outConsole.add(this.exp.eval(state.getSymTable(), state.getHeap()));
        state.setExeStack(stack);
        state.setOutConsole(outConsole);
        return state;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        this.exp.typecheck(typeEnvironment);
        return typeEnvironment;
    }

    @Override
    public String toString(){
        return "print(" + this.exp.toString() +")";
    }

}
