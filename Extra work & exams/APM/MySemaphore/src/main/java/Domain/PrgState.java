package Domain;

import Domain.ADT.*;
import Domain.Statements.IStatement;
import Domain.Values.StringValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.MyException;
import Exceptions.StmtException;

import java.io.BufferedReader;

public class PrgState {
    private IMyStack<IStatement> exeStack;
    private IMyDictionary<String, Value> symTable;
    private IMyHeap<Value> heap;
    private IMyList<Value> out;
    private IMyDictionary<StringValue, BufferedReader> fileTable;
    private ISemTable semTable;
    private final int stateID;
    private static int freeID = 0;

    // CONSTRUCTOR
    public PrgState(IMyStack<IStatement> exeStack, IMyDictionary<String, Value> symTable, IMyHeap<Value> heap, IMyList<Value> out, IMyDictionary<StringValue, BufferedReader> fileTable, ISemTable semTable, IStatement prg) {
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.heap = heap;
        this.out = out;
        this.fileTable = fileTable;
        this.semTable = semTable;
        this.exeStack.push(prg);
        stateID = getNewPrgStateID();
    }

    // CONSTRUCTOR FOR PRG FROM STATEMENT
    public PrgState(IStatement statement) {
        this.exeStack = new MyStack<>();
        this.symTable = new MyDictionary<>();
        this.heap = new MyHeap<>();
        this.out = new MyList<>();
        this.fileTable = new MyDictionary<>();
        this.semTable = new SemTable();
        this.exeStack.push(statement);
        stateID = getNewPrgStateID();
    }

    // GETTERS
    public IMyStack<IStatement> getStack() {
        return this.exeStack;
    }

    public IMyDictionary<String, Value> getSymTable() {
        return this.symTable;
    }

    public IMyHeap<Value> getHeap() {
        return this.heap;
    }

    public IMyDictionary<StringValue, BufferedReader> getFileTable() {
        return this.fileTable;
    }

    public static synchronized int getNewPrgStateID() {
        return ++freeID;
    }

    public int getStateID(){
        return stateID;
    }

    public IMyList<Value> getOutConsole() {
        return this.out;
    }

    public ISemTable getSemTable() {
        return this.semTable;
    }


    // SETTERS

    public void setExeStack(IMyStack<IStatement> stack) {
        this.exeStack = stack;
    }

    public void setSymTable(IMyDictionary<String, Value> table) {
        this.symTable = table;
    }

    public void setHeap(IMyHeap<Value> gHeap) {
        this.heap = gHeap;
    }

    public void setOutConsole(IMyList<Value> outConsole) {
        this.out = outConsole;
    }


    public boolean isNotCompleted() {
        return !exeStack.isEmpty();
    }

    public PrgState oneStep() throws MyException, ADTException, StmtException, ExprException {
        if (exeStack.isEmpty()) {
            throw new MyException("ERROR: Execution stack is empty when attempting to execute one step.");
        }
        IStatement currentStmt = exeStack.pop();
        return currentStmt.execute(this);
    }


    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("Program state\n");
        str.append("ID: ").append(stateID).append(" \n");
        str.append("Exe Stack: ").append(exeStack).append(" \n");
        str.append("Sym Table: ").append(symTable).append(" \n");
        str.append("Output Console: ").append(out).append(" \n");
        str.append("FileTable: ").append(fileTable).append(" \n");
        str.append("Heap: ").append(heap).append(" \n");
        str.append("SemTable: ").append(semTable).append(" \n");
        return str.toString();
    }
}
