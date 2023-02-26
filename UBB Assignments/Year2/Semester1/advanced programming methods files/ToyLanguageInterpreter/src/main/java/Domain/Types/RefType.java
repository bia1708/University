package Domain.Types;

import Domain.Values.RefValue;
import Domain.Values.Value;

public class RefType implements Type{
    // pointer type
    private Type inner;

    // constructor
    public RefType(Type inner) {
        this.inner = inner;
    }

    public Type getInner() {
        return this.inner;
    }

    @Override
    public Value defaultValue() {
        return new RefValue(inner, 0);
    }

    @Override
    public boolean equals(Type other){
        if (other instanceof RefType)
            return inner.equals(((RefType)other).getInner());
        else
            return false;
    }

    @Override
    public String toString(){
        return "Ref(" + this.inner + ")";
    }
}
