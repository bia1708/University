package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyStack;
import Domain.PrgState;
import Domain.Types.*;
import Domain.Values.*;
import Exceptions.ADTException;
import Exceptions.StmtException;

public class VarDeclStmt implements IStatement{
    String name;
    Type type;

    public VarDeclStmt(String name, Type type) {
        this.name = name;
        this.type = type;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ADTException {
        IMyStack<IStatement> stack = state.getStack();
        IMyDictionary<String, Value> table = state.getSymTable();
        if (table.isDefined(this.name)) {
            throw new StmtException("Variable is already declared");
        } else {
            table.add(this.name, this.type.defaultValue());
        }
        state.setSymTable(table);
        state.setExeStack(stack);
        return state;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ADTException {
        if (typeEnvironment.isDefined(this.name)) {
            throw new StmtException("The variable " + this.name + " already defined");
        }
        typeEnvironment.update(this.name, this.type);
        return typeEnvironment;
    }

    @Override
    public String toString() {
        return this.type + " " + this.name;
    }
}
