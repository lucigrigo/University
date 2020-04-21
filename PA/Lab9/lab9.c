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
int G[10][10];

// variabilele folosite pentru punctele de articulatie
int low_art[10];
int d_art[10];
int art[10];
int vizitat_art[10];
int timp_art;
int subarb_art[10];
int p_art[10];

// variabilele folosite pentru punti
int timp_punti;
int vizitat_punti[10];
int d_punti[10];
int p_punti[10];
int low_punti[10];
int punte[10];
int nr_punti;

// functia care realizeaza explorarea pentru alg. de determinare a pct.
// de articulatie
void exploreaza_art(int u) {
  d_art[u] = low_art[u] = timp_art++;
  vizitat_art[u] = 1;
  // printf("%d: nod %d d=%d low=%d\n", pas++, u, d_art[u], low_art[u]);
  int v;
  for (v = 0; v < n; v++) {
    if (G[u][v] == 1 || G[v][u] == 1) {
      if (vizitat_art[v] == 0) {
        p_art[v] = u; // atribuire parinte nod nou
        subarb_art[u]++; // actualizare nr subarbori dominati de u
        exploreaza_art(v);
        low_art[u] = min(low_art[u], low_art[v]);
        // if(low_art[v] < low_art[u]) {
        //     low_art[u] = low_art[v];
        // }
        if (p_art[u] != -1 && low_art[v] >= d_art[u]) {
          art[u] = 1; // cazul 2 al teoremei
        }
    } else if (p_art[u] != v) {
        low_art[u] = min(low_art[u], d_art[v]);
        // low_art[u] = d_art[v];
      }
    }
  }
    // printf("%d: nod %d d=%d low=%d\n", pas++, u, d_art[u], low_art[u]);
}

void alg_tarjan() { // functia care determina punctele de articulatie din graf
  int i;
  for (i = 0; i < n; ++i) {
    p_art[i] = -1; // valoare default pentru parinte
  }
  for (i = 0; i < n; ++i) {    // parcurgerea grafului
    if (vizitat_art[i] == 0) { // daca gasim un nod nevizitat
      exploreaza_art(i);       // exploram nodul
      if (subarb_art[i] > 1) { // verificare radacina subarb
        art[i] = 1;
      }
    }
  }
  int nr_art = 0;
  printf("\npunctele de articulatie sunt:\n");
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
  vizitat_punti[u] = 1; // il marcam ca vizitat
  int v;
  for (v = 0; v < n; ++v) {
    if (G[u][v] == 1 || G[v][u] == 1) {
      if (vizitat_punti[v] == 0) {
        p_punti[v] = u;
        exploreaza_punti(v);
        low_punti[u] = min(low_punti[u], low_punti[v]);
        if (low_punti[v] >= d_punti[u]) {
          punte[v] = 1;
        }
      } else if (p_punti[v] != u) {
        low_punti[u] = min(low_punti[u], d_punti[v]);
      }
    }
  }
}

void punti_tarjan() { // functia care determina puntile dintr-un graf
  int i;
  for (i = 0; i < n; ++i) {
    p_punti[i] = -1; // initializare valoare default pentru parinte
  }
  for (i = 0; i < n; ++i) { // parcurgem graful
    if (vizitat_punti[i] == 0) { // daca am gasit un nod neexplorat
      exploreaza_punti(i); // il exploram
    }
  }
  printf("puntile sunt:\n");
  for (i = 0; i < n; ++i) {
    if (punte[i] == 1) {
      printf("\t%d\n", i);
      nr_punti++;
    }
  }
  printf("nr total punti=%d\n\n", nr_punti);
}

int main() {
  // puncte de articulatie
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
  printf("\n\n--- PUNTI ---\n");
  punti_tarjan();
  printf("\n");
  return 0;
}
