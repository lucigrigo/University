/*
    Proiectarea Algoritmilor
    Laborator 6
    Grigore Lucian-Florin
    324CD semigrupa b
*/

#include <stdio.h>
#include <stdlib.h>

// functia care afiseaza o permutare (problema 1)
void afisare_permutare(int v[], int n) {
  int j;
  for (j = 0; j < n; j++) {
    // afisare element din permutare
    printf("%d ", v[j]);
  }
  printf("\n");
}

// functia care verifica daca o solutie generata este o permutare valida
int validare_permutare(int poz, int v[], int n) {
  int j;
  for (j = 0; j < n; j++) {
    // verifica daca cumva in vector exista un element egal cu cel de pe
    // pozitia curenta; daca da, atunci nu e o permutare valida
    if (j != poz && v[j] == v[poz]) {
      return 0;
    }
  }
  return 1;
}

// functia care genereaza toate permutarile unei multimi de o dimensiune data
void permutari(int n) {
  int max = n;      // valoarea maxima din vector
  int init_val = 0; // valoarea initiala
  int v[n];         // vectorul de solutii
  int i;            // iterator
  int val = 1;      // valoarea de incrementare

  // initializare elemente din vector cu valorea initiala
  for (i = 0; i < n; i++) {
    v[i] = init_val;
  }

  i = 0;
  // inceput backtracking
  while (i >= 0) {
    int valid = 0;
    while (valid == 0 && v[i] <= max) {
      // generez valori pentru pozitia curenta
      v[i] += val;
      // verific daca solutia generata partial este valida
      valid = validare_permutare(i, v, n);
    }
    // daca este valida generarea
    if (v[i] <= max) {
      if (i == (n - 1)) {
        // daca am ajuns pe ultima pozitie, afisez solutia
        afisare_permutare(v, n);
      } else {
        // daca nu, trec la urmatoarea pozitie
        i += 1;
      }
    } else {
      // daca nu este valida, ma intorc in vector
      v[i] = init_val;
      i -= 1;
    }
  }
}

// functia care se ocupa de afisarea unei submultimi a unui vector
// la un pas anume din desfasurarea algoritmului
void afisare_submultime(int v[], int n, int max) {
  int i;
  for (i = 0; i < n; i++) {
    if (v[i] == max) {
      // daca gasesc un element care este "1" (max), ii afisez
      // valoarea corespunzatoare
      printf("%d ", i + 1);
    }
  }
  printf("\n");
}
// functia care verifica ca o submultime este generata corect
// in acest caz, returneaza mereu 1 (nu avem conditii de generare pentru
// solutiile partiale)
int validare_submultime(int poz, int n, int v[], int init_val) { return 1; }

// functia care foloseste backtracking pentru generarea submultimilor
void submultimi(int n) {
  int init_val = -1; // valoarea initiala
  int max = 1;       // valoarea maxima
  int v[n];          // vectorul solutie
  int i;             // iterator
  int val = 1;       // valorea de incrementare

  // initializare vector cu valoarea initiala
  for (i = 0; i < n; i++) {
    v[i] = init_val;
  }

  i = 0;
  // start backtracking
  while (i >= 0) {
    int valid = 0;
    while (valid == 0 && v[i] <= max) {
      // generare valori pentru pozitia curenta din vector
      v[i] += val;
      // verificare daca solutia partial generata este corecta (in acest
      // caz, mereu este corecta)
      valid = validare_submultime(i, n, v, init_val);
    }
    // daca este valida generarea
    if (v[i] <= max) {
      // daca sunt pe ultima pozitie
      if (i == (n - 1)) {
        // afisez submultimea generata
        afisare_submultime(v, n, max);
      } else {
        // trec pe urmatoarea pozitie daca nu am ajuns inca la final
        i += 1;
      }
    } else {
      // daca solutia nu este valida pentru nicio valoare, ma intorc in vector
      v[i] = init_val;
      i -= 1;
    }
  }
}

// functia care se ocupa de afisarea unei solutii pentru problema damelor
// afisarea este de tipul (index_linie,index_coloana)
void afisare_dame(int v[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("(%d,%d) ", i, v[i]);
  }
  printf("\n");
}

// functia care se ocupa de verificarea ca o solutie partiala generata
// este valida in cadrul problemei reginelor
int validare_dame(int v[], int n, int poz) {
  int i;
  for (i = 0; i <= poz; i++) {
    int j;
    for (j = 0; j <= poz; j++) {
      // verific daca pentru un element din vector care nu este cel de la
      // pasul curent din algoritm "reginele se ataca", adica daca
      // sunt pe aceeasi linie sau aceeasi coloana sau pe aceeasi diagonala
      // conditie linie -> mereu ok pentru ca indicii i si j sunt diferiti
      // conditie coloana -> verific daca v[i] == v[j]
      // conditie diagonala, verific daca |i-j| == |v[i]-v[j]|
      if (i != j && ((abs(j - i) == abs(v[j] - v[i])) || (v[i] == v[j]))) {
        return 0;
      }
    }
  }
  return 1;
}

// functie care utilizeaza backtracking pentru a genera solutiile
// pentru problema reginelor
void problema_damelor(int n) {
  int init_val = -1; // valoarea de initializare
  int max = (n - 1); // valoarea maxima
  int val = 1;       // valoarea de incrementare
  int i;             // iterator
  int v[n];          // vectorul solutie

  // initializare vector solutie cu valoarea initiala
  for (i = 0; i < n; i++) {
    v[i] = init_val;
  }

  i = 0;
  // start backtracking
  while (i >= 0) {
    int valid = 0;
    while (valid == 0 && v[i] <= max) {
      // generez valori pentru pozitia curenta din solutie
      v[i] += val;
      // verific daca regina nou amplasata se ataca cu vreuna amplasata anterior
      valid = validare_dame(v, n, i);
    }
    // daca solutie este valida
    if (v[i] <= max) {
      // daca sunt pe ultima pozitie
      if (i == (n - 1)) {
        // afisez solutia
        afisare_dame(v, n);
      } else {
        // daca nu sunt pe ultima pozitie, inaintez in vector
        i += 1;
      }
    } else {
      // daca solutia nu este valida, ma intorc in vector
      v[i] = init_val;
      i -= 1;
    }
  }
}

// functia main
int main() {
  int n = 3;
  // 1. permutari
  printf("\n--- 1. PERMUTARI ---\n");
  permutari(n);
  // 2. problema submultimilor
  printf("---\n\n--- 2. SUBMULTIMI ---");
  submultimi(n);
  // 3. problema damelor
  printf("---\n\n--- 3. PROBLEMA DAMELOR ---\n");
  int m = 4;
  problema_damelor(m);
  printf("---\n\n");
  return 0;
}
