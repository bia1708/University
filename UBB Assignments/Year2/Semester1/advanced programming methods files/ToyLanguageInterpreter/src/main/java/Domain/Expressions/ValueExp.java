package Domain.Expressions;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyHeap;
import Domain.Types.Type;
import Domain.Values.Value;
import Exceptions.ExprException;

public class ValueExp implements Expression{
    Value e;

    public ValueExp(Value val) {
        this.e = val;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> tbl, IMyHeap<Value> heap) throws ExprException {
        return this.e;
    }

    @Override
    public String toString() {
        return this.e.toString();
    }

    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnv) throws ExprException {
        return this.e.getType();
    }
}
