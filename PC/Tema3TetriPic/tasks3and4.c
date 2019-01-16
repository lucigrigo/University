#include "tasks3and4.h"
#include <stdlib.h>

/*
 *  Functia de initializare a jocului este aproape la fel pentru task-urile 3
 *  si 4, cu singura diferenta ca la cel din urma mai este apelata o functie
 *  care transforma BitMap-ul intr-o matrice de char-uri.
 */
void StartGame(FILE *ffile,
               int numberOfPieces,
               bmpPixel **bitMap,
               int height,
               int width,
               bool preLoadedMap) {
  int i, j, k;
  char **charMatrix;
  //  Alocarea dinamica a matricii de char-uri
  if (preLoadedMap == true) {
    //  Cazul in care se citeste o imagine (task4)
    height -= 4;
    charMatrix = (char **)malloc((height)*width * (int)sizeof(char));
  } else {
    /*
     *  Cazul in care se creeaza o tabla de joc noua (task3).
     *  Nu stiu cum sa explic de ce am (height + 12) acolo pentru ca stiu ca nu
     *  pare logic, dar orice valoare mai mica as fi dat, as fi primit seg
     *  fault la alocarea dinamica a fiecarei linii (linia 32).
     */
    charMatrix = (char **)malloc((height + 12) * width * (int)sizeof(char));
  }
  for (i = 0; i < (height + 4); i++) {
    charMatrix[i] = (char *)malloc(width * (int)sizeof(char));
  }
  //  Colorarea cu negru - 'N', respectiv alb - 'A' a zonelor corespunzatoare
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      charMatrix[i][j] = 'N';
    }
  }
  for (i = height; i < (height + 4); i++) {
    for (j = 0; j < width; j++) {
      charMatrix[i][j] = 'A';
    }
  }
  if (preLoadedMap == true) {
    /*
     *  In cazul unei imagini citite, se transforma BitMap-ul in matricea de
     *  char-uri prin plasarea caracterelor respective {O, L, J, T, S, Z, I} in
     *  fiecare patratica (10px x 10px) unde se regasesc piesele.
     */
    ConvertToMatrix(charMatrix, bitMap, height, width);
  }
  k = 0;
  while (k < numberOfPieces) {
    int widthIndex, rotation;
    char pieceIndex = '\0';
    bool endGame = false;
    /*
     *  Citirea unei piese si apelarea functiei corespunzatoare plasarii
     *  acesteia pe tabla de joc
     */
    fscanf(ffile, "%c %d %d\n", &pieceIndex, &rotation, &widthIndex);
    switch (pieceIndex) {
    case 'I':
      endGame = placeI(charMatrix, rotation, widthIndex, height);
      break;
    case 'O':
      endGame = placeO(charMatrix, widthIndex, height);
      break;
    case 'S':
      endGame = placeS(charMatrix, rotation, widthIndex, height);
      break;
    case 'Z':
      endGame = placeZ(charMatrix, rotation, widthIndex, height);
      break;
    case 'L':
      endGame = placeL(charMatrix, rotation, widthIndex, height);
      break;
    case 'J':
      endGame = placeJ(charMatrix, rotation, widthIndex, height);
      break;
    case 'T':
      endGame = placeT(charMatrix, rotation, widthIndex, height);
      break;
    default:
      endGame = true;
      break;
    }
    //  Verifica daca exista linii complete
    CheckCompletedLines(charMatrix, height, width);
    if (endGame == true) {
      break;
    }
    k++;
  }
  //  Se transforma matricea de char-uri in BitMap
  ConvertMatrix(bitMap, charMatrix, width, height);
  //  Se elibereaza memoria ocupata
  for (i = 0; i < (height + 3); i++) {
    free(charMatrix[i]);
  }
  free(charMatrix);
}

/*
 *    Pentru functiile menite sa plaseze fiecare piesa pe tabla de joc, se
 *  urmeaza aceeasi pasi pentru fiecare rotatie posibila a acesteia:
 *  - se parcurge in jos matricea, incepand cu prima coloana de pe partea alba
 *  si se cauta "loc" pentru piesa respectiva. Functia FreeSpot() face acest
 *  lucru. Functia BreakingTheGame() impiedica piesa sa treaca de vreo alta
 *  pe coloana/coloanele pe care coboara.
 *  - se marcheaza locul ocupat de piesa prin scrierea caracterului aferent
 *  - se testeaza daca piesa iese in partea alba a tablei de joc pentru a
 *  intrerupe sau nu jocul
 *    Fiind apelate din cadrul functiei StartGame(), functiile de plasare a
 *  pieselor returneaza true/false aferent variabile endGame (true daca jocul
 *  se termina, false daca el poate continua).
 */

//  Plasarea piesei I
bool placeI(char **charMatrix,
            int rotation,
            int wIndex,
            int matrixHeight) {
  int i, rowIndex = -1;
  if ((rotation == 0) ||
      (rotation == 180)) {
    // Rotatie 0˚ sau 180˚
    for (i = matrixHeight; i >= 0; i--) {
      if (FreeSpot(i, wIndex, charMatrix) &&
          !(BreakingTheGame(wIndex, 0, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 0, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    for (i = rowIndex; i < (rowIndex + 4); i++) {
      charMatrix[i][wIndex] = 'I';
    }
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 4) < 0)) {
      return true;
    }
  } else if ((rotation == 90) ||
             (rotation == 270)) {
    // Rotatie 90˚ sau 270˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          (FreeSpot(i, (wIndex + 3), charMatrix)) &&
          !(BreakingTheGame(wIndex, 3, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
    }
    charMatrix[rowIndex][wIndex] = 'I';
    charMatrix[rowIndex][wIndex + 1] = 'I';
    charMatrix[rowIndex][wIndex + 2] = 'I';
    charMatrix[rowIndex][wIndex + 3] = 'I';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 1) < 0)) {
      return true;
    }
  }
  return false;
}

//  Plasarea piesei O
bool placeO(char **charMatrix,
            int wIndex,
            int matrixHeight) {
  int i, rowIndex = -1;
  for (i = matrixHeight; i >= 0; i--) {
    if ((FreeSpot(i, wIndex, charMatrix)) &&
        (FreeSpot(i, (wIndex + 1), charMatrix)) &&
        (FreeSpot((i + 1), wIndex, charMatrix)) &&
        (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
        (!BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
      rowIndex = i;
    }
    if (BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)) {
      break;
    }
  }
  charMatrix[rowIndex][wIndex] = 'O';
  charMatrix[rowIndex][wIndex + 1] = 'O';
  charMatrix[rowIndex + 1][wIndex] = 'O';
  charMatrix[rowIndex + 1][wIndex + 1] = 'O';
  if ((rowIndex == -1) ||
      ((matrixHeight - rowIndex - 2) < 0)) {
    return true;
  }
  return false;
}

//  Plasarea piesei S
bool placeS(char **charMatrix,
            int rotation,
            int wIndex,
            int matrixHeight) {
  int i, rowIndex = -1;
  if ((rotation == 0) ||
      (rotation == 180)) {
    // Rotatie 0˚ sau 180˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, (i + 1), matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 2, 0, (i + 1), matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'S';
    charMatrix[rowIndex][wIndex + 1] = 'S';
    charMatrix[rowIndex + 1][wIndex + 1] = 'S';
    charMatrix[rowIndex + 1][wIndex + 2] = 'S';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if ((rotation == 90) ||
             (rotation == 270)) {
    // Rotatie 90˚ sau 270˚
    for (i = matrixHeight; i >= 1; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'S';
    charMatrix[rowIndex + 1][wIndex] = 'S';
    charMatrix[rowIndex][wIndex + 1] = 'S';
    charMatrix[rowIndex - 1][wIndex + 1] = 'S';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  }
  return false;
}

//  Plasarea piesei Z
bool placeZ(char **charMatrix,
            int rotation,
            int wIndex,
            int matrixHeight) {
  int i, rowIndex = -1;
  if ((rotation == 0) ||
      (rotation == 180)) {
    // Rotatie 0˚ sau 180˚
    for (i = matrixHeight; i >= 1; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'Z';
    charMatrix[rowIndex][wIndex + 1] = 'Z';
    charMatrix[rowIndex - 1][wIndex + 1] = 'Z';
    charMatrix[rowIndex - 1][wIndex + 2] = 'Z';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if ((rotation == 90) ||
             (rotation == 270)) {
    // Rotatie 90˚ sau 270˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 2), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, (i + 1), matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 1, 0, (i + 1), matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'Z';
    charMatrix[rowIndex + 1][wIndex] = 'Z';
    charMatrix[rowIndex + 1][wIndex + 1] = 'Z';
    charMatrix[rowIndex + 2][wIndex + 1] = 'Z';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  }
  return false;
}

//  Plasarea piesei L
bool placeL(char **charMatrix,
            int rotation,
            int wIndex,
            int matrixHeight) {
  int i, rowIndex = -1;
  if (rotation == 0) {
    //  Rotatie 0˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i + 2), wIndex, charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex + 1][wIndex] = 'L';
    charMatrix[rowIndex + 2][wIndex] = 'L';
    charMatrix[rowIndex][wIndex + 1] = 'L';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  } else if (rotation == 90) {
    //  Rotatie 90˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 2), charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, (i + 1), matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex + 1][wIndex] = 'L';
    charMatrix[rowIndex + 1][wIndex + 1] = 'L';
    charMatrix[rowIndex + 1][wIndex + 2] = 'L';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if (rotation == 180) {
    //  Rotatie 180˚
    for (i = matrixHeight; i >= 2; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i - 2), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex][wIndex + 1] = 'L';
    charMatrix[rowIndex - 1][wIndex + 1] = 'L';
    charMatrix[rowIndex - 2][wIndex + 1] = 'L';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  } else if (rotation == 270) {
    //  Rotatie 270˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex][wIndex + 1] = 'L';
    charMatrix[rowIndex][wIndex + 2] = 'L';
    charMatrix[rowIndex + 1][wIndex + 2] = 'L';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  }
  return false;
}

//  Plasarea piesei J
bool placeJ(char **charMatrix,
            int rotation,
            int wIndex,
            int matrixHeight) {
  int i, rowIndex = -1;
  if (rotation == 0) {
    //  Rotatie 0˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 2), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 2), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex][wIndex + 1] = 'J';
    charMatrix[rowIndex + 1][wIndex + 1] = 'J';
    charMatrix[rowIndex + 2][wIndex + 1] = 'J';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  } else if (rotation == 90) {
    //  Rotatie 90˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex + 1][wIndex] = 'J';
    charMatrix[rowIndex][wIndex + 1] = 'J';
    charMatrix[rowIndex][wIndex + 2] = 'J';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if (rotation == 180) {
    //  Rotatie 180˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i + 2), wIndex, charMatrix)) &&
          (FreeSpot((i + 2), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, (i + 2), matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 1, 0, (i + 2), matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex + 1][wIndex] = 'J';
    charMatrix[rowIndex + 2][wIndex] = 'J';
    charMatrix[rowIndex + 2][wIndex + 1] = 'J';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  } else if (rotation == 270) {
    //  Rotatie 270˚
    for (i = matrixHeight; i >= 1; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 2), charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex][wIndex + 1] = 'J';
    charMatrix[rowIndex][wIndex + 2] = 'J';
    charMatrix[rowIndex - 1][wIndex + 2] = 'J';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 1) < 0)) {
      return true;
    }
  }
  return false;
}

//  Plasarea piesei T
bool placeT(char **charMatrix,
            int rotation,
            int wIndex,
            int matrixHeight) {
  int i, rowIndex = -1;
  if (rotation == 0) {
    //  Rotatie 0˚
    for (i = matrixHeight; i >= 1; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex][wIndex + 1] = 'T';
    charMatrix[rowIndex][wIndex + 2] = 'T';
    charMatrix[rowIndex - 1][wIndex + 1] = 'T';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if (rotation == 90) {
    //  Rotatie 90˚
    for (i = matrixHeight; i >= 1; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex][wIndex + 1] = 'T';
    charMatrix[rowIndex + 1][wIndex + 1] = 'T';
    charMatrix[rowIndex - 1][wIndex + 1] = 'T';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  } else if (rotation == 180) {
    //  Rotatie 180˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex][wIndex + 1] = 'T';
    charMatrix[rowIndex][wIndex + 2] = 'T';
    charMatrix[rowIndex + 1][wIndex + 1] = 'T';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if (rotation == 270) {
    //  Rotatie 270˚
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 2), wIndex, charMatrix)) &&
          (!BreakingTheGame(wIndex, 1, 0, (i + 1), matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if (BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)) {
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex + 1][wIndex + 1] = 'T';
    charMatrix[rowIndex + 1][wIndex] = 'T';
    charMatrix[rowIndex + 2][wIndex] = 'T';
    if ((rowIndex == -1) ||
        ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  }
  return false;
}
