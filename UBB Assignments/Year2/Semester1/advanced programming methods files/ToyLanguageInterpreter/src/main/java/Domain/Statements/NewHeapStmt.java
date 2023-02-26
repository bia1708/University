package Domain.Statements;

import Domain.ADT.IMyDictionary;
import Domain.ADT.IMyHeap;
import Domain.ADT.IMyStack;
import Domain.Expressions.Expression;
import Domain.PrgState;
import Domain.Types.RefType;
import Domain.Types.Type;
import Domain.Values.RefValue;
import Domain.Values.Value;
import Exceptions.ADTException;
import Exceptions.ExprException;
import Exceptions.StmtException;

public class NewHeapStmt implements IStatement{
    String varName;
    Expression exp;

    public NewHeapStmt(String varName, Expression exp) {
        this.varName = varName;
        this.exp = exp;
    }



    @Override
    public PrgState execute(PrgState state) throws StmtException, ExprException, ADTException {
        IMyStack<IStatement> stack = state.getStack();
        IMyDictionary<String, Value> symTbl = state.getSymTable();
        IMyHeap<Value> heap = state.getHeap();

        if(symTbl.isDefined(this.varName)){
            if(symTbl.lookup(this.varName).getType() instanceof RefType){
                Value val = this.exp.eval(symTbl, heap);
                Value tblVal = symTbl.lookup(this.varName);
                if(val.getType().equals(((RefType)(tblVal.getType())).getInner())){
                    int addr = heap.allocate(val);
                    symTbl.update(this.varName, new RefValue(val.getType(), addr));
                }
                else{
                    throw new StmtException("Value's type is not correct!");
                }
            }
            else{
                throw new StmtException("Value's type is not reference!");
            }
        }
        else{
            throw new StmtException("Value is not declared!");
        }
        state.setSymTable(symTbl);
        state.setHeap(heap);
        state.setExeStack(stack);
        return state;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws StmtException, ExprException, ADTException {
        if (!typeEnvironment.isDefined(this.varName)) {
            throw new StmtException("The variable " + this.varName + " not defined");
        }
        else {
            Type variableType = typeEnvironment.lookup(this.varName);
            Type expType = this.exp.typecheck(typeEnvironment);
            if (variableType.equals(new RefType(expType))) {
                return typeEnvironment;
            }
            else {
                throw new StmtException("The right side and left side in " + this.toString() + " have different types");
            }
        }
    }

    @Override
    public String toString(){
        return "new(" + this.varName + ", " + this.exp + ")";
    }

}
