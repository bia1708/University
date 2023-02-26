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
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.Reader;

public class OpenRFileStmt implements IStatement {
    private Expression exp;

    public OpenRFileStmt(Expression exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyDictionary<String, Value> symTable = state.getSymTable();
        Value val = this.exp.eval(symTable, state.getHeap());

        if (val.getType().equals(new StringType())) {
            IMyDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
            StringValue stringVal = (StringValue) val;
            if (!fileTable.isDefined(stringVal)) {
                try {
                    Reader reader = new FileReader(stringVal.getVal());
                    BufferedReader bufferedReader = new BufferedReader(reader);
                    fileTable.add(stringVal, bufferedReader);
                }
                catch (FileNotFoundException e) {
                    throw new StmtException(e.getMessage());
                }
            }
            else {
                throw new StmtException("The file is already in use!");
            }
        }
        else {
            throw new StmtException("Expression couldn't be evaluated to a string value in File Open!");
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
        return "Open(" + exp + ")";
    }
}
