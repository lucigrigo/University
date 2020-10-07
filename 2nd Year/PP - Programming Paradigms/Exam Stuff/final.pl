p(1).
p(2).
p(3).
q(3).
q(4).
r(1).
r(2).
r(3).

riddle(E, E+1, "Fail").
riddle(X, Y, "Success") :- riddle(Y, X, "Fail").

odd1(L, R) :- findall(X, (member(X, L), X mod 2 =:= 1), R).
odd2(L, R) :- bagof(X, (member(X, L), X mod 2 =:= 1), R).
odd3(L, R) :- setof(X, (member(X, L), X mod 2 =:= 1), R).