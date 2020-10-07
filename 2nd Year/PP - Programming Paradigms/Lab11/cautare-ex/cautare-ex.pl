%% -------------------------------------------------------------
%% -------------------------------------------------------------
:- discontiguous exercitiul/2, initial_state/2, final_state/2, next_state/3.

%% -- BACKTRACKING ATUNCI CÂND CUNOAȘTEM LUNGIMEA SOLUȚIEI --
exercitiul(1, [2, puncte]).
%% Înțelegeți predicatele solve_latin/1, template/1 și correct/1.
%% Observați că lipsește definiția predicatului safe/2.

%% template/1
%% template(?List)
%% List are forma unei soluții pentru problema pătratului latin.
%% Lungimea soluției este cunoscută și fixă.
template([1/1/_, 1/2/_, 1/3/_, 2/1/_, 2/2/_, 2/3/_, 3/1/_, 3/2/_, 3/3/_]).

%% correct/1
%% correct(?Solution)
%% Solution reprezintă o soluție validă pentru problemă.
correct([]):-!.
correct([X/Y/S|Others]):-
        correct(Others),
        member(S, [a, b, c]),
        once(safe(X/Y/S, Others)).

%% solve_latin/1
%% solve_latin(-Solution)
%% Solution este o soluție a problemei pătratului latin.
solve_latin(S):-template(S), correct(S).

%% Scrieți predicatul safe/2 utilizat în rezolvarea problemei.
%% Predicatul verifică dacă plasarea simbolului S pe coloana X
%% și linia Y este validă în raport cu lista Others. Aceasta
%% are forma [X1/Y1/S1, X2/Y2/S2 ...].

%% TODO
%% safe/2
%% safe(+X/Y/S, +Others)

safe(_, []):-true, !.
safe(X/Y/T, [A/B/K | Rest]) :- ((X \== A, Y \== B, T == K); T \== K),
                                safe(X/Y/T, Rest).


check1 :- tests([
              uck(safe(1/1/a, [1/3/a])),
              uck(safe(1/2/b, [3/2/b])),
              chk(safe(2/2/b, [1/1/b, 3/3/b, 2/1/a, 2/3/c, 1/2/a])),
              chk(safe(1/1/a, [1/2/b, 1/3/c, 2/1/c, 2/2/a, 2/3/b, 3/1/b, 3/2/c, 3/3/a])),
              uck(safe(3/2/b, [1/2/b, 1/3/c, 2/1/c, 2/2/a, 2/3/b, 3/1/b, 3/3/a])),
              chk(safe(3/2/c, [1/1/a, 1/2/b, 1/3/c, 2/1/c, 2/2/a, 2/3/b, 3/1/b, 3/3/a])),
              nsl('(Sol=[1/1/a, 1/2/b, 1/3/c, 2/1/c, 2/2/a, 2/3/b, 3/1/_, 3/2/_, 3/3/_],
                        solve_latin(Sol))', 'Sol', 1),
              nsl('(Sol=[1/1/a, 1/2/b, 1/3/c, 2/1/_, 2/2/_, 2/3/_, 3/1/_, 3/2/_, 3/3/_],
                        solve_latin(Sol))', 'Sol', 2),
              nsl('solve_latin(Sol)', 'Sol', 12)
          ]).

%% Întrebați-l pe Prolog "solve_latin(Sol)" pentru a vizualiza
%% soluțiile.

%% -------------------------------------------------------------
%% -------------------------------------------------------------

%% -- BACKTRACKING ATUNCI CÂND NU CUNOAȘTEM LUNGIMEA SOLUȚIEI --
exercitiul(2, [6, puncte]).
%% Înțelegeți cum funcționează predicatele solve/2 și search/3 pentru
%% rezolvarea unei probleme de căutare în spațiul stărilor. Observați
%% utilizarea predicatelor initial_state/2, final_state/2 și
%% next_state/3. fiecare dintre predicate ia ca prim argument problema
%% pe care o rezolvăm.

search(Pb, [CurrentState|Other], Solution) :-
        final_state(Pb, CurrentState),
        !,
        reverse([CurrentState|Other], Solution).

search(Pb, [CurrentState|Other], Solution) :-
        next_state(Pb, CurrentState, NextState),
        \+ member(NextState, Other),
        search(Pb, [NextState,CurrentState|Other], Solution).

solve(Pb, Solution):-
        initial_state(Pb, State),
        search(Pb, [State], Solution).

%% Exemplu: problema țăranului, a lupului, a caprei și a verzei.
%% Vom reprezenta o stare astfel:
%% state(MalTaran, Lista-cu-cine-este-pe-malul-cu-taranul)
%% Vom da acestei probleme numele 'taran'.
%% NOTĂ: implementarea se putea face doar cu 2 clauze pentru  next_state

opus(est, vest).
opus(vest, est).

safeTaran([]).
safeTaran([_]).
safeTaran(Cine) :- sort(Cine, [lup, varza]).


allTaran([capra, lup, varza]).

initial_state(taran, state(est, Cine)) :- allTaran(Cine).

final_state(taran, state(vest, Cine)) :- allTaran(All), sort(Cine, All).

%% Țăranul călătorește singur
next_state(taran, state(MalTaran1, Cine1), state(MalTaran2, Cine2)) :-
        allTaran(All),
        % pe celălalt mal sunt cei care nu sunt pe malul cu țăranul.
        setMinus(All, Cine1, Cine2),
        % cine rămâne pe vechiul mal este ok.
        safeTaran(Cine1),
        % țăranul merge pe celălalt mal.
        opus(MalTaran1, MalTaran2).

%% Țăranul călătorește cu lupul
next_state(taran, state(MalTaran1, Cine1), state(MalTaran2, Cine2)) :-
        allTaran(All),
        % lupul este pe același mal cu țăranul, inițial.
        member(lup, Cine1),
        % pe celălalt mal sunt cei care nu sunt pe malul cu țăranul.
        setMinus(All, Cine1, Cine2A),
        % pe malul unde ajunge țăranul ajunge și lupul.
        Cine2 = [lup | Cine2A],
        % cine rămâne pe vechiul mal este ok.
        setMinus(All, Cine2, Ramas), safeTaran(Ramas),
        % țăranul merge pe celălalt mal.
        opus(MalTaran1, MalTaran2).

%% Țăranul călătorește cu varza
next_state(taran, state(MalTaran1, Cine1), state(MalTaran2, Cine2)) :-
        allTaran(All),
        % varza este pe același mal cu țăranul, inițial.
        member(varza, Cine1),
        % pe celălalt mal sunt cei care nu sunt pe malul cu țăranul.
        setMinus(All, Cine1, Cine2A),
        % pe malul unde ajunge țăranul ajunge și varza.
        Cine2 = [varza | Cine2A],
        % cine rămâne pe vechiul mal este ok.
        setMinus(All, Cine2, Ramas), safeTaran(Ramas),
        % țăranul merge pe celălalt mal.
        opus(MalTaran1, MalTaran2).

%% Țăranul călătorește cu capra
next_state(taran, state(MalTaran1, Cine1), state(MalTaran2, Cine2)) :-
        allTaran(All),
        % capra este pe același mal cu țăranul, inițial.
        member(capra, Cine1),
        % pe celălalt mal sunt cei care nu sunt pe malul cu țăranul.
        setMinus(All, Cine1, Cine2A),
        % pe malul unde ajunge țăranul ajunge și capra.
        Cine2 = [capra | Cine2A],
        % cine rămâne pe vechiul mal este ok.
        setMinus(All, Cine2, Ramas), safeTaran(Ramas),
        % țăranul merge pe celălalt mal.
        opus(MalTaran1, MalTaran2).

%% vizualizați soluțiile cu
% solve(taran, Sol), validSol(taran, Sol).

% setPlus(+A, +B, -Result)
% concatenează A și B în Result (Atenție! nu elimină duplicate).
setPlus(A, B, Result) :- append(A, B, Result).

% subSet(+Smaller, +Bigger)
% Verifică dacă setul Smaller este inclus în sau egal cu setul Bigger.
subSet(A, B) :- forall(member(X, A), member(X, B)).

% setMinus(+From, +ToRemove, -Result)
% Produce în result lista elementelor din From care nu sunt în ToRemove.
setMinus(From, ToRemove, Result) :-
        findall(E, (member(E, From), \+ member(E, ToRemove)), Result).


%% Problema Misionarilor și Canibalilor
%% ====================================
%% Fie un râu cu două maluri, trei misionari, trei canibali și o
%% barcă. Barca și cei 6 se află inițial pe un mal, iar
%% scopul este ca toți să ajungă pe malul opus. Barca are capacitate de
%% maximum două persoane și nu poate călători fără nicio persoană.
%% Găsiți o secvență de traversări, astfel încât nicăieri să nu existe
%% mai mulți canibali decât misionari (pot exista însă pe un mal doar
%% canibali).

%% Scrieți predicatele initial_state, final_state, și next_state
%% pentru problema misionarilor.

%% Pentru o mai bună structură, implementați întâi predicatele boat/2
%% și safeMisionari/2 detaliate mai jos.


% TODO
% boat/2
% boat(-NM, -NC)
% Posibilele combinații de număr de misionari și canibali care pot
% călători cu barca.
boat(1, 0).
boat(1, 1).
boat(2, 0).
boat(0, 1).
boat(0, 2).

% TODO
% safe/2
% safe(+NM, +NC)
% Verifică dacă numărul dat de misionari și canibali pot fi pe același
% mal.
% Atenție la de câte ori este adevărat safeMisionari pentru diverse
% valori ale argumentelor - poate influența numărul soluțiilor pentru
% problemă.
safeMisionari(NMis, NCan) :- NMis >= NCan; NMis == 0.


% TODO
% parseState/3
% parseState(+State, -Mal, -NM_Est, -NC_Est, -NM_Vest, -NC_Vest)
% Întoarce în ultimele 5 argumente malul unde este barca și numerele de
% misionari / canibali de pe malul estic, respectiv vestic, în starea
% dată.
parseState(state(M, NME, NCE, NMV, NCV), M, NME, NCE, NMV, NCV).


% TODO
% initial_state(misionari, -State)
% Determină starea inițială pentru problema misionarilor, în formatul
% ales.
initial_state(misionari, state(est, 3, 3, 0, 0)).


% TODO
% final_state(misionari, +State)
% Verifică dacă starea dată este stare finală pentru problema
% misionarilor.
final_state(misionari, state(vest, 0, 0, 3, 3)).


% TODO
% next_state(misionari, +S1, -S2)
% Produce o stare următoare S2 a stării curente S1.
% Toate soluțiile predicatului next_state pentru o stare S1 dată trebuie
% să fie toate posibilele stări următoare S2 în care se poate ajunge din
% S1.
next_state(misionari, Start, Final) :- parseState(Start, Mal1, NME1, NCE1, NMV1, NCV1),
                                        Mal1 == est,
                                        boat(NM, NC),
                                        NM =< NME1, NC =< NCE1, 
                                        NME2 is NME1 - NM, NCE2 is NCE1 - NC,
                                        NMV2 is NMV1 + NM, NCV2 is NCV1 + NC,
                                        safeMisionari(NME2, NCE2),
                                        safeMisionari(NMV2, NCV2),
                                        Final = state(vest, NME2, NCE2, NMV2, NCV2).

next_state(misionari, Start, Final) :- parseState(Start, Mal1, NME1, NCE1, NMV1, NCV1),
                                        Mal1 == vest,
                                        boat(NM, NC),
                                        NM =< NMV1, NC =< NCV1,
                                        NMV2 is NMV1 - NM, NCV2 is NCV1 - NC,
                                        NME2 is NME1 + NM, NCE2 is NCE1 + NC,
                                        safeMisionari(NME2, NCE2),
                                        safeMisionari(NMV2, NCV2),
                                        Final = state(est, NME2, NCE2, NMV2, NCV2).


% dacă solve(misionari, Sol) eșuează, folosiți
% tracksolve(misionari, Sol) pentru a inspecta construcția soluției.

check2 :- tests([
              % a - c
              ckA('boat', [(1, 0), (1, 1), (2, 0)]),
              ech('boat(X, Y)', ['X + Y > 0', '(X >= Y ; X == 0)', 'X + Y =< 2']),
              nsl('boat(X, Y)', 'X/Y', 5),
              % d - h
         0.2, chk(safeMisionari(3, 3)),
         0.2, chk(safeMisionari(3, 2)),
         0.2, chk(safeMisionari(0, 3)),
         0.2, uck(safeMisionari(2, 3)),
         0.2, uck(safeMisionari(1, 3)),
              % i - k
              chk(initial_state(misionari, _)),
              exp('initial_state(misionari, S), parseState(S, M, ME, CE, MV, CV)',
                  ['M', est, 'ME', 3, 'CE', 3, 'MV', 0, 'CV', 0]),
              exp('initial_state(misionari, S), next_state(misionari, S, S1)',
                  [cond('parseState(S1, _, _, _, _, _)')]),
              % l - n
           2, exp('solve(misionari, Sol)', [cond('validSol(misionari, Sol)')]),
           2, ech('solve(misionari, Sol)', ['validSol(misionari, Sol)']),
           2, nsl('solve(misionari, Sol)', 'Sol', 4)
          ]).


%% -------------------------------------------------------------
%% -------------------------------------------------------------
exercitiul(3, [2, puncte]).

%% Se dau următoarele fapte ce descriu arcele unei păduri de arbori,
%% bazat pe exercițiul de la laboratorul trecut.
%% ATENȚIE: Fiecare nod poate avea acum oricâți copii.

nod(a). nod(b). nod(c). nod(d). nod(e). nod(f). nod(g).
nod(h). nod(i). nod(j). nod(k). nod(l).
nod(m).
nod(n). nod(o). nod(p). nod(q). nod(r). nod(s). nod(t). nod(u). nod(v).

arc(a, [b, c, d]). arc(c, [e, g]). arc(e, [f]).
arc(h, [i]). arc(i, [j, k, l]).
arc(n, [o, p]). arc(o, [q, r, s]). arc(p, [t, u, v]).

% TODO
% preorder/2
% preorder(+N, -Parc)
% Întoarce în Parc o listă de noduri rezultate din parcurgerea în
% preordine începând din noudl N.
preorder(N, [N | PChld]) :- arc(N, Chld), chldDfs(Chld, [], PChld).
preorder(N, [N]) :- \+ arc(N, _).

chldDfs([], Vis, P) :- reverse(Vis, P).
chldDfs([C | Chld], Vis, P) :- \+ arc(C, _),
                               chldDfs(Chld, [C | Vis], P).
chldDfs([C | Chld], Vis, P) :- arc(C, CChld),
                               chldDfs(CChld, [C | Vis], PChld),
                               reverse(PChld, VisChld),
                               chldDfs(Chld, VisChld, P).

check3 :- tests([
          exp('preorder(a, P)', ['P', [a, b, c, e, f, g, d]]),
          exp('preorder(n, P)', ['P', [n, o, q, r, s, p, t, u, v]])
          ]).


exercitiul(4, [2, puncte]).
% Dată fiind funcția nodes, parcurgeți toată pădurea de arbori.

% nodes(-NN)
% Întoarce în NN toate nodurile din pădurea de arbori.
nodes(NN) :- findall(N, nod(N), NN).

% TODO
% trees/1
% trees(-Trees)
% Întoarce în trees o listă în care fiecare element este parcurgerea
% unui arbore.
trees(Trees) :- nodes(NN), sort(NN, Nodes), traverse(Nodes, [], Trees).

traverse(NN, NN, Trees) :- Trees = [].
traverse(NN, Vis, Trees) :- nod(X), \+ member(X, Vis),
                                preorder(X, Tree),
                                append(Vis, Tree, NewVis),
                                sort(NewVis, SNewVis),
                                traverse(NN, SNewVis, NewTrees),
                                Trees = [Tree | NewTrees].

check4 :- tests([
              exp('trees(TT)', ['TT',
                                [[a,b,c,e,f,g,d],[h,i,j,k,l],[m],[n,o,q,r,s,p,t,u,v]]])
          ]).


exercitiul(5, [3, puncte]).

% se dă un graf cu nodurile numere de la 1 la 10, și muchiile date mai
% jos.
graph(NN) :- findall(N, between(1, 10, N), NN).

edges(1, [2, 10]).
edges(3, [5, 8, 10]). edges(5, [6]). edges(4, [6, 7, 8]).
edges(8, [3, 8, 9]). edges(6, [2, 5, 9, 10]).

% TODO
% span/1
% span(-Trees)
% Întoarce o listă de arbori.
% Fiecare arbore este reprezentat prin nodul său rădăcină.
% Fiecare nod este reprezentat ca o listă care în primul element are
% valoarea nodului iar restul elementelor sunt reprezentările nodurilor
% sale copii.
% E.g. Arborele cu a rădăcină, având pe b și c copii, iar b având un
% copil d, este reprezentat ca [a, [b, [d]], [c]].
span(_) :- fail.


check5 :- tests([
          exp('span(Trees)', ['Trees', [[1,[2],[10]],[3,[5,[6,[9]]],[8]],[4,[7]]]])
          ]).



%% --------------------------------------------
%% teste specifice pentru problemele de căutare
%% --------------------------------------------


tracksearch(Pb, [CurrentState|Other], Solution) :-
        final_state(Pb, CurrentState),
        !,
        write('DONE.'), nl,
        reverse([CurrentState|Other], Solution).

tracksearch(Pb, [CurrentState|Other], Solution) :-
        format('Finding next state from ~w ... ', [CurrentState]),
        next_state(Pb, CurrentState, NextState),
        format('Try state: ~w ...', [NextState]),
        trackmember(NextState, Other),
        reverse([NextState,CurrentState|Other], Prog), print_progress(Pb, Prog),
        tracksearch(Pb, [NextState,CurrentState|Other], Solution).
trackmember(State, Other) :- \+ member(State, Other), !, write('continue...'), nl.
trackmember(_, _) :- write('already visited'), nl, nl, fail.

print_progress(misionari, [_]).
print_progress(misionari, [S1, S2 | Rest]) :-
        parseState(S1, M1, ME1, CE1, MV1, CV1),
        parseState(S2, _, ME2, CE2, MV2, CV2),
        (   M1 == est, !, MB is ME1 - ME2, CB is CE1 - CE2,
            format('~w M  ~w C  ~10| v~~~~~~~~  ~10| ~w M  ~w C ~30| ~w~n',
                   [ME1, CE1, MV1, CV1, S1]),
            format('~8| ~w M  ~w C ->~n', [MB, CB]),
            format('~w M  ~w C  ~10| ~~~~~~~~v  ~10| ~w M  ~w C ~30| ~w~n',
                   [ME2, CE2, MV2, CV2, S2])
        ;   MB is MV1 - MV2, CB is CV1 - CV2,
            format('~w M  ~w C  ~10| ~~~~~~~~v  ~10| ~w M  ~w C ~30| ~w~n',
                   [ME1, CE1, MV1, CV1, S1]),
            format('~7| <- ~w M  ~w C ~n', [MB, CB]),
            format('~w M  ~w C  ~10| v~~~~~~~~  ~10| ~w M  ~w C ~30| ~w~n',
                   [ME2, CE2, MV2, CV2, S2])
        ),
        print_progress(misionari, [S2 | Rest]).
tracksolve(Pb, Solution) :-
        write('====================================================='), nl,
        write('====================================================='), nl,
        write('====================================================='), nl,
        initial_state(Pb, State),
        parseState(State, _, ME, CE, MV, CV),
        format('~w M ~w C v~~~~ ~w M ~w C~n', [ME, CE, MV, CV]),
        tracksearch(Pb, [State], Solution).

err(Sol, Msg, Value) :-
        format('~n~n Solutia: ~n'),
        (   is_list(Sol) -> forall(member(E, Sol), format('~w~n', [E]))),
        format('~w: ~w.~n', [Msg, Value]), fail.

validSol(Pb, Sol) :- %format('~n~n Solutia: ~n'),
        (   \+ is_list(Sol), !, err(Sol, 'Solutia nu este o lista', Sol)
        ;   !, forall(member(E, Sol), validState(Pb, Sol, E))
        , validTransitions(Pb, Sol, Sol), last(Sol, Last), validFinal(Pb, Sol, Last)).
validSol(Pb, Sol) :- format('INTERN: caz invalid validSol ~w: ~w~n', [Pb, Sol]), fail.

validMal(_, _, _, 0, _) :- !.
validMal(_, _, _, M, C) :- M >= C, !.
validMal(Sol, S, Mal, M, C) :-
        swritef(Msg, 'Numar incorect de misionari/canibali %w/%w pe malul %wic in starea',
               [M, C, Mal]),
        err(Sol, Msg, S).
validState(taran, Sol, S) :- allTaran(All),
        (   S = state(Mal, Elements),
            (   \+ member(Mal, [est, vest]), err(Sol, 'Mal invalid', Mal)
            ;   (\+ subSet(Elements, All), setMinus(Elements, All, Inv),
                err(Sol, 'Elemente invalide', Inv)
                ;   setMinus(All, Elements, OtherSide), validOther(Sol, OtherSide)))
        ;   err(Sol, 'Stare in format incorect', S)).
validState(misionari, Sol, S) :-
        (   parseState(S, M, ME, CE, MV, CV), !,
            (   member(M, [est, vest]), !,
                (   ME + MV =:= 3, CE + CV =:= 3, !,
                    validMal(Sol, S, est, ME, CE), validMal(Sol, S, vest, MV, CV)
                ;   err(Sol, 'numar incorect de persoane in stare', S)
                )
            ;   err(Sol, 'mal incorect in stare', M/S)
            )
        ;   err(Sol, 'parseState a esuat pentru', S)
        ).
validState(_, Sol, S) :- err(Sol, 'INTERN: caz invalid validState', S).
validOther(_, []) :- !.
validOther(_, [_]) :- !.
validOther(_, L) :- sort(L, [lup, varza]), !.
validOther(Sol, L) :- member(lup, L), member(capra, L), !, err(Sol, 'Lupul mananca capra', L).
validOther(Sol, L) :- member(varza, L), member(capra, L), !, err(Sol, 'Capra mananca varza', L).
validOther(Sol, L) :- err(Sol, 'INTERN: caz invalid validOthers', L).
validTransitions(_, _, [_]) :- !.
validTransitions(taran, Sol, [S1, S2 | Rest]) :- !,
        S1 = state(Mal1, _Cine1), S2 = state(Mal2, _Cine2),
        (   \+ opus(Mal1, Mal2), !, err(Sol, 'nu sunt opuse:', [Mal1, Mal2])
        ;   validTransitions(taran, Sol, [S2 | Rest])). % not fully checked
validTransitions(misionari, Sol, [S1, S2 | Rest]) :- !,
        parseState(S1, Mal1, ME1, CE1, MV1, CV1), parseState(S2, Mal2, ME2, CE2, MV2, CV2),
        (   \+ opus(Mal1, Mal2), !, err(Sol, 'nu sunt opuse:', [Mal1, Mal2])
        ;
        (   Mal1 == est, !, validBoat(misionari, Sol, S1, S2, ME1, CE1, ME2, CE2)
        ;   validBoat(misionari, Sol, S1, S2, MV1, CV1, MV2, CV2)
        )), validTransitions(misionari, Sol, [S2 | Rest]).
validTransitions(_, Sol, Rest) :- err(Sol, 'INTERN: caz invalid validTransitions', Rest).
validBoat(misionari, Sol, S1, S2, M1, C1, M2, C2) :-
        MB is M1 - M2, CB is C1 - C2,
        (   MB + CB > 0, MB + CB =< 2, (MB == 0, !; MB >= CB), !
        ;   swritef(Msg, 'numar incorect de misionari/canibali %w/%w in barca intre starile',
                    [MB, CB]), err(Sol, Msg, S1/S2)
        ).
validFinal(taran, Sol, state(Mal, Elements)) :- allTaran(All),
        (   Mal \= vest, !, err(Sol, 'Nu ajunge pe malul vestic la sfarsit', Mal)
        ;   ( \+ sort(Elements, All), setMinus(All, Elements, Miss),
            !, err(Sol, 'Nu au ajuns', Miss/Elements), fail
            ; !, true)).
validFinal(misionari, Sol, S) :- parseState(S, Mal, _, _, MV, CV),
        (   Mal \= vest, !, err(Sol, 'Nu ajunge pe malul vestic la sfarsit', Mal)
        ;   ( MV \= 3, CV \= 3, !, err(Sol, 'Au ajuns doar', MV/CV), fail
            ; !, true)).
validFinal(_, Sol, S) :- err(Sol, 'INTERN: caz invalid validFinal', S).



%% ----------------------------------------
%% ----------------------------------------

%test_mode(vmchecker). % not implemented yet
test_mode(quick).
testtimelimit(5). % în secunde



:-dynamic(punct/2).
:-dynamic(current/1).
%:-clean.

clean :- retractall(punct(_, _)), retractall(current(_)).

testtest(5).
testtest(6).
testtest(9).
testtest(a, 5).
testtest(b, _).
testtest(d, [2, 1, 3]).
testtest(e, [2, 1, 3, 1, 2]).
testtest(1, 2, 3).
testtest(c, X, X).
testtest(d, 5, excepting) :- X is 5 / 0, write(X).
testtest(d, 5, limitless) :-  testtest(d, 5, limitless).

testtest :- tests([
               % chk(P) ("check") verifică evaluarea cu succes a lui P
               chk(testtest(5)), % a
               chk(testtest(6)), % b % eșuează
               % uck(P) ("uncheck") verifică evaluarea cu eșec a lui P
               uck(testtest(6)), % c
               uck(testtest(5)), % d % eșuează
               % exp(P, Exps) ("expect") verifică evaluarea cu succes a lui P și a unor condiții
               % P este dat ca șir de caractere pentru o verificare și afișare mai bune.
               % Condițiile sunt evaluate pe rând și independent unele de altele.
               % Dacă în lista de condiții avem un nume de variabilă,
               % se verifică că aceasta a fost legat la valoarea care urmează imediat în listă.
               % valoarea de verificat nu poate conține variabile din interogare
               % (pentru asta folosiți cond, vezi mai jos).
               exp('testtest(X, X)', ['X', b]), % e
               exp('testtest(X, Y, Z)', ['X', 1, 'Y', 2, 'Z', 3]), % f
               exp('testtest(X, X)', ['X', a]), % g % eșuează
               % Dacă în lista de condiții avem v('Var'), se verifică că Var a rămas nelegată.
               exp('testtest(b, Y)', [v('Y')]), % h
               exp('testtest(a, Y)', [v('Y')]), % i % eșuează
               % Dacă în lista de condiții avem cond('P'), se verifică că P este adevărat.
               % Diversele condiții din structuri cond diferite se verifică independent.
               exp('testtest(c, X, X)', [v('X'), cond('X==X')]), % j
               % Dacă în lista de condiții avem set('V', Set), se verifică că V este legată la mulțimea Set.
               % Duplicatele contează.
               exp('testtest(d, L)', [set('L', [1, 2, 3]), 'L', [1, 2, 3]]), % k % eșuează pe a 2a condiție
               exp('testtest(d, L)', [set('L', [2, 3, 4, 5])]), % l
               exp('testtest(e, L)', [set('L', [1, 2, 3])]), % m
               % setU funcționează la fel, dar ignoră duplicatele.
               exp('testtest(e, L)', [setU('L', [1, 2, 3])]), % n
               % ckA(P, Argss) ("check all") verifică evaluarea cu succes a lui P pe fiecare dintre variantele de argumente din Argss.
               % e.g. dacă P este pred, iar Argss este [(1, a, []), (2, b, [5])],
               % se vor evalua atomii pred(1, a, []) și pred(2, b, [5]).
               ckA('testtest', [(a, 5), (b, 1), (b, 3), (b, 4)]), %o
               ckA('testtest', [(a, 5), (c, 1), (c, 3), (b, 4)]), %p
               % ech(P, Conds) ("each") verifică dacă condițiile țin pentru fiecare dintre soluțiile lui P
               ech('testtest(X)', ['X < 10', 'X > 3']), % q
               ech('testtest(X)', ['X > 3', 'X > 5']), % r
               % nsl(P, Template, NSols) ("N Solutions") verifică dacă lungimea lui L din findall(P, Template, L) este NSols
               2, nsl('testtest(X, Y)', '(X, Y)', 4), % s
               % testul de mai sus valorează de 2 ori mai mult decât celelalte

               % sls(P, Template, Sols) ("Solutions") verifică dacă findall(P, Template, L) leagă L la aceeași mulțime cu Sols.
               % Duplicatele contează
               2, sls('testtest(X, X)', '(X, X)', [(b, b)]), % t
               % testul de mai sus valorează de 2 ori mai mult decât celelalte

               sls('testtest(X, Y)', '(X, Y)', [(b, 5)]), % u
               % gestionare exceptii
               chk(testtest(d, 5, excepting)),
               % gestionare limita de timp
               chk(testtest(d, 5, limitless))
           ]).


tests(Tests) :- (   current(_), ! ; retractall(punct(_, _))),
    total_fractions(Tests, TF),
    (   current(Ex), !, exercitiul(Ex, [Pts | _]), Total is TF / Pts
    ;   Total is TF / 100
    ),
    tests(Tests, 1, Total),
    (   current(_), !
    ;   findall(P, punct(_, P), L), sum_list(L, S), format('Rezolvat ~0f%.~n', [S])
    ).

tests([], _, _) :- !.
tests([P, T|R], Idx, Tot) :- number(P), !, test(T, Idx, P, Tot), tests(R, Idx+1, Tot).
tests([T|R], Idx, Tot) :- test(T, Idx, 1, Tot), tests(R, Idx+1, Tot).

total_fractions([], 0).
total_fractions([P, _|R], Tot) :- number(P), !, total_fractions(R, TotR), Tot is TotR + P.
total_fractions([_|R], Tot) :- total_fractions(R, TotR), Tot is TotR + 1.

test(T, Idx, Frac, Tot) :- IdxI is Idx + 96, char_code(CEx, IdxI),
    (   current(NEx), !, swritef(Ex, '[%w|%w]', [NEx, CEx]) ; swritef(Ex, '%w|', [CEx])),
    testtimelimit(Time), swritef(MTime, 'limita de %w secunde depasita', [Time]),
    (   catch(
            catch(call_with_time_limit(Time, once(test(Ex, T))),
                  time_limit_exceeded,
                  except(Ex, MTime)
                 ),
            Expt,
            (   swritef(M, 'exceptie: %w', [Expt]),
                except(Ex, M))
        ),
        !, success(Ex, Frac, Tot)
    ; true).

success(Ex, Frac, Tot) :-
    Score is Frac / Tot,
    assert(punct(Ex, Score)),
    format('~w[OK] Corect. +~2f.~n', [Ex, Score]).

failure(Ex, M) :- format('~w[--] ~w~n', [Ex, M]), fail.
except(Ex, M) :- format('~w[/-] ~w~n', [Ex, M]), fail.

test(Ex, chk(P)) :- !, testCall(Ex, P).
test(Ex, uck(P)) :- !, testCall(Ex, \+ P).
test(Ex, exp(Text, ExpList)) :- !,
    read_term_from_atom(Text, P, [variable_names(Vars)]),
    testCall(Ex, P, Text), testExp(Ex, Text, Vars, ExpList).
test(_, ckA(_, [])) :- !.
test(Ex, ckA(Pred, [Test|Tests])) :- !,
    swritef(S, '%w(%w)', [Pred, Test]),
    read_term_from_atom(S, P, []),
    testCall(Ex, P, S), test(Ex, ckA(Pred, Tests)).
test(_, ech(_, [])) :- !.
test(Ex, ech(Text, [Cond|Conds])) :- !,
    swritef(S, '%w|%w', [Text, Cond]),
    read_term_from_atom(S, P|Q, [variable_names(Vars)]),
    forall(P, (
               swritef(Msg, '%w pentru soluția %w a predicatului %w', [Cond, Vars, Text]),
               testCall(Ex, Q, Msg))),
    test(Ex, ech(Text, Conds)).
test(Ex, nsl(Text, Tmplt, N)) :- !,
    swritef(S, 'findall(%w, %w, TheList)', [Tmplt, Text]),
    read_term_from_atom(S, P, [variable_names(Vars)]),
    testCall(Ex, P, S), testNSols(Ex, Text, Vars, N).
test(Ex, sls(Text, Tmplt, Sols)) :- !,
    swritef(S, 'findall(%w, %w, TheList)', [Tmplt, Text]),
    read_term_from_atom(S, P, [variable_names(Vars)]),
    testCall(Ex, P, S), testSols(Ex, Text, Vars, Sols).
test(Ex, sSO(Text, Tmplt, Sols)) :- !,
    swritef(S, 'setof(%w, %w, TheList)', [Tmplt, Text]),
    read_term_from_atom(S, P, [variable_names(Vars)]),
    testCall(Ex, P, S), testSols(Ex, Text, Vars, Sols).
test(Ex, _) :- failure(Ex, 'INTERN: Test necunoscut').

% Pentru exercițiul Ex, evaluează clauza Do, dată ca termen.
% Opțional, în mesajul de eroare interogarea poate fi afișată ca
% parametrul Text.
testCall(Ex, Do) :- swritef(Text, '%q', [Do]), testCall(Ex, Do, Text).
testCall(Ex, Do, Text) :-
        catch((call(Do), !
              ;   !, swritef(M, 'Interogarea %w a esuat.', [Text]), failure(Ex, M)
              ), Exc,
              (swritef(M, 'Interogarea %w a produs exceptie: %w', [Text, Exc]),
              except(Ex, M))
             ).

testExp(_, _, _, []) :- !.
testExp(Ex, Text, Vars, [v(Var) | Rest]) :- !,
    (   getVal(Var, Vars, V), !,
        (   var(V), !, testExp(Ex, Text, Vars, Rest) ;
            swritef(M, 'Interogarea %w leaga %w (la valoarea %w) dar nu ar fi trebuit legata.',
                    [Text, Var, V]), failure(Ex, M)
        )
    ;
    swritef(M, 'INTERN: Interogarea %w nu contine variabila %w.', [Text, Var]),
    failure(Ex, M)
    ).
testExp(Ex, Text, Vars, [set(Var, Set) | Rest]) :- !,
    (   getVal(Var, Vars, V), !,
        testSet(Ex, Text, 'intoarce', V, Set),
        testExp(Ex, Text, Vars, Rest)
    ;
    swritef(M, 'INTERN: Interogarea %w nu contine variabila %w.', [Text, Var]),
    failure(Ex, M)
    ).
testExp(Ex, Text, Vars, [setU(Var, Set) | Rest]) :- !,
    (   getVal(Var, Vars, V), !,
        testSetU(Ex, Text, 'intoarce', V, Set),
        testExp(Ex, Text, Vars, Rest)
    ;
    swritef(M, 'INTERN: Interogarea %w nu contine variabila %w.', [Text, Var]),
    failure(Ex, M)
    ).
testExp(Ex, Text, Vars, [cond(Cond) | Rest]) :- !,
    swritef(S, "(%w, %w)", [Text, Cond]),
    read_term_from_atom(S, P, []),
    (
        call(P), !, testExp(Ex, Text, Vars, Rest)
        ;
        swritef(M, 'Dupa interogarea %w conditia %w nu este adevarata.', [Text, Cond]),
        failure(Ex, M)
    ).
testExp(Ex, Text, Vars, [Var, Val | Rest]) :- !,
    (   getVal(Var, Vars, V), !,
        (   V == Val, !, testExp(Ex, Text, Vars, Rest) ;
            swritef(M, 'Interogarea %w leaga %w la %w in loc de %w.',
                    [Text, Var, V, Val]), failure(Ex, M)
        )
    ;
    swritef(M, 'INTERN: Interogarea %w nu contine variabila %w.', [Text, Var]),
    failure(Ex, M)
    ).
testExp(Ex, _, _, [X | _]) :- !,
        swritef(M, 'INTERN: element necunoscut pentru exp: %w', [X]),
        failure(Ex, M).
testExp(Ex, _, _, X) :- !,
        swritef(M, 'INTERN: format gresit pentru exp: %w', [X]),
        failure(Ex, M).

testNSols(Ex, Text, Vars, N) :-
    (   getVal('TheList', Vars, V), length(V, NSols), !,
        (   NSols =:= N, !
        ;   swritef(M, 'Numarul de solutii pentru %w este %w in loc de %w.',
                    [Text, NSols, N]), failure(Ex, M)
        )
    ;   failure(Ex, 'INTERNAL: nu avem variabila TheList sau aceasta nu este lista.')
    ).

testSols(Ex, Text, Vars, Sols) :-
    (   getVal('TheList', Vars, V), !,
        testSet(Ex, Text, 'are ca solutii', V, Sols)
    ;   failure(Ex, 'INTERNAL: nu avem variabila TheList sau aceasta nu este lista.')
    ).

testSetU(Ex, Text, TypeText, SetG, SetE) :- sort(SetG, SetGUnique),
    testSet(Ex, Text, TypeText, SetGUnique, SetE).
testSet(Ex, Text, TypeText, SetG, SetE) :- msort(SetG, SetGSorted),
    (   SetGSorted == SetE, ! ;
        testSetMinus(SetG, SetE, TooMuch),
        testSetMinus(SetE, SetG, TooLittle),
        (   TooMuch == [], TooLittle == [], !,
            M1 = 'vezi duplicate'
        ;   swritef(M1, '%w sunt in plus, %w lipsesc', [TooMuch, TooLittle])
        ),
        swritef(M,
                'Interogarea %w %w %w dar se astepta %w (%w)',
                [Text, TypeText, SetG, SetE, M1]), failure(Ex, M)
    ).

testSetMinus(From, ToRemove, Result) :-
        findall(E, (member(E, From), \+ member(E, ToRemove)), Result).

getVal(Var, [Var=Val | _], Val) :- !.
getVal(Var, [_ | Vars], Val) :- getVal(Var, Vars, Val).

check:-
    clean,
    forall(exercitiul(Ex, _),
           (   atom_concat(check, Ex, Ck),
               retractall(current(_)), assert(current(Ex)),
               once(call(Ck)) ; true)),
    findall(P, punct(_, P), L),
    sum_list(L, S),
    format('Punctaj total: ~f~n',[S]),
    clean.
