package Domain.Expressions;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyHeap;
import Domain.Types.IntType;
import Domain.Types.Type;
import Domain.Values.IntValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;

public class ArithExp implements Expression{
    Expression e1;
    Expression e2;
    int op; //1-plus, 2-minus, 3-star, 4-divide


    public ArithExp(Expression deepCopy, Expression deepCopy1, char op) {
        this.e1 = deepCopy;
        this.e2 = deepCopy1;
        if(op == '+')
            this.op = 1;
        if(op == '-')
            this.op = 2;
        if(op == '*')
            this.op = 3;
        if(op == '/')
            this.op = 4;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> tbl, IMyHeap<Value> heap) throws ExprException, ADTException {
        Value val1, val2;
        val1 = e1.eval(tbl, heap);
        if (val1.getType().equals(new IntType())) {
            val2 = e2.eval(tbl, heap);
            if (val2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue)val1;
                IntValue i2 = (IntValue)val2;
                int n1 = i1.getValue();
                int n2 = i2.getValue();
                switch (op) {
                    case 1:
                        return new IntValue(n1 + n2);
                    case 2:
                        return new IntValue(n1 - n2);
                    case 3:
                        return new IntValue(n1 * n2);
                    case 4:
                        if (n2 == 0) {
                            throw new ExprException("Division by zero");
                        }
                        else {
                            return new IntValue(n1 / n2);
                        }
                    default:
                        throw new ExprException("Incorrect operation");
                }
            }
            else {
                throw new ExprException("Second operand is not an integer");
            }
        }
        else {
            throw new ExprException("First operand is not an integer");
        }

    }

    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnv) throws ExprException, ADTException {
        Type type1 = e1.typecheck(typeEnv);
        Type type2 = e2.typecheck(typeEnv);

        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new IntType();
            }
            else {
                throw new ExprException("The second operand is not an integer in " + this.toString());
            }
        }
        else {
            throw new ExprException("The first operand is not an integer in " + this.toString());
        }
    }

    @Override
    public String toString() {
        switch (op) {
            case 1:
                return e1.toString() + "+" + e2.toString();
            case 2:
                return e1.toString() + "-" + e2.toString();
            case 3:
                return e1.toString() + "*" + e2.toString();
            case 4:
                return e1.toString() + '/' + e2.toString();
            default:
                return "";
        }
    }
}
