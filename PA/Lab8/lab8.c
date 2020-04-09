/*
                            Proiectarea Algoritmilor
                                Laborator 8
                          Grigore Lucian-Florin 324CDb
*/
#include <stdio.h>
#include <stdlib.h>

// variabile sortare topologica
int G1[10][10];
int d1[10];
int f1[10];
int vizitat1[10];
int timp1;
int n1 = 7;

// variabile CTC
int G2[16][16];

void exploreaza_st(int u) {
  d1[u] = ++timp1;
  int j;
  for (j = 0; j < n1; j++) {
    if (j != u && vizitat1[j] == 0 && G1[u][j] == 1) {
      vizitat1[j] = 1;
      exploreaza_st(j);
    }
  }
  f1[u] = ++timp1;
}

void sortare_topologica() {
  int i;
  for (i = 0; i < n1; ++i) {
    if (vizitat1[i] == 0) {
      vizitat1[i] = 1;
      exploreaza_st(i);
    }
  }
  printf("\n-------------------\n\n    SORTARE TOPOLOGICA\n--- invers dpdv "
         "alfabetic ---\n\n");
  int max = 20;
  while (max > 0) {
    for (i = 0; i < n1; i++) {
      if (f1[i] == max) {
        printf("Nod %c d(%c)=%d f(%c)=%d\n", (char)i + 65, (char)i + 65, d1[i],
               (char)i + 65, f1[i]);
      }
    }
    max--;
  }
  printf("\n-------------------\n--- direct dpdv alfabetic ---\n\n");
  timp1 = 0;
  for (i = 0; i < n1; ++i) {
    d1[i] = 0;
    f1[i] = 0;
    vizitat1[i] = 0;
  }
  for (i = (n1 - 1); i >= 0; --i) {
    if (vizitat1[i] == 0) {
      vizitat1[i] = 1;
      exploreaza_st(i);
    }
  }
  max = 20;
  while (max > 0) {
    for (i = 0; i < n1; ++i) {
      if (f1[i] == max) {
        printf("Nod %c d(%c)=%d f(%c)=%d\n", (char)i + 65, (char)i + 65, d1[i],
               (char)i + 65, f1[i]);
      }
    }
    max--;
  }

  printf("\n-------------------\n");
}

void CTC() {
  printf("\n    COMPONENTE TARE CONEXE\n");

  printf("\n-------------------\n");
}

int main() {
  G1[0][1] = 1;
  G1[0][3] = 1;
  G1[0][6] = 1;
  G1[1][6] = 1;
  G1[3][4] = 1;
  G1[5][4] = 1;
  G1[6][2] = 1;
  // sortare topologica
  sortare_topologica();
  // componente tare conexe
  CTC();
  return 0;
}
