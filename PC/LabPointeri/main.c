#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

//  cerinta 1
void cerinta1(int *a, int *b) {
  int p = *a;
  *a = *b;
  *b = p;
}

//  cerinta 2
int f(int a) { return (2 * a); }
int g(int a) { return (a + pow(2, a)); }
void map(int (*f)(int), int *v, int n) {
  int i = 0;
  for (; i < n; i++) {
    v[i] = (f(v[i]));
  }
}

//  cerinta 3
void suma(int *v, int n) {
  int i = 0;
  int suma = 0;
  for (; i < n; i++) {
    suma += *(v + i);
  }
  printf("Suma elementelor este %d. \n", suma);
}

//  cerinta 4
int cresc(const void *a, const void *b) { return (*(int *)a - *(int *)b); }
int descresc(const void *a, const void *b) { return (*(int *)b - *(int *)a); }

int main() {

  //  cerinta 1
  /*
  int a, b;
  printf("Dati a si b : \n");
  scanf("%d %d", &a, &b);
  cerinta1(&a, &b);
  printf("Cele 2 valori dupa swap sunt %d si %d . \n", a, b);
  */

  //  cerinta 2
  /*
  int n;
  printf("Dati n\n");
  scanf("%d \n", &n);
  int A[MAX];
  int i = 0;
  for (; i < n; i++) {
    scanf("%d", &A[i]);
  }
  map(*f, A, n);
  for (i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
  map(*g, A, n);
  printf("\n");
  for (i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
  printf("\n");
  */

  //  cerinta 3
  /*
  int n;
  printf("Dati n\n");
  scanf("%d \n", &n);
  int A[MAX];
  int i = 0;
  for (; i < n; i++) {
    scanf("%d", &A[i]);
  }
  suma(A, n);
  */

  //  cerinta 4
  /*
  int n;
  printf("Dati n\n");
  scanf("%d \n", &n);
  int A[MAX];
  int i = 0;
  for (; i < n; i++) {
    scanf("%d", &A[i]);
  }
  qsort(A, n, sizeof(int), *cresc);
  for (i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
  printf("\n");
  qsort(A, n, sizeof(int), *descresc);
  for (i = 0; i < n; i++) {
    printf("%d ", A[i]);
  }
  printf("\n");
  */

  return 0;
}
