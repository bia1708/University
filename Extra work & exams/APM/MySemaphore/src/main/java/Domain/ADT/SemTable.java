package Domain.ADT;

import Exceptions.MyException;
import javafx.util.Pair;

import java.util.HashMap;
import java.util.List;

public class SemTable implements ISemTable{
    private HashMap<Integer, Pair<Integer, List<Integer>>> semTable;
    private int freeLocation;

    // CONSTRUCTOR
    public SemTable() {
        this.semTable = new HashMap<>();
    }

    // GETTER
    public HashMap<Integer, Pair<Integer, List<Integer>>> getSemTable() {
        synchronized (this) {
            return semTable;
        }
    }

    // SETTER
    public void setSemTable(HashMap<Integer, Pair<Integer, List<Integer>>> newSemaphoreTable) {
        synchronized (this) {
            this.semTable = newSemaphoreTable;
        }
    }

    // add an elem
    @Override
    public void put(int key, Pair<Integer, List<Integer>> value) throws MyException {
        synchronized (this) {
            if (!semTable.containsKey(key)) {
                semTable.put(key, value);
            } else {
                throw new MyException(String.format("Semaphore table already contains the key %d!", key));
            }
        }
    }

    // get elem by key
    @Override
    public Pair<Integer, List<Integer>> get(int key) throws MyException {
        synchronized (this) {
            if (semTable.containsKey(key)) {
                return semTable.get(key);
            } else {
                throw new MyException(String.format("Semaphore table doesn't contain the key %d!", key));
            }
        }
    }


    // check if key in tbl
    @Override
    public boolean containsKey(int key) {
        synchronized (this) {
            return semTable.containsKey(key);
        }
    }

    // get usable addr
    @Override
    public int getFreeAddress() {
        synchronized (this) {
            freeLocation++;
            return freeLocation;
        }
    }

    // set an address
    @Override
    public void setFreeAddress(int freeAddress) {
        synchronized (this) {
            this.freeLocation = freeAddress;
        }
    }

    // update elem inside tbl
    @Override
    public void update(int key, Pair<Integer, List<Integer>> value) throws MyException {
        synchronized (this) {
            if (semTable.containsKey(key)) {
                semTable.replace(key, value);
            } else {
                throw new MyException(String.format("Semaphore table doesn't contain key %d!", key));
            }
        }
    }

    @Override
    public String toString() {
        return semTable.toString();
    }
}

