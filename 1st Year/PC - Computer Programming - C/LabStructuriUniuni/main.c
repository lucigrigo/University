#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  int re;int im;
} nrComplex;

int main(){

  int n;
  printf("Dati n:\n");
  scanf("%d",&n);
  nrComplex A[n + 1];
  int i = 0;
  printf("Dati Re() si Im() pentru cele %d numere :\n",n);
  while(i < n){
    scanf("%d\n%d", &A[i].re, &A[i].im );
    i++;
  }

  i = 0;
  while(i < (n - 1)){
    int j = (i + 1);
    while(j < n){
      double modulI = sqrt(A[i].im * A[i].im + A[i].re * A[i].re) ;
      double modulJ = sqrt(A[j].im * A[j].im + A[j].re * A[j].re) ;
      if(modulI > modulJ){
        int reTemp,imTemp;
        reTemp = A[i].re;
        imTemp = A[i].im;
        A[i].re = A[j].re;
        A[i].im = A[j].im;
        A[j].re = reTemp;
        A[j].im = imTemp;
      }
      j++;
    }
    i++;
  }

  i=0;
  printf("Numerele in ordine dupa modulul lor sunt\n");
  while(i<n){
    printf("(%d + %d * i)\n", A[i].re, A[i].im);
    i++;
  }
  return 0;
}
