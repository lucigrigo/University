// Proiectarea Algoritmilor
// Laboratorul 10
// Grigore Lucian-Florin 324CDb
#include <stdio.h>
#include <stdlib.h>

int G[10][10]; // graful folosit
int n = 7;     // numarul de noduri din graf

int dist_djk[7]; // vectorul care va memora distantele pentru Dijkstra
int p_djk[7];    // vectorul care va memora parintii pentru Dijkstra

int dist_bf[7]; // vectorul care va memora distantele pentru Bellman-Ford
int p_bf[7];    // vectorul care va memora distantele pentru Bellman-Ford

// functie care extrage nodul cu distanta cea mai mica din coada
int *extrage_min(int *q, int *size, int *elem) {
  int i;
  int min = 1000000;             // valoare initiala pentru minim
  int index = -1;                // valoare initiala pentru pozitie
  for (i = 1; i <= *size; ++i) { // parcurgere vector
    if (dist_djk[q[i]] < min) {  // daca gasim un minim nou
      min = dist_djk[q[i]];      // memoram noul minim
      index = i;                 // memoram pozitia minimului
    }
  }
  *elem = q[index];    // atribuim minimul
  q[index] = q[*size]; // micsoram coada
  (*size)--;           // micsoram dimensiunea cozii
  return q;
}

// functie care implementeaza algoritmul lui Dijkstra
void dijkstra() {
  int *q = (int *)malloc(n * sizeof(int)); // coada
  int q_size = 0;                          // dimensiunea cozii
  int i;
  for (i = 1; i <= n; ++i) { // initializari parinti si distante
    p_djk[i] = -1;
    dist_djk[i] = 1000000;
  }
  dist_djk[1] = 0;           // distanta nod sursa
  for (i = 1; i <= n; ++i) { // initializare coada cu toate nodurile
    q[i] = i;
    ++q_size;
  }
  int elem_curent;
  while (q_size > 0) { // repetare pana cand coada e goala
    q = extrage_min(q, &q_size, &elem_curent); // extragem minimul
    for (i = 1; i <= n; i++) {                 // ii parcurgem vecinii
      if (G[elem_curent][i] != 0) {            // daca exista muchie
        if (dist_djk[i] > dist_djk[elem_curent] + G[elem_curent][i]) {
          // daca se poate efectua o relaxare a unui arc prin nodul curent
          dist_djk[i] = dist_djk[elem_curent] + G[elem_curent][i];
          p_djk[i] = elem_curent;
        }
      }
    }
  }
  // printare rezultate algoritm
  printf("\n-- Rezultate Dijkstra --\n");
  for (i = 1; i <= n; ++i) {
    printf("\tnod %d d=%d p=%d\n", i, dist_djk[i], p_djk[i]);
  }
  printf("\n-----------------------\n");
  free(q);
}

// functie care implementeaza algoritmul Bellman-Ford
void bellman_ford() {
  int i;
  for (i = 1; i <= n; ++i) {
    dist_bf[i] = 100000000; // initializare vector distante
    p_bf[i] = -1;           // initializare vector parinti
  }
  dist_bf[1] = 0;                  // nod sursa
  for (i = 1; i <= (n - 1); ++i) { // pasul curenta
    int j;
    for (j = 1; j <= n; ++j) { // nodul sursa curent
      int k;
      for (k = 1; k <= n; ++k) { // nodul destinatie curent
        if (G[j][k] != 0) { // daca exista muchie de la sursa la destinatie
          int sursa = j;
          int destinatie = k;
          int cost_drum = G[j][k];
          if (dist_bf[k] > dist_bf[j] + cost_drum) {
            // daca se poate face o relaxare a unui arc
            dist_bf[k] = dist_bf[j] + cost_drum;
            p_bf[k] = j;
          }
        }
      }
    }
  }
  // printare rezultate algoritm
  printf("\n-- Rezultate Bellman-Ford --\n");
  for (i = 1; i <= n; ++i) {
    printf("\tnod %d d=%d p=%d\n", i, dist_bf[i], p_bf[i]);
  }
  printf("\n-----------------------\n");
}

int main() {
  // muchiile din graf si costul asociat
  G[1][2] = 3;
  G[1][3] = 4;
  G[1][5] = 1;
  G[1][6] = 10;
  G[1][7] = 3;
  G[2][3] = 2;
  G[3][4] = 2;
  G[3][6] = 2;
  G[5][4] = 3;
  G[5][7] = 1;
  G[6][4] = 2;
  G[7][3] = 1;
  G[7][4] = 10;
  G[7][5] = 2;
  dijkstra();
  bellman_ford();
  return 0;
}
