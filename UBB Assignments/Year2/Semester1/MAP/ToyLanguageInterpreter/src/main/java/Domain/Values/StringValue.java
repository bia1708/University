package Domain.Values;

import Domain.Types.StringType;
import Domain.Types.Type;

import java.util.Objects;

public class StringValue implements Value{
    private String val = "";

    public StringValue(String str) {
        this.val = str;
    }

    @Override
    public Type getType() {
        return new StringType();
    }

    public String getVal(){
        return this.val;
    }

    @Override
    public boolean equals(Object obj){
        if(!(obj instanceof StringValue))
            return false;
         StringValue other = (StringValue) obj;
         return Objects.equals(this.val, other.val);
    }

    @Override
    public String toString(){
        return this.val;
    }
}
