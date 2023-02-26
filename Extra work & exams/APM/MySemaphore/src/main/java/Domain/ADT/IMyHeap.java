package Domain.ADT;

import java.util.Map;
import java.util.Set;

public interface IMyHeap<V> {
    int allocate(V value);

    void deallocate(int address);

    void update(int address, V value);

    V get(int address);

    boolean contains(int address);

    Map<Integer, V> getContent();

    void setContent(Map<Integer, V> content);

    public Set<Map.Entry<Integer,V>> entrySet();

}
