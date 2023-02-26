package Domain.ADT;

import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class MyHeap<V> implements IMyHeap<V> {
    private Map<Integer, V> map;
    private AtomicInteger freeLocation;

    public MyHeap() {
        this.map = new ConcurrentHashMap<Integer, V>();
        this.freeLocation = new AtomicInteger(0);
    }

    @Override
    public int allocate(V value) {
        int newLocation = this.freeLocation.incrementAndGet();
        this.map.put(newLocation, value);
        return newLocation;
    }

    @Override
    public void deallocate(int address) {
        this.map.remove(address);
    }

    @Override
    public void update(int address, V value) {
        this.map.put(address, value);
    }

    @Override
    public V get(int address) {
        return this.map.get(address);
    }

    @Override
    public boolean contains(int address) {
        return this.map.containsKey(address);
    }

    @Override
    public Map<Integer, V> getContent() {
        return this.map;
    }

    @Override
    public void setContent(Map<Integer, V> content) {
        this.map = content;
    }

    @Override
    public String toString() {
        StringBuilder content = new StringBuilder();

        for (Map.Entry<Integer, V> el : map.entrySet()) {
            content.append(el.getKey()).append("-").append(el.getValue()).append(" ");
        }
        return content.toString();
    }

    public Set<Map.Entry<Integer,V>> entrySet(){
        return this.map.entrySet();
    }
}
