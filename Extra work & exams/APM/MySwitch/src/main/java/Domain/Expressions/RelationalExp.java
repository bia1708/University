package Domain.Expressions;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyHeap;
import Domain.Types.BoolType;
import Domain.Types.IntType;
import Domain.Types.Type;
import Domain.Values.BoolValue;
import Domain.Values.IntValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;

public class RelationalExp implements Expression {
    private Expression exp1;
    private Expression exp2;
    private int op; // 1 <, 2 <=, 3 ==, 4 !=, 5 >, 6 >=

    public RelationalExp(Expression exp1, Expression exp2, int op) {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.op = op;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> symTable, IMyHeap<Value> heap) throws ExprException, ADTException {
        Value val1, val2;
        val1 = exp1.eval(symTable, heap);
        val2 = exp2.eval(symTable, heap);
        if (val1.getType().equals(new IntType()) && val2.getType().equals(new IntType())) {
            IntValue intVal1, intVal2;
            intVal1 = (IntValue) val1;
            intVal2 = (IntValue) val2;
            int x = intVal1.getValue();
            int y = intVal2.getValue();
            switch (op) {
                case 1:
                    return new BoolValue(x < y);
                case 2:
                    return new BoolValue(x <= y);
                case 3:
                    return new BoolValue(x == y);
                case 4:
                    return new BoolValue(x != y);
                case 5:
                    return new BoolValue(x > y);
                case 6:
                    return new BoolValue(x >= y);
            }
        }
        else {
            throw new ExprException("At least one operand is not an integer");
        }

        return new BoolValue(false);
    }


    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnv) throws ExprException, ADTException {
        Type type1 = exp1.typecheck(typeEnv);
        Type type2 = exp2.typecheck(typeEnv);

        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new BoolType();
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
        String s = "";
        switch (op) {
            case 1:
                s = "<";
                break;
            case 2:
                s = "<=";
                break;
            case 3:
                s = "==";
                break;
            case 4:
                s = "!=";
                break;
            case 5:
                s = ">";
                break;
            default:
                s = ">=";
        }
        return exp1 + s + exp2;
    }
}
