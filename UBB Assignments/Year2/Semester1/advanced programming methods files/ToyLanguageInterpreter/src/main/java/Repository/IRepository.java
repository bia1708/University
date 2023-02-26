package Repository;

import Domain.PrgState;
import Exceptions.MyException;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    void addState(PrgState state);

    public List<PrgState> getPrgList();

    void setPrgList(List<PrgState> list);

    void logPrgState(PrgState prgState) throws MyException, IOException;
}
