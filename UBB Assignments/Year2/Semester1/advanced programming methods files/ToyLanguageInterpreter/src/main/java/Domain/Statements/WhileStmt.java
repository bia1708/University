package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyStack;
import Domain.Expressions.Expression;
import Domain.PrgState;
import Domain.Types.BoolType;
import Domain.Types.Type;
import Domain.Values.BoolValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

public class WhileStmt implements IStatement{
    private Expression exp;
    private IStatement statement;

    public WhileStmt(Expression exp, IStatement statement) {
        this.exp = exp;
        this.statement = statement;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyStack<IStatement> stk = state.getStack();
        IMyDictionary<String, Value> symTable = state.getSymTable();
        Value val = this.exp.eval(symTable, state.getHeap());

        if (val.getType().equals(new BoolType())) {
            BoolValue boolVal = (BoolValue) val;
            if (boolVal.getVal()) {
                stk.push(this);
                stk.push(this.statement);
            }
        }
        else {
            throw new StmtException("The While condition is not a boolean");
        }
        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        Type expType = this.exp.typecheck(typeEnvironment);
        if (expType.equals(new BoolType())) {
            this.statement.typecheck(typeEnvironment);
            return typeEnvironment;
        }
        else {
            throw new StmtException("The condition in " + this.toString() + " is not a boolean");
        }
    }

    @Override
    public String toString() {
        return "(while (" + this.exp + ") " + this.statement + ")";
    }
}
