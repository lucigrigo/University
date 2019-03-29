================================== README =====================================

                            CURS: Metode Numerice
                                   Tema 1
                            Grigore Lucian-Florin
                                   314CD

===============================================================================

Descrierea modului de rezolvare a problemei:

Task1: Citirea numarului de puncte am folosit functia 'load', iar pentru citi-
rea variabilei NC am folosit o citire asemenatoare cu cea din C (fscanf).

Task2: Pentru rezolvarea algoritmului, pur si simplu am urmarit pasii indicati
in enuntul temei, facand o asociere cu modalitatile de rezolvare din C. In plus,
m-am documentat cu privire la anumite functii din Matlab/Octave (norm, mean) si
cu privire la anumite aspecte ale sintaxei care usureaza munca (selectarea mai
multor valori dintr-un vector cu o singura comanda).

Task3: Am realizat impartirea punctelor in functie de centroidul de care apartin
folosind un vector care sa indice, pentru fiecare punct, indicele centroidului
de care apartin (in acelasi cluster). Dupa aceea, am colorat punctele aferente
fiecarui centroid intr-o culoare diferita (am ales culorile verde, albastru si
magenta :) ), folosind un vector temporar pentru fiecare vector de puncte, cu
functia scatter3.

Task4: Am realizat aceeasi impartire in functie de centroizi ca la task-urile
precendente si dupa pur si simplu am adunat distantele de la fiecare punct la
centroidului corespondent ca sa obtin costul final.

Task5: Am apelat functiile clustering_pc si compute_cost_pc ca sa obtin centro-
izii si costurile in fiecare caz, adica de la 1 la 10 NC pentru aceleasi puncte.
Dupa am folosit plot ca sa desenez graficul cerut cu valorile din vectorul cu
costuri construit la fiecare iteratie.

Probleme intampinate: Dificultati in privinta intelegerii 100% a sintaxei speci-
fice Matlab/Octave si a functiilor precum norm, mean, scatter3 sau plot, difi-
cultati intampinate doar la inceput. Insa nu am intampinat vreo problema care sa
fie prea severa sau care sa nu fie rezolvata cu putina documentare de pe inter-
net.

Am mai adaugat si anumite comentarii prin codul scris de mine care sa clarifice
si eventualele neintelegeri care pot aparea.
