#include <stdio.h>
#include <stdlib.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))

int D(int capacitate_curenta, int index, int m[], int v[], int obj[]) {
  if (index < 1) {
    return 0;
  }
  if (capacitate_curenta < 0) {
    return 0;
  }
  if (D(capacitate_curenta, index - 1, m, v, obj) <
      D(capacitate_curenta - m[index], index - 1, m, v, obj) + v[index]) {
    obj[index] = m[index];
  }

  return max(D(capacitate_curenta, index - 1, m, v, obj),
             D(capacitate_curenta - m[index], index - 1, m, v, obj) + v[index]);
}

void problema_rucsacului_discret(int m[], int v[], int n, int max) {

  int *obj = (int *)malloc(n * sizeof(int));
  printf("valoare maxima este: %d\n", D(max, n - 1, m, v, obj));
}

void problema_subsir(int v[], int n) {
  int D[n];
  int i;

  for (i = 0; i < n; i++) {
    D[i] = 0;
  }

  for (i = 0; i < n; i++) {
    int j = 0;
    int max = 0;
    for (; j < i; j++) {
      if (D[j] > max && v[i] > v[j]) {
        max = D[j];
      }
    }
    D[i] = max + 1;
  }

  int max = -1;
  for (i = 0; i < n; i++) {
    if (D[i] > max) {
      max = D[i];
    }
  }
  printf("lungimea maxima este %d\n", max);
  printf("si vectorul cu lungimi este:\n\t");
  for (i = 0; i < n; i++) {
    printf("%d ", v[i]);
  }
  printf("\n\t");
  for (i = 0; i < n; i++) {
    printf("%d ", D[i]);
  }
  printf("\n");
  int curent_max = 1000000;
  printf("subsirul solutie este:\n\t");
  for (i = n - 1; i >= 0; i--) {
    if (D[i] == max && curent_max > v[i]) {
      printf("%d ", v[i]);
      max--;
      curent_max = v[i];
    }
  }
  printf("\n");
}

int main() {
  printf("\n---------------------------------------------\n");

  printf("\n--- PROBLEMA RUCSACULUI DISCRET ---\n");
  int m[] = {10, 30, 20};
  int v[] = {60, 120, 100};
  problema_rucsacului_discret(m, v, 3, 50);

  printf("\n--- PROBLEMA CELUI MAI LUNG SUBSIR ---\n");
  int v1[] = {6, 1, 2, 9, 3, 8, 4, 7};
  problema_subsir(v1, 8);

  printf("\n---------------------------------------------\n");
  return 0;
}
