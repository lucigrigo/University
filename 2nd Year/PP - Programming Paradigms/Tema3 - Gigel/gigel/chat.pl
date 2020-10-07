:- ensure_loaded('gigel.pl').

% Functii ajutatoare
% =====

% add_answer(+Answer, +Memory, -NewMemory)
% Adauga un raspuns la memorie, iar daca raspunsul există deja in
% memorie va incrementa numarul de folosiri; daca nu, il va adauga cu
% valoarea initială 1.
add_answer(Answer, Memory, NewMemory) :-
	unwords(Answer, Key),
	(Val = Memory.get(Key), !; Val = 0),
	NewVal is Val + 1,
	NewMemory = Memory.put(Key, NewVal).

% get_value(+Dict, +Key, -Val)
% Returnează valoarea dintr-un dictionar sau 0 daca cheia nu există în
% dicționar.
get_value(Dict, Key, Val) :-
	(Val = Dict.get(Key), !; Val = 0).


% get_answer(+Answer, +Memory, -Val)
% Returnează numărul de folosiri ale unui replici din memorie
% sau 0 daca replica nu există in memorie. e.g:
% ?- get_answer([joc, box], memory{'joc fotbal': 2, 'joc box': 3}, Val).
% Val = 3.
get_answer(Answer, Memory, Val) :-
	unwords(Answer, Key),
	get_value(Memory, Key, Val).

% min_element(+KeyValueList, Key)
% Gaseste elementul minim dintr-o lista de forma [(score, element)], e.g:
% ?- min_element([('joc fotbal', 1), ('joc box', 3)], Min).
% Min = 'joc fotbal'.
% Este util pentru a gasi sau replicile folosite de cele mai puține ori
% în conversație sau emoțiile/tag-uri cu cel mai mic scor.
min_element(L, Answer) :-
	select((Answer, Min), L, Rest), \+ (member((_, E), Rest), E < Min), !.

% max_element(+KeyValueList, Key)
% Analog cu min_element
max_element(L, Answer) :-
	select((Answer, Max), L, Rest), \+ (member((_, E), Rest), E > Max), !.

% words(+Sentence, -Words)
% Imparte propozitia in tokens (cuvinte sau semne de punctuatie).
words(Sentence, Words) :-
	((functor(A, re_replace, 4), predicate_property(A, visible)) ->
		re_replace("\\77"/i, " ?", Sentence, L1),
		re_replace("\\56|!"/i, "", L1, L2),
		re_replace(" {2,}"/i, " ", L2, L3);
		L3 = Sentence),
	string_lower(L3, SentenceLower),
	split_string(SentenceLower, " ", "", W),
	maplist(term_string, Words, W).

% unwords(+Answer, -Sentence)
% Formeaza o propozitie dintr-o lista de tokens.
unwords(Answer, S) :- atomic_list_concat(Answer, " ", S).

% Logica pentru conversație.
% =====

rules([salut], [
	rule([_], [
		[salutare],
		[salut]
	], [], [], [])
]).

rules([hey], [
	rule([_], [
		[hey],
		[howdy]
	], [], [], [])
]).

rules([faci], [
	rule([ce, faci, '?'], [
		[bine, tu, '?']
	], [], [], [])
]).

rules([Z], [
	rule([ma, Z, la, _, X], [
		[ce, X, '?']
	], [], [], []),
	rule([ma, Z, la, X], [
		[nu, am, auzit, de, X, ',', care, este, filmul, tau, favorit, '?']
	], [], [], [])
]) :- member(Z, [uit, uitam]).

rules([filmul], [
	rule([filmul, meu, favorit, este, X], [
		[X, '?', nu, am, auzit, de, el, ',', despre, ce, e, vorba, '?']
	], [], [], [film])
]).

rules([scuze], [
	rule([_], [
		[te, rog, nu, iti, cere, scuze],
		[de, ce, simti, nevoia, sa, iti, ceri, scuze, '?'],
		[nu, e, nicio, problema]
	], [], [], [])
]).

rules([esti], [
	rule([esti, X], [
		[nu, cred, ca, pot, fi, X, sunt, doar, un, robot],
		[tu, esti, X]
	], [], [], []),
	rule([esti, X, '?'], [
		[sunt, la, fel, de, X, ca, tine],
		[X, '?', nu, cred, dar, tu, '?']
	], [], [], [])
]).

rules(X, [
	rule(_, [
		[pa, pa],
		[o, zi, buna],
		[pe, curand]
	], [exit], [], [])
]) :- member(X, [[pa], [bye], [la, revedere]]).

rules([simt], [
	rule([cum, ma, simt, '?'], [
		[nu, stiu]
	], [], [], []),
	rule([cum, ma, simt, '?'], [
		[pari, cam, trist]
	], [], [trist], []),
	rule([cum, ma, simt, '?'], [
		[cred, ca, esti, fericit]
	], [], [fericit], [])
]).

rules([interese], [
	rule([ce, interese, am, '?'], [
		[nu, stiu]
	], [], [], []),
	rule([ce, interese, am, '?'], [
		[filmele, evident]
	], [], [], [film]),
	rule([ce, interese, am, '?'], [
		[cred, ca, iti, place, sportul]
	], [], [], [sport])
]).

rules(_, [
	rule(_, [
		[nu, inteleg]
	], [], [], [])
]).

happy(fericit). happy(bucuros). happy(vesel).
happy(voios). happy(incantat). happy(recunoscator).
happy(multumit). happy(entuziasmat). happy(entuziast).

sad(rau). sad(trist). sad(regret). sad(suferinta).
sad(sumbru). sad(intristare). sad(intristat).
sad(durere). sad(amaraciune). sad(dezolare).


tag(sport, [tenis, volei, fotbal, fotbalist, box, gimnastica, judo, oina, schi, sah]).
tag(film, [film, filmul, camera, actor, scena, cameraman, scenariu, colorizare, regizor]).


write_answer(Answer) :-
  write("Gigel:"),
	unwords(Answer, S),
	write(S),
	nl.

gigel(UserMemory, BotMemory):-
	writeln("Tu:"),
  read_line_to_string(user_input,Line),
  words(Line, Words),
	add_answer(Words, UserMemory, NewUserMemory),
  select_answer(Words, NewUserMemory, BotMemory, Answer, Actions),
  write_answer(Answer),
	add_answer(Answer, BotMemory, NewBotMemory),
  handle_actions(Actions),
  gigel(NewUserMemory, NewBotMemory).

gigel :- gigel(memory{}, memory{}).
