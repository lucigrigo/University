:- ensure_loaded('gigel.pl').

vmpoints(Test, Points) :-
    member(Test:Points,
           [ inceput_conversatie:10
           , sfarsit_conversatie:10
           , handle_actions:5
           , conversatie_simpla:20
           , conversatie_complicata:25
           , emotii:30
           , bonus:20
           ]).

tt(inceput_conversatie, [
 exp("select_answer([salut], memory{}, memory{}, A, _)", ['A', [salutare]]),
 exp("select_answer([salut], memory{}, memory{'salutare':1}, A, _)", ['A', [salut]]),
 exp("select_answer([hey], memory{}, memory{}, A, _)", ['A', [hey]]),
 exp("select_answer([hey], memory{}, memory{'hey':1}, A, _)", ['A', [howdy]])
]).

tt(handle_actions, [
 chk(handle_actions([])),
 uck(handle_actions([exit]))
]).

tt(sfarsit_conversatie, [
 exp("select_answer([pa], memory{}, memory{}, A, Act)", ['A', [pa, pa], 'Act', [exit]]),
 exp("select_answer([bye], memory{}, memory{'pa pa':1}, A, Act)", ['A', [o, zi, buna], 'Act', [exit]]),
 exp("select_answer([la, revedere], memory{}, memory{'pa pa':1, 'o zi buna': 1}, A, Act)",
     ['A', [pe, curand], 'Act', [exit]]),
 exp("select_answer([la, revedere], memory{}, memory{'pa pa':1, 'o zi buna': 1, 'pe curand': 1}, A, Act)",
     ['A', [pa, pa], 'Act', [exit]])
]).

tt(conversatie_simpla, [
 exp("select_answer([hey], memory{}, memory{}, A, _)", ['A', [hey]]),
 exp("select_answer([ce, faci, '?'], memory{}, memory{}, A, _)", ['A', [bine, tu, '?']]),
 exp("select_answer([scuze], memory{}, memory{}, A, Act)", ['A', [te, rog, nu, iti, cere, scuze], 'Act', []]),
 exp("select_answer([scuze],
									 memory{}, memory{
											'te rog nu iti cere scuze':1,
											'de ce simti nevoia sa iti ceri scuze ?':1
									 },
									 A, Act)",
									 ['A', [nu, e, nicio, problema], 'Act', []]),
 exp("select_answer([scuze],
									 memory{}, memory{
											'te rog nu iti cere scuze':1,
											'de ce simti nevoia sa iti ceri scuze ?':1,
											'nu e nicio problema':1
									 },
									 A, Act)",
                                                                         ['A', [te, rog, nu, iti, cere, scuze], 'Act', []]),
 exp("select_answer(
	[divulgaritatea, umanistica, a, unui, om, s-ar, putea, retusa, pe, un, blastom, al, nonsalantei, nonconformiste],
	memory{}, memory{}, A, _)",
	['A', [nu, inteleg]])
]).

tt(conversatie_complicata, [
 exp("select_answer([hey], memory{}, memory{}, A, _)", ['A', [hey]]),
 exp("select_answer([ce, faci, '?'], memory{}, memory{}, A, _)", ['A', [bine, tu, '?']]),
 exp("select_answer([ma, uit, la, un, videoclip], memory{}, memory{}, A, _)", ['A', [ce, videoclip, '?']]),
 exp("select_answer([ma, uitam, la, pewdiepie], memory{}, memory{}, A, _)",
     ['A', [nu, am, auzit, de, pewdiepie, ',', care, este, filmul, tau, favorit, '?']]),
 exp("select_answer([esti, destept, '?'], memory{}, memory{}, A, _)", ['A', [sunt, la, fel, de, destept, ca, tine]]),
 exp("select_answer([esti, destept], memory{}, memory{}, A, _)", ['A', [nu, cred, ca, pot, fi, destept, sunt, doar, un, robot]]),
 exp("select_answer([esti, destept], memory{}, memory{'nu cred ca pot fi destept sunt doar un robot':1}, A, _)",
     ['A', [tu, esti, destept]]),
 exp("select_answer([esti, destept, '?'], memory{}, memory{'sunt la fel de destept ca tine': 2}, A, _)",
     ['A', [destept, '?', nu, cred, dar, tu, '?']])
]).

tt(emotii, [
 exp("get_emotion(memory{'ma simt trist': 3, 'sunt trist': 2, 'sunt fericit': 4}, E)", ['E', trist]),
 exp("get_emotion(memory{'ma simt fericit': 3, 'sunt fericit': 2, 'sunt trist': 4}, E)", ['E', fericit]),
 exp("get_emotion(memory{'ma simt fericit': 2, 'sunt fericit': 2, 'sunt trist': 4}, E)", ['E', neutru]),
 exp("select_answer([cum, ma, simt, '?'], memory{'sunt trist': 3, 'sunt fericit': 2}, memory{}, A, _)", ['A', [pari, cam, trist]]),
 exp("select_answer([cum, ma, simt, '?'], memory{'sunt trist': 2, 'sunt fericit': 3}, memory{}, A, _)", ['A', [cred, ca, esti, fericit]]),
 exp("select_answer([cum, ma, simt, '?'], memory{'sunt trist': 2, 'sunt fericit': 2}, memory{}, A, _)", ['A', [nu, stiu]])
]).

tt(bonus, [
 exp("get_tag(memory{'joc tenis': 3, 'ma uit la box': 2, 'ma uit la un film': 4}, T)", ['T', sport]),
 exp("get_tag(memory{'am vazut doar o scena': 3, 'ma uit la un film': 2, 'ma uit la box': 4}, T)", ['T', film]),
 exp("get_tag(memory{}, T)", ['T', none]),
 exp("select_answer([ce, interese, am, '?'], memory{'joc tenis': 3, 'ma uit la box': 2, 'ma uit la un film': 4}, memory{}, A, _)",
     ['A', [cred, ca, iti, place, sportul]]),
 exp("select_answer([ce, interese, am, '?'], memory{'am vazut doar o scena': 3, 'ma uit la un film': 2, 'ma uit la box': 4}, memory{}, A, _)",
     ['A', [filmele, evident]]),
 exp("select_answer([ce, interese, am, '?'], memory{}, memory{}, A, _)",
     ['A', [nu, stiu]])
]).



%% ----------------------------------------
%% ----------------------------------------
%% Tester

testtimelimit(30). % în secunde

test_mode(vmchecker).
test_mode(quickcheck) :- \+ test_mode(vmchecker).

:-dynamic(punct/2).
:-dynamic(current/1).
%:-clean.

clean :- retractall(punct(_, _)), retractall(current(_)).


% -----------------

% runs vm tests
vmtest :- checkVm.
vmcheck :- checkVm.
checkVm :-
        clean,
        findall(T:Score, (tt(T, _), vmtest(T, Score)), Results),
        findall(Score, member(_:Score, Results), Scores),
        sum_list(Scores, S),
        format('Total: ~w~n', [S]),
        clean.

% entry point (for users) for individual vm tests.
vmtest(T) :-
        vmtest(T, Score),
        format('Total: ~w.', [Score]).

% performes a vm test, outputs score.
vmtest(T, Score) :-
        once(vmpoints(T, Pts)),
        tt(T, TestList),
        tests(TestList, Pts, T, Score).


% ---------------
% general testing

% unified entry point for testing; computes fractions, computes if
% exercise is not done, and starts per-test iteration.
tests(Tests, TotalPoints, Ex, Score) :- %trace,
    total_units(Tests, TF, Ck/AllCheck, UCk/AllUCk, Others/AllOthers),
    (   isNotDone(Ck/AllCheck, UCk/AllUCk, Others/AllOthers), !,
        (   Ex == none, !
        ;   ( test_mode(vmchecker), !, format("+0.00 ~10t ") ; true ),
            format("[~w] Nerezolvat.~n", [Ex])
        ),
        Score = 0
    ;   Unit is TotalPoints / TF,
        tests(Tests, Ex, 1, Unit, 0, Score)
    ), !.
tests(_, _, Ex, _) :- failure(Ex, 'INTERN: tests/4 failed').

isNotDone(0/TC, TU/TU, 0/TO) :- (TO > 0, !; TC > 0).
% otherwise, probably done

% iterates through tests, handles test index, generates test id, adds
% points
tests([], _, _, _, Points, Points) :- !.
tests([wait|R], Ex, Idx, Unit, PointsIn, PointsOut) :- !,
    tests(R, Ex, Idx, Unit, PointsIn, PointsOut).
tests([Fraction, T|R], Ex, Idx, Unit, PointsIn, PointsOut) :-
        number(Fraction), !, test(T, Ex, Idx, Fraction, Unit, PointsIn, PointsOut1),
        tests(R, Ex, Idx+1, Unit, PointsOut1, PointsOut).
tests([T|R], Ex, Idx, Unit, PointsIn, PointsOut) :-
        test(T, Ex, Idx, 1, Unit, PointsIn, PointsOut1),
        tests(R, Ex, Idx+1, Unit, PointsOut1, PointsOut).
tests(_, Ex, _, _, _, _) :- failure(Ex, 'INTERN: tests/6 failed').

total_units([], 0, 0/0, 0/0, 0/0).
total_units([wait, P, _|R], Tot, A, B, C) :-
    number(P), !, total_units(R, TotR, A, B, C), Tot is TotR + P.
total_units([wait, _|R], Tot, CO/TCO, UO/TUO, OO/TOO) :- !,
    total_units(R, TotR, CO/TCO, UO/TUO, OO/TOO), Tot is TotR + 1.
total_units([P, T|R], Tot, A, B, C) :-
    number(P), !, total_units([T|R], TotR, A, B, C), Tot is TotR + P.
total_units([T|R], Tot, CO/TCO, UO/TUO, OO/TOO) :- %trace,
    test(T, dry, dry, _, _, 0, P),
    (   ( T = chk(_), ! ; T = ckA(_, _) ), !, TA = 1,
        (   P > 0, A = 1, !; A = 0 )
    ;   TA = 0, A = 0),
    (   ( T = uck(_), ! ; T = nsl(_, _, 0) ), !, TB = 1,
        (   P > 0, B = 1, !; B = 0 )
    ;   TB = 0, B = 0),
    (   T \= chk(_), T \= ckA(_, _), T \= uck(_), T \= ech(_, _), T \= nsl(_, _, 0), !,
        TD = 1, (   P > 0, D = 1, !; D = 0 )
    ;   TD = 0, D = 0),
    total_units(R, TotR, C/TC, U/TU, O/TO), Tot is TotR + 1,
    CO is C+A, TCO is TC+TA, UO is U+B, TUO is TU+TB, OO is O+D, TOO is TO+TD.

test(T, NEx, Idx, Fraction, Unit, PointsIn, PointsOut) :-
        (   NEx == dry, !, Ex = dry, TimeLimit = 0.1
        ;   testtimelimit(TimeLimit),
            IdxI is Idx + 96, char_code(CEx, IdxI),
            (   NEx == none, !, swritef(Ex, '%w|', [CEx])
            ;   swritef(Ex, '[%w|%w]', [NEx, CEx]))
        ),
        swritef(MTime, 'limita de %w secunde depasita', [TimeLimit]),
        (   catch(
                catch(call_with_time_limit(TimeLimit, once(test(Ex, T))),
                      time_limit_exceeded,
                      except(Ex, MTime)
                     ),
                Expt,
                (   swritef(M, 'exceptie: %w', [Expt]), except(Ex, M))
            ),
            !, success(Ex, Fraction, Unit, Points),
            PointsOut is PointsIn + Points
        ; PointsOut = PointsIn).
test(_, Ex, Idx, _, _, _, _) :- failure(Ex/Idx, 'INTERN: test/7 failed').

success(dry, _, _, 1) :- !.
success(Ex, Fraction, Unit, Score) :-
    Score is Fraction * Unit,
    (   test_mode(vmchecker), !,
        format('+~2f ~10t ~w Corect.~n', [Score, Ex])
    ;   format('~w[OK] Corect. +~2f.~n', [Ex, Score])).
failure(dry, _) :- !, fail.
failure(Ex, M) :-
        (   test_mode(vmchecker), !,
            format('+0.00 ~10t  ~w ~w~n', [Ex, M]), fail
        ;   format('~w[--] ~w~n', [Ex, M]), fail).
except(dry, _) :- !, fail.
except(Ex, M) :-
        (   test_mode(vmchecker), !,
            format('+0.00 ~10t ~w Exception: ~w~n', [Ex, M]), fail
        ;   format('~w[/-] ~w~n', [Ex, M]), fail).

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
testSet(Ex, Text, TypeText, SetG, SetE) :-
    msort(SetG, SetGSorted), msort(SetE, SetESorted),
    (   SetGSorted == SetESorted, ! ;
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
