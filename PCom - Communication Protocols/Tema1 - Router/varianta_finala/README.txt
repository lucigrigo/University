--------------------------------------------------------------------------------
                        Protocoale de Comunicatii
                            Tema 1 - Router
                        Grigore Lucian-Florin 324CD

--------------------------------------------------------------------------------

    Descrierea implementarii:

    Construirea tabelelor de rutare:
Pentru implementarea celor doua tabele, cea de rutare si cea arp, am utilizat
un arbore de tip TRIE, folosi si in practica la asa ceva. Este bazat pe folosi-
rea unui arbore binar in functie de bitul curent din prefix (rtable) sau din
adresa ip (arp table). Cele doua functii de care am avut nevoie au fost cea
de inserare si cea de cautare in tabela. Pentru rtable am folosit prefixul la
inserare si de (current_prefix == search_address & current_mask) la cautare. In
cadrul unui nod din arbore, pot exista mai multe, una singura sau nicio intrare
de rutare. Intrarile care au acelasi prefix sunt retinute in acelasi nod, sor-
tate descrescator dupa masca (folosind quick sort). Astfel, intrarea cu masca
cea mai mare e chiar prima din nod. Pentru tabela arp, procesul este similar.
Inserarea si cautarea le fac dupa o valoarea uint32_t a adresei ip. In acest
caz, nu mai exista noduri cu mai multe intrari corespondente, adresele fiind
unice. In ambele cazuri, nu am facut nicio conversie de la network byte order
la host byte order pentru ca as fi facut un numar de operatii aditionale si la
convertirea inversa fara vreun rost. In acest fel, cei doi arbori utilizeaza
network byte order.

In functia main, incep prin a parsa tabela de rutare. Dupa, in bucla infinita,
pachetele urmeaza urmatorii pasi:

    Daca sunt de tip IP:
    - vad ce tip de pachet este. Daca este destinat ruterului, verific daca este
de tip ICMP ECHO. Daca da, ii raspund. Daca nu, il arunc. Daca nu este destinat
ruterului, urmeaza procesul normal de forwarding.
    - daca trebuie trimis raspuns, pachetul este trimis inapoi cu anumite
campuri modificate si cu tipul icmp ICMP_ECHOREPLY
    - daca trebuie forwarduit, functia trece prin procesul de forward. Ii este
verificat checksum-ul, ttl-ul si se cauta urmatorul hop. Daca una din aceste
verificari pica, este trimis inapoi mesajul de eroare corespunzator (destination
unreachable, time exceeded sau pachetul este aruncat daca are checksum gresit)
    - daca trece de aceste verificari, se cauta in tabela arp adresa ceruta
    - daca este gasita, pachetul este forwarduit
    - daca nu, pachetul este memorat intr-o lista de pachete si se trimite un
arp request catre adresa destinatie

    Daca sunt de tip ARP:
    - daca este ARP REPLY, se insereaza in arborele de rutare arp adresa nou
obtinute si se cauta printre pachetele on hold daca este vreunul ce trebuie
trimis
    - daca este ARP REQUEST, se trimite un ARP REPLY catre adresa sursa cu date-
le ruterului


    Observatii:
--------------------------------------------------------------------------------
