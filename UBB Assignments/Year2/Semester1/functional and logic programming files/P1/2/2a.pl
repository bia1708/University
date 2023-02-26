% rem(L:list, V:value, R:list)
% rem(i, i, o)

rem([], _, []).
rem([H|T], V, [H|R]) :- H =\= V,
    rem(T, V, R).
rem([H|T], V, R) :- H =:= V,
    rem(T, V, R).
