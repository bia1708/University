package Domain.Values;

import Domain.Types.IntType;
import Domain.Types.Type;

public class IntValue implements Value{
    private int val = 0;

    public IntValue(int val) {
        this.val = val;
    }

    @Override
    public Type getType() {
        return new IntType();
    }

    public int getValue(){
        return this.val;
    }

    @Override
    public boolean equals(Object obj){
        if(!(obj instanceof IntValue))
            return false;
        // we need to cast obj to IntValue type
        IntValue other = (IntValue) obj;
        return this.val == other.val;
    }

    @Override
    public String toString(){
        return Integer.toString(this.val);
    }
}
