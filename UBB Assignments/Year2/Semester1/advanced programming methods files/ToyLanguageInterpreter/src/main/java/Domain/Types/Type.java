package Domain.Types;

import Domain.Values.Value;

public interface Type {
    Value defaultValue();

    boolean equals(Type another);
}
