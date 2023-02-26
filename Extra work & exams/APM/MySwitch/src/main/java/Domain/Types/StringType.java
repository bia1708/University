package Domain.Types;

import Domain.Values.StringValue;
import Domain.Values.Value;

public class StringType implements Type{
    @Override
    public Value defaultValue() {
        return new StringValue("");
    }

    @Override
    public boolean equals(Type another) {
        return another instanceof StringType;
    }

    @Override
    public String toString(){
        return "string";
    }
}
