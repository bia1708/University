package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyStack;
import Domain.Expressions.Expression;
import Domain.Expressions.RelationalExp;
import Domain.PrgState;
import Domain.Types.Type;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

public class SwitchStmt implements IStatement{
    private Expression exp;
    private Expression exp1;
    private Expression exp2;
    private IStatement statement1;
    private IStatement statement2;
    private IStatement statement3;

    public SwitchStmt(Expression exp, Expression exp1, Expression exp2, IStatement statement1, IStatement statement2, IStatement statement3) {
        this.exp = exp;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.statement1 = statement1;
        this.statement2 = statement2;
        this.statement3 = statement3;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyStack<IStatement> stack = state.getStack();


        IStatement st = new IfStmt(new RelationalExp(exp, exp1, 3), statement1,
                new IfStmt(new RelationalExp(exp, exp2, 3), statement2,
                        statement3));

        stack.push(st);

        state.setExeStack(stack);
        return state;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        Type expType = exp.typecheck(typeEnvironment);
        Type exp1Type = exp1.typecheck(typeEnvironment);
        Type exp2Type = exp2.typecheck(typeEnvironment);

        if (expType.equals(exp1Type) && expType.equals(exp2Type)) {
            statement1.typecheck(typeEnvironment);
            statement2.typecheck(typeEnvironment);
            statement3.typecheck(typeEnvironment);
            return typeEnvironment;
        }
        else {
            throw new StmtException("The types of the expressions don't match.");
        }
    }

    @Override
    public String toString(){
        return "switch(" + this.exp + ")" + "case(" + this.exp + "): " + this.statement1 + " case(" + this.exp + "): "+
                this.statement2 + " default: " + this.statement3;
    }
}
