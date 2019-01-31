/*
 *                Curs: Programarea Calculatoarelor
 *                              Tema 3 - TetriPic
 *                    Nume si prenume: Grigore Lucian-Florin
 *                    Grupa si seria: 314CD
 */
#include "utils.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  /*
   *  Am lasat if-ul asta ca sa nu mai imi dea warning la compilare ca nu
   *    folosesc argc :D
   */
  if (argc == 2) {
    CitireComanda(argv);
  }
  return 0;
}
