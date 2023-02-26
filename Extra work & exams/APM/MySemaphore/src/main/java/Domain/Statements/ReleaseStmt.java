package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.ADT.ISemTable;
import Domain.PrgState;
import Domain.Types.IntType;
import Domain.Types.Type;
import Domain.Values.IntValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.MyException;
import Exceptions.StmtException;
import javafx.util.Pair;

import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ReleaseStmt implements IStatement{
    private final String var;
    private static final Lock lock = new ReentrantLock();

    public ReleaseStmt(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, MyException, ADTException {
        lock.lock();
        IMyDictionary<String, Value> symTable = state.getSymTable();
        ISemTable semaphoreTable = state.getSemTable();

        // same as b4
        if (symTable.isDefined(var)) {
            if (symTable.lookup(var).getType().equals(new IntType())) {
                IntValue fi = (IntValue) symTable.lookup(var);
                int foundIndex = fi.getValue();
                if (semaphoreTable.getSemTable().containsKey(foundIndex)) {
                    Pair<Integer, List<Integer>> foundSemaphore = semaphoreTable.get(foundIndex);
                    // remove the stateID from the semTbl
                    if (foundSemaphore.getValue().contains(state.getStateID()))
                        foundSemaphore.getValue().remove((Integer) state.getStateID());
                    semaphoreTable.update(foundIndex, new Pair<>(foundSemaphore.getKey(), foundSemaphore.getValue()));
                } else {
                    throw new StmtException("Index not in the semaphore table!");
                }
            } else {
                throw new StmtException("Index must be of int type!");
            }
        } else {
            throw new StmtException("Index not in symbol table!");
        }
        lock.unlock();
        return state;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnv) throws ADTException, StmtException {
        if (typeEnv.lookup(var).equals(new IntType())) {
            return typeEnv;
        } else {
            throw new StmtException(String.format("%s is not int!", var));
        }
    }


    @Override
    public String toString() {
        return String.format("release(%s)", var);
    }
}


