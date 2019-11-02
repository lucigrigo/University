#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void cerinta1() {
  printf("Dati n si elementele matricei \n");
  int n;
  scanf("%d", &n);
  int i, j;
  int A[MAX][MAX];
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &A[i][j]);
    }
  }
  int sum, sum2;
  for (i = 0; i < n; i++) {
    sum = 0;
    sum2 = 0;
    for (j = 0; j < n; j++) {
      sum += A[i][j];
      sum2 += A[j][i];
    }
    printf("Suma liniei %d este %d \n", i + 1, sum);
    printf("Suma coloanei %d este %d \n", i + 1, sum2);
  }
}

void cerinta2() {
  int m, n, A[MAX][MAX], B[MAX][MAX];
  printf("Dati m si n \n");
  scanf("%d %d", &m, &n);
  int i, j, k;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      scanf("%d", &A[i][j]);
    }
  }
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &B[i][j]);
    }
  }
  int C[n][n];
  printf("Matricea rezultata in urma imultirii celor doua \n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      int sum = 0;
      for (k = 0; k < n; k++) {
        sum += A[i][k] * B[k][j];
      }
      C[i][j] = sum;
    }
  }
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("%d ", C[i][j]);
    }
    printf("\n");
  }
}

void cerinta3() {
  int n;
  printf("Dati n = ");
  scanf("%d", &n);
  int i = 0, j = 0, A[MAX][MAX];

  // for (i = 0; i < n; i++) {
  //   for (j = 0; j < n; j++) {
  //     printf("%d ", A[i][j]);
  //   }
  //   printf("\n");
  // }
}

int main() {
  // cerinta1();
  // cerinta2();
  cerinta3();
  return 0;
}
