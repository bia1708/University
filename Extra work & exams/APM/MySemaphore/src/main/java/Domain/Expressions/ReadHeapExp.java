package Domain.Expressions;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyHeap;
import Domain.Types.RefType;
import Domain.Types.Type;
import Domain.Values.RefValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;

public class ReadHeapExp implements Expression{
    private Expression exp;

    public ReadHeapExp(Expression exp) {
        this.exp = exp;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> symTable, IMyHeap<Value> heap) throws ExprException, ADTException {
        Value val = exp.eval(symTable, heap);
        if (val instanceof RefValue) {
            RefValue refVal = (RefValue) val;
            if (heap.contains(refVal.getAddress())) {
                return heap.get(refVal.getAddress());
            } else {
                throw new ExprException("The address doesn't exist in the heap");
            }

        } else {
            throw new ExprException("The expression could not be evaluated to a RefValue");
        }
    }

    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnv) throws ExprException, ADTException {
        Type type = exp.typecheck(typeEnv);
        if (type instanceof RefType) {
            RefType refType = (RefType)type;
            return refType.getInner();
        }
        else {
            throw new ExprException("The expression is not of a reference type in " + this.toString());
        }
    }

    @Override
    public String toString() {
        return "rH(" + exp + ")";
    }
}
