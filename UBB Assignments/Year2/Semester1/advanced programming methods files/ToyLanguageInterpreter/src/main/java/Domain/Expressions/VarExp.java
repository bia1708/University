package Domain.Expressions;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyHeap;
import Domain.Types.Type;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;

public class VarExp implements Expression{
    String id;

    public VarExp(String s) {
        this.id = s;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> tbl, IMyHeap<Value> heap) throws ExprException, ADTException {
        return tbl.lookup(this.id);
    }

    @Override
    public String toString() {
        return this.id;
    }

    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnv) throws ExprException, ADTException {
        if(typeEnv.isDefined(this.id)){
            return typeEnv.lookup(this.id);
        }
        else{
            throw new ExprException("The variable " + this.toString() + " is not defined");
        }
    }
}
