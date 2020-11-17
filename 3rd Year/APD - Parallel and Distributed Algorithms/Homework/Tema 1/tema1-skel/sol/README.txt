==================    Grigore Lucian-Florin
==================    Grupa 336CA
==================    Algoritmi Paraleli si Distribuiti
==================    Tema 1

================== Descrierea implementarii
    Unele functionalitati oferite in schelet le-am scris din nou, dar am
pastrat aceleasi instructiuni, cum ar fi:
    - get_args()
    - read_input_file()
    - write_output_file()
    - alloc_mem()
    - free_mem()
    - structura pentru reprezentarea unui numar complex
    - structura pentru memorarea parametrilor de intrare pentru fiecare fractal

    Executia programului incepe in main(), care, in afara de citirea
argumentelor programului, executa:
    - initializarea si dezalocarea barierei folosite in rezolvare
    - pornirea si asteptarea executiei thread-urilor

    Marea parte a rezolvarii cerintei are loc in functia f_thread(), care
executa, in ordine, urmatorii pasi:
    - doar pentru primul thread (thread_id = 0), citeste fisierul de intrare
    pentru Julia, calculeaza inaltimea si latimea imaginii, memoreaza datele si
    aloca memorie pentru memorarea calculelor
    - se asteapta la o bariera terminarea acestor pasi pe primul thread din 
    partea tuturor thread-urilor
    - pentru toate thread-urile, imparte calculele pe latime, adica primul for
    din rezolvare nu va merge 0:width, ci de la niste indici w_start:w_end,
    calculati pentru fiecare thread in parte
    - o bariera intre calcule si transformarea dintre coordonatele matematice
    si ecran
    - bariera pentru sincronizarea tuturor thread-urilor
    - doar pentru primul thread, scrie rezultatele calculului in fisier si 
    elibereaza memoria alocata dinamic pentru Julia
    Acesti pasi sunt repetati, in continuare, in cadrul aceleiasi functii, si
pentru Mandelbrot.

================== Precizari
    Am incercat in mai multe feluri sa paralelizez cerinta data, dar in modul
descris mai sus am obtinut cea mai buna scalabilitate.
    Prima varianta incercata a fost sa paralelizez fiecare thread ori pentru
Julia, ori pentru Mandelbrot. In cazul unui numar impar de thread-uri, Julia
ar fi avut unul in plus. Dar aceasta abordare are multe minusuri, cum ar fi:
numar inegal de thread-uri/fractal in unele cazuri, numar inegal de calcule 
per fractal (incetinirea unor thread-uri), folosirea a doua bariere in loc de
una singura; daca era specificat un singur thread, Mandelbrot nu ar fi fost
calculat deloc.
    A doua varianta pe care am vrut sa o implementez presupunea sa execut 
calculele pentru cei doi fractali intercalat, astfel incat citirea si scrierea
ambelor fractali erau la inceput si, respectiv, finalul functiei de thread.
Intre citiri si scrieri ar fi fost aceleasi calcule paralelizate si aceleasi
transformari, doar ca nu executate secvential, ci ambele calcule si ambele 
transformari distantate de o singura bariera. Sincer, nu cred ca rezultatele ar
fi diferit prea mult, doar ca, dupa parerea mea, codul ar fi fost mai greu de
urmarit si nu mult mai eficient, daca nu chiar deloc.