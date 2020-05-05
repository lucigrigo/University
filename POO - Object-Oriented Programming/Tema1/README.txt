

Programare Orientata pe Obiecte - Tema I
“Sheriff of Nottingham”
Grigore Lucian-Florin
324CD
Facultatea de Automatica si Calculatoare
Universitatea Politehnica, Bucuresti



Prezentarea implementarii

		Am considerat structurarea rezolvarii cat mai logic, astfel incat derularea jocului sa fie in concordanta cat mai stransa cu realitatea, in viziunea mea. Am creat clase separate pentru orice element important, cum ar fi: toate bunurile (fie ele ilegale legale), fiecare tip de jucator, precum si clase suplimentare ca un “factory” de bunuri, o clasa de utilitati sau o clasa care sa contina doar constantele folosite in tot codul. Desfasurarea jocului (elementele principale ale ei) are loc intr-un singur loc pentru o urmarire mai usoara.

Structura solutiei
	
	Interfata Player - contine toate declaratiile pentru fiecare functie care este mai apoi implementata in clasa pentru fiecare tip de jucator.
	Clasa BaseStrategyPlayer - implementeaza strategia de joc de baza.
	Clasa GreedyStrategyPlayer - implementeaza strategia de joc “greedy”.
	Clasa BribeStrategyPlayer - implementeaza strategie de joc “bribe”.

	Clasa Game - clasa principala folosita pentru desfasurarea jocului. Din interiorul functiilor ei (startGame() si endGame()) se apeleaza functii prezente ori in clasa de utilitati (Utilities) ori care se leaga de crearea sacilor jucatorilor, recompletarea cartilor din mana sau inspectarea celorlalti jucatori de catre serif.

	Clasa Bag - reprezinta un sac care este dat spre inspectie la un anumit moment de timp, avand urmatoarele atribute: bunul care este declarat ca fiind singurul din sac (int dominantAsset), mita (int bribe) si lista de bunuri din sac (List<Goods> assets).

	Clasele Apple, Barrel, etc. - cate o clasa pentru fiecare tip de bun pentru a fi mai usor de urmarit initializarea fiecaruia. Fiecare initializarea foloseste constante din clasa Constants.

	Clasa Utilities - reprezinta o clasa de utilitati folosite pentru orice tip de sarcina suplimentara, cum ar fi: cautarea celui mai frecvent bun legal dintr-o lista de carti, calcularea scorului unui jucator, adaugarea bonusului de king/queen la scorul unui jucator, afisarea clasamentului final, confiscarea unui sac sau acceptarea mitei de la un jucator de catre serif etc.

	Clasa Constants - in clasa asta am introdus toate constantele folosite in cod ori de cate un jucator, ori la crearea listei cu toate bunurile posibile in joc. Daca e necesara o modificare a unui profit, sau penalty, aici se pot face aceste modificari si ele vor fi modificate in tot codul. Am scris constante pentru: profitul bunurilor, penalty-ul bunurilor, id-ul bunurilor, bonusul de king/queen al bunurilor legale, numarul de bunuri .

	Clasa GoodsFactory - este un “factory” pentru initializarea bunurilor(hardcodate).
	
	Clasele Goods, IllegalGoods, LegalGoods - reprezinta un bun in general, un bun ilegal si, respectiv, un bun legal. Ultimele doua au caracteristici diferite. 

	Clasa GameInput - este o clasa care semnifica input-ul primit dintr-un fisier dat spre citire Am pastrat exact structura care a fost data in scheletul de cod.

	Clasa GameInputLoader - este o clasa care se ocupa de “incarcarea” datelor de input. Aici am modificat citirea, n-am mai folosit FileSystem, ci am folosit un Scanner.

Observatii

	Am considerat crearea unei interfete Player, si nu abstractizarea acesteia deoarece mi s-a parut mai logica abordarea, dar si pentru ca, in cazul abstractizarii, am avut unele probleme de adresare a membrilor din clasele de jucatori.
	Pentru anumite operatii pe lista de bunuri am facut anumite sortari 