% insertElemsOfList(L1:list, L2:list, R:list)
% insertElemsOfList(i, i, o)

insertElemsOfList([], L, L) :- !.
insertElemsOfList([H|T], L, [H|R]) :-
    insertElemsOfList(T, L, R).


% substituteElem2(L1:list, E: value, L2:list, R:list)
% substituteElem2(i, i, i, o)

substituteElem2([], _, _, []) :- !.
substituteElem2([[H|HT]|T], E, L, [[H|HT]|R]) :-
    substituteElem2(T, E, L, R), !.
substituteElem2([H|T], E, L, R) :- H =:= E,
    insertElemsOfList(L, R1, R),
    substituteElem2(T, E, L, R1).
substituteElem2([H|T], E, L, [H|R]) :- H =\= E,
    substituteElem2(T, E, L, R).


% heterogList(L1:list, L2:list, R:list)
% heterogList(i, i, o)

heterogList([], _, []).
heterogList([H|T], L, [H|R]) :- number(H),
    heterogList(T, L, R).
heterogList([[H|HT]|T], L, [R1|R]) :- 
    substituteElem2([H|HT], H, L, R1),
    heterogList(T, L, R), !.


% firstNumber(L:list, R:value)
% firstNumber(i, o)

firstNumber([], _).
firstNumber([H|_], H) :- number(H).
firstNumber([[_|_]|T], R) :-
    firstNumber(T, R).

% heterogList2(L1:list, L2:list, R:list)
% heterogList2(i, i, o)

heterogList2(L1, L2, RF) :-
    heterogList(L1, L2, R),
    firstNumber(R, F),
    substituteElem2(R, F, L2, RF).


test_heterogList2 :-
    heterogList2([1, [2, 3, 2], 5, 1, [5, 6]], [33, 33],[33, 33, [33, 33, 3, 33, 33], 5, 33, 33, [33, 33, 6]]),
    heterogList2([[2, 3, 2], 5, 1, [5, 6], 5], [33, 33], [[33, 33, 3, 33, 33], 33, 33, 1, [33, 33, 6], 33, 33]).
    
