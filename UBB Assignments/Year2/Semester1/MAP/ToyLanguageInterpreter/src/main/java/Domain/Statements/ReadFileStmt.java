package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.Expressions.Expression;
import Domain.PrgState;
import Domain.Types.IntType;
import Domain.Types.StringType;
import Domain.Types.Type;
import Domain.Values.IntValue;
import Domain.Values.StringValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStmt implements IStatement {
    private Expression exp;
    private String varName;
    private String fileName;

    public ReadFileStmt(Expression exp, String varName) {
        this.exp = exp;
        this.varName = varName;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyDictionary<String, Value> symTable = state.getSymTable();
        IMyDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();

        if (symTable.isDefined(this.varName)) {
            if (symTable.lookup(this.varName).getType().equals(new IntType())) {
                Value val = this.exp.eval(symTable, state.getHeap());
                if (val.getType().equals(new StringType())) {
                    StringValue stringVal = (StringValue) val;
                    if (fileTable.isDefined(stringVal)) {
                        BufferedReader bufferedReader = fileTable.lookup(stringVal);
                        try {
                            String line = bufferedReader.readLine();
                            Value intVal;
                            IntType type = new IntType();
                            if (line == null) {
                                intVal = type.defaultValue();
                            } else {
                                intVal = new IntValue(Integer.parseInt(line));
                            }
                            symTable.update(this.varName, intVal);
                        } catch (IOException e) {
                            throw new StmtException(e.getMessage());
                        }
                    }
                    else {
                        throw new StmtException("The file " + stringVal.getVal() + " is not in the File Table!");
                    }
                }
                else {
                    throw new StmtException("The value couldn't be evaluated to a string value!");
                }
            }
            else {
                throw new StmtException(this.varName + " is not of type int!");
            }
        }
        else {
            throw new StmtException(this.varName + " is not defined in Sym Table");
        }

        return null;
    }


    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        if (typeEnvironment.isDefined(this.varName)) {
            Type variableType = typeEnvironment.lookup(this.varName);
            Type expType = this.exp.typecheck(typeEnvironment);
            if (!variableType.equals(new IntType())) {
                throw new StmtException("The variable in " + this.toString() + " is not an integer");
            }
            if (!expType.equals(new StringType())) {
                throw new StmtException("The file name in " + this.toString() + " is not a string");
            }
            return typeEnvironment;
        }
        else {
            throw new StmtException("The variable " + this.varName + " is not defined");
        }
    }

    @Override
    public String toString() {
        return "Read From " + this.exp + " into " + this.varName;
    }
}
