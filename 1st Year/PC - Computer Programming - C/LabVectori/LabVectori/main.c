#include <stdio.h>

void exercitiul0() {
  int i, S[10];
  printf("Dati cele 10 nr : \n");
  for (i = 0; i < 10; i++) {
    scanf("%d", &S[i]);
  }
  for (i = 0; i < 10; i++) {
    printf("%d ", S[i]);
  }
  printf("\n");
  for (i = 9; i > 0; i--) {
    if ((i % 2) == 0) {
      printf("%d ", S[i]);
    }
  }
  printf("\n");
}

void exercitiul1() {
  int n, x, i, S[101];
  for (i = 0; i <= 99; i++) {
    S[i] = i;
  }
  printf("Dati n si x : ");
  scanf("%d %d", &n, &x);
  for (i = 100; i >= n; i--) {
    S[i + 1] = S[i];
  }
  S[n] = x;
  for (i = 0; i <= 100; i++) {
    printf("%d ", S[i]);
  }
}

void exercitiul3() {
  int n, i, S[100];
  printf("Dati n:");
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &S[i]);
  }

  //  bubble sort

  int j;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (S[j] > S[j + 1]) {
        int a = S[j];
        S[j] = S[j + 1];
        S[j + 1] = a;
      }
    }
  }
  for (i = 0; i < n; i++) {
    printf("%d ", S[i]);
  }
}

int main() {
  // exercitiul0();
  // exercitiul1();
  exercitiul3();
  return 0;
}
