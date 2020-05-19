:- discontiguous exercitiul/2.

% Povestea (inspirată de Știrile de la Ora 5)
%
% În liniștitul nostru oraș s-a produs o crimă. Un individ a pătruns
% în casa unui bătrân și l-a ucis. Cadavrul a fost ascuns de către
% criminal și nu este de găsit. Este un caz complicat, dar doi
% detectivi, D1 și D2, fac cercetări și au deja o listă de
% suspecți. Știu despre fiecare dintre aceștia ce mașină are și care
% este arma lui preferată.
%
% Pentru a rezolva cazul trebuie să afle cu ce armă a fost ucisă
% victima și cu ce mașină a fugit criminalul. Din fericire, dacă se
% poate vorbi despre așa ceva în cazul unei crime îngrozitoare, nu
% există doi suspecți care să aibă aceeași mașină și aceeași armă.
%
% Cei doi detectivi se întâlnesc la secție. D1 s-a întâlnit cu un
% martor și a aflat cu ce mașină a fugit criminalul. D2 a găsit arma
% crimei. Cei doi se întâlnesc la secție, unde au următorul dialog pe
% care tu îl asculți indiscret.
%
% D1: Știu că nu știi cine-i criminalul. Nici eu nu știu.
% D2: Încă nu știu cine este.
% D1: Nici eu nu știu încă cine este criminalul.
% D1: Acum mi-am dat seama.
% D2: Mi-am dat seama și eu.
%
% Cine este criminalul?

% ----------------------------------------------------------------------------
% Mașini

conduce(aurel, ford).
conduce(bogdan, bmw).
conduce(cosmin, bmw).
conduce(daniel, ford).
conduce(eugen, bmw).
conduce(florin, dacia).
conduce(george, fiat).
conduce(horia, audi).
conduce(irina, dacia).
conduce(jean, fiat).
conduce(kiki, audi).
conduce(laura, seat).
conduce(marian, mercedes).
conduce(nicodim, opel).
conduce(ovidiu, honda).
conduce(paul, honda).
conduce(roxana, honda).

% Arme

inarmat(aurel, sabie).
inarmat(bogdan, pistol).
inarmat(cosmin, arbaleta).
inarmat(daniel, grenada).
inarmat(eugen, grenada).
inarmat(florin, sabie).
inarmat(george, pistol).
inarmat(horia, arbaleta).
inarmat(irina, pusca).
inarmat(jean, cutit).
inarmat(kiki, prastie).
inarmat(laura, pusca).
inarmat(marian, cutit).
inarmat(nicodim, prastie).
inarmat(ovidiu, maceta).
inarmat(paul, sabie).
inarmat(roxana, pusca).

% ----------------------------------------------------------------------------
% 1. (1p) Scrieți un predicat suspect(Nume:Marca:Arma) care să fie
% adevărat pentru fiecare suspect al problemei noastre.
exercitiul(1, [1, puncte]).

suspect(Nume : Marca : Arma) :- conduce(Nume, Marca), inarmat(Nume, Arma).

check1:- tests([
             exp('setof(Nume_Marca_Arma, suspect(Nume_Marca_Arma), All)', [set('All', [aurel:ford:sabie, bogdan:bmw:pistol,
             cosmin:bmw:arbaleta, daniel:ford:grenada, eugen:bmw:grenada,
             florin:dacia:sabie, george:fiat:pistol, horia:audi:arbaleta,
             irina:dacia:pusca, jean:fiat:cutit, kiki:audi:prastie,
             laura:seat:pusca, marian:mercedes:cutit, nicodim:opel:prastie,
             ovidiu:honda:maceta, paul:honda:sabie, roxana:honda:pusca])])
          ]).

% ----------------------------------------------------------------------------
% 2. (1p) Scrieți un predicat au_pusca(-ListaNume) care să fie
% adevărat atunci când ListaNume este lista cu numele tuturor celor care
% au pușcă.
exercitiul(2, [1, puncte]).

au_pusca(ListaNume) :- findall(Nume, inarmat(Nume, pusca), ListaNume).

check2:- tests([
             exp('au_pusca(ListaNume)', [set('ListaNume', [irina, laura, roxana])])
          ]).


% ----------------------------------------------------------------------------
% 3. (1p) Scrieți predicatele au_arma(+Arma, -ListaNume)
% și au_marca(+Arma, -ListaNume), care să fie adevărate atunci când
% ListaNume este lista cu numele tuturor celor care au arma de tipul
% Arma, respectiv mașina de tipul Marca.
exercitiul(3, [1, puncte]).

au_arma(Arma, ListaNume) :- findall(Nume, inarmat(Nume, Arma), ListaNume).

au_marca(Marca, ListaNume) :- findall(Nume, conduce(Nume, Marca), ListaNume).

check3:- tests([
             exp('au_arma(pistol, Pistolari)', [set('Pistolari', [bogdan, george])]),
             exp('au_arma(cutit, Cutitari)', [set('Cutitari', [jean, marian])]),
             exp('au_arma(maceta, Macelari)', [set('Macelari', [ovidiu])]),
             exp('au_marca(bmw, NuSemnalizeaza)', [set('NuSemnalizeaza', [bogdan, cosmin, eugen])]),
             exp('au_marca(dacia, ConducDacie)', [set('ConducDacie', [florin, irina])]),
             exp('au_marca(seat, ConducSeat)', [set('ConducSeat', [laura])]),
             exp('findall(_, au_marca(X,Y), L)',  [cond('length(L, 9)')])
          ]).

% ----------------------------------------------------------------------------
% 4. (1.5p) Scrieți un predicat arme_bmw(ListaArme) care să fie adevărat
% atunci când ListaArme reprezintă mulțimea tuturor armelor deținute
% de conducători de bmw.
exercitiul(4, [1.5, puncte]).

arme_bmw(ListaArme) :- au_marca(bmw, ListaNume),
                       findall(Arma, (member(Nume, ListaNume), inarmat(Nume, Arma)), ListaArme).

check4:- tests([
             exp('arme_bmw(Arme)', [set('Arme', [arbaleta, grenada, pistol])])
          ]).


% ----------------------------------------------------------------------------
% 5. (1.5p) Scrieți un predicat arme_marca(Marca, ListaArme) care să
% fie adevărat atunci când ListaArme reprezintă mulțimea tuturor
% armelor deținute de conducători de mașini de tipul Marca.
exercitiul(5, [1.5, puncte]).

arme_marca(Marca, ListaArme) :- setof(Arma, Nume ^ (conduce(Nume, Marca), inarmat(Nume, Arma)), ListaArme).

check5:- tests([
             exp('arme_marca(bmw, ArmeBmw)', [set('ArmeBmw', [arbaleta, grenada, pistol])]),
             exp('arme_marca(dacia, ArmeDacia)', [set('ArmeDacia', [pusca, sabie])]),
             exp('arme_marca(seat, ArmeSeat)', [set('ArmeSeat', [pusca])]),
             exp('findall(Y, arme_marca(X,Y), [ _ , L | _ ])', [set('L', [arbaleta, grenada, pistol])])
          ]).

% ----------------------------------------------------------------------------
% 6. (2p) Scrie un predicat marci_arma_unica(ListaMarci) care să afișeze
% lista mașinilor pentru care lista armelor pe care le dețin
% conducătorii unei mărci conține un singur element. Hint: folosiți-vă
% de rezolvarea exercițiului 5. Nu folosiți length/2.
exercitiul(6, [2, puncte]).

marci_arma_unica(ListaMarci) :- findall(Marca, (conduce(_, Marca), arme_marca(Marca, [_])), ListaMarci).

check6:- tests([
             exp('marci_arma_unica(ListaMarci)', [set('ListaMarci', [mercedes, opel, seat])])
          ]).

% ----------------------------------------------------------------------------
% ----------------------------------------------------------------------------

% Să revenim la secție de poliție unde tu tragi cu urechea la dialogul
% dintre cei doi detectivi:
%
% Prima replică:
% Detectiv A : Știam că nu știi cine-i criminalul.
%
% Ce înseamnă asta? Detectivul A știe mașina cu care a fugit
% suspectul. Această marcă de mașină este condusă de suspecți care
% mânuiesc diferite arme. Dacă măcar una dintre aceste arme ar fi
% aparținut doar unui singur suspect, atunci Detectivul B ar fi putut
% ști care este soluția acestui caz.
%
% Ce soluții eliminăm?
%
% Dacă Detectivul A ar fi aflat că adevăratul criminal a condus o
% Honda, atunci ar fi existat două soluții posibile:
%
% ovidiu - honda - maceta
% paul - honda - sabie
%
% Dar cum nu există decât un singur individ care are macetă (Ovidiu),
% Detectivul A nu ar fi putut afirma că Detectivul B nu poate ști.
%
% honda nu este, deci, o soluție
%
% Trebuie eliminate toate mașinile care sunt "în pereche" cu arme
% pentru care nu există mai multe posibilități.

% ----------------------------------------------------------------------------
% 7. (2.5p) Scrie un predicat suspect1/1 care este adevărat doar pentru
% numele suspecților care respectă condiția impusă de replica
% Detectivului A: niciuna dintre armele asociate cu mașina suspectului
% nu indică în mod unic un anumit individ.
exercitiul(7, [2.5, puncte]).

suspect1(Nume:Marca:Arma) :- suspect(Nume:Marca:Arma), arme_marca(Marca, ListaArme),
                             forall(member(A, ListaArme), au_arma(A, [_, _ | _])).
                             
check7:- tests([
             exp('setof(Nume_Marca_Arma, suspect1(Nume_Marca_Arma), All)',
            [set('All',
            [aurel:ford:sabie,bogdan:bmw:pistol,cosmin:bmw:arbaleta,
             daniel:ford:grenada,eugen:bmw:grenada,florin:dacia:sabie,
             george:fiat:pistol,horia:audi:arbaleta,irina:dacia:pusca,
             jean:fiat:cutit,kiki:audi:prastie,laura:seat:pusca,
             marian:mercedes:cutit,nicodim:opel:prastie])])
          ]).

% ----------------------------------------------------------------------------
% A doua replică:
%
% Detectivul A: Nici eu nu știu!
%
% 8. (1.5p) Scrie un predicat suspect2/1 care este adevărat doar pentru
% numele suspecților care respectă condiția impusă de replica
% Detectivului A: marca nu indică unic un individ.
%
% Atenție: informația ce trebuie filtrată acum este cea care
% corespunde primei replici.
exercitiul(8, [1.5, puncte]).

suspect2(Nume:Marca:Arma) :- suspect1(Nume:Marca:Arma),
                             findall(Name, suspect1(Name:Marca:_), [_, _ |_]).
check8:- tests([
             exp('setof(Nume_Marca_Arma, suspect2(Nume_Marca_Arma), All)',
            [set('All',
            [aurel:ford:sabie,bogdan:bmw:pistol,cosmin:bmw:arbaleta,
              daniel:ford:grenada,eugen:bmw:grenada,florin:dacia:sabie,
              george:fiat:pistol,horia:audi:arbaleta,irina:dacia:pusca,
              jean:fiat:cutit,kiki:audi:prastie])])
          ]).

% ----------------------------------------------------------------------------
% A treia replică:
%
% Detectivul B: Nici eu nu știu!
%
% 9. (1p) Scrie un predicat suspect3/1 care este adevărat doar pentru
% numele suspecților care respectă condiția impusă de replica
% Detectivului B: arma nu identifică unic un individ.
%
% Atenție: informația ce trebuie filtrată acum este cea care
% corespunde primelor două replici.
exercitiul(9, [1, puncte]).

suspect3(Nume:Marca:Arma) :- suspect2(Nume:Marca:Arma),
                             findall(Name, suspect2(Name:_:Arma), [_, _ |_]).
check9:- tests([
             exp('setof(Nume_Marca_Arma, suspect3(Nume_Marca_Arma), All)',
            [set('All',
            [aurel:ford:sabie,bogdan:bmw:pistol,cosmin:bmw:arbaleta,
              daniel:ford:grenada,eugen:bmw:grenada,florin:dacia:sabie,
              george:fiat:pistol,horia:audi:arbaleta])])
          ]).

% ----------------------------------------------------------------------------
% A patra replică:
%
% Detectivul A: Eu tot nu știu!
%
% 10. (1p) Scrie un predicat suspect4/1 care este adevărat doar pentru
% numele suspecților care respectă condiția impusă de replica
% Detectivului A.
%
% Atenție: informația ce trebuie filtrată acum este cea care
% corespunde primelor trei replici.
exercitiul(10, [1, puncte]).

suspect4(Nume:Marca:Arma) :- suspect3(Nume:Marca:Arma),
                             findall(Name, suspect3(Name:Marca:_), [_, _ | _]).
check10:- tests([
             exp('setof(Nume_Marca_Arma, suspect4(Nume_Marca_Arma), All)',
            [set('All',
            [aurel:ford:sabie,bogdan:bmw:pistol,cosmin:bmw:arbaleta,
              daniel:ford:grenada,eugen:bmw:grenada])])
          ]).

% ----------------------------------------------------------------------------
% A cincea replică:
%
% Detectivul B: Eu am aflat!
%
% 11. (0.5p) Scrie un predicat suspect5/1 care este adevărat doar pentru
% numele suspecților care respectă condiția impusă de replica
% Detectivului B.
%
% Atenție: informația ce trebuie filtrată acum este cea care
% corespunde primelor patru replici.
exercitiul(11, [0.5, puncte]).

suspect5(Nume:Marca:Arma) :- suspect4(Nume:Marca:Arma),
                             findall(Name, suspect4(Name:_:Arma), [_]).
check11:- tests([
             exp('setof(Nume_Marca_Arma, suspect5(Nume_Marca_Arma), All)',
            [set('All',
            [aurel:ford:sabie,bogdan:bmw:pistol,cosmin:bmw:arbaleta])])
          ]).

% ----------------------------------------------------------------------------
% A șasea replică:
%
% Detectivul A: Și eu am aflat!
%
% 12. (0.5p) Scrie un predicat suspect6/1 care este adevărat doar pentru
% numele suspecților care respectă condiția impusă de replica
% Detectivului A.
%
% Atenție: informația ce trebuie filtrată acum este cea care
% corespunde primelor cinci replici.
exercitiul(12, [0.5, puncte]).

suspect6(Nume:Marca:Arma) :- suspect5(Nume:Marca:Arma),
                             findall(Name, suspect5(Name:Marca:_), [_]).
check12:- tests([
             exp('setof(Nume_Marca_Arma, suspect6(Nume_Marca_Arma), All)',
            [set('All',
            [aurel:ford:sabie])])
          ]).
%% ----------------------------------------
%% ----------------------------------------

testtimelimit(5). % în secunde

test_mode(quickcheck) :- \+ test_mode(vmchecker).

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

% aceasta va fi ordinea de testare
vmpoints(1, 5).
vmpoints(T, 2.5) :- member(T, ['2a', '2b']).

% entry point (for users) for vm tests.
vmtest(T) :-
        vmtest(T, Score),
        format('Total: ~w.', [Score]).

% performes a vm test, outputs score.
vmtest(T, Score) :-
        once(vmpoints(T, Pts)),
        tt(T, TestList),
        tests(TestList, Pts, T, Score).

tt(1, [
       chk(testtest(5)),
       chk(testtest(6)),
       uck(testtest(6)),
       uck(testtest(5))
       ]).
tt('2a', [
       exp('testtest(X, X)', ['X', b])
   ]).
tt('2b', [
       exp('testtest(X, Y, Z)', ['X', 1, 'Y', 2, 'Z', 3]),
       exp('testtest(X, X)', ['X', a])
   ]).


% entry point for quick check; handles checking all exercises or just
% one.
tests(Tests) :- (   current(_), ! ; retractall(punct(_, _))),
        (   current(Ex), !, exercitiul(Ex, [Pts | _]), Total is Pts
        ;   Total is 100, Ex = none
        ),
        tests(Tests, Total, Ex, Score),
        (   current(Ex), assert(punct(Ex, Score)), !
        ;   format('Rezolvat ~0f%.~n', [Score])
        ), !.

tests(_) :- failure(unknown, 'INTERN: tests/1 failed').

tests(Tests, TotalPoints, Ex, Score) :-
    total_units(Tests, TF),
    Unit is TotalPoints / TF,
    tests(Tests, Ex, 1, Unit, 0, Score), !.
tests(_, _, Ex, _) :- failure(Ex, 'INTERN: tests/4 failed').

% iterates through tests, handles test index, generates test id, adds
% points
tests([], _, _, _, Points, Points) :- !.
tests([Fraction, T|R], Ex, Idx, Unit, PointsIn, PointsOut) :-
        number(Fraction), !, test(T, Ex, Idx, Fraction, Unit, PointsIn, PointsOut1),
        tests(R, Ex, Idx+1, Unit, PointsOut1, PointsOut).
tests([T|R], Ex, Idx, Unit, PointsIn, PointsOut) :-
        test(T, Ex, Idx, 1, Unit, PointsIn, PointsOut1),
        tests(R, Ex, Idx+1, Unit, PointsOut1, PointsOut).
tests(_, Ex, _, _, _, _) :- failure(Ex, 'INTERN: tests/6 failed').

total_units([], 0).
total_units([P, _|R], Tot) :- number(P), !, total_units(R, TotR), Tot is TotR + P.
total_units([_|R], Tot) :- total_units(R, TotR), Tot is TotR + 1.

test(T, NEx, Idx, Fraction, Unit, PointsIn, PointsOut) :-
        IdxI is Idx + 96, char_code(CEx, IdxI),
        (   NEx == none, !, swritef(Ex, '%w|', [CEx]) ; swritef(Ex, '[%w|%w]', [NEx, CEx])),
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
            !, success(Ex, Fraction, Unit, Points),
            PointsOut is PointsIn + Points
        ; PointsOut = PointsIn).
test(_, Ex, Idx, _, _, _, _) :- failure(Ex/Idx, 'INTERN: test/7 failed').

success(Ex, Fraction, Unit, Score) :-
    Score is Fraction * Unit,
    (   test_mode(vmchecker), !,
        format('+~2f ~10t ~w Corect.~n', [Score, Ex])
    ;   format('~w[OK] Corect. +~2f.~n', [Ex, Score])).
failure(Ex, M) :-
        (   test_mode(vmchecker), !,
            format('+0.0 ~10t  ~w ~w~n', [Ex, M]), fail
        ;   format('~w[--] ~w~n', [Ex, M]), fail).
except(Ex, M) :-
        (   test_mode(vmchecker), !,
            format('+0.0 ~10t ~w Exception: ~w~n', [Ex, M]), fail
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
testSet(Ex, Text, TypeText, SetG, SetE) :- msort(SetG, SetGSorted),
    (   SetGSorted == SetE, ! ;
        testSetMinus(SetG, SetE, TooMuch),
        testSetMinus(SetE, SetG, TooLittle),
        (   TooMuch == [], TooLittle == [], !,
            M1 = 'vezi duplicate'
        ;   swritef(M1, '\n%w sunt in plus,\n%w lipsesc', [TooMuch, TooLittle])
        ),
        swritef(M,
                'Interogarea %w %w %w dar se astepta %w (%w)',
                [Text, TypeText, SetG, SetE, M1]), failure(Ex, M)
    ).

testSetMinus(From, ToRemove, Result) :-
        findall(E, (member(E, From), \+ member(E, ToRemove)), Result).

getVal(Var, [Var=Val | _], Val) :- !.
getVal(Var, [_ | Vars], Val) :- getVal(Var, Vars, Val).

check :-
        clean,
        forall(exercitiul(Ex, _),
               (   atom_concat(check, Ex, Ck),
                   retractall(current(_)), assert(current(Ex)),
                   once(call(Ck)) ; true)),
        findall(P, punct(_, P), L),
        sum_list(L, S),
        format('Punctaj total: ~f~n',[S]),
        clean.

vmtest :- checkVm.
checkVm :-
        clean,
        findall(T:Score, (tt(T, _), vmtest(T, Score)), Results),
        findall(Score, member(_:Score, Results), Scores),
        sum_list(Scores, S),
        format('Total: ~w~n', [S]),
        clean.
