% insert(L:list, List:list, R:list)
% insert(i, i, o)

insert([], L, L).
insert([H|T], L, [H|R]) :- insert(T, L, R).

% substitute_elem(L:list, E:number, List:list, R:list)
% substitute_elem(i, i, i, o)

substitute_elem([], _, _, []).
substitute_elem([H|T], E, List, R) :- H =:= E, number(H), 
    insert(List, T, RI),
    substitute_elem(RI, E, List, R).
substitute_elem([H|T], E, List, [H|R]) :- H =\= E, number(H),
    substitute_elem(T, E, List, R).