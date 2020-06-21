#include <stdio.h>
#include <stdlib.h>

void problema_rucsacului(float m[], float v[], int len, int max) {
  float p[len];
  int k;
  // initializare ponderi
  for (k = 0; k < len; k++) {
    p[k] = v[k] / m[k];
  }

  // sortare descrescatoare dupa ponderi
  for (k = 0; k < (len - 1); k++) {
    int j = k + 1;
    for (; j < len; j++) {
      if (p[j] > p[k]) {
        int temp = p[k];
        p[k] = p[j];
        p[j] = temp;
        temp = v[k];
        v[k] = v[j];
        v[j] = temp;
        temp = m[k];
        m[k] = m[j];
        m[j] = temp;
      }
    }
  }

  // umplere rucsac
  float cant = 0, val = 0;
  while (cant < max) {
    for (k = 0; k < len; k++) {
      if (cant + m[k] <= max) {
        cant += m[k];
        val += v[k];
        printf("Se adauga in totalitate elem cu masa %.2f\n", m[k]);
        if (cant == max) {
          break;
        }
      }
      if (cant + m[k] > max) {
        float procent = (max - cant) / m[k];
        cant += m[k] * procent;
        val += v[k] * procent;
        printf("Se adauga in proportie de %.3f elem cu masa %.2f\n", procent,
               m[k]);
        break;
      }
    }
  }
  printf("Valoare totala rucsac = %.2f\n", val);
}

void problema_spectacolelor(float start[], float final[], int nr_filme) {
  int k;
  // ordonare crescatoare dupa timpul de terminare al filmelor
  for (k = 0; k < (nr_filme - 1); k++) {
    int j = k + 1;
    for (; j < nr_filme; j++) {
      if (final[j] < final[k]) {
        int temp = final[j];
        final[j] = final[k];
        final[k] = temp;
        temp = start[j];
        start[j] = start[k];
        start[k] = temp;
      }
    }
  }

  // punere in redare filme
  int final_spectacol = 0, nr = 0;
  for (k = 0; k < nr_filme; k++) {
    if (start[k] >= final_spectacol) {
      nr++;
      final_spectacol = final[k];
      printf("Se reda filmul de la %.2f la %.2f\n", start[k], final[k]);
    }
  }
  printf("S-au redat in total %d filme\n", nr);
}

void problema_cuburi(int cul[], int len[], int nr) {
  int k;
  // sortare crescator dupa lungimi
  for (k = 0; k < (nr - 1); k++) {
    int j = k + 1;
    for (; j < nr; j++) {
      if (len[j] > len[k]) {
        int temp = len[j];
        len[j] = len[k];
        len[k] = temp;
        temp = cul[j];
        cul[j] = cul[k];
        cul[k] = temp;
      }
    }
  }

  // construire turn
  int inaltime = 0, ultima_culoare = -1, ultima_lungime = 10000000;

  for (k = 0; k < nr; k++) {
    if (ultima_culoare != cul[k] && ultima_lungime >= len[k]) {
      ultima_culoare = cul[k];
      ultima_lungime = len[k];
      inaltime += len[k];
      printf("Se asaza cubul cu latura %d si culoare %d\n", len[k], cul[k]);
    }
  }

  printf("Inaltimea turnului construit este %d\n", inaltime);
}

void problema_segmente(int start[], int final[], int culori[], int nr) {
  int k;
  // ordonare crescator dupa finalul segmentului
  for (k = 0; k < (nr - 1); k++) {
    int j = k + 1;
    for (; j < nr; j++) {
      if (final[j] < final[k]) {
        int temp = final[j];
        final[j] = final[k];
        final[k] = temp;
        temp = start[j];
        start[j] = start[k];
        start[k] = temp;
      }
    }
  }

  int c[nr], seg_valide[nr];
  while (1) {
    break;
  }
}

int main() {
  // PROBLEMA RUCSACULUI
  float m[] = {10, 30, 20};
  float v[] = {60, 120, 100};
  int nr_obj = 3;
  int max = 50;
  printf("\n--- PROBLEMA RUCSACULUI ---\n");
  problema_rucsacului(m, v, nr_obj, max);

  // PROBLEMA SPECTACOLELOR
  float start[] = {10, 11, 12, 14, 16, 17};
  float final[] = {11, 13, 13, 18, 17, 19};
  int nr_filme = 6;
  printf("\n--- PROBLEMA SPECTACOLELOR ---\n");
  problema_spectacolelor(start, final, nr_filme);

  // PROBLEMA CUBURI
  int culori[] = {0, 1, 2, 0, 1, 2, 0, 1};
  int lungimi[] = {3, 2, 3, 1, 6, 4, 3, 1};
  int nr_cuburi = 8;
  printf("\n--- PROBLEMA CUBURILOR ---\n");
  problema_cuburi(culori, lungimi, nr_cuburi);

  // PROBLEMA SEGMENTELOR
  int begin[] = {};
  int end[] = {};
  int culori_segmente[] = {};
  int nr_segmente = 0;
  printf("\n--- PROBLEMA SEGMENTELOR ---\n");
  problema_segmente(begin, end, culori_segmente, nr_segmente);
  return 0;
}
