% valley(L:list, F:number)
% valley(i, i, i)
% valley(i, o, o)

valley([_], 0).
valley([H1, H2|T], R) :- H1 < H2, 
    valley([H2|T], R1), R is R1-1, !.
valley([H1, H2|T], R) :- H1 > H2,
    valley([H2|T], R1), R is R1+1, !.


test_valley :-
    valley([10,8,5,7,8],0),
    valley([3,2,1,2,3],0),
    \+valley([1,2,3],0),
    \+valley([],0).

