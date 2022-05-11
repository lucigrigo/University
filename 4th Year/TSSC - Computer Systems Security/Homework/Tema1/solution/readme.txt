--- Testarea Securitatii Sistemelor de Calcul
--- Tema 1
--- Lucian Grigore, 343C4

--- Task 1 ---

Folosind hint-urile din cerinta, mi-am dat seama ca al doilea hint pare a fi un link care incepe cu 'http www.' codat in cifrul lui Cezar. Dupa ce am folosit un decodor online, am confimat ca este cifrul lui Cezar, then I got rick rolled (ggwp), dupa care din celalalt hint am primit indicatia ca trebuie sa execut un RSA chosen cypher attack.

Din prima eroare primita de server, am vazut ca face un json.loads(base64.b64decode(...)) si atunci am realizat ca trebuie sa fac si eu asta pe fisierul message.txt. Astfel, am descoperit cheia de criptare, n-ul si flag-ul criptat. Am transformat flag-ul criptat in base64 si dupa in binar. L-am inmultit, conform teoriei atacului cu 2 ridicat la puterea 'e' si modulo 'n' din algoritm. Apoi i-am pasat acest nou json rezultat prin inversul operatiilor de decriptare serverului. Am luat rezultatul intors de server, l-am impartit la 2 si dupa am putut afla flag-ul.

Flag: SpeishFlag{oMi26bIJVya6PKl3kggOAP49ZeJEv9fY}

--- Task 2 ---
- not solved -

--- Task 3 ---

Am folosit Ghidra pentru a vedea objdump-ul executabilului pasat, cu tot cu functiile din C folosite la compilare. Am observat ca numele initial cerut nu are nicio importanta pentru exploit. Exploit-ul are loc in functia loop si flag-ul este printat in functia win. Dar pentru a putea ajunge la functia win, trebuie sa fac un buffer overflow in loop. Acolo se poate citi un array care contine 50 de numere intregi, dar care poate face overflow. Astfel, daca suprascriu adresa de intoarcere din functia loop cu adresa functiei win, pot ajunge la flag. Astfel, payload-ul pentru exploit contine 54 de numere intregi si dupa adresa functiei win in decimal.

Payload: 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 134514450

Flag: SpeishFlag{4dICBwvg4846tIwKkN1jlE7FlyfkmpPe}
