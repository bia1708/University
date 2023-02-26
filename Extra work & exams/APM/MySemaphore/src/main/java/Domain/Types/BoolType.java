package Domain.Types;

import Domain.Values.BoolValue;
import Domain.Values.Value;

public class BoolType implements Type{
    @Override
    public Value defaultValue() {
        return new BoolValue(false);
    }

    @Override
    public boolean equals(Type another) {
        return another instanceof BoolType;
    }

    @Override
    public String toString(){
        return "bool";
    }
}
