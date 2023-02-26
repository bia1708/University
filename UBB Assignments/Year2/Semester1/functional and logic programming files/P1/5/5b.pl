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


% elemPairs(L:list, E:value, R:list)
% elemPairs(i, o)

elemPairs([], _, []).
elemPairs([H|T], E, [[E|H]|R]) :-
    elemPairs(T, E, R).


% listPairs(L:list, R:list)
% listPairs(i, o)

listPairs([], []).
listPairs([H|T], [R1|R]) :-
    elemPairs(T, H, R1),
    listPairs(T, R).


% setPairs(L:list, R:list)
% setPairs(i, o)

setPairs(L, R) :-
    remrep(L, S),
    listPairs(S, R).  