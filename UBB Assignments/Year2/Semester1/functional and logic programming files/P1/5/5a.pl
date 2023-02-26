% union(L1:list, L2:list, R:list)
% union(i, i, o)

union([], [], []) :- !.
union([], L, L) :- !.
union([H|T], L, [H|R]) :-
    union(T, L, R).

% countoc(L:list, V:value, R:value)
% countoc(i, i, o)

countoc([], _, 0).
countoc([H|T], V, R) :- H =\= V,
    countoc(T, V, R).
countoc([H|T], V, R) :- H =:= V,
    countoc(T, V, R1),
    R is R1 + 1.


% rem(L:list, V:value, R:list)
% rem(i, i, o)

rem([], _, []).
rem([H|T], V, [H|R]) :- H =\= V,
    rem(T, V, R).
rem([H|T], V, R) :- H =:= V,
    rem(T, V, R).


% remrep(L:list, R:list)
% remrep(i, o)

remrep([], []).
remrep([H|T], [H|R]) :-
    countoc([H|T], H, C), 
    C =:= 1,
    remrep(T, R).
remrep([H|T], [H|R]) :-
    countoc([H|T], H, C), 
    C > 1,
    rem([H|T], H, RR),
    remrep(RR, R).

% setUnion(L1:list, L2:list, R:list)
% setUnion(i, i, o)

setUnion(L1, L2, FR) :-
    union(L1, L2, R),
    remrep(R, FR).




    