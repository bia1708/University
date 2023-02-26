package Domain.ADT;

import Exceptions.MyException;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;

public interface ISemTable {
    void put(int key, Pair<Integer, List<Integer>> value) throws MyException;
    Pair<Integer, List<Integer>> get(int key) throws MyException;
    boolean containsKey(int key);
    int getFreeAddress();
    void setFreeAddress(int freeAddress);
    void update(int key, Pair<Integer, List<Integer>> value) throws MyException;
    HashMap<Integer, Pair<Integer, List<Integer>>> getSemTable();
    void setSemTable(HashMap<Integer, Pair<Integer, List<Integer>>> newSemaphoreTable);

//    List toList();
}
