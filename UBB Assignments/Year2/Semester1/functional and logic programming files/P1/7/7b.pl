% createListOfInt(M:value, N:value, R:list)
% createListOfInt(i, i, o)

createListOfInt(E, E, [E]).
createListOfInt(M, N, [M|R]) :-
    M =\= N,
    M1 is M + 1,
    createListOfInt(M1, N, R).