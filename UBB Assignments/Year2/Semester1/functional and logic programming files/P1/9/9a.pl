% insertOnPos(L:list, E:value, P: value, C:value, R:list)
% insertOnPos(i, i, i, i, o)

insertOnPos([], _, _, _, []).
insertOnPos([H|T], E, P, C, [E, H|R]) :- P =:= C,
    C1 is C + 1,
    insertOnPos(T, E, P, C1, R).
insertOnPos([H|T], E, P, C, [H|R]) :- P =\= C,
    C1 is C + 1,
    insertOnPos(T, E, P, C1, R).
    

% insertElemOnPos(L:list, E:value, P:value, R:list)
% insertElemOnPos(i, i, i, o)

insertElemOnPos(L, E, P, R) :-
    insertOnPos(L, E, P, 0, R).