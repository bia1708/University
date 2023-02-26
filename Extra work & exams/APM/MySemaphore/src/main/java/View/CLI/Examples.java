package View.CLI;

import Domain.Expressions.*;
import Domain.Statements.*;
import Domain.Types.BoolType;
import Domain.Types.IntType;
import Domain.Types.RefType;
import Domain.Types.StringType;
import Domain.Values.BoolValue;
import Domain.Values.IntValue;
import Domain.Values.StringValue;

public class Examples {
    public static IStatement[] getExamples() {
        return new IStatement[]{
                example1(), example2(), example3(), example4(), example5(), example6(), example7(), example8(), example9()
        };
    }

    private static IStatement example1() {
        return new CompStmt(
                new VarDeclStmt("x", new IntType()),
                new CompStmt(
                        new AssignStmt("x", new ValueExp(new IntValue(17))),
                        new PrintStmt(new VarExp("x"))
                ));
    }

    private static IStatement example2(){
        return new CompStmt(
                new VarDeclStmt("x" , new IntType()),
                new CompStmt(new AssignStmt("x", new ArithExp(
                        new ValueExp(new IntValue(3)),
                        new ArithExp(
                                new ValueExp(new IntValue(5)), new ValueExp(new IntValue(7)), '*'
                        ),
                        '+'
                )
                ),
                        new PrintStmt(new VarExp("x"))
                )
        );
    }

    private static IStatement example3(){
        return new CompStmt(
                new VarDeclStmt("s" , new BoolType()),
                new CompStmt(new VarDeclStmt("x", new IntType()),
                        new CompStmt(
                                new AssignStmt("s", new ValueExp(new BoolValue(true))),
                                new CompStmt(
                                        new IfStmt(
                                                new VarExp("s"),
                                                new AssignStmt("x", new ValueExp(new IntValue(20))),
                                                new AssignStmt("x", new ValueExp(new IntValue(2)))
                                        ),
                                        new PrintStmt(new VarExp("x"))
                                )
                        )
                )
        );
    }

    private static IStatement example4(){
        return new CompStmt(
                new VarDeclStmt("fileName", new StringType()),
                new CompStmt(new AssignStmt("fileName", new ValueExp(new StringValue("test.txt"))),
                        new CompStmt(new OpenRFileStmt(new VarExp("fileName")),
                                new CompStmt(new VarDeclStmt("x", new IntType()),
                                        new CompStmt(new ReadFileStmt(new VarExp("fileName"), "x"),
                                                new CompStmt(new PrintStmt(new VarExp("x")),
                                                        new CompStmt(new ReadFileStmt(new VarExp("fileName"), "x"),
                                                                new CompStmt(new PrintStmt(new VarExp("x")),
                                                                        new CloseRFileStmt(new VarExp("fileName"))))))))));

    }

    private static IStatement example5(){
        return new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewHeapStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewHeapStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp(new ReadHeapExp(new ReadHeapExp(new VarExp("a"))),
                                                        new ValueExp(new IntValue(5)),
                                                        '+')))))));
    }

    private static IStatement example6() {
        return new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewHeapStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewHeapStmt("a", new VarExp("v")),
                                        new CompStmt(new NewHeapStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a")))))))));
    }

    private static IStatement example7(){
        return new CompStmt(new VarDeclStmt("x", new IntType()),
                new CompStmt(new AssignStmt("x", new ValueExp(new IntValue(10))),
                        new CompStmt(new WhileStmt(new RelationalExp(new VarExp("x"), new ValueExp(new IntValue(0)), 5), new CompStmt(new PrintStmt(new VarExp("x")), new AssignStmt("x", new ArithExp(new VarExp("x"), new ValueExp(new IntValue(1)), '-')))),
                                new PrintStmt(new VarExp("x")))));
    }

    private static IStatement example8(){
        return new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewHeapStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new WriteHeapStmt("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))))))),
                                                new CompStmt(new PrintStmt(new VarExp("v")),
                                                        new PrintStmt(new ReadHeapExp(new VarExp("a")))))))));
    }

    private static IStatement example9() {
        return new CompStmt(new VarDeclStmt("v1", new RefType(new IntType())),
                new CompStmt(new VarDeclStmt("cnt", new IntType()),
                        new CompStmt(new NewHeapStmt("v1", new ValueExp(new IntValue(1))),
                                new CompStmt(new CreateSemStmt("cnt", new ReadHeapExp(new VarExp("v1"))),
                                        new CompStmt(
                                                new ForkStmt(new CompStmt(new AcquireStmt("cnt"),
                                                        new CompStmt(new WriteHeapStmt("v1", new ArithExp(
                                                                new ReadHeapExp(new VarExp("v1")),
                                                                new ValueExp(new IntValue(10)),
                                                                '*')),
                                                                new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v1"))),
                                                                        new ReleaseStmt("cnt"))))),
                                                new CompStmt(
                                                        new ForkStmt(new CompStmt(new AcquireStmt("cnt"),
                                                                new CompStmt(new WriteHeapStmt("v1", new ArithExp(
                                                                        new ReadHeapExp(new VarExp("v1")),
                                                                        new ValueExp(new IntValue(10)),
                                                                        '*')),
                                                                        new CompStmt(new WriteHeapStmt("v1", new ArithExp(
                                                                                new ReadHeapExp(new VarExp("v1")),
                                                                                new ValueExp(new IntValue(2)),
                                                                                '*')),
                                                                                new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v1"))),
                                                                                        new ReleaseStmt("cnt")))))),
                                                        new CompStmt(new AcquireStmt("cnt"),
                                                                new CompStmt(new PrintStmt(new ArithExp(
                                                                        new ReadHeapExp(new VarExp("v1")),
                                                                        new ValueExp(new IntValue(1)),
                                                                        '-')),
                                                                        new ReleaseStmt("cnt")))))))));
    }

}
