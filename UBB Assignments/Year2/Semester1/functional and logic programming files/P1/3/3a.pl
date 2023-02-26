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
remrep([H|T], R) :-
    countoc([H|T], H, C), 
    C > 1,
    rem([H|T], H, RR),
    remrep(RR, R).