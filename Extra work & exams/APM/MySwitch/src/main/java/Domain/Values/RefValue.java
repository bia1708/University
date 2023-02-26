package Domain.Values;

import Domain.Types.RefType;
import Domain.Types.Type;

public class RefValue implements Value{
    private Type locationType;
    private int address;

    public RefValue(Type locationType, int address) {
        this.locationType = locationType;
        this.address = address;
    }

    @Override
    public Type getType() {
        return new RefType(this.locationType);
    }

    public Type getLocationType() {
        return this.locationType;
    }

    public int getAddress() {
        return this.address;
    }


    @Override
    public String toString(){
        return "(" + this.address + ", " + this.locationType + ")";
    }
}
