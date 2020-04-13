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
int timp2;
int n2 = 16;
int d2_direct[16];
int d2_transpus[16];
int f2_direct[16];
int f2_transpus[16];
int vizitat2_direct[16];
int vizitat2_transpus[16];

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
  printf("\n-------------------\n\n    SORTARE TOPOLOGICA\n--- direct dpdv "
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
  printf("\n-------------------\n--- invers dpdv alfabetic ---\n\n");
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

void exploreaza_transpus(int v) {
  d2_transpus[v] = ++timp2;
  vizitat2_transpus[v] = 1;
  printf("%c ", (char)v + 65);
  int j;
  for (j = 0; j < n2; ++j) {
    if (vizitat2_transpus[j] == 0 && G2[j][v] == 1) {
      exploreaza_transpus(j);
    }
  }
  f2_transpus[v] = ++timp2;
}

void exploreaza_direct(int u) {
  d2_direct[u] = ++timp2;
  vizitat2_direct[u] = 1;
  int j;
  for (j = 0; j < n2; ++j) {
    if (vizitat2_direct[j] == 0 && G2[u][j] == 1) {
      exploreaza_direct(j);
    }
  }
  f2_direct[u] = ++timp2;
}

void CTC() {
  printf("\n    COMPONENTE TARE CONEXE\n\n   rezultate DFS(G)\n");
  // parcurgerea DFS pe G direct
  int i;
  timp2 = 0;
  for (i = 0; i < n2; ++i) {
    if (vizitat2_direct[i] == 0) {
      exploreaza_direct(i);
    }
  }
  // rezultate DFS pe G direct
  for (i = 0; i < n2; ++i) {
    printf("(%c) d(%c)=%d f(%c)=%d\n", (char)i + 65, (char)i + 65, d2_direct[i],
           (char)i + 65, f2_direct[i]);
  }
  // parcurgerea DFS pe G transpus
  timp2 = 0;
  int max = 50;
  int nr_comp = 1;
  while (max >= 0) {
    for (i = 0; i < n2; ++i) {
      if (vizitat2_transpus[i] == 0 && f2_direct[i] == max) {
        printf("\nComponenta conexa #%d:\n\t", nr_comp++);
        exploreaza_transpus(i);
      }
    }
    max--;
  }
  // rezultatele DFS pe G transpus
  printf("\n\n   rezultate DFS(G_t)\n");
  for (i = 0; i < n2; ++i) {
    printf("(%c) d(%c)=%d f(%c)=%d\n", (char)i + 65, (char)i + 65,
           d2_transpus[i], (char)i + 65, f2_transpus[i]);
  }
  printf("\n-------------------\n");
}

int main() {
  // graful pentru prima problema - sortare topologica
  G1[0][1] = 1;
  G1[0][3] = 1;
  G1[0][6] = 1;
  G1[1][6] = 1;
  G1[3][4] = 1;
  G1[5][4] = 1;
  G1[6][2] = 1;
  // sortare topologica
  sortare_topologica();
  // graful pentru a doua problema - componente tare conexe
  G2[0][1] = 1;
  G2[0][6] = 1;
  G2[1][2] = 1;
  G2[1][6] = 1;
  G2[2][4] = 1;
  G2[3][2] = 1;
  G2[3][5] = 1;
  G2[4][3] = 1;
  G2[6][7] = 1;
  G2[8][0] = 1;
  G2[8][9] = 1;
  G2[8][11] = 1;
  G2[9][10] = 1;
  G2[10][8] = 1;
  G2[10][12] = 1;
  G2[11][10] = 1;
  G2[12][13] = 1;
  G2[13][14] = 1;
  G2[14][12] = 1;
  G2[14][15] = 1;
  // componente tare conexe
  CTC();
  return 0;
}
