#include "taskbonus.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/*
 *    Pentru rezolvarea task-ului bonus, am folosit functii din task-urile 3 si
 *  4 pentru:
 *  - citirea imaginii de input
 *  - transformarea imaginii primite intr-una de char-uri
 *    Astfel, cautarea pieselor (in cazul meu) se desfasoara pe o tabla cu
 *  caractere, reducand complexitatea cerintei. Parcurg tabela de la stanga la
 *  dreapta pe fiecare linie, iar cand dau de una dintre {O, L, J, T, I, S, Z},
 *  fac niste testari suplimentare pentru a determina cu exactitate rotatia
 *  piesei. Dupa memorarea piesei, rotatiei sale si coloanei pe care se
 *  gaseste, ma asigur ca pun, in locul patratelelor ocupate de piesa,
 *  caracterul 'N' - simbolizand partea neagra a imaginii, adica background-ul
 *  tablei de joc, pentru a evita a da peste aceeasi piesa de mai multe ori.
 *    Pentru fiecare piesa au loc aceiasi pasi odata ce pozitia exacta a piesei
 *  a fost determinata:
 *  - se trec caracterul specific piesei, rotatia si coloana intr-un vector de
 *  string-uri (folosesc sprintf() pentru conversie la numerele mai mari ca 10)
 *  - se "coloreaza cu negru" locul unde a fost piesa
 *    In schimb, diferentele dintre fiecare tip de piesa se regasesc in testele
 *  care au ca scop determinarea pozitiei exacte. Astfel, pentru piesa "O", este
 *  de ajuns sa gasesc o singura patratica, pentru piesele care au 2 rotatii
 *  simetrice 2 cate 2 (S, Z, I) sunt necesare 2 teste, iar pentru piesele care
 *  au toate rotatiile diferite (T, L, J) sunt necesare 3 teste.
 */

void StartBonus(char **gameTable,
                int height,
                int width) {
  int i, j, numberOfPieces = 0;
  char A[15000][5];
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      switch (gameTable[i][j]) {
      case 'O':
        //  Gaseste piesa "O"
        A[numberOfPieces++][0] = 'O';
        A[numberOfPieces++][0] = '0';
        sprintf(A[numberOfPieces++], "%d", j);
        gameTable[i][j] = 'N';
        gameTable[i][j + 1] = 'N';
        gameTable[i + 1][j] = 'N';
        gameTable[i + 1][j + 1] = 'N';
        break;
      case 'I':
        if (gameTable[i][j + 1] == 'I') {
          //  Gaseste piesa "I" cu rotatie 90˚ (270˚)
          A[numberOfPieces++][0] = 'I';
          sprintf(A[numberOfPieces++], "%d", 90);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i][j + 1] = 'N';
          gameTable[i][j + 2] = 'N';
          gameTable[i][j + 3] = 'N';
        } else if (gameTable[i + 1][j] == 'I') {
          //  Gaseste piesa "I" cu rotatie 0˚ (180˚)
          A[numberOfPieces++][0] = 'I';
          A[numberOfPieces++][0] = '0';
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 2][j] = 'N';
          gameTable[i + 3][j] = 'N';
        }
        break;
      case 'S':
        if (gameTable[i][j + 1] == 'S') {
          //  Gaseste piesa "S" cu rotatie 0˚ (180˚)
          A[numberOfPieces++][0] = 'S';
          A[numberOfPieces++][0] = '0';
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i][j + 1] = 'N';
          gameTable[i + 1][j + 1] = 'N';
          gameTable[i + 1][j + 2] = 'N';
        } else if (gameTable[i + 1][j] == 'S') {
          //  Gaseste piesa "S" cu rotatie 90˚ (270˚)
          A[numberOfPieces++][0] = 'S';
          sprintf(A[numberOfPieces++], "%d", 90);
          sprintf(A[numberOfPieces++], "%d", (j - 1));
          gameTable[i][j] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 1][j - 1] = 'N';
          gameTable[i + 2][j - 1] = 'N';
        }
        break;
      case 'Z':
        if (gameTable[i][j + 1] == 'Z') {
          //  Gaseste piesa "Z" cu rotatie 0˚ (180˚)
          A[numberOfPieces++][0] = 'Z';
          A[numberOfPieces++][0] = '0';
          sprintf(A[numberOfPieces++], "%d", (j - 1));
          gameTable[i][j] = 'N';
          gameTable[i][j + 1] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 1][j - 1] = 'N';
        } else if (gameTable[i + 1][j] == 'Z') {
          //  Gaseste piesa "Z" cu rotatie 90˚ (270˚)
          A[numberOfPieces++][0] = 'Z';
          sprintf(A[numberOfPieces++], "%d", 90);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 1][j + 1] = 'N';
          gameTable[i + 2][j + 1] = 'N';
        }
        break;
      case 'J':
        if ((gameTable[i][j + 1] != 'J') &&
            (gameTable[i + 1][j] == 'J') &&
            (gameTable[i + 2][j] == 'J')) {
          //  Gaseste piesa "J" cu rotatie 180˚
          A[numberOfPieces++][0] = 'J';
          sprintf(A[numberOfPieces++], "%d", 180);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 2][j] = 'N';
          gameTable[i + 2][j + 1] = 'N';
        } else if ((gameTable[i][j + 2] == 'J') &&
                   (gameTable[i + 1][j] == 'J')) {
          //  Gaseste piesa "J" cu rotatie 90˚
          A[numberOfPieces++][0] = 'J';
          sprintf(A[numberOfPieces++], "%d", 90);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i][j + 1] = 'N';
          gameTable[i][j + 2] = 'N';
        } else if ((gameTable[i][j + 1] == 'J') &&
                   (gameTable[i + 2][j + 1] == 'J')) {
          //  Gaseste piesa "J" cu rotatie 0˚
          A[numberOfPieces++][0] = 'J';
          sprintf(A[numberOfPieces++], "%d", 0);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i][j + 1] = 'N';
          gameTable[i + 1][j + 1] = 'N';
          gameTable[i + 2][j + 1] = 'N';
        } else if ((gameTable[i][j + 2] == 'J') &&
                   (gameTable[i - 1][j + 2] == 'J')) {
          //  Gaseste piesa "J" cu rotatie 270˚
          A[numberOfPieces++][0] = 'J';
          sprintf(A[numberOfPieces++], "%d", 270);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i][j + 1] = 'N';
          gameTable[i][j + 2] = 'N';
          gameTable[i - 1][j + 2] = 'N';
        }
        break;
      case 'L':
        if ((gameTable[i][j + 1] == 'L') &&
            (gameTable[i + 2][j] == 'L')) {
          //  Gaseste piesa "L" cu rotatie 0˚
          A[numberOfPieces++][0] = 'L';
          sprintf(A[numberOfPieces++], "%d", 0);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i][j + 1] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 2][j] = 'N';
        } else if ((gameTable[i][j + 2] == 'L') &&
                   (gameTable[i + 1][j + 2] == 'L')) {
          //  Gaseste piesa "L" cu rotatie 270˚
          A[numberOfPieces++][0] = 'L';
          sprintf(A[numberOfPieces++], "%d", 270);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i][j + 1] = 'N';
          gameTable[i][j + 2] = 'N';
          gameTable[i + 1][j + 2] = 'N';
        } else if ((gameTable[i + 1][j] == 'L') &&
                   (gameTable[i + 1][j + 1] == 'L')) {
          //  Gaseste piesa "L" cu rotatie 90˚
          A[numberOfPieces++][0] = 'L';
          sprintf(A[numberOfPieces++], "%d", 90);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 1][j + 1] = 'N';
          gameTable[i + 1][j + 2] = 'N';
        } else if ((gameTable[i + 2][j] == 'L') &&
                   (gameTable[i + 2][j + 1] == 'L')) {
          //  Gaseste piesa "L" cu rotatie 180˚
          A[numberOfPieces++][0] = 'L';
          sprintf(A[numberOfPieces++], "%d", 180);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 2][j] = 'N';
          gameTable[i + 1][j + 1] = 'N';
        }
        break;
      case 'T':
        if ((gameTable[i][j + 1] == 'T') &&
            (gameTable[i][j + 2] == 'T')) {
          //  Gaseste piesa "T" cu rotatie 180˚
          A[numberOfPieces++][0] = 'T';
          sprintf(A[numberOfPieces++], "%d", 180);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i][j + 1] = 'N';
          gameTable[i][j + 2] = 'N';
          gameTable[i + 1][j + 1] = 'N';
        } else if ((gameTable[i + 1][j - 1] == 'T') &&
                   (gameTable[i + 1][j + 1]) == 'T') {
          //  Gaseste piesa "T" cu rotatie 0˚
          A[numberOfPieces++][0] = 'T';
          sprintf(A[numberOfPieces++], "%d", 0);
          sprintf(A[numberOfPieces++], "%d", (j - 1));
          gameTable[i][j] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 1][j - 1] = 'N';
          gameTable[i + 1][j + 1] = 'N';
        } else if ((gameTable[i + 2][j] == 'T') &&
                   (gameTable[i + 1][j - 1] == 'T')) {
          //  Gaseste piesa "T" cu rotatie 90˚
          A[numberOfPieces++][0] = 'T';
          sprintf(A[numberOfPieces++], "%d", 90);
          sprintf(A[numberOfPieces++], "%d", (j - 1));
          gameTable[i][j] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 1][j - 1] = 'N';
          gameTable[i + 2][j] = 'N';
        } else if ((gameTable[i + 2][j] == 'T') &&
                   (gameTable[i + 1][j + 1] == 'T')) {
          //  Gaseste piesa "T" cu rotatie 270˚
          A[numberOfPieces++][0] = 'T';
          sprintf(A[numberOfPieces++], "%d", 270);
          sprintf(A[numberOfPieces++], "%d", j);
          gameTable[i][j] = 'N';
          gameTable[i + 1][j] = 'N';
          gameTable[i + 1][j + 1] = 'N';
          gameTable[i + 2][j] = 'N';
        }
        break;
      default:
        break;
      }
    }
  }
  /*
   *  Ca sa ajung la numarul real de piese citite, trebuie sa impart la 3,
   *  din cauza metodei mele de memorare a informatiilor necesare.
   */
  numberOfPieces /= 3;
  FILE *ffile = fopen("bonus.out", "w");
  /*
   *  Scrierea fisierului de output cu piesele, rotatiile si coloanele pe care
   *  se afla.
   */
  fprintf(ffile, "%d\n", numberOfPieces);
  for (i = 0; i < (3 * numberOfPieces); i += 3) {
    fprintf(ffile, "%s %s %s\n", A[i], A[i + 1], A[i + 2]);
  }
  //  Inchiderea fisierului de output
  fclose(ffile);
}
