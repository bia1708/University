package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyHeap;
import Domain.Expressions.Expression;
import Domain.PrgState;
import Domain.Types.RefType;
import Domain.Types.Type;
import Domain.Values.RefValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

public class WriteHeapStmt implements IStatement{
    private String variableName;
    private Expression exp;

    public WriteHeapStmt(String variableName, Expression exp) {
        this.variableName = variableName;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyDictionary<String, Value> symTable = state.getSymTable();
        IMyHeap<Value> heap = state.getHeap();

        if (symTable.isDefined(variableName)) {
            if (symTable.lookup(variableName).getType() instanceof RefType) {
                RefValue refVal = (RefValue) symTable.lookup(variableName);
                if (heap.contains(refVal.getAddress())) {
                    Value val = exp.eval(symTable, heap);
                    if (symTable.lookup(variableName).getType().equals(new RefType(val.getType()))) {
                        int address = refVal.getAddress();
                        heap.update(address, val);
                    }
                    else {
                        throw new StmtException("The pointing variable has a different type than the evaluated expression.");
                    }
                }
                else {
                    throw new StmtException("The address to which " + variableName + " points is not in the heap");
                }
            }
            else {
                throw new StmtException(variableName + " is not a reference variable");
            }
        }
        else {
            throw new StmtException(variableName + " is not defined");
        }

        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        if (typeEnvironment.isDefined(variableName)) {
            Type variableType = typeEnvironment.lookup(variableName);
            Type expType = exp.typecheck(typeEnvironment);
            if (!(variableType instanceof RefType)) {
                throw new StmtException("The file name in " + this.toString() + " is not a string");
            }
            if (!variableType.equals(new RefType(expType))) {
                throw new StmtException("The right side of " + this.toString() + " has other type than the referenced type of the left side");
            }
            return typeEnvironment;
        }
        else {
            throw new StmtException("The variable " + variableName + " is not defined");
        }
    }

    @Override
    public String toString() {
        return "wH(" + variableName + "," + exp + ")";
    }

}
