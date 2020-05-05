#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *numeVolum;
  short anPublicare;
  int stare : 8;
  unsigned int idPersoana : 5;
} TVolum;

typedef struct {
  char *numeAutor;
  char codTara[3];
  int nrVolume;
  TVolum *volume;
} TAutor;

TAutor *alocaAutor(int nrVolume) {
  TAutor *ptr = (TAutor *)malloc(sizeof(char *) + sizeof(int) + 3 +
                                 (nrVolume * sizeof(TVolum)));
  ptr->nrVolume = nrVolume;
  return ptr;
}

TAutor **alocaAutori(int nrAutori, int *nrVolumeAutori) {
  TAutor **ptr = (TAutor **)malloc(nrAutori);
  int i;
  for (i = 0; i < nrAutori; i++) {
    ptr[i] = alocaAutor(nrVolumeAutori[i]);
  }
  return ptr;
}

void test(int *p){
  *p = 6;
}

int main() {
  printf("SALUT\n");
  TAutor *autor = alocaAutor(5);
  int A[4] = {1, 2, 3};
  // TAutor **autori = alocaAutori(3, A);
  // free(autor);
  int a = 2;
  test(&a);
  printf("%d\n", a);
  return 0;
}
