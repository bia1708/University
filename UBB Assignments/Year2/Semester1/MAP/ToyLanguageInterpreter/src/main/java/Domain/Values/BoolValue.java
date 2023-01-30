package Domain.Values;

import Domain.Types.BoolType;
import Domain.Types.Type;

public class BoolValue implements Value{
    private boolean val = false;

    // Constructor
    public BoolValue(boolean val) {
        this.val = val;
    }

    @Override
    public Type getType() {
        return new BoolType();
    }

    public boolean getVal(){
        return this.val;
    }

    @Override
    public boolean equals(Object obj){
        if(!(obj instanceof BoolValue))
            return false;
        BoolValue other = (BoolValue) obj;
        return other.val == this.val;
    }

    @Override
    public String toString(){
        return Boolean.toString(this.val);
    }
}
