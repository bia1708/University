% alternative_sum(L:list, R:number)
% alternative_sum(i, o)
% alternative_sum(i,i)

alternative_sum([], 0).
alternative_sum([H], H).
alternative_sum([H1, H2|T], R) :-
    alternative_sum(T, R1),
    R is H1 - H2 + R1.

test_alternative_sum :-
    alternative_sum([1,2,3],2),
    alternative_sum([], 0),
    alternative_sum([1,2],-1),
    \+alternative_sum([1,2],0).