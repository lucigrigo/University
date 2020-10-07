ordered([]). % cazul in care avem lista goala
ordered([_]). % cazul in care avem un singur element
ordered([X, Y | Z]) :- X =< Y , ordered([Y|Z]). % luam primele doua elemente din Lista si le comparam si apelam recursiv, pastrand
                                                % al doilea element din comparatie

filtersorted(L, Rez) :- findall(X, (member(X, L), ordered(X)), Rez).

% functia filtersorted aplica un findall care cauta acele elemente X din L (X este oricare lista din L) astfel incat X indeplineste criteriul
% ordered. Ordered este o simpla 'functie' recursiva care compara element cu element lista de input.

 secondMax(L, Y) :- [F, S | Rez] is L, X is max(F, S), Y is min(F, S),
                forall(member(A, Rez), (A > X, A > Y, X is A, Y is X; A < X, A > Y, Y is A)).

%listmin([L|Ls], Min) :- foldl(comp_min, Ls, L, Min).
%listmin2(E, [L|Ls], Min) :- foldl(comp_min2, Ls, E, Min).

%comp_min(X, Y, Min) :- Min is min(X, Y).
%comp_min()

%secondMax(L, X) :- listmin(L, Y), listmin2(Y, L, X).