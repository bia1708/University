% addv(L-list, V-value, P-position, Le-length, R-list) 
% addv(i, i, o)

addv([], _, _, _, []).
addv([H|T], V, P, L, [H|R]) :- P =\= L,
    L1 is L + 1,
    addv(T, V, P, L1, R).
addv([H|T], V, P, L, [H, V|R]) :- P =:= L,
    L1 is L + 1, 
    P1 is P * 2,
    addv(T, V, P1, L1, R).

insert(L, V, R) :- addv(L, V, 1, 1, R).