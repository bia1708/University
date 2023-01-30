package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.Expressions.Expression;
import Domain.PrgState;
import Domain.Types.Type;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

public class AssignStmt implements IStatement {
    String id;
    Expression exp;

    public AssignStmt(String id, Expression exp) {
        this.id = id;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyDictionary<String, Value> symTable = state.getSymTable();
        Value value = this.exp.eval(symTable, state.getHeap());

        if (symTable.isDefined(this.id)) {
            Type type = (symTable.lookup(this.id)).getType();
            if (value.getType().equals(type)) {
                symTable.update(this.id, value);
            }
            else {
                throw new StmtException("Declared type of variable " +
                        this.id +
                        " and type of the assigned expression do not match");
            }
        }
        else {
            throw new StmtException("The used variable " + this.id + " was not declared before");
        }
        state.setSymTable(symTable);
        return state;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnv) throws StmtException, ExprException, ADTException {
        if (!typeEnv.isDefined(this.id)) {
            throw new StmtException("The variable " + this.id + " is not defined in the assignment statement " + this.toString());
        }
        else {
            Type variableType = typeEnv.lookup(this.id);
            Type expType = this.exp.typecheck(typeEnv);
            if (variableType.equals(expType)) {
                return typeEnv;
            }
            else {
                throw new StmtException("The right side and left side of the assignment " + this.toString() + " have different types");
            }
        }
    }

    @Override
    public String toString(){
        return this.id + "=" + this.exp.toString();
    }

}
