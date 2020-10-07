#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int main (int argc,char *argv[]){

  FILE *stream;
  char buf[MAX],A[MAX][MAX];
  int linesNumber = 0, i = 0;

  stream = fopen(argv[1],"r");
  while(fgets(buf,MAX,stream)){
    strcpy(A[linesNumber],buf);
    linesNumber++;
  }

  char I[MAX][MAX];
  while(i < linesNumber){
    strcpy(I[i],A[i]);
    i++;
  }

  i = 0;
  char C[MAX][MAX];
  while(i < linesNumber){
    int len;
    char *wordToken = strtok(I[i]," \n\0");
    while(wordToken != NULL){
      if(strcmp(wordToken,argv[2]) == 0){
        strcat(C[i],argv[3]);
        len = strlen(C[i]);
        C[i][len] = ' ';

      } else {
        strcat(C[i],wordToken);
        len = strlen(C[i]);
        C[i][len] = ' ';
      }
      wordToken = strtok(NULL," \n\0");
    }
    len = strlen(C[i]);
    C[i][len] = '\n';
    C[i][len + 1] = '\0';
    i++;
  }


  i = 0;
  while(i < linesNumber){
    strcpy(A[i],C[i]);
    i++;
  }
  stream = fopen(argv[1],"w");
  i = 0;
  while(i < linesNumber){
    fputs(A[i],stream);
    i++;
  }
  fclose(stream);
  return 0;
}
