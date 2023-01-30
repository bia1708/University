package Domain.ADT;

import Exceptions.ADTException;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

public class MyList<T> implements IMyList<T>{
    private List<T> list;

    // constructor
    public MyList() {
        this.list = new ArrayList<>();
    }

    @Override
    public void add(T obj) {
        this.list.add(obj);
    }

    @Override
    public void remove(T obj) throws ADTException {
        try {
            this.list.remove(obj);
        } catch (NoSuchElementException e){
            throw new ADTException("The element doesn't exist!" + e);
        }
    }

    @Override
    public int size() {
        return this.list.size();
    }

    @Override
    public T get(int index) throws ADTException {
        try {
            return this.list.get(index);
        } catch (NoSuchElementException e){
            throw new ADTException("The element doesn't exist!" + e);
        }
    }

    @Override
    public String toString(){
        StringBuilder content = new StringBuilder();
        for (T elem : this.list) {
            content.append(elem).append(" ");
        }
        return content.toString();
    }

    @Override
    public List<T> getList(){
        return this.list;
    }
}
