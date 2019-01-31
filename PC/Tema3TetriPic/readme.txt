===================================README======================================

                  Curs : Programarea Calculatoarelor
                          Tema 3 - TetriPic
                  Nume si Prenume : Grigore Lucian-Florin
                  Grupa : 314CD

===============================================================================

Link enunt: https://ocw.cs.pub.ro/courses/programare/teme_2018/tema3_2018_cbd

===============================================================================

Descrierea rezolvarii:

      TASK 1: Am reprezentat BitMap-ul ca un vector de pixeli (de structuri de
tip pixel). Am colorat intre anumiti indici cu culoarea (valorile RGB) core-
spunzatoare fiecarui tip de piesa. Din cauza ca am folosit un vector (nu ma
intrebati de ce, probabil ganduri suicidale), indicii nu sunt prea (deloc)
frumosi, dar macar sunt corecti :). In cazul in care a trebuit sa adaug padding
pentru o imagine, cand am facut scrierea fisierului [.bmp], la finalul fiecarei
linii am adaut acel PaddingPixel care ocupa 2 biti.

      TASK 2: Similar cu ce am facut la task-ul 1, am folosit un vector pentru a
reprezenta imaginea BitMap. Am incercat sa grupez in functii ca sa fie mai usor
de urmarit crearea pieselor care se aseamana (in afara de cele care au unele
rotatii identice).

      TASK 3: Pentru a simplifica rezolvarea, am asociat BitMap-ului o matrice
de char-uri care permite o urmarire si o desfasurare mai usoara a jocului pro-
priu-zis. Fiecarui caracter din matricea de char-uri ii corespunde un patrat
(10px x 10px) din BitMap. Initial, tabela de char-uri contine 'N' pentru partea
neagra si 'A' pentru cea alba. Pentru plasarea fiecarei piese se fac verificari
astfel incat regulile jocului nu sunt incalcate. Dupa pozitionarea unei piese
se verifica daca exista anumite linii complete, acestea fiind eliminate. Dupa
terminarea pieselor, sau daca jocul este intrerupt inainte, se coloreaza
BitMap-ul (de data aceasta, sub forma unei matrici) corespunzator formei
matricei de char-uri. Pasul final este de a scrie fisierul [.bmp] corespunzator
BitMap-ului rezultat.

      TASK 4: Singura diferenta fata de task-ul 3 este faptul ca matricea de
char-uri initiala nu contine doar 'N' si 'A'. Pentru fiecare patratel ocupat de
o parte dintr-o piesa din BitMap-ul citit, se pune in matrice litera corespun-
zatoare piesei respective. De la acel punct incolo, au loc aceiasi pasi ca la
task-ul 3.

      TASK BONUS: Avand in vedere ca de la task-urile anterioare aveam cateva
functii care sa ma ajute la simplificarea problemei (citirea imaginii, tran-
sformarea imaginii intr-o matrice de char-uri), singurul lucru pe care am avut
sa il fac a fost sa identific fiecare piesa cu rotatia si pozitia ei. Pentru a
face asta, am parcurs matricea pe fiecare linie pana am gasit un caracter care
indica gasirea unei piese. Pentru a determina rotatia acesteia, am avut nevoie
de unul (piesa O), doua (piesele S, Z, I) sau trei (piesele L, J, T) teste
referitoare la patratelele adiacente si la felul in care acestea se gasesc.
Dupa gasirea unei piese, am colorat cu negru - 'N' - zona ocupata de aceasta
pentru a evita citirea aceleiasi piese de mai multe ori. Am pus informatiile
legate de toate piesele intr-un string de char-uri, pe care la final il scriu
in fisierul de output.

===============================================================================
