% hasEvenAmount(L:list, F:value)
% hasEvenAmount(i, o)

hasEvenAmount([], 0) :- !.
hasEvenAmount([_|T], 0) :-
    hasEvenAmount(T, 1).
hasEvenAmount([_|T], 1) :-
    hasEvenAmount(T, 0).


% verifyEven(L:list)
% verifyEven(i)

verifyEven(L) :-
    hasEvenAmount(L, 0).