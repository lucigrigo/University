#include <stdio.h>
#include <stdlib.h>

void cerinta1() {
  //  Construirea unui cub de dimesiune n x n x n
  printf("Dati dimensiunea cubului :");
  int n;
  scanf("%d", &n);

  int ***m = (int ***)malloc(n * sizeof(int **));
  if (m == NULL) {
    printf("Alocarea nu a reusit!");
    return;
  }

  int i, j;
  for (i = 0; i < n; i++) {
    m[i] = (int **)malloc(n * sizeof(int *));
    for (j = 0; j < n; j++) {
      m[i][j] = (int *)malloc(n * sizeof(int));
    }
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      free(m[i][j]);
    }
    free(m[i]);
  }
  free(m);
}



int *realloc2(int *p, int oldsize, int newsize) {
  int *new = (int *)malloc(newsize * sizeof(int));
  int i;
  for (i = 0; i < oldsize; i++) {
    new[i] = p[i];
  }
  free(p);
  return new;
}

void cerinta2() {
  //  Implementare realloc2()
  printf("Dati dimensiunea vectorului :");
  int n;
  scanf("%d", &n);

  int *p = (int *)malloc(n * sizeof(int));
  if (p == NULL) {
    printf("Alocarea nu a reusit!");
    return;
  }

  int i;
  for (i = 0; i < n; i++) {
    p[i] = (i+1);
  }

  int newsize = 29;
  p = realloc2(p, n, newsize);

  for (i = 0; i < newsize; i++) {
    printf("%d\n", p[i]);
  }
  free(p);
}



int **realloc3(int **M,int size){
    int **newM = (int **) calloc((2*size) , sizeof(int*));
    int i;
    for(i=0;i<(2*size);i++){
      newM[i] = (int*) calloc((2*size) ,sizeof(int));
    }

    int j;
    for(i=0;i<size;i++){
      for(j=0;j<size;j++){
        newM[i][j] = M[i][j];
      }
    }

    for(i=0;i<(2*size);i++){
      free(M[i]);
    }
    free(M);
    return newM;
}

void cerinta3(){
  //  Implementare realloc3 -> dubleaza dimensiunile unei matrici
  printf("Dati dimensiunea matricei\n");
  int n;
  scanf("%d",&n );

  int **m=(int **) calloc(n,sizeof(int*));
  if (m == NULL) {
    printf("Alocarea nu a reusit!\n");
    return;
  }
  int i;
  for(i=0;i<n;i++){
    m[i] = (int*) calloc(n,sizeof(int));
  }

  printf("Dati elementele matricei de %d x %d\n",n,n);
  for(i=0;i<n;i++){
    int j;
    for(j=0;j<n;j++){
      scanf("%d",&m[i][j]);
    }
  }

  m = realloc3(m,n);

  printf("Elementele noii matrici sunt\n");
  for(i=0;i<2*n;i++){
    int j;
    for(j=0;j<2*n;j++){
        printf("%d ",m[i][j]);
    }
    printf("\n");
  }

  for(i=0;i<n;i++){
    free(m[i]);
  }
  free(m);
}



int main() {
   // cerinta1();
   // cerinta2();
   // cerinta3();
  return 0;
}
