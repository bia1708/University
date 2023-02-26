% insertElemsOfList(L1:list, L2:list, R:list)
% insertElemsOfList(i, i, o)

insertElemsOfList([], L, L) :- !.
insertElemsOfList([H|T], L, [H|R]) :-
    insertElemsOfList(T, L, R).


% substituteElems(L1:list, E: value, L2:list, R:list)
% substituteElems(i, i, i, o)

substituteElem([], _, _, []) :- !.
substituteElem([H|T], E, L, R) :- H =:= E,
    substituteElem(T, E, L, R1),
    insertElemsOfList(L, R1, R).
substituteElem([H|T], E, L, [H|R]) :- H =\= E,
    substituteElem(T, E, L, R).


test_substituteElem :-
    substituteElem([1,2,1,3,1,4],1,[10,11],[10,11,2,10,11,3,10,11,4]),
    substituteElem([], 1, [], []),
    substituteElem([1, 2], 2, [2, 3], [1, 2, 3]).