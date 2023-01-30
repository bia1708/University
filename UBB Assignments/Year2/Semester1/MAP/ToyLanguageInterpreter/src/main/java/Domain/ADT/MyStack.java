package Domain.ADT;

import Exceptions.ADTException;

import java.util.List;
import java.util.Stack;

public class MyStack<T> implements IMyStack<T>{
    private Stack<T> stack;

    public MyStack() {
        this.stack = new Stack<T>();
    }

    @Override
    public void push(T obj) {
        this.stack.push(obj);
    }

    @Override
    public T pop() throws ADTException {
        if(this.stack.isEmpty())
            throw new ADTException("The stack is empty!");
        return this.stack.pop();
    }

    @Override
    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    @Override
    public String toString(){
        StringBuilder str = new StringBuilder();
        for(T elem : this.stack)
            str.append(elem.toString()).append(" ");
        return str.toString();
    }

    @Override
    public T peek(){
        return this.stack.peek();
    }

    @Override
    public List<T> toList(){
        return this.stack.stream().toList().stream().toList();
    }
}
