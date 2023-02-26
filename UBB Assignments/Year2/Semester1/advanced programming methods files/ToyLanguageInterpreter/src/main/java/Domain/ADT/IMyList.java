package Domain.ADT;

import Exceptions.ADTException;

import java.util.List;

public interface IMyList<T> {
    void add(T obj);

    void remove(T obj) throws ADTException;

    int size();

    T get(int index) throws ADTException;

    List<T> getList();
}
