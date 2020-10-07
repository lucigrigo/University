#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

void cerinta1();
void cerinta2();
void cerinta3();

int main() {

  // cerinta1();
  // cerinta2();
  // cerinta3();
  return 0;
}

void cerinta1() {

  printf("Dati cuvantul si caracterul pe care vreti sa il cautati!\n");
  char a[MAX];
  char b;
  fgets(a, MAX, stdin);
  b = fgetc(stdin);
  int nr = 0;
  int j = 0;
  while (j < strlen(a)) {
    if (a[j] == b) {
      nr++;
    }
    j++;
  }
  printf("Litera %c apare de %d ori.\n", b, nr);
}

void cerinta2() {

  printf("Dati n\n");
  int n;
  char A[MAX][MAX];
  scanf("%d", &n);
  int i = 0;
  while (i <= n) {
    fgets(A[i], MAX, stdin);
    i++;
  }

  i = 0;
  while (i < n) {
    int j = i;
    while (j <= n) {
      if (strcmp(A[i], A[j]) > 0) {
        char p[MAX];
        strcpy(p, A[i]);
        strcpy(A[i], A[j]);
        strcpy(A[j], p);
      }
      j++;
    }
    i++;
  }

  printf("Cuvintele sortate lexicografic sunt:\n");
  i = 0;
  while (i <= n) {
    printf("%s", A[i]);
    i++;
  }
}

void cerinta3() {

  char A[MAX];
  printf("Introduceti cuvintele\n");
  fgets(A, MAX, stdin);
  char *token = strtok(A, " \n");
  char pare[MAX][MAX], impare[MAX][MAX];
  int iPar = 0, iImpar = 0;
  while (token != NULL) {
    if ((strlen(token) % 2) == 0) {
      strcpy(pare[iPar++], token);
    } else {
      strcpy(impare[iImpar++], token);
    }
    token = strtok(NULL, " \n");
  }
  printf("Cele cu lungime para sunt\n");
  int i = 0;
  while (i <= iPar) {
    printf("%s\n", pare[i]);
    i++;
  }
  printf("Cele cu lungime impara sunt\n");
  i = 0;
  while (i <= iImpar) {
    printf("%s\n", impare[i]);
    i++;
  }
}
