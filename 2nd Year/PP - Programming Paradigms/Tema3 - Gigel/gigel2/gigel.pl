:- ensure_loaded('chat.pl').

% Returneaza true dacă regula dată ca argument se potriveste cu
% replica data de utilizator. Replica utilizatorului este
% reprezentata ca o lista de tokens. Are nevoie de
% memoria replicilor utilizatorului pentru a deduce emoția/tag-ul
% conversației.
% match_rule/3
% match_rule(_Tokens, _UserMemory, rule(_, _, _, _, _)) :- fail.
match_rule(Tokens, _UserMemory, rule(X, _, _, _, _)) :- X = Tokens.

% Primeste replica utilizatorului (ca lista de tokens) si o lista de
% reguli, iar folosind match_rule le filtrează doar pe cele care se
% potrivesc cu replica dată de utilizator.
% find_matching_rules/4
% find_matching_rules(+Tokens, +Rules, +UserMemory, -MatchingRules)
find_matching_rules(Tokens, Rules, _UserMemory, MatchingRules) :-
	findall(X, (member(X, Rules), match_rule(Tokens, _, X)), MatchingRules).

% Intoarce in Answer replica lui Gigel. Selecteaza un set de reguli
% (folosind predicatul rules) pentru care cuvintele cheie se afla in
% replica utilizatorului, in ordine; pe setul de reguli foloseste
% find_matching_rules pentru a obtine un set de raspunsuri posibile.
% Dintre acestea selecteaza pe cea mai putin folosita in conversatie.
%
% Replica utilizatorului este primita in Tokens ca lista de tokens.
% Replica lui Gigel va fi intoarsa tot ca lista de tokens.
%
% UserMemory este memoria cu replicile utilizatorului, folosita pentru
% detectarea emotiei / tag-ului.
% BotMemory este memoria cu replicile lui Gigel și va si folosită pentru
% numararea numarului de utilizari ale unei replici.
%
% In Actions se vor intoarce actiunile de realizat de catre Gigel in
% urma replicii (e.g. exit).
%
% Hint: min_score, ord_subset, find_matching_rules

get_rules(Tokens, Rules) :-
	rules([Token | _], Rules),
	member(Token, Tokens).

get_replies(Tokens, Replies) :-
	get_rules(Tokens, Rules),
	find_matching_rules(Tokens, Rules, _, Replies).

find_action(Rules, Selected, Action) :-
	findall(X, (member(rule(_, S, X, _, _), Rules), S = Selected), [Action | _]).

% select_answer/5
% select_answer(+Tokens, +UserMemory, +BotMemory, -Answer, -Actions)
select_answer(Tokens, UserMemory, BotMemory, Answer, Action) :-
	get_replies(Tokens, RulesReplies),
	get_emotion(UserMemory, Emotion),
	(Emotion = 'trist'; Emotion = 'fericit'),
	findall(X, (member(rule(_, R, _, [Emotion | _], _), RulesReplies), member(X, R)), Replies),
	findall((E, V), (member(E, Replies), get_answer(E, BotMemory, V)), ListReplies),
	find_action(RulesReplies, Answer, Action),
	min_element(ListReplies, Answer), !.

select_answer(Tokens, UserMemory, BotMemory, Answer, Action) :-
	get_replies(Tokens, RulesReplies),
	get_tag(UserMemory, Tag),
	\+ Tag = 'none',
	findall(X, (member(rule(_, R, _, _, [Tag | _]), RulesReplies), member(X, R)), Replies),
	findall((E, V), (member(E, Replies), get_answer(E, BotMemory, V)), ListReplies),
	find_action(RulesReplies, Answer, Action),
	min_element(ListReplies, Answer), !.

select_answer(Tokens, _UserMemory, BotMemory, Answer, Action) :-
	get_replies(Tokens, RulesReplies),
	findall(X, (member(rule(_, R, _, _, _), RulesReplies), member(X, R)), Replies),
	findall((E, V), (member(E, Replies), get_answer(E, BotMemory, V)), ListReplies),
	find_action(RulesReplies, Answer, Action),
	min_element(ListReplies, Answer).


% Esuează doar daca valoarea exit se afla in lista Actions.
% Altfel, returnează true.
% handle_actions/1
% handle_actions(+Actions)
handle_actions(Actions) :- \+ member(exit, Actions).

% Caută frecvența (numărul de apariți) al fiecarui cuvânt din fiecare
% cheie a memoriei.
% e.g
% ?- find_occurrences(memory{'joc tenis': 3, 'ma uit la box': 2, 'ma uit la un film': 4}, Result).
% Result = count{box:2, film:4, joc:3, la:6, ma:6, tenis:3, uit:6, un:4}.
% Observați ca de exemplu cuvântul tenis are 3 apariți deoarce replica
% din care face parte a fost spusă de 3 ori (are valoarea 3 în memorie).
% Recomandăm pentru usurința să folosiți înca un dicționar în care să tineți
% frecvențele cuvintelor, dar puteți modifica oricum structura, această funcție
% nu este testată direct.

add_to_dict([(K, V) | L], OldR, NewR) :-
	(OldV = OldR.get(K), !; OldV = 0),
	NewV is OldV + V,
	put_dict(K, OldR, NewV, NewRR),
	add_to_dict(L, NewRR, NewR),
	!.

add_to_dict(_, R, R).

% find_occurrences/2
% find_occurrences(+UserMemory, -Result)
find_occurrences(UserMemory, R) :-
	dict_keys(UserMemory, Keys),
	findall((K, V), (member(X, Keys), words(X, Kv),
			member(K, Kv), get_value(UserMemory, X, V)), Res),
	Result = memory{},
	add_to_dict(Res, Result, R).

% Atribuie un scor pentru fericire (de cate ori au fost folosit cuvinte din predicatul happy(X))
% cu cât scorul e mai mare cu atât e mai probabil ca utilizatorul să fie fericit.

compute_happy([K | L], M, Prev, Final) :-
	happy(K),
	get_value(M, K, V),
	Temp is Prev + V,
	compute_happy(L, M, Temp, Final), !.

compute_happy([_ | L], M, S, Snew) :-
	compute_happy(L, M, S, Snew), !.

compute_happy([], _, S, S).

% get_happy_score/2
% get_happy_score(+UserMemory, -Score)
get_happy_score(UserMemory, Score) :-
	find_occurrences(UserMemory, NewMemory),
	dict_keys(NewMemory, States),
	compute_happy(States, NewMemory, 0, Score).

% Atribuie un scor pentru tristețe (de cate ori au fost folosit cuvinte din predicatul sad(X))
% cu cât scorul e mai mare cu atât e mai probabil ca utilizatorul să fie trist.

compute_sad([K | L], M, Prev, Final) :-
	sad(K),
	get_value(M, K, V),
	Temp is Prev + V,
	compute_happy(L, M, Temp, Final), !.

compute_sad([_ | L], M, S, Snew) :-
	compute_sad(L, M, S, Snew), !.

compute_sad([], _, S, S).

% get_sad_score/2
% get_sad_score(+UserMemory, -Score)
get_sad_score(UserMemory, Score) :-
	find_occurrences(UserMemory, NewMemory),
	dict_keys(NewMemory, States),
	compute_sad(States, NewMemory, 0, Score).

% Pe baza celor doua scoruri alege emoția utilizatorul: `fericit`/`trist`,
% sau `neutru` daca scorurile sunt egale.
% e.g:
% ?- get_emotion(memory{'sunt trist': 1}, Emotion).
% Emotion = trist.
% get_emotion/2
% get_emotion(+UserMemory, -Emotion)
get_emotion(UserMemory, Emotion) :-
	get_sad_score(UserMemory, SadScore),
	get_happy_score(UserMemory, HappyScore),
	(SadScore > HappyScore, Emotion = trist, !;
	 HappyScore > SadScore, Emotion = fericit, !;
	 Emotion = neutru).

% Atribuie un scor pentru un Tag (de cate ori au fost folosit cuvinte din lista tag(Tag, Lista))
% cu cât scorul e mai mare cu atât e mai probabil ca utilizatorul să vorbească despre acel subiect.

compute_tag([A | Lst], L, Prev, Final) :-
	member(A, L),
	Temp is Prev + 1,
	compute_tag(Lst, L, Temp, Final),
	!.

compute_tag([_ | Lst], L, Prev, Final) :-
	compute_tag(Lst, L, Prev, Final).

compute_tag([], _, S, S).

% get_tag_score/3
% get_tag_score(+Tag, +UserMemory, -Score)
get_tag_score(Tag, UserMemory, Score) :-
	find_occurrences(UserMemory, Words),
	dict_keys(Words, Keys),
	tag(Tag, L),
	compute_tag(Keys, L, 0, Score).

% Pentru fiecare tag calculeaza scorul și îl alege pe cel cu scorul maxim.
% Dacă toate scorurile sunt 0 tag-ul va fi none.
% e.g:
% ?- get_tag(memory{'joc fotbal': 2, 'joc box': 3}, Tag).
% Tag = sport.
% get_tag/2
% get_tag(+UserMemory, -Tag)
get_tag(memory{}, 'none').

get_tag(UserMemory, Tag) :-
	findall((X, S), (tag(X, _), get_tag_score(X, UserMemory, S), S > 0), Res),
	max_element(Res, Tag).
