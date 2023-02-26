package Domain.Expressions;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyHeap;
import Domain.Types.BoolType;
import Domain.Types.Type;
import Domain.Values.BoolValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;

public class LogicExp implements Expression{
    Expression e1;
    Expression e2;
    int op;

    public LogicExp(Expression e1, Expression e2, int op) {
        this.e1 = e1;
        this.e2 = e2;
        this.op = op;
    }

    public LogicExp(String not, Expression exp) {
        e1 = exp;
        e2 = exp;
        op = 3;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> tbl, IMyHeap<Value> heap) throws ExprException, ADTException {
        Value val1, val2;
        val1 = e1.eval(tbl, heap);

        if (val1.getType().equals(new BoolType())) {
            if (op == 3) {
                Value falseVal = new BoolValue(false);
                return new BoolValue(val1.equals(falseVal));
            }
            val2 = e2.eval(tbl, heap);
            if (val2.getType().equals(new BoolType())) {
                BoolValue i1 = (BoolValue)val1;
                BoolValue i2 = (BoolValue)val2;
                boolean x = i1.getVal();
                boolean y = i2.getVal();

                if (op == 1) {
                    return new BoolValue(x && y);
                }
                else if (op == 2) {
                    return new BoolValue(x || y);
                }
            }
            else {
                throw new ExprException("Second operand is not a boolean");
            }
        }
        else {
            throw new ExprException("First operand is not a boolean");
        }

        return new BoolValue(false);
    }

    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnv) throws ExprException, ADTException {
        Type type1 = e1.typecheck(typeEnv);
        Type type2 = e2.typecheck(typeEnv);

        if (type1.equals(new BoolType())) {
            if (type2.equals(new BoolType())) {
                return new BoolType();
            }
            else {
                throw new ExprException("The second operand is not a boolean in " + this.toString());
            }
        }
        else {
            throw new ExprException("The first operand is not a boolean in " + this.toString());
        }
    }
}
