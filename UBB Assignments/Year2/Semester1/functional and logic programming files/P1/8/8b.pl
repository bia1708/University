% min(A:value, B:value, R:value)
% min(i, i, o)

min(A, B, A) :- A =< B.
min(A, B, B) :- B < A.


% minOfList(L:list, R:value)
% minOfList(i, o)

minOfList([], 100000000).
minOfList([H|T], R) :-
    minOfList(T, R1),
    min(H, R1, R).


% deleteFirstOc(L:list, E:value, R:list)
% deleteFirstOc(i, i, o)

deleteFirstOc([], _, []).
deleteFirstOc([H|T], E, [H|R]) :- H =\= E,
    deleteFirstOc(T, E, R).
deleteFirstOc([H|T], E, R) :- H =:= E,
    deleteFirstOc(T, -1, R).


% deleteFirstMin(L:list, R:list)
% deleteFirstMin(i, o)

deleteFirstMin(L, R) :-
    minOfList(L, M),
    deleteFirstOc(L, M, R).