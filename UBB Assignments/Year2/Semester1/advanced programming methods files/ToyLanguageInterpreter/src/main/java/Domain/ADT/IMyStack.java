package Domain.ADT;

import Exceptions.ADTException;

import java.util.List;

public interface IMyStack<T> {
    void push(T obj);

    T pop() throws ADTException;

    boolean isEmpty();

    T peek();

    List<T> toList();
}
