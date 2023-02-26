% gcd(A:value, B:value, R:value)
% gcd(i, i, o)

gcd(0, B, B) :- !.
gcd(A, 0, A) :- !.
gcd(A, B, R) :- A > B,
    R1 is A mod B, 
    gcd(B, R1, R).
gcd(A, B, R) :- A =< B,
    R1 is B mod A, 
    gcd(A, R1, R).    


% gcdOfList(L:list, R:value)
% gcdOfList(i,o)

gcdOfList([H], H).
gcdOfList([H|T], R) :-
    gcdOfList(T, R1),
    gcd(H, R1, R).