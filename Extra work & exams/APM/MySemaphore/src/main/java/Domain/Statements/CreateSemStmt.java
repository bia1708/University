package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyHeap;
import Domain.ADT.ISemTable;
import Domain.Expressions.Expression;
import Domain.PrgState;
import Domain.Types.IntType;
import Domain.Types.Type;
import Domain.Values.IntValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.MyException;
import Exceptions.StmtException;
import javafx.util.Pair;

import java.util.ArrayList;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CreateSemStmt implements IStatement{
    private final String var;
    private final Expression expression;
    private static final Lock lock = new ReentrantLock();

    public CreateSemStmt(String var, Expression expression) {
        this.var = var;
        this.expression = expression;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException, MyException {
        lock.lock();
        IMyDictionary<String, Value> symTable = state.getSymTable();
        IMyHeap<Value> heap = state.getHeap();
        ISemTable semaphoreTable = state.getSemTable();

        // eval the exp and check if the result is a number
        if(!(expression.eval(symTable, heap) instanceof IntValue))
            throw new ADTException("The result is not a number!");
        IntValue nr = (IntValue) (expression.eval(symTable, heap));
        int number = nr.getValue();

        //make new sem with number and empty list
        int freeAddress = semaphoreTable.getFreeAddress();
        semaphoreTable.put(freeAddress, new Pair<>(number, new ArrayList<>()));
        // if var already in symtbl update it
        if (symTable.isDefined(var) && symTable.lookup(var).getType().equals(new IntType()))
            symTable.update(var, new IntValue(freeAddress));
        else
            throw new MyException(String.format("Error for variable %s: not defined/does not have int type!", var));
        lock.unlock();
        return state;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        if (typeEnvironment.lookup(var).equals(new IntType())) {
            if (expression.typecheck(typeEnvironment).equals(new IntType()))
                return typeEnvironment;
            else
                throw new StmtException("Expression is not of int type!");
        } else {
            throw new StmtException(String.format("%s is not of type int!", var));
        }
    }

    @Override
    public String toString() {
        return String.format("createSemaphore(%s, %s)", var, expression);
    }
}
