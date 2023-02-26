% heterList(L:list, R:list)
% flow model: heterList(i, o)

heterList([], _, []).

heterList([[H|HT]|T], E, [HR|R]) :- 
    substitute_elem([H|HT], H, E, HR),
    heterList(T, E, R).

heterList([H|T], E, [HR|R]) :- number(H),
    substitute_elem([H|T], H, E, HR),
    heterList(T, E, R).