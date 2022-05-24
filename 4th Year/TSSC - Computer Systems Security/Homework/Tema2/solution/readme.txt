=== Testarea Securitatii Sistemelor de Calcul
=== Tema 2
=== Grigore Lucian-Florin - 343C4

--- Task 1
Am vazut ca exista un script pentru tunelare. Pentru a afla alte ip-uri din
retea am folosit comanda "nmap -sT -O IP_SERVER.0/24", astfel vazand ca 
exista un host care nu era nici cel de teme, nici cel de mysql. Am vazut
ca are si un port http deschis (80), asa ca i-am folosit ip-ul si portul
in scriptul de tunelare pe localhost:8080. Astfel am ajuns la pagina de
login. Dupa logare, am dat un ctrl+f pe 'speish', astfel gasind primul flag.

SpeishFlag{G4qMWTy0lF0kDTUn4aK8hyoFdnbaGv29}

--- Task 2
Pentru acest task am lasat scriptul de tunelare sa ruleze in background si am
captat traficul pe interfata containerului folosind 'tcpdump -i eth0'. Astfel,
am vazut ca se intampla niste Request + Response pe mai multe porturi locale.
Dupa ce le-am incercat pe toate, am ajus sa ascult folosind "nc -l" portul 
8385. Astfel, am primit mesajul de la gardian, continand username-ul si parola
pentru el. Dupa ce m-am logat, am vazut o imagine funny :) (printre altele),
in care era ascuns flag-ul pentru acest task.

username=guard
password=db2456fc70
SpeishFlag{r7XTEeT4o7YTZcywUpjnvORPmJKatIWT}

--- Task 3
M-am folosit de hint-urile oferite si dupa putina documentare pe internet,
mi-am creat scriptul "xss_phishing.txt" (prezent in arhiva), care executa fix
un atac de tipul XSS. Astfel, m-am putut loga ca decan si am dat un ctrl+f pe
'speish' in Inspect pe pagina de Home pentru a gasi flag-ul.

user=dekhan
pass=8e93f6eabc
SpeishFlag{YLsGf6BRBHOyLjJ6vvjvPRX781zeo94y}

--- Task 4
Folosindu-ma de output-urile botului de chat, am banuit ca rectorul este
persoana cu ID-ul 1. Astfel, am schimbat parola contului, dar, din greseala,
primele dati am schimbat si username-ul. Astfel, m-a luat ceva pana sa ma
prind ca probabil flag-ul apare doar daca las username-ul original (rekt0r).
Dupa ce l-am schimbat inapoi, am vazut ca background-ul este negru, nu alb.
Astfel, pe pagina de Admin, am gasit flag-ul folosind aceeasi cautare ca la
task-ul anterior. PS: stiu ca apareau si in consola, insa parca e mai
satisfying sa le gasesc in cod HTML :D

noua parola va fi
sha1(student)=204036a1ef6e7360e536300ea78c6aeb4a9333dd
rector_original_password=571505dff6
SpeishFlag{GkamaR7roT15xgRm5bIecEYkUERfFjJ9}

--- Task 5
Pentru acest ultim flag, m-am folosit de posibilitatea de a urca fisiere pe
site. Si dupa niste cautari pe internet, am gasit ca pot face asa ceva:
https://medium.com/codex/bypass-file-upload-restrictions-f30c88e1fccb.
Astfel mi-am creat scriptul "script.sh" (prezent in arhiva). Dupa o cautare
in sursa HTML, am vazut ca la apelarea "Fix em'", se executa un script
aflat la o cale definita static. Deci dupa modificarea acelei cai pentru
a executa script-ul meu, am reusit sa gasesc locatia lui "/bin/bash".
Exploit-ul a functionat cu:
"../../../../../bin/sh /var/www/userupload/posts/script.sh" si in terminal
mi-a aparut ultimul flag.

SpeishFlag{X3hbgK2CWiZHZi05XaoTgVQnwENYH5kh}
