/*
                        Proiectarea Algoritmilor
                              Laborator 9
                      Grigore Lucian-Florin 324CDb
*/
#include <stdio.h>
#include <stdlib.h>
#define min(a, b) ((a) < (b) ? (a) : (b))

// graful folosit
int n = 10;    // numarul de noduri din graf
int G[10][10]; // graful

// variabilele folosite pentru punctele de articulatie
int low_art[10];     // low
int d_art[10];       // d
int art[10];         // art
int vizitat_art[10]; // c
int timp_art;        // variabila timp
int subarb_art[10];  // subarb
int p_art[10];       // p

// variabilele folosite pentru punti
int timp_punti;        // variabila timp
int vizitat_punti[10]; // c
int d_punti[10];       // d
int p_punti[10];       // p
int low_punti[10];     // low
int punte[10][2];      // punte
int nr_punti;          // nr de punti

// functia care realizeaza explorarea din nodul curent pentru alg. de
// determinare a pct. de articulatie
void exploreaza_art(int u) {
  d_art[u] = low_art[u] = timp_art++; // initializari
  vizitat_art[u] = 1;                 // il marchez ca vizitat
  int v;
  for (v = 0; v < n; v++) {             // parcurg nodurile
    if (G[u][v] == 1 || G[v][u] == 1) { // daca este vecin
      if (vizitat_art[v] == 0) {        // daca este nevizitat
        p_art[v] = u;                   // atribuire parinte nod nou
        subarb_art[u]++;   // actualizare nr subarbori dominati de u
        exploreaza_art(v); // il explorez
        low_art[u] = min(low_art[u], low_art[v]); // reactualizez low[u]
        if (p_art[u] != -1 && low_art[v] >= d_art[u]) {
          art[u] = 1; // cazul 2 al teoremei
        }
      } else if (p_art[u] != v) { // daca nodul curent nu este parintele
        low_art[u] = min(low_art[u], d_art[v]); // reactualizez low[u]
      }
    }
  }
}

void alg_tarjan() { // functia care determina punctele de articulatie din graf
  int i;
  for (i = 0; i < n; ++i) {
    p_art[i] = -1; // valoarea default pentru parinte
  }
  for (i = 0; i < n; ++i) {    // parcurgerea grafului
    if (vizitat_art[i] == 0) { // daca gasim un nod nevizitat
      exploreaza_art(i);       // exploram nodul
      if (subarb_art[i] > 1) { // verificare radacina subarb
        art[i] = 1;            // este punct de articulatie
      }
    }
  }
  // printare puncte de articulatie din graf
  int nr_art = 0;
  printf("punctele de articulatie sunt:\n");
  for (i = 0; i < n; ++i) {
    if (art[i] == 1) {
      nr_art++;
      printf("\t%d\n", i);
    }
  }
  printf("nr total pct de articulatie = %d\n\n", nr_art);
}

// functia care exploreaza un nod pt. alg. de determinare a puntilor
void exploreaza_punti(int u) {
  d_punti[u] = low_punti[u] = timp_punti++; // initializari
  vizitat_punti[u] = 1;                     // il marcam ca vizitat
  int v;
  for (v = 0; v < n; ++v) {             // parcurg nodurile din graf
    if (G[u][v] == 1 || G[v][u] == 1) { // daca este vecin
      if (vizitat_punti[v] == 0) {      // daca nu a fost vizitat
        p_punti[v] = u;                 // setez parintele
        exploreaza_punti(v);            // il explorez
        low_punti[u] = min(low_punti[u], low_punti[v]); // reactualizez low[u]
        if (low_punti[v] > d_punti[u]) {                // daca low[v] > d[u]
          // memorez puntea gasita
          punte[nr_punti][0] = v;
          punte[nr_punti][1] = u;
          nr_punti++;
        }
      } else if (p_punti[u] != v) { // daca nodul curent nu este parintele
        low_punti[u] = min(low_punti[u], d_punti[v]); // reactualizez low[u]
      }
    }
  }
}

void punti_tarjan() { // functia care determina puntile dintr-un graf
  int i;
  for (i = 0; i < n; ++i) {
    p_punti[i] = -1; // initializare valoare default pentru parinte
  }
  for (i = 0; i < n; ++i) {      // parcurgem graful
    if (vizitat_punti[i] == 0) { // daca am gasit un nod neexplorat
      exploreaza_punti(i);       // il exploram
    }
  }
  // afisare punti din graf
  printf("puntile sunt:\n");
  for (i = 0; i < nr_punti; ++i) {
    printf("\t%d - %d\n", punte[i][0], punte[i][1]);
  }
  printf("nr total punti=%d\n\n", nr_punti);
}

int main() {
  // muchiile din graf
  G[0][1] = 1;
  G[0][9] = 1;
  G[1][2] = 1;
  G[1][8] = 1;
  G[2][3] = 1;
  G[2][4] = 1;
  G[2][7] = 1;
  G[3][4] = 1;
  G[3][5] = 1;
  G[5][6] = 1;
  G[7][8] = 1;
  printf("\n--- PUNCTE DE ARTICULATIE ---\n");
  alg_tarjan();
  printf("\n--- PUNTI ---\n");
  punti_tarjan();
  return 0;
}
