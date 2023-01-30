package Domain.ADT;

import Exceptions.ADTException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public interface IMyDictionary<K, V>{
    void add(K key, V value) throws ADTException;

    void remove(K key) throws ADTException;

    void update(K key, V value) throws ADTException;

    V lookup(K key) throws ADTException;

    boolean isDefined(K key);

    void setContent(HashMap<K, V> content);

    HashMap<K, V> getContent();

    Set<Map.Entry<K,V>> entrySet();
}
