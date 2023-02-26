package Domain.Statements;

import Domain.ADT.*;
import Domain.PrgState;
import Domain.Types.Type;
import Domain.Values.StringValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

import java.io.BufferedReader;
import java.util.Map;

public class ForkStmt implements IStatement{
    private IStatement statement;

    public ForkStmt(IStatement statement) {
        this.statement = statement;
    }


    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyStack<IStatement> stk = state.getStack();
        IMyDictionary<String, Value> symTable = state.getSymTable();
        IMyHeap<Value> heap = state.getHeap();
        IMyList<Value> outList = state.getOutConsole();
        IMyDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();

        MyStack<IStatement> newStk = new MyStack<IStatement>();
        MyDictionary<String, Value> newSymTable = new MyDictionary<String, Value>();
        for (Map.Entry<String, Value> entry : symTable.getContent().entrySet()) {
            newSymTable.add(new String(entry.getKey()), entry.getValue());
        }
        return new PrgState(newStk, newSymTable, heap, outList, fileTable, state.getSemTable(), this.statement);
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        statement.typecheck(typeEnvironment);
        return typeEnvironment;
    }

    @Override
    public String toString() {
        return "fork(" + statement + ")";
    }
}
