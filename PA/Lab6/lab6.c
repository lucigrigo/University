#include <stdio.h>
#include <stdlib.h>

void afisare_permutare(int v[], int n) {
  int j;
  for (j = 0; j < n; j++) {
    printf("%d ", v[j]);
  }
  printf("\n");
}

int validare_permutare(int poz, int v[], int n) {
  int j;
  for (j = 0; j < n; j++) {
    if (j != poz && v[j] == v[poz]) {
      return 0;
    }
  }
  return 1;
}

void permutari(int n) {
  int max = n;
  int init_val = 0;
  int v[n];
  int i;
  int val = 1;

  for (i = 0; i < n; i++) {
    v[i] = init_val;
  }

  i = 0;
  while (i >= 0) {
    int valid = 0;
    while (valid == 0 && v[i] <= max) {
      v[i] += val;
      valid = validare_permutare(i, v, n);
    }
    if (v[i] <= max) {
      if (i == (n - 1)) {
        afisare_permutare(v, n);
      } else {
        i += 1;
      }
    } else {
      v[i] = init_val;
      i -= 1;
    }
  }
}

void afisare_submultime(int v[], int n, int max) {
  int i;
  for (i = 0; i < n; i++) {
    if (v[i] == max) {
      printf("%d ", i + 1);
    }
  }
  printf("\n");
}

int validare_submultime(int poz, int n, int v[], int init_val) { return 1; }

void submultimi(int n) {
  int init_val = -1;
  int max = 1;
  int v[n];
  int i;
  int val = 1;

  for (i = 0; i < n; i++) {
    v[i] = init_val;
  }

  i = 0;
  while (i >= 0) {
    int valid = 0;
    while (valid == 0 && v[i] <= max) {
      v[i] += val;
      valid = validare_submultime(i, n, v, init_val);
    }
    if (v[i] <= max) {
      if (i == (n - 1)) {
        afisare_submultime(v, n, max);
      } else {
        i += 1;
      }
    } else {
      v[i] = init_val;
      i -= 1;
    }
  }
}

void afisare_dame(int v[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("(%d,%d) ", i, v[i]);
  }
  printf("\n");
}

int validare_dame(int v[], int n, int poz) {
  int i;
  for (i = 0; i <= poz; i++) {
    int j;
    for (j = 0; j <= poz; j++) {
      if (i != j && ((abs(j - i) == abs(v[j] - v[i])) || (v[i] == v[j]))) {
        return 0;
      }
    }
  }
  return 1;
}

void problema_damelor(int n) {
  int init_val = -1;
  int max = (n - 1);
  int val = 1;
  int i;
  int v[n];

  for (i = 0; i < n; i++) {
    v[i] = init_val;
  }

  i = 0;
  while (i >= 0) {
    int valid = 0;
    while (valid == 0 && v[i] <= max) {
      v[i] += val;
      valid = validare_dame(v, n, i);
    }
    if (v[i] <= max) {
      if (i == (n - 1)) {
        afisare_dame(v, n);
      } else {
        i += 1;
      }
    } else {
      v[i] = init_val;
      i -= 1;
    }
  }
}

int main() {
  int n = 3;
  // 1. permutari
  printf("\n--- 1. PERMUTARI ---\n");
  permutari(n);
  // 2. problema submultimilor
  printf("---\n\n--- 2. SUBMULTIMI ---");
  submultimi(n);
  // 3. problema damelor
  printf("---\n\n--- 3. PROBLEMA DAMELOR ---\n");
  int m = 4;
  problema_damelor(m);
  printf("---\n\n");
  return 0;
}
