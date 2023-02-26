package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.Expressions.Expression;
import Domain.PrgState;
import Domain.Types.StringType;
import Domain.Types.Type;
import Domain.Values.StringValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStmt implements IStatement {
    private Expression exp;


    public CloseRFileStmt(Expression exp) {
        this.exp = exp;
    }


    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyDictionary<String, Value> symTable = state.getSymTable();
        Value val = exp.eval(symTable, state.getHeap());
        if (val.getType().equals(new StringType())) {
            IMyDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
            StringValue stringVal = (StringValue) val;
            if (fileTable.isDefined(stringVal)) {
                BufferedReader bufferedReader = fileTable.lookup(stringVal);
                try {
                    bufferedReader.close();
                } catch (IOException e) {
                    throw new StmtException(e.getMessage());
                }
                fileTable.remove(stringVal);
            } else {
                throw new StmtException("The file doesn't exist in the File Table!");
            }
        }
        else {
            throw new StmtException("Expression could not be evaluated to a string in File Close!");
        }
        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        Type expType = this.exp.typecheck(typeEnvironment);
        if (expType.equals(new StringType())) {
            return typeEnvironment;
        }
        else {
            throw new StmtException("The close file expression " + this.toString() + " is not a string");
        }
    }

    @Override
    public String toString() {
        return "close(" + exp + ")";
    }
}
