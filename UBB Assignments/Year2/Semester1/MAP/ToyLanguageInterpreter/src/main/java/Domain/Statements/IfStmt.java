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

public class IfStmt implements IStatement {
    private Expression expression;
    private IStatement thenStatement;
    private IStatement elseStatement;

    public IfStmt(Expression expression, IStatement thenStatement, IStatement elseStatement) {
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    @Override
    public String toString() {
        return "if (" + this.expression + ") then {" + this.thenStatement + "} else {" + this.elseStatement + "}";
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyStack<IStatement> stack = state.getStack();
        Value cond = this.expression.eval(state.getSymTable(), state.getHeap());
        if (!cond.getType().equals(new BoolType())) {
            throw new StmtException("Condition is not of boolean");
        }
        if (cond.equals(new BoolValue(true))) {
            stack.push(this.thenStatement);
        } else {
            stack.push(this.elseStatement);
        }
        state.setExeStack(stack);
        return state;
    }


    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        Type expType = expression.typecheck(typeEnvironment);
        if (expType.equals(new BoolType())) {
            thenStatement.typecheck(typeEnvironment);
            elseStatement.typecheck(typeEnvironment);
            return typeEnvironment;
        }
        else {
            throw new StmtException("The condition in " + this.toString() + " statement is not a boolean");
        }
    }
}
