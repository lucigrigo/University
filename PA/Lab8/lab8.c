/*
                            Proiectarea Algoritmilor
                                Laborator 8
                          Grigore Lucian-Florin 324CDb
*/
#include <stdio.h>
#include <stdlib.h>

// variabile sortare topologica
int G1[7][7];
int d1[7];
int f1[7];
int vizitat1[7];
int timp1;
int n1 = 7;

// variabile CTC
int G2[16][16];

int comp1(const void *p, const void *q) { return q - p; }

void exploreaza_st(int u) {
  d1[u] = ++timp1;
  vizitat1[u] = 1;
  printf("NOD %c\n", (char)u + 65);
  int j;
  for (j = 0; j < n1; j++) {
    if (vizitat1[j] == 0 && G1[u][j] == 1) {
      exploreaza_st(j);
    }
  }
  f1[u] = timp1;
}

void sortare_topologica() {
  int i;
  for (i = 0; i < n1; ++i) {
    if (vizitat1[i] == 0) {
      exploreaza_st(i);
    }
  }
  qsort(f1, n1, sizeof(int), comp1);
  printf("\n-------------------\n");
  printf("\nSORTARE TOPOLOGICA\n");
  int max = 20;
  while (max >= 0) {
    for (i = 0; i < n1; i++) {
      if (f1[i] == max) {
        printf("nod %c d(%c)=%d f(%c)=%d\n", (char)i + 65, (char)i + 65, d1[i],
               (char)i + 65, f1[i]);
        // break;
      }
    }
    max--;
  }
  printf("\n-------------------\n");
}

void CTC() {}

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
