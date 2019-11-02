==================================>README<===================================

                    CURS : PROGRAMAREA CALCULATOARELOR
                    Tema 2 - Formatare text
                    Grupa : 314CD
                    Nume si prenume : Grigore Lucian-Florin


Descrierea metodei de rezolvare :


  Pentru citire am "formatat" comanda ( am eliminat spatiile in plus ) si am
  pus fiecare instructiune intr-o linie dintr-o matrice. Parcurgand matricea,
  cu strtok am luat fiecare argument despartit de spatiu. In functie de primul
  caracter (W,L,O,i etc.), am luat fiecare parametru transmis (list_type etc.)
  , apeland functia corespunzatoare. De asemenea, am testat daca vreunul este
  invalid, sau unul care trebuie neaparat transmis nu se regaseste in comanda.

  Pentru wrap (probabil m-am complicat putin, dar merge :) ), am spart matricea
  initiala (o copie a ei) cu strtok in cuvinte si am asezat cuvintele pe
  liniile unei matrice noi, respectand wrapLength. Inainte de apelarea
  functiei, testez daca wrap length este mai mare decat lungimea celui mai
  lung cuvant din text.

  Pentru allign left am mutat caracterele de pe fiecare rand la stanga atat
  timp cat primul caracter este un spatiu.

  Pentru allign right am mutat caracterele de pe fiecare rand la dreapta pana
  cand lungimea randului este egala cu lungimea celui mai lung rand din fisier.

  Pentru center am calculat diferenta dintre lungimea randului curent si
  lungimea celui mai lung cuvant si am adaugat la inceput un numar de spatii
  egal cu jumatate din acea diferenta.

  Pentru justify, am facut intai allign left pentru toate liniile. Cu exceptia
  ultimei linii din fisier si a ultimei linii din fiecare paragraf, am adaugat
  spatii progresiv pentru fiecare linie. Prin progresiv vreau sa spun ca am
  adaugat un spatiu (incepand de la inceputul liniei) la fiecare spatiu
  intalnit, facand asta de mai multe ori, daca a fost necesar.

  Pentru paragrafare am adaugat numarul cerut de spatii la inceputul fiecarui
  paragraf, testand daca linia precedenta este goala ('\n'), sau daca este
  prima linie din fisier sau daca startLine si endLine sunt egale.

  Pentru liste (si simple si ordonate) am creat functii diferite pentru
  fiecare lista : numbered, alphabetical sau bullet. Acestea mutau caracterele
  la dreapta de pe fiecare rand ca sa creeze spatiu la inceput, adaugand apoi
  indicele (daca era vorba de una din primele doua), special character-ul
  comunicat in comanda si un spatiu liber. De asemenea, pentru listele ordonate
  am creat 2 functii pentru sortare (una lexicografica si una invers lexico-
  grafica), care folosesc bubble sort (am incercat sa le fac folosind qsort,
  dar nu mi-a mers functia de comparare pe care o facusem :( ).

  Am mai creat alte functii care sa indeplineasca diferite task-uri, cum ar fi
  calcularea lungimii celei mai lungi linii, calcularea lungimii celui mai
  lung cuvant, tratarea cazurilor de "Invalid operation!" si "Cannot wrap!",
  eliminarea trailing whitespace-urilor de pe fiecare linie, aplicarea
  indentarii asupra unei linii, formatarea comenzii primite, returnarea
  indicelui caracterului '\n' de pe un rand anume (pretty much ce face
  strlen(), dar am scris-o la inceput ca sa fiu sigur ca stiu perfect cum
  functioneaza si ce trebuie sa fac eu dupa. Si chiar daca la final am vrut
  sa o sterg, am zis ca nu strica daca folosesc atat functia asta, cat si
  strlen() ). De asemenea, la inceput am definit un tip boolean pentru ca ma
  asteptam sa fie unul deja (mi-a fost mai usor in anumite locuri sa tratez
  anumite cazuri folosind true/false decat 1/0).

  Pentru functii precum allign left, allign right, center sau wrap poate
  abordarea mea nu a fost cea mai simpla, dar prin aceasta am simtit ca am
  mai mult control asupra codului si asupra tot ce am scris in el, cat si
  asupra functionalitatii acestuia.
