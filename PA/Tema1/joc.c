/*
  Proiectarea Algoritmilor - Tema 1
  Problema 4 - Jocul numerelor impare
  Grigore Lucian-Florin 324CD
*/
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define INPUT_FILENAME "joc.in"
#define OUTPUT_FILENAME "joc.out"

// valoare default pentru suma jocului
#define DEFAULT_VALUE -2147483648

int main() {
  int i;

  // date de intrare (semnificatia din enunt)
  int n;
  int k;
  int l;

  // citire date de intrare
  FILE *file_in = fopen(INPUT_FILENAME, "r");
  fscanf(file_in, "%d %d %d\n", &n, &k, &l);
  int *numere = (int *)malloc(n * sizeof(int));
  for (i = 0; i < n; ++i) {
    fscanf(file_in, "%d ", &numere[i]);
  }
  fclose(file_in);

  // alocare memorie pentru structura de solutii
  // D la pasul i va memora toate solutiile optime in intervalul [1, i - 1]
  int *****D = (int *****)calloc(n + 1, sizeof(int ****));
  int ni, ki, li, p;
  for (ni = 0; ni <= n; ++ni) {
    D[ni] = (int ****)calloc(k + 1, sizeof(int ***));
    for (ki = 0; ki <= k; ++ki) {
      D[ni][ki] = (int ***)calloc(l + 1, sizeof(int **));
      for (li = 0; li <= l; ++li) {
        D[ni][ki][li] = (int **)calloc(2, sizeof(int *));
        D[ni][ki][li][0] = (int *)calloc(2, sizeof(int));
        D[ni][ki][li][1] = (int *)calloc(2, sizeof(int));
      }
    }
  }

  // initializare cu valori default
  for (ni = 0; ni <= n; ni++) {
    for (ki = 0; ki <= k; ki++) {
      for (li = 0; li <= l; li++) {
        D[ni][ki][li][0][0] = DEFAULT_VALUE;
        D[ni][ki][li][0][1] = DEFAULT_VALUE;
        D[ni][ki][li][1][0] = DEFAULT_VALUE;
        D[ni][ki][li][1][1] = DEFAULT_VALUE;
      }
    }
  }

  //  initializare caz de baza (nu alegem niciun element)
  for (ni = 0; ni < n; ni++) {
    D[ni][0][0][0][0] = D[ni][0][0][0][1] = 0;
  }

  // construirea solutiilor
  for (ni = 1; ni <= n; ni++) {
    for (ki = 1; ki <= min(k, ni); ki++) {
      for (li = ki; li <= l; li++) {
        for (p = 0; p <= 1; p++) {
          //  daca nu alegem elementul curent
          D[ni][ki][li][p][0] =
              max(D[ni - 1][ki][li][p][0], D[ni - 1][ki][li][p][1]);

          //  daca alegem elementul curent
          // ii aflam paritatea
          int p_curenta = numere[ni - 1] % 2;

          // exista doua cazuri
          // daca alegem sa continuam o secventa care contine si v[i - 1]
          // sau putem incepe una noua
          D[ni][ki][li][p][1] =
              max(D[ni - 1][ki][li - 1][p != p_curenta][1],
                  D[ni - 1][ki - 1][li - 1][p != p_curenta][0]) +
              numere[ni - 1];
        }
      }
    }
  }

  // scriere date de iesire
  FILE *file_out = fopen(OUTPUT_FILENAME, "w");
  fprintf(file_out, "%d",
          max(D[n][k][l][1][0], D[n][k][l][1][1]) <= 0
              ? -1
              : max(D[n][k][l][1][0], D[n][k][l][1][1]));
  fclose(file_out);

  // eliberare memorie alocata
  for (ni = 0; ni <= n; ++ni) {
    for (ki = 0; ki <= k; ++ki) {
      for (li = 0; li <= l; ++li) {
        free(D[ni][ki][li][0]);
        free(D[ni][ki][li][1]);
        free(D[ni][ki][li]);
      }
      free(D[ni][ki]);
    }
    free(D[ni]);
  }
  free(D);
  return 0;
}
