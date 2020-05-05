/*
                            Proiectarea Algoritmilor
                                  Laborator 8
                          Grigore Lucian-Florin 324CDb
*/
#include <stdio.h>
#include <stdlib.h>

//                          VARIABILE GLOBALE FOLOSITE

// variabile sortare topologica
int G1[10][10];   // graful pentru prima problema
int d1[10];       // vectorul d (inceput explorare) pentru prima problema
int f1[10];       // vectorul f (finalizare explorare) pentru prima problema
int vizitat1[10]; // vectorul c (culoarea nodului) pentru prima problema
int timp1;        // variabila timp pentru prima problema
int n1 = 7;       // dimensiunea grafului pentru prima problema

// variabile CTC
int G2[16][16];            // graful pentru a doua problema
int timp2;                 // variabile timp pentru a doua problema
int n2 = 16;               // dimensiunea grafului pentru a doua problema
int d2_direct[16];         // vectorul d pentru DFS pe graful direct
int d2_transpus[16];       // vectorul d pentru DFS pe graful transpus
int f2_direct[16];         // vectorul f pentru DFS pe graful direct
int f2_transpus[16];       // vectorul f pentru DFS pe graful transpus
int vizitat2_direct[16];   // vectorul c pentru DFS pe graful direct
int vizitat2_transpus[16]; // vectorul c pentru DFS pe graful transpus

// functie ce exploreaza pentru SORTAREA TOPOLOGICA
void exploreaza_st(int u) {
  d1[u] = ++timp1; // inceputul explorarii pentru nodul curent
  int j;
  for (j = 0; j < n1; j++) {
    if (j != u && vizitat1[j] == 0 && G1[u][j] == 1) {
      // explorarea vecinilor nodului curent
      vizitat1[j] = 1;
      exploreaza_st(j);
    }
  }
  f1[u] = ++timp1; // finalizarea explorarii pentru nodul curent
}

// functia ce realizeaza sortarea topologica
void sortare_topologica() {
  // sortarea directa dpdv alfabetic
  int i;
  for (i = 0; i < n1; ++i) { // parcurgerea nodurilor
    if (vizitat1[i] == 0) {  // daca nu este vizitat
      vizitat1[i] = 1;       // il marcam ca vizitat
      exploreaza_st(i);      // il exploram
    }
  }
  printf("\n-------------------\n\n    SORTARE TOPOLOGICA\n--- direct dpdv "
         "alfabetic ---\n\n");
  int max = 20;
  // printarea nodurilor in ordine descrescatoare dupa timpul de finalizare
  while (max > 0) {
    for (i = 0; i < n1; i++) {
      if (f1[i] == max) {
        printf("Nod %c d(%c)=%d f(%c)=%d\n", (char)i + 65, (char)i + 65, d1[i],
               (char)i + 65, f1[i]);
      }
    }
    max--;
  }
  // sortarea invers dpdv alfabetic
  printf("\n-------------------\n--- invers dpdv alfabetic ---\n\n");
  timp1 = 0;
  // reinitializarea vectorilor d,f si c
  for (i = 0; i < n1; ++i) {
    d1[i] = 0;
    f1[i] = 0;
    vizitat1[i] = 0;
  }
  for (i = (n1 - 1); i >= 0; --i) { // parcurgerea nodurilor
    if (vizitat1[i] == 0) {         // daca nu este vizitat
      vizitat1[i] = 1;              // il marcam ca vizitat
      exploreaza_st(i);             // il exploram
    }
  }
  // afisarea rezultatelor pentru parcurgerea inversa dpdv alfabetic
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

//  functia care exploreaza un nod avand in vedere graful transpus
void exploreaza_transpus(int v) {
  d2_transpus[v] = ++timp2;    // timpul de inceput de explorare
  vizitat2_transpus[v] = 1;    // marcam nodul ca vizitat
  printf("%c ", (char)v + 65); // il printam
  int j;
  for (j = 0; j < n2; ++j) { // parcurgem vecinii sai
    if (vizitat2_transpus[j] == 0 && G2[j][v] == 1) {
      // il exploram daca exista muchie si nodul vecin nu este explorat
      exploreaza_transpus(j);
    }
  }
  f2_transpus[v] = ++timp2; // timpul de finalizare al explorarii
}

// functia care exploreaza un nod pentru graful direct
void exploreaza_direct(int u) {
  d2_direct[u] = ++timp2; // timpul de inceput de explorare
  vizitat2_direct[u] = 1; // il marcam ca vizitat
  int j;
  for (j = 0; j < n2; ++j) { // parcurgem vecinii sai
    if (vizitat2_direct[j] == 0 && G2[u][j] == 1) {
      // exploram din nodul vecin daca exista muchie si acesta nu e vizitat
      exploreaza_direct(j);
    }
  }
  f2_direct[u] = ++timp2; // timpul de finalizare de explorare
}

// functia care realizeaza determinarea componentelor conexe
void CTC() {
  printf("\n    COMPONENTE TARE CONEXE\n\n   rezultate DFS(G)\n");
  // parcurgerea DFS pe G direct
  int i;
  timp2 = 0;                       // initializare timp
  for (i = 0; i < n2; ++i) {       // parcurgem nodurile
    if (vizitat2_direct[i] == 0) { // daca nodul curent nu a fost vizitat
      exploreaza_direct(i);        // il exploram
    }
  }
  // afisare rezultate DFS pe G direct
  for (i = 0; i < n2; ++i) {
    printf("(%c) d(%c)=%d f(%c)=%d\n", (char)i + 65, (char)i + 65, d2_direct[i],
           (char)i + 65, f2_direct[i]);
  }
  // parcurgerea DFS pe G transpus
  timp2 = 0;    // resetare timp
  int max = 50; // valoarea maxima a timpului (poate varia in functie de graf)
  int nr_comp = 1; // indexul componentei conexe
  while (max >= 0) {
    // parcurgem nodurile in ordine descrescatoare dupa timpul de finalizare
    for (i = 0; i < n2; ++i) {
      if (vizitat2_transpus[i] == 0 && f2_direct[i] == max) {
        // am gasit o noua componenta conexa
        printf("\nComponenta conexa #%d:\n\t", nr_comp++);
        exploreaza_transpus(i); // incepem explorarea din nodul curent
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

// functia main
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
