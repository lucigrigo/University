# Darius-Florentin Neatu <neatudarius@gmail.com>
# Copyright 2018

Rulare: ./check.sh help
	Usage:
		./check.sh                 # run the entire homework
		./check.sh task_id         # run only one problem (e.g. number or name)
		./check.sh cs              # run only the coding style check

Mentiuni:
	- Sursele + Makefile trebuie sa se afle in directorul curent.
	- Makefile-ul trebuie sa urmeze modelul din Makefile.template.

Legenda checker:
	- Run time error = eroare aparuta in timpul rularii unui test
	- TLE = time limit exceeded (s-a depasit limita de timp a testului curent)
	- WA = wrong answer (valoarea din fisierul .out difera de cea din .ref)

Timpi de executie problema $id:
	- C/C++: _utils/timeout/c.timeout$id

	-  Java: _utils/timeout/java.timeout$id

Checker coding style:
	- C/C++: _utils/coding_style/check_cpp.py
		- sursa: https://google.github.io/styleguide/cppguide.html

	-  Java: _utils/coding_style/check_java.jar
		- sursa: http://checkstyle.sourceforge.net/google_style.html

Exemplu debug:
	- rulare `./check.sh
	- rezultatul este WA la problema "gigel", pe testul 4
	- inspectare fisiere:
		- public_test/gigel/input/4-gigel.in   // input
		- public_test/gigel/out/4-gigel.out    // rezultatul solutiei studentului
		- public_test/gigel/ref/4-gigel.ref    // raspuns corect
