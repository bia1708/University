package Domain.Expressions;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyHeap;
import Domain.Types.Type;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;

public interface Expression {
    public Value eval(IMyDictionary<String, Value> tbl, IMyHeap<Value> heap) throws ExprException, ADTException;

    Type typecheck(IMyDictionary<String,Type> typeEnv) throws ExprException, ADTException;
}
