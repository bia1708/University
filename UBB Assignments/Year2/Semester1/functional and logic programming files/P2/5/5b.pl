% heterogList(L1:list, L2:list, R:list)
% heterogList(i, i, o)

heterogList([], _, []).
heterogList([H|T], L, [H|R]) :- number(H),
    heterogList(T, L, R).
heterogList([[H|HT]|T], L, [R1|R]) :- 
    substituteElem([H|HT], H, L, R1),
    heterogList(T, L, R), !.


test_heterogList :-
    heterogList([1, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7],  [11, 11], [1, [11, 11, 1, 11, 11], 3, 6, [11, 11, 10, 1, 3, 9], 5, [11, 11, 11, 11, 11, 11], 7]),
    heterogList([], [7, 7], []).