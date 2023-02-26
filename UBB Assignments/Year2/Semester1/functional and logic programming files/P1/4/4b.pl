% insertEven(L:list, R:result)
% insertEven(i, o)

insertEven([], []).
insertEven([H|T], [H, 1|R]) :- H mod 2 =:= 0,
    insertEven(T, R).
insertEven([H|T], [H|R]) :- H mod 2 =\= 0,
    insertEven(T, R).