% maxnumber(A:value, B:value, R:value)
% maxnumber(i, i, o)

maxnumber(A, B, A) :- A >= B.
maxnumber(A, B, B) :- A < B.


% findmax(L:list, R:value)
% findmax(i, i, o)

findmax([H], H).
findmax([H|T], M) :-
    findmax(T, RM), 
    maxnumber(H, RM, M).

% rem(L:list, V:value, R:list)
% rem(i, i, o)

rem([], _, []).
rem([H|T], V, [H|R]) :- H =\= V,
    rem(T, V, R).
rem([H|T], V, R) :- H =:= V,
    rem(T, V, R).

% remMax(L:list, R:list)
% remMax(i, o)

remMax([], []).
remMax(L, R) :-
    findmax(L, M),
    rem(L, M, R).
