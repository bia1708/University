% remMultiple(L:list, E:value, N:value, R:list)
% remMultiple(i, i, i, o)

remMultiple([], _, _, []).
remMultiple([H|T], E, N, R) :- H =:= E,
    N > 0,
    N1 is N - 1,
    remMultiple(T, E, N1, R).
remMultiple([H|T], E, N, [H|R]) :- H =\= E,
    remMultiple(T, E, N, R).  
remMultiple([H|T], E, N, [H|R]) :- H =:= E,
    N =:= 0,
    remMultiple(T, E, N, R).  


%rem3(L:list, E:value, R:list)
%rem3(i, i, o)

rem3(L, E, R) :-
    remMultiple(L, E, 3, R).