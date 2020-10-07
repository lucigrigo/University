#include <stdio.h>
#include <stdlib.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))

int search_app(int v[], int i, int j, int elem) {
  if (i > j) {
    return 0;
  }
  int half = (i + j) / 2;
  if (v[half] == elem) {
    int nr_app = 1;
    int index = half + 1;
    while (v[index++] == elem) {
      nr_app++;
    }
    index = half - 1;
    while (v[index--] == elem) {
      nr_app++;
    }
    return nr_app;
  }
  if (v[half] >= elem) {
    return search_app(v, i, half, elem);
  }
  return search_app(v, half + 1, j, elem);
}

// NUMAR DE APARITII - NESORTAT
int app(int v[], int i, int j, int elem) {
  if (i == j) {
    if (v[i] == elem) {
      return 1;
    }
    return 0;
  }
  int half = (i + j) / 2;
  return app(v, i, half, elem) + app(v, half + 1, j, elem);
}

// NUMAR DE APARITII - SORTAT
int app_sort(int v[], int left, int right, int elem) {
  return search_app(v, left, right, elem);
}

// CAUTARE BINARA
int search(int v[], int i, int j, int elem) {
  if (i > j) {
    return -1;
  }
  int half = (i + j) / 2;
  if (v[half] == elem) {
    return half;
  }
  if (v[half] > elem) {
    return search(v, i, half - 1, elem);
  }
  return search(v, half + 1, j, elem);
}

void interclasare(int *v, int i, int m, int j) {
  int x = i, y = m + 1, index = 0;
  int *new_vector = (int *)malloc((j - i + 1) * sizeof(int));

  while (x <= m && y <= j) {
    if (v[x] < v[y]) {
      new_vector[index++] = v[x++];
    } else {
      new_vector[index++] = v[y++];
    }
  }
  while (x <= m) {
    new_vector[index++] = v[x++];
  }
  while (y <= j) {
    new_vector[index++] = v[y++];
  }

  int k, l;
  for (k = i, l = 0; k <= j;) {
    v[k++] = new_vector[l++];
  }
}

// SORTARE PRIN INTERCLASARE
void sort_interclasare(int *v, int i, int j) {
  if (i < j) {
    int half = (i + j) / 2;
    sort_interclasare(v, i, half);
    sort_interclasare(v, half + 1, j);
    interclasare(v, i, half, j);
  }
}

// MAXIMUL DINTR-UN VECTOR
int max_vector(int v[], int i, int j) {
  if (i == j) {
    return v[i];
  }
  int half = (i + j) / 2;
  return max(max_vector(v, i, half), max_vector(v, half + 1, j));
}

int main() {
  // max
  int vector[] = {1, 2000, 3, 3, -6, 3, 10, -15, -2, 0};
  int length = 10;
  int i = 0;
  int maxim = max_vector(vector, 0, length - 1);
  printf("maximul = %d\n\n", maxim);

  // sort
  sort_interclasare(vector, 0, length - 1);
  printf("vector sortat : ");
  for (i = 0; i < length; i++) {
    printf("%d ", vector[i]);
  }
  printf("\n");

  // search
  printf("\ncautare : %d\n", search(vector, 0, length, 2000));

  // nr de aparitii
  printf("\nnr aparitii nesortat : %d\n", app_sort(vector, 0, length, 3));
  printf("\nnr aparitii sortat : %d\n", app(vector, 0, length, 3));

  // subsecventa de suma maxima
  return 0;
}
