													Analiza Algoritmilor
													  Proiect - Etapa 2

Grigore Lucian-Florin 324CDb
Facultatea de Automatica si Calculatoare
Universitatea Politehnica, Bucuresti


Notiuni teoretice:
	Algoritmii Rabin-Karp si Knuth-Morris-Pratt sunt folositi pentru a cauta
	un pattern intr-un text prin doua modalitati diferite. Primul algoritm este
	la baza un bruteforce, dar la care se adauga o componenta foarte puternica in
	programare, si anume, hashing. Cel de-al doilea este mai complex, dar si mai
	eficient datorita utilizarii unei tabele speciale numita 'failure-function'
	sau 'longest suffix preffix table' care e capabila sa pre-calculeze daca un
	anume sufix al potrivirii (partiale, in cele mai multe cazuri) poate re-
	prezenta un prefix pentru o posibila urmatoare potrivire.

Complexitati:
	(Consideram lungimea textului = n si lungimea patternului = m)

	 	Rabin-Karp: timp: worst-case: O(nm)
											best-case: O(n+m) (la fel si pentru average-case)
											memorie: neglijabil

		Knuth-Morris-Pratt: timp: cautare: O(n)
															pre-procesare: O(m)
															overall: O(n+m)
												memorie: O(m)


Descrierea implementarii:
	Am impartit proiectul in 4 parti: cate o clasa care se ocupa de fiecare algo-
	ritm, o clasa Main si o clasa care se ocupa de transmiterea parametrilor catre
	cei doi algoritmi si de structurarea rezolvarii in cazul unui test de input
 	sau unor inputuri din linia de comanda.

	Clasa Main primeste parametrii din linia de comanda, ii verifica initial si ii
	transmite metodei din clasa MatchingAdministrator corespunzatoare input-ului.

	Clasa MatchingAdministrator poate rula un singur test din fisier, sau poate
	aplica algoritmii in cauza pentru un input primit in stdin. De asemenea, se
	ocupa de afisarea rezultatelor in parte pentru fiecare algoritm, de afisarea
	unor diferente intre diferitele posibilitati de rulare a algoritmului
	Rabin-Karp si de afisarea unor diferente de eficienta referitor la ambii
 	algoritmi in materie de timp.

	Clasa RabinKarp implementeaza algoritmul cu acelasi nume si dispune de functii
	care se ocupa de: parcurgerea textului si cautarea unui posibil match la
 	nivel de hash, compararea caracter cu caracter dintre doua string-uri cu
	scopul de a verifica un match la nivel de hash, calcularea unui hash folosind
	atat o modalitate eficienta, cat si una ineficienta, nerecomandata.
	Calcularea recomandata a unui hash a fost realizata folosind djb2, o
	modalitate de hashing creata de Dan Bernstein care presupune urmatoarea
	formula:
		hash = hash * 33 + current_element_value; (relevanta si eficienta
		folosirii numarului 33 a fost demonstrata de Bernstein)
	Calcularea nerecomandata pentru valoarea hash a fost realizata folosind
	formula:
		hash = hash + 10; (practic adauga inca 5 pentru oricare element al
		 pattern-ului, indiferent de tip)

	Clasa KnuthMorrisPratt implementeaza algoritmul cu acelasi nume si are o
	structura mai simpla decat cea anterioara, continand doar doua functii: una
	care sa parcurga textul in cautarea unui match si alta care sa precalculeze
	vectorul cunoscut ca "failure-function" pentru pattern-ul dat. Prescurtarea
	LSPTable este folosita pentru a denumi "longest suffix preffix table" intr-un
	mod minimal.

	Orice apel de cautare, folosind oricare dintre cei doi algoritmi, returneaza
	o lista de matchuri -List<Integer>- care poate fi si vida. Textul si
	patternul sunt convertite la un vector de elemente de tip char -char[]-
	la momentul apelarii functiilor search() atat pentru o sintaxa mai usoara,
	cat si pentru o implementare mai generalizata.

Descrierea setului de teste:
	Am considerat ca un numar prea mic de teste nu este relevant pentru a vedea
	comportamentul celor doi algoritmi in totalitate. Cele 30 de teste create se
	impart in mai multe categorii:
		[1 - 5]: text de dimensiune scurta cu o singura potrivire
		[6 - 10]: text de dimensiune scurta cu nicio potrivire
		[11 - 15]: text de dimensiune medie cu multiple potriviri
		[16 - 20]: text de dimensiune medie cu nicio potrivire
		[21 - 25]: text de dimensiune mare cu multiple potriviri
		[26 - 30]: text de dimensiune foarte mare cu multiple potriviri sau niciuna
	Folderul 'in' contine testele de input.
	Pentru a vedea continutul unui fisier de input se foloseste:
	cat in/test[nr].in
	Folderul 'out' este creat de fiecare data cand scriptul pentru testarea
	algoritmilor este rulat.
	Pentru a vedea rezultatele unui test anume (cu fisierul corespondent
	test[nr].in), se poate folosi comanda:
		cat out/test[nr].out

Pachete necesare testarii:
	- java
	- javac

Instructiuni de utilizare a scriptului:
	Rolul scriptului este de a sterge rezultatele anterioare si de a crea din nou
	rezultatele pentru fiecare test in parte.
	Scriptul se numeste 'checker.sh' si s-ar putea sa aiba nevoie de drepturi de
	executie pe masina curenta:
		sudo chmod a+x checker.sh
	Rularea lui se face folosind:
		./checker.sh

		!<
		! ATENTIE ! -> s-ar putea ca instructiunile prezente in functia
		function cleanOutDir() {
		  rm -rf out
		  mkdir out
		}
		sa aiba nevoie de aprobare de tip administrator.
		In acest caz, rularea scriptului se face folosind:
		sudo ./checker.sh
		Am avut problema aceasta la un moment dat si, desi acum nu mai este prezen-
		ta, m-am gandit sa mentionez acest aspect pentru a evita eventualele
		probleme.
		>!

Instructiuni de utilizare a Makefile-ului:
	Makefile-ul poate fi folosit pentru a compila tema manual si a obtine execu-
	tabilul cu scopul testarii algoritmilor pe un pattern si un text primite in
	linia de comanda.
	Pentru compilare se foloseste:
		make build
	Pentru rularea unui test manual se foloseste:
		java Main manual "[pattern]" "[text]"
	Programul va afisa la stdout rezultatele rularii testului.
	Pentru a rula un test manual dintr-un fisier anume se foloseste:
		java Main test "[cale_input]" "[cale_output]"
	Pentru a restabili structura temei se foloseste:
		make clean

Observatii:
	Am folosit functia Bernstein deoarece este printre cele mai perfomante functii
	de hashing atat din punct de vedere al timpului, cat si de securitate (in
	cazul altor aplicatii). Am folosit in trecut o functie de hashing mai
	complicata, de forma:
	hash_i	= hash_i-1 + (array[i] - 96) * (prime ^ i)
	unde prime este un numar prim, de exemplu 3.
	Valoarea hash de mai sus poate fi recalculata folosind rolling hash in felul
	urmator:
	newValue = ((oldValue - (oldChar - 96)) / prime)
	+ prime ^ (pattern_length - 1) * (newChar - 96)
	unde oldChar este primul caracter din fostul array de lungimea patternului
	din text, iar newChar este caracterul care se adauga la array.
	Aceasta abordare doar ar fi complicat implementarea atat din punctul de vedere
	al sintaxei, cat si al perfomantei.
	In crearea testelor am incercat sa fiu cat mai variat pentru a intelege cat
	mai bine comportamentul algoritmilor in speta, asa ca am inclus de la carti
	intregi ("Hobbitul" - copiat de 2 ori pentru ca parea cam scurt, multiple
	carti ale lui Jules Verne in acelasi test, "Povestea lui Harap-Alb" si altele)
	pana la primul milion de zecimale ale lui pi, sau un sir de zeci de milioane
	de numere generate random.

! Disclaimer !
	In anumite cazuri, rularea algoritmului Rabin-Karp cu functia ineficienta se
	aseamana foarte mult cu cea eficienta, chiar fiind mai rapida in anumite
	teste. Acest fapt poate avea mai multe cauze:
		- Cauza principala este faptul ca pattern-ul este de o lungime mica ->
		Faptul ca folosind functia ineficienta se parcurge efectiv toate grupurile
		de lungimea pattern-ului prezente in text nu face nicio diferenta, sau
		aproape niciuna.
		- Functia Bernstein are si o inmultire pe langa adunarea pe care o are si
		cealalta functie.
	Din nou, acest aspect se modifica la fiecare rulare a testelor datorita
	perfomantelor de moment ale masinii.
	De asemenea, acest aspect apare din ce in ce mai putin cu cat dimensiunea
	textului este mai mare. Asta deoarece creste diferenta dintre a parcurge
	pattern-ul doar cand valoarea hash Bernstein este aceiasi pentru doua
	siruri de caractere si atunci cand se parcurge pattern-ul efectiv la fiecare
	pas din parcurgerea textului.
	Nu exista o descriere clara a acestui comportament, dar reprezinta o caracte-
	ristica secundara interesanta a algoritmilor utilizati.
