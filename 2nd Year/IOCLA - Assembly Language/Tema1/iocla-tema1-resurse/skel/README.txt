Introducere in Organizarea Calculatoarelor si Limbaj de Asamblare
Tema 1 – Prefix AST
Grigore Lucian – Florin, 324CD
Facultatea de Automatica si Calculatoare
Universitatea Politehnica, Bucuresti


	Descrierea implementarii:
      Pentru rezolvarea temei am considerat ca este mai usor de calculat expresia data in sens 
invers (Reverse Polish Notation) intrucat se foloseste mai logic de stiva, in opinia mea, fiind si 
mai usor de urmarit. De asemenea, nu are nevoie de apeluri recursive de functii, iar codul este 
mai minimalist.
      Pasii care trebuie luati in considerare pentru aceasta rezolvare sunt urmatorii:
*	Calcularea lungimii inputului.
*	Parcurgerea de la final la inceput a inputului. 
*	Atunci cand gasim un numar, il punem pe stiva – push –  dupa ce il convertim din 
string in decimal.
*	Atunci cand gasim un operator, extragem primele doua numere de pe stiva – pop 
– si aplicam asupra lor operatorul gasit, punand la final rezultatul obinut pe stiva.
*	Dupa parcurgerea secventei de input, singurul element ramas pe stiva va fi 
rezultatul final al secventei de input.


Observatii:
*	Pe parcursul codului am folosit diferite variabile (index, indexTemp, var) in care 
sa retin anumite valori / adrese pentru ca aveam nevoie de cat mai multi registri 
liberi pentru operatii sau comparatii anume la acel moment de timp.
*	A trebuit sa introduc o testare suplimentara in labelul corespunzator operatiei de 
scadere deoarece la testarea initiala, care compara primul byte, atat semnul 
minus, cat si orice numar negative ar fi fost la fel.


