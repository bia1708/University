% countoc(L:list, V:value, R:value)
% countoc(i, i, o)

countoc([], _, 0).
countoc([H|T], V, R) :- H =\= V,
    countoc(T, V, R).
countoc([H|T], V, R) :- H =:= V,
    countoc(T, V, R1),
    R is R1 + 1.

% numberatom(L:list, R:list)
% numberatom(i,o)

numberatom([],[]).
numberatom([H|T], [[H|C]|R]) :-
    countoc([H|T], H, C),
    rem([H|T], H, RT),
    numberatom(RT, R).