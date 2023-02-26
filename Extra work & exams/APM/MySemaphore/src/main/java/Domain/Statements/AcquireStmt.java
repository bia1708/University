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

public class AcquireStmt implements IStatement{
    private final String var;
    private static final Lock lock = new ReentrantLock();

    public AcquireStmt(String var) {
        this.var = var;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ADTException, MyException {
        lock.lock();
        IMyDictionary<String, Value> symTable = state.getSymTable();
        ISemTable semaphoreTable = state.getSemTable();

        // look for the key var in sym tbl
        if (symTable.isDefined(var)) {
            if (symTable.lookup(var).getType().equals(new IntType())){
                IntValue fi = (IntValue) symTable.lookup(var);
                int foundIndex = fi.getValue();

                // look for key var in sem tbl
                if (semaphoreTable.getSemTable().containsKey(foundIndex)) {
                    Pair<Integer, List<Integer>> foundSemaphore = semaphoreTable.get(foundIndex);
                    int NL = foundSemaphore.getValue().size();
                    int N1 = foundSemaphore.getKey();
                    if (N1 > NL) {
                        // add the stateID to the sem's list
                        if (!foundSemaphore.getValue().contains(state.getStateID())) {
                            foundSemaphore.getValue().add(state.getStateID());
                            semaphoreTable.update(foundIndex, new Pair<>(N1, foundSemaphore.getValue()));
                        }
                    } else {
                        // push this stmt to the stack
                        state.getStack().push(this);
                    }
                } else {
                    throw new StmtException("Index not a key in the semaphore table!");
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
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnv) throws StmtException, ADTException {
        if (typeEnv.lookup(var).equals(new IntType())) {
            return typeEnv;
        } else {
            throw new StmtException(String.format("%s is not int!", var));
        }
    }


    @Override
    public String toString() {
        return String.format("acquire(%s)", var);
    }
}
