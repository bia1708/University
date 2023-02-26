package Domain.Types;

import Domain.Values.IntValue;
import Domain.Values.Value;

public class IntType implements Type{
    @Override
    public Value defaultValue() {
        return new IntValue(0);
    }

    @Override
    public boolean equals(Type another) {
        return another instanceof IntType;
    }

    @Override
    public String toString(){
        return "int";
    }
}
