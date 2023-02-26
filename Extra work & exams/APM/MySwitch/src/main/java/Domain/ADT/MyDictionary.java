package Domain.ADT;

import Exceptions.ADTException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyDictionary<K, V> implements IMyDictionary<K, V> {
    private HashMap<K, V> map;

    public MyDictionary() {
        this.map = new HashMap<>();
    }

    @Override
    public void add(K key, V value) throws ADTException {
        if(this.map.containsKey(key))
            throw new ADTException("Element already exists!");
        this.map.put(key, value);
    }

    @Override
    public void remove(K key) throws ADTException {
        if(!this.map.containsKey(key))
            throw new ADTException("Element doesn't exist!");
        this.map.remove(key);
    }

    @Override
    public void update(K key, V value) throws ADTException {
        if(!this.map.containsKey(key))
            throw new ADTException("Element doesn't exist!");
        this.map.replace(key, value);
    }

    @Override
    public V lookup(K key) throws ADTException {
        if(!this.map.containsKey(key))
            throw new ADTException("Element doesn't exist!");
        return this.map.get(key);
    }

    @Override
    public boolean isDefined(K key) {
        return this.map.containsKey(key);
    }

    @Override
    public void setContent(HashMap<K, V> content) {
        this.map = content;
    }

    @Override
    public HashMap<K, V> getContent() {
        return this.map;
    }

    @Override
    public String toString() {
        StringBuilder content = new StringBuilder();
        for (Map.Entry<K, V> el : map.entrySet()) {
            content.append(el.getKey()).append("-").append(el.getValue()).append(" ");
        }
        return content.toString();
    }

    @Override
    public Set<Map.Entry<K,V>> entrySet(){
        return this.map.entrySet();
    }
}
