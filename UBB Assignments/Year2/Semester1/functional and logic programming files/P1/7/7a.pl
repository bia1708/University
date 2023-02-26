% exists(L:list, E:value)
% exists(i, i)

exists([H|_], E) :- H =:= E.
exists([H|T], E) :- H =\= E, 
    exists(T, E).


% intersection(L1:list, L2:list, R:list)
% intersection(i, i, o)

intersection([], [], []) :- !.
intersection(_, [], []) :- !.
intersection([], _, []) :- !.
intersection([H|T], L, [H|R]) :-
    exists(L, H),
    intersection(T, L, R).
intersection([H|T], L, R) :-
    \+ exists(L, H),
    intersection(T, L, R).

