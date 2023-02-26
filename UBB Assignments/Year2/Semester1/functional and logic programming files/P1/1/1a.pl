% gcd(i, i, o)


gcd(0, B, B) :- !.
gcd(A, 0, A) :- !.
gcd(A, B, R) :- A >= B,
    A1 is A mod B,
    gcd(A1, B, R), !.
gcd(A, B, R) :- A < B,
    B1 is B mod A,
    gcd(A, B1, R), !.

% lcm(i, i, o)

lcm([], 1).
lcm([H], H).
lcm([H|T], R) :-
    lcm(T, R1),
    gcd(H, R1, R2),
    R is H * R1 / R2.