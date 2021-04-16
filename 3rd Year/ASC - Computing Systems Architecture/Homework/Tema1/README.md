# Arhitectura Sistemelor de calcul - Tema 1 - Marketplace, Martie 2021

# Enunt
http://ocw.cs.pub.ro/courses/asc/teme/tema1

# Testare


* Folositi scriptul run_tests.sh.
* Schimbați înainte de a îl rula variabila PYTHON din interiorul lui cu path-ul de pe sistemul vostru
* Fișierele de input și output-referință se află în directorul tests/
   * tot în acest director se generează și fisierul output al rulării temei folosind test.py
* Pentru a verifica partea de code-style, trebuie să aveți instalat pylint
   * am oferit în schelet fișierul pylintrc cu configurarea acestui tool
   * puteți da comanda pylint pe sursele voastre sau să decomentați linia pentru pylint din scriptul run_tests.sh

Directorul test-gen conține scripturi pentru generarea testelor.

* README_TESTS - descrie formatul json al fișierelor de intrare
* test_generator.py - generează fișierele aferente unui test
* test_utils.py - constante utilizate în test_generator
* generate_tests.sh - generează cele 10 teste oferite în schelet și pentru care se va oferi punctajul temei

Puteți să testați tema și pe teste proprii create folosind scriptul test_generator.py

Informații despre conținutul fișierelor de intrare/ ieșire se regăsesc [aici](https://bitbucket.org/ASC-admin/asc/src/master/assignments/1-marketplace/skel/test-gen/README_TESTS.md).