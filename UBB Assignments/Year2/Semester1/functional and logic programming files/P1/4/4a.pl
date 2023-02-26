% exists(L:list, E:value)
% exists(i, i)

exists([H|_], E) :- H =:= E.
exists([H|T], E) :- H =\= E, 
    exists(T, E).

% setdiff(L1:list, L2:list, R:list)
% setdiff(i, i, o)

setdiff(L, [], L) :- !.
setdiff([], [], []) :- !.
setdiff([], _, []) :- !.
setdiff([H|T], L2, [H|R]) :-
    \+ exists(L2, H),
    setdiff(T, L2, R).
setdiff([H|T], L2, R) :-
    exists(L2, H), 
    setdiff(T, L2, R).
  