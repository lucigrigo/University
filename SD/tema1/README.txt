================================ README ======================================

                        CURS: STRUCTURI DE DATE
                                TEMA 1
                        Grigore Lucian-Florin
                                314CD

================================ README ======================================

                  Descrierea modului de rezolvare a cerintei

Pentru rezolvarea primei cerinte am urmarit urmatoarele aspecte:
  - pentru initializarea cluburilor am luat separat adaugarea primului club
  din lista, si dupa, pe rand, a celorlalte cluburi.
  - pentru adaugarea unui club la o lista de cluburi doar am legat clubul nou
  alocat la lista deja existenta.
  - pentru adaugarea unui jucator la o lista de jucatori am alocat memorie
  pentru jucator si numele lui, si dupa pur si simplu l-am legat la finalul
  listei de jucatori. Pentru a mentine ordinea jucatorilor asa cum trebuie,
  am creat o functie de sortare a acestora in functie de criteriile cerute,
  care este apelata ori de cate ori lista este modificata.
  - am creat o functie de adaugare a playerilor la cei accidentati, pentru a
  usura mutarea acestuia in cazul unei accidentari.
  - transferarea unui player am realizat-o mutand pointerul aceluiasi jucator
  (puteam sa ma folosesc si de functia de add_player(), dar nu stiu de ce
  am abordat transferarea astfel, asa ca am lasat-o asa pana la final) de la
  lista de jucatori de la old_club la cea care apartine de new_club. Lista de
  jucatori a noului club va fi resortata.
  - eliminarea unui jucator a presupus cautarea pointerului catre jucatorul
  care se doreste eliminat (daca el exista), elibarea memoriei ocupate, dar si
  refacerea legaturilor jucatorului precedent sau urmator, plus cazurile sepa-
  rate cand este primul jucator din lista sau ultimul sau singurul.
  - functiile de update_score sau update_game_position le-am abordat in aceeasi
  maniera: am cautat jucatorul care trebuie modificat. In cazul in care este
  gasit, i se modifica atributele si dupa este resortata lista de care el
  apartine.
  - pentru tratarea situatiei cand un jucator se accidenteaza: il caut in lista
  de jucatori a clubului, ii modific atributul injured, refac legaturile din
  jurul lui si il adaug in lista de jucatori accidentati. Functia de recover
  from injury face exact aceleasi operatii, dar in sens invers.
  - functiile de dezalocare au urmat aceiasi pasi: elibereaza atributele
  pointerului care au fost alocate, memoreaza in alt pointer adresa urmatorului
  element si dupa elibereaza elementul curent.

Pentru rezolvarea cerintei doi am implementat urmatoarele aspecte:
  - in fiecare dintre functii, cu exceptia la get_best_player, am creat un club
  fictiv ca sa pot folosi functiile implementate la primul task pentru adau-
  garea jucatorilor in lista si sortarea acesteia dupa diferite criterii.
  - la union_teams am adaugat in aceeasi lista jucatorii ambelor echipe (daca
  amandoua exista; sau doar a unuia; am intors NULL daca niciun club nu exista);
  dupa am sortat lista dupa criteriile din cerinta.
  - la get_top_players am adaugat in aceeasi lista cei mai buni N jucatori sau
  toti, daca sunt mai putini de N. Pentru a-i selecta pe cei mai buni am sortat
  lista de jucatori a clubului din lista descrescator dupa scor (am restabilit
  ordinea normala a listei dupa selectarea celor mai buni jucatori).
  - pentru functiile get_players_by_position si get_players_by_score am adaugat
  in lista finala toti jucatorii care indeplinesc criteriile aferente (de scor
  sau de pozitie)
  - pentru functia get_best_team am creat o lista comuna cu toti jucatorii de
  la toate cluburile, din care am selectat pe cei mai buni pentru a forma cel
  mai bun 11
  - pentru functia get_best_player am creat un nou element de tip Player care
  sa memoreze toate atributele celui mai bun jucator gasit pentru pozitia ceruta

Precizari:
  - in loc de sortarea jucatorilor de fiecare data cand se adauga unul nou,
  neaccidentat sau accidentat, as fi putut sa il adaug de prima data in locul
  potrivit din lista, dar m-am simtit eu mai confortabil cu un numar de functii
  de sortare dupa diferite criterii (scor, nume, pozitie etc.)
  - in functiile transfer_player si remove_player am un numar de linii de cod
  care se repeta: cele legate de refacerea legaturilor cu ceilalti jucatori,
  dar si reciproc dupa scoaterea unui jucator din lista. Acelasi lucru am si la
  functiile recover_from_injury si add_injury, referitor la acelasi aspect al
  eliminarii elementului din lista. Probabil as fi putut modulariza putin aceste
  doua parti din cod.
  - mi-as fi putut face si o functie de cautare a unui jucator ca sa scap de a
  scrie mereu aceeasi parte in anumite functii
  - mi-am creat o functie de updateStatus care sa modifice starea injured a
  unui jucator (am folosit-o doar la cerinta2, unde am vrut sa am in aceeasi
  lista si jucatori accidentati, si jucatori neaccidentati)
