% insertElemsOfList(L1:list, L2:list, R:list)
% insertElemsOfList(i, i, o)

insertElemsOfList([], L, L) :- !.
insertElemsOfList([H|T], L, [H|R]) :-
    insertElemsOfList(T, L, R).


% substituteElems(L1:list, E: value, L2:list, R:list)
% substituteElems(i, i, i, o)

substituteElem([], _, _, []) :- !.
substituteElem([H|T], E, L, R) :- H =:= E,
    insertElemsOfList(L, T, RI),
    substituteElem(RI, E, L, R).
substituteElem([H|T], E, L, [H|R]) :- H =\= E,
    substituteElem(T, E, L, R).