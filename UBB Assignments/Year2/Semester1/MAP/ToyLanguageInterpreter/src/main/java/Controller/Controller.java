package Controller;

import Domain.ADT.IMyDictionary;
import Domain.ADT.MyDictionary;
import Domain.PrgState;
import Domain.Statements.IStatement;
import Domain.Types.Type;
import Domain.Values.RefValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.MyException;
import Exceptions.StmtException;
import Repository.IRepository;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;


public class Controller {
    private final IRepository repository;
    private ExecutorService executor = Executors.newFixedThreadPool(2);


    // CONSTRUCTOR
    public Controller(IRepository repository) {
        this.repository = repository;
    }


    // GETTERS
    public ExecutorService getExecutor() {
        return this.executor;
    }

    public List<PrgState> getProgramStates() {
        return this.repository.getPrgList();
    }


    // SETTERS
    public void setExecutor(ExecutorService executor) {
        this.executor = executor;
    }

    public void setProgram(IStatement prg) throws ExprException, StmtException, ADTException {
        this.repository.setPrgList(new ArrayList<>());
        this.repository.addState(new PrgState(prg));
//        runTypeChecker();
    }


    // ADD A PROGRAM TO THE REPOSITORY
    public void addProgram(PrgState newPrg) {
        this.repository.addState(newPrg);
    }


    // REMOVE PROGRAMS THAT FINISHED EXECUTING
    List<PrgState> removeCompletedPrograms(List<PrgState> programStateList) {
        // we keep only those programs that haven't finished executing and return this list
        List<PrgState> toReturn = programStateList.stream()
                .filter(PrgState::isNotCompleted)
                .collect(Collectors.toList());
        return toReturn;
    }


    // GET ADDRESSES FROM THE SYMBOL TABLE FOR THE GARBAGE COLLECTOR
    Set<Integer> getAddrFromSymTable(List<Collection<Value>> symTableValues, Map<Integer, Value> heap){
        Set<Integer> toReturn = new TreeSet<>();
        symTableValues.forEach(symTable -> symTable.stream()
                .filter(v -> v instanceof RefValue)
                .forEach(v -> {
                    while (v instanceof RefValue) {
                        toReturn.add(((RefValue)v).getAddress());
                        v = heap.get(((RefValue)v).getAddress());
                    }
                }));

        return toReturn;
    }

    // GARBAGE COLLECTOR
    Map<Integer, Value> garbageCollector(Set<Integer> symTableAddr, Map<Integer, Value> heap){
        return heap.entrySet().stream()
                .filter(e -> symTableAddr.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }



//     TYPECHECKER FOR EACH PRGSTATE
    public void runTypeChecker() throws ExprException, StmtException, ADTException {
        for (PrgState state: repository.getPrgList()) {
            IMyDictionary<String, Type> typeTable = new MyDictionary<>();
            state.getStack().peek().typecheck(typeTable);
        }
    }


    private void oneStepForEachProgram() {
        // get the prg state list
        List<PrgState> programStates = this.repository.getPrgList();

        // log each of the states in the file
        programStates.forEach(prg -> {
            try {
                repository.logPrgState(prg);
            } catch (IOException | MyException e) {
                System.out.println(e.getMessage());
                System.exit(1);
            }
        });

        // create list of executables - map each prgState to a callable obj (executeOneStep)
        List<Callable<PrgState>> callables = programStates.stream()
                .map(prg -> (Callable<PrgState>) prg::oneStep)
                .toList();

        // execute each task and map the program states to the result of each thread (the executed program)
        List<PrgState> newProgramStates;
        try {
            newProgramStates = this.executor.invokeAll(callables).stream()
                    .map(programStateFuture -> {
                        try {
                            return programStateFuture.get();
                        } catch (InterruptedException | ExecutionException e) {
                            System.out.println(e.getMessage());
                        }
                        return null;
                    }).filter(Objects::nonNull).toList();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        programStates.addAll(newProgramStates);
        // eliminate duplicates
        programStates = programStates.stream().distinct().toList();

        programStates.forEach(prg -> {
            try {
                repository.logPrgState(prg);
            } catch (MyException | IOException e) {
                System.out.println(e.toString());
            }
        });
        repository.setPrgList(programStates);
    }


    public void oneStepAll() throws ExprException, StmtException, ADTException {
        List<PrgState> programList = removeCompletedPrograms(repository.getPrgList());
        PrgState state = programList.get(0);

        state.getHeap().setContent(
                garbageCollector(
                        getAddrFromSymTable(
                                programList.stream().map(programState -> programState.getSymTable().getContent().values()).collect(Collectors.toList()),
                                state.getHeap().getContent()
                        ),
                        state.getHeap().getContent()
                )
        );
        oneStepForEachProgram();
        programList = removeCompletedPrograms(repository.getPrgList());
        repository.setPrgList(programList);
    }


    public void allSteps() throws ExprException, StmtException, ADTException {
        this.repository.setPrgList(removeCompletedPrograms(this.repository.getPrgList()));
        while (!repository.getPrgList().isEmpty()) {
            oneStepAll();
            this.repository.setPrgList(removeCompletedPrograms(repository.getPrgList()));
        }
        this.executor.shutdownNow();
    }
}
