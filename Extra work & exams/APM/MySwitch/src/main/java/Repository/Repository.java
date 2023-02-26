package Repository;

import Domain.PrgState;
import Exceptions.MyException;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class Repository implements IRepository{
    private List<PrgState> states;
    private String fileName;

    // CONSTRUCTOR (load repo to given file)
    public Repository(String fileName) {
        this.states = new LinkedList<>();
        this.fileName = fileName;
    }

    @Override
    public void addState(PrgState state) {
        this.states.add(state);
    }

    @Override
    public List<PrgState> getPrgList() {
        return this.states;
    }

    @Override
    public void setPrgList(List<PrgState> list) {
        this.states = list;
    }

    // each repo is logged into a different file
    @Override
    public void logPrgState(PrgState prgState) throws MyException, IOException {
        File logFile = new File(this.fileName);
        logFile.createNewFile();
        try (FileWriter fileWriter = new FileWriter(logFile, true)) {
            fileWriter.write(prgState + "\n");
            fileWriter.close();
        }
        catch (IOException e) {
            throw new MyException(e.getMessage());
        }
//        PrintWriter logFile;
//        logFile = new PrintWriter(new BufferedWriter(new FileWriter(this.fileName, true)));
//        logFile.println(prgState.toString());
//        logFile.close();
    }
}
