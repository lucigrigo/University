/*
              Curs: Programarea Calculatoarelor
                        Tema 3 - TetriPic
              Nume si prenume: Grigore Lucian-Florin
              Grupa si seria: 314CD
*/
#include <stdio.h>
#include <stdlib.h>
#include "bmp_header.h"

void CitireComenzi(int, char **);
void Task1();

int main(int argc, char *argv[]) {
  CitireComenzi(argc, argv);
  return 0;
}

void CitireComenzi(int argc, char *argv[]) {
  int taskNumber = (int)strtol(argv[1], (char **)NULL, 10);
  switch (taskNumber) {
  case 1:
    Task1();
    break;
  }
}

void Task1() {

}
