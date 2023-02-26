% countoc(L:list, V:value, R:value)
% countoc(i, i, o)

countoc([], _, 0).
countoc([H|T], V, R) :- H =\= V,
    countoc(T, V, R).
countoc([H|T], V, R) :- H =:= V,
    countoc(T, V, R1),
    R is R1 + 1.


% checkDup(L:list)
% checkDup(i)

checkDup([]).
checkDup([H|T]) :- 
    countoc([H|T], H, C),
    C =:= 1, 
    checkDup(T).