/*
              Curs: Programarea Calculatoarelor
                        Tema 3 - TetriPic
              Nume si prenume: Grigore Lucian-Florin
              Grupa si seria: 314CD
*/
#include "bmp_header.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum { true, false } bool;

void CitireComanda(char **);
void Task1();
void Task2();
<<<<<<< HEAD
void Task3(bool);
void Task4();
=======
>>>>>>> 658ad79b07536f815853140947a2efefddf68a97
void CreateO(bmpFileHeader *, bmpInfoHeader *, char *);
void CreateJ(bmpFileHeader *, bmpInfoHeader *);
void CreateL(bmpFileHeader *, bmpInfoHeader *);
void CreateLAndJ180(bmpFileHeader *, bmpInfoHeader *);
void CreateLAndJHoriz(bmpFileHeader *, bmpInfoHeader *);
void CreateS(bmpFileHeader *, bmpInfoHeader *, char *);
void CreateS90And270(bmpFileHeader *, bmpInfoHeader *);
void CreateZ(bmpFileHeader *, bmpInfoHeader *, char *);
void CreateZ90And270(bmpFileHeader *, bmpInfoHeader *);
void CreateT(bmpFileHeader *, bmpInfoHeader *);
void CreateAllT(bmpFileHeader *, bmpInfoHeader *);
void CreateTVert(bmpFileHeader *, bmpInfoHeader *);
void CreateI(bmpFileHeader *, bmpInfoHeader *, char *);
void CreateI90And270(bmpFileHeader *, bmpInfoHeader *);
void SetDefaultValues(bmpFileHeader *, bmpInfoHeader *);
<<<<<<< HEAD
void SetValues(bmpFileHeader *, bmpInfoHeader *, int, int, bool);
void Write(bmpFileHeader *, bmpInfoHeader *, bmpPixel *, char *, bool);
void WriteMap(bmpFileHeader *, bmpInfoHeader *, bmpPixel **, char *, bool);
void Draw(bmpPixel *, int, int, int, int, bmpPixel);
void DrawMap(bmpPixel **, int, int, int, int, bmpPixel *);
bmpPixel *CreateBitMap(int, int);
bmpPixel **CreateGameBitMap(int, int);
void StartGame(FILE *, int, bmpPixel **, int, int);
void ConvertMatrix(bmpPixel **, char **, int, int);
void CheckCompletedLines(char **, int, int);
bool placeI(char **, int, int, int);
bool placeO(char **, int, int);
bool placeS(char **, int, int, int);
bool placeZ(char **, int, int, int);
bool placeL(char **, int, int, int);
bool placeJ(char **, int, int, int);
bool placeT(char **, int, int, int);

int main(int argc, char *argv[]) {

=======
void Write(bmpFileHeader *, bmpInfoHeader *, bmpPixel *, char *, bool);
bmpPixel *CreateBitMap(int, int);

int main(int argc, char *argv[]) {
>>>>>>> 658ad79b07536f815853140947a2efefddf68a97
  if (argc == 2) {
    CitireComanda(argv);
  };
  return 0;
}

void CitireComanda(char *argv[]) {

  int taskNumber = atoi(argv[1]);
  switch (taskNumber) {
  case 1:
    Task1();
    break;
  case 2:
    Task2();
    break;
<<<<<<< HEAD
  case 3:
    Task3(true);
    break;
  case 4:
    Task4();
    break;
  }
}

void Draw(bmpPixel *bitMap, int start, int end, int width, int lineWidth,
          bmpPixel color) {

  int i, j;
  for (i = start; i <= end; i += lineWidth) {
    for (j = i; j < (i + width); j++) {
      (bitMap + j)->b = color.b;
      (bitMap + j)->g = color.g;
      (bitMap + j)->r = color.r;
    }
  }
}

void DrawMap(bmpPixel **bitMap, int startH, int endH, int startW, int endW,
             bmpPixel *color) {

  int i, j;
  for (i = startH; i < endH; i++) {
    for (j = startW; j < endW; j++) {
      bitMap[i][j].b = color->b;
      bitMap[i][j].r = color->r;
      bitMap[i][j].g = color->g;
    }
=======
>>>>>>> 658ad79b07536f815853140947a2efefddf68a97
  }
}

void Task1() {

  bmpFileHeader *fileHeader = (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
  bmpInfoHeader *infoHeader = (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));
  SetDefaultValues(fileHeader, infoHeader);

  CreateO(fileHeader, infoHeader, "piesa_O.bmp");
  CreateJ(fileHeader, infoHeader);
  CreateL(fileHeader, infoHeader);
  CreateS(fileHeader, infoHeader, "piesa_S.bmp");
  CreateZ(fileHeader, infoHeader, "piesa_Z.bmp");
  CreateT(fileHeader, infoHeader);
  CreateI(fileHeader, infoHeader, "piesa_I.bmp");

  free(fileHeader);
  free(infoHeader);
}

void Task2() {

  bmpFileHeader *fileHeader = (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
  bmpInfoHeader *infoHeader = (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));
  SetDefaultValues(fileHeader, infoHeader);

  CreateO(fileHeader, infoHeader, "piesa_O_90.bmp");
  CreateO(fileHeader, infoHeader, "piesa_O_180.bmp");
  CreateO(fileHeader, infoHeader, "piesa_O_270.bmp");
  CreateI(fileHeader, infoHeader, "piesa_I_180.bmp");
  CreateS(fileHeader, infoHeader, "piesa_S_180.bmp");
  CreateZ(fileHeader, infoHeader, "piesa_Z_180.bmp");
  CreateAllT(fileHeader, infoHeader);
  CreateLAndJ180(fileHeader, infoHeader);
  CreateLAndJHoriz(fileHeader, infoHeader);
  CreateI90And270(fileHeader, infoHeader);
  CreateS90And270(fileHeader, infoHeader);
  CreateZ90And270(fileHeader, infoHeader);

  free(fileHeader);
  free(infoHeader);
}

<<<<<<< HEAD
void Task3(bool newMap) {

  FILE *ffile;
  ffile = fopen("cerinta3.in", "r");

  if (ffile != NULL) {
    if (newMap == true) {
      int N, H, L, height, width;
      bool hasPadding = false;
      fscanf(ffile, "%d %d %d\n", &N, &H, &L);
      width = L * 10;
      height = H * 10;
      if ((width % 4) != 0) {
        hasPadding = true;
        width += 2;
      }
      bmpFileHeader *fileHeader =
          (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
      bmpInfoHeader *infoHeader =
          (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));
      SetDefaultValues(fileHeader, infoHeader);
      SetValues(fileHeader, infoHeader, width, height, hasPadding);
      bmpPixel(**bitMap) = CreateGameBitMap(width, height);
      StartGame(ffile, N, bitMap, H, L);
      WriteMap(fileHeader, infoHeader, bitMap, "task3.bmp", hasPadding);
      int i;
      for (i = 0; i < (infoHeader->height); i++) {
        free(bitMap[i]);
      }
      free(bitMap);
      free(fileHeader);
      free(infoHeader);
    } else {
    }
    fclose(ffile);
  }
}

void Task4() {}

void StartGame(FILE *ffile, int numberOfPieces, bmpPixel **bitMap, int height,
               int width) {

  int i, j, k;
  char **charMatrix = (char **)malloc(height + 4);
  for (i = 0; i < (height + 4); i++) {
    charMatrix[i] = (char *)malloc(width);
  }

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
  k = 0;
  while (k < numberOfPieces) {
    int widthIndex, rotation;
    char pieceIndex = '\0';
    bool endGame = false;
    fscanf(ffile, "%c %d %d\n", &pieceIndex, &rotation, &widthIndex);
    k++;
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
    }
    if (endGame == true) {
      break;
    } else {
      CheckCompletedLines(charMatrix, height, width);
    }
  }
  ConvertMatrix(bitMap, charMatrix, width, height);
  for (i = 0; i < (height + 4); i++) {
    free(charMatrix[i]);
  }
  free(charMatrix);
}

void CheckCompletedLines(char **charMatrix, int height, int width) {

  int i, j;
  for (i = 0; i < height; i++) {
    bool completedLine = true;
    for (j = 0; j < width; j++) {
      if (charMatrix[i][j] == 'N') {
        completedLine = false;
      }
    }
    if (completedLine == true) {
      int k, lastLine = (height - 1);
      for (k = i; k < (height - 1); k++) {
        for (j = 0; j < width; j++) {
          charMatrix[k][j] = charMatrix[k + 1][j];
        }
      }
      for (k = 0; k < height; k++) {
        for (j = 0; j < width; j++) {
          if (charMatrix[k][j] != 'N') {
            lastLine = k;
          }
        }
      }
      for (k = 0; k < width; k++) {
        charMatrix[lastLine][k] = 'N';
      }
    }
  }
}

bool placeI(char **charMatrix, int rotation, int wIndex, int matrixHeight) {

  int i, rowIndex = -1;
  if ((rotation == 0) || (rotation == 180)) {
    for (i = (matrixHeight - 1); i >= 0; i--) {
      if (charMatrix[i][wIndex] == 'N') {
        rowIndex = i;
      }
    }
    if ((rowIndex == -1) || ((matrixHeight - rowIndex) < 0)) {
      return true;
    }
    for (i = rowIndex; i < (rowIndex + 4); i++) {
      charMatrix[i][wIndex] = 'I';
    }
  } else if ((rotation == 90) || (rotation == 270)) {
    for (i = (matrixHeight - 1); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i][wIndex + 2] == 'N') &&
          (charMatrix[i][wIndex + 3] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'I';
    charMatrix[rowIndex][wIndex + 1] = 'I';
    charMatrix[rowIndex][wIndex + 2] = 'I';
    charMatrix[rowIndex][wIndex + 3] = 'I';
  }
  return false;
}

bool placeO(char **charMatrix, int wIndex, int matrixHeight) {

  int i, rowIndex = -1;
  for (i = (matrixHeight - 2); i >= 0; i--) {
    if ((charMatrix[i][wIndex] == 'N') && (charMatrix[i][wIndex + 1] == 'N') &&
        (charMatrix[i + 1][wIndex] == 'N') &&
        (charMatrix[i + 1][wIndex + 1] == 'N')) {
      rowIndex = i;
    }
  }
  if (rowIndex == -1) {
    return true;
  }
  charMatrix[rowIndex][wIndex] = 'O';
  charMatrix[rowIndex][wIndex + 1] = 'O';
  charMatrix[rowIndex + 1][wIndex] = 'O';
  charMatrix[rowIndex + 1][wIndex + 1] = 'O';
  return false;
}

bool placeS(char **charMatrix, int rotation, int wIndex, int matrixHeight) {

  int i, rowIndex = -1;
  if ((rotation == 0) || (rotation == 180)) {
    for (i = (matrixHeight - 2); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i + 1][wIndex + 1] == 'N') &&
          (charMatrix[i + 1][wIndex + 2] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'S';
    charMatrix[rowIndex][wIndex + 1] = 'S';
    charMatrix[rowIndex + 1][wIndex + 1] = 'S';
    charMatrix[rowIndex + 1][wIndex + 2] = 'S';
  } else if ((rotation == 90) || (rotation == 270)) {
    for (i = (matrixHeight - 2); i >= 1; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i + 1][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i - 1][wIndex + 1] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'S';
    charMatrix[rowIndex + 1][wIndex] = 'S';
    charMatrix[rowIndex][wIndex + 1] = 'S';
    charMatrix[rowIndex - 1][wIndex + 1] = 'S';
  }
  return false;
}

bool placeZ(char **charMatrix, int rotation, int wIndex, int matrixHeight) {

  int i, rowIndex = -1;
  if ((rotation == 0) || (rotation == 180)) {
    for (i = (matrixHeight - 2); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i + 1][wIndex + 1] == 'N') &&
          (charMatrix[i + 1][wIndex + 2] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'Z';
    charMatrix[rowIndex][wIndex + 1] = 'Z';
    charMatrix[rowIndex + 1][wIndex + 1] = 'Z';
    charMatrix[rowIndex + 1][wIndex + 2] = 'Z';
  } else if ((rotation == 90) || (rotation == 270)) {
    for (i = (matrixHeight - 3); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i + 1][wIndex] == 'N') &&
          (charMatrix[i + 1][wIndex + 1] == 'N') &&
          (charMatrix[i + 2][wIndex + 1] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'Z';
    charMatrix[rowIndex + 1][wIndex] = 'Z';
    charMatrix[rowIndex + 1][wIndex + 1] = 'Z';
    charMatrix[rowIndex + 2][wIndex + 1] = 'Z';
  }
  return false;
}

bool placeL(char **charMatrix, int rotation, int wIndex, int matrixHeight) {

  int i, rowIndex = -1;
  if (rotation == 0) {
    for (i = (matrixHeight - 3); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i + 1][wIndex] == 'N') &&
          (charMatrix[i + 2][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex + 1][wIndex] = 'L';
    charMatrix[rowIndex + 2][wIndex] = 'L';
    charMatrix[rowIndex][wIndex + 1] = 'L';
  } else if (rotation == 90) {
    for (i = (matrixHeight - 2); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i + 1][wIndex] == 'N') &&
          (charMatrix[i + 1][wIndex + 1] == 'N') &&
          (charMatrix[i + 1][wIndex + 2] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex + 1][wIndex] = 'L';
    charMatrix[rowIndex + 1][wIndex + 1] = 'L';
    charMatrix[rowIndex + 1][wIndex + 2] = 'L';
  } else if (rotation == 180) {
    for (i = (matrixHeight - 1); i >= 2; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i - 1][wIndex + 1] == 'N') &&
          (charMatrix[i - 2][wIndex + 1] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex][wIndex + 1] = 'L';
    charMatrix[rowIndex - 1][wIndex + 1] = 'L';
    charMatrix[rowIndex - 2][wIndex + 1] = 'L';
  } else if (rotation == 270) {
    for (i = (matrixHeight - 3); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i + 1][wIndex] == 'N') &&
          (charMatrix[i + 2][wIndex] == 'N') &&
          (charMatrix[i + 2][wIndex + 1] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex + 1][wIndex] = 'L';
    charMatrix[rowIndex + 2][wIndex] = 'L';
    charMatrix[rowIndex + 2][wIndex + 1] = 'L';
  }
  return false;
}

bool placeJ(char **charMatrix, int rotation, int wIndex, int matrixHeight) {

  int i, rowIndex = -1;
  if (rotation == 0) {
    for (i = (matrixHeight - 3); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i + 1][wIndex] == 'N') &&
          (charMatrix[i + 2][wIndex] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex][wIndex + 1] = 'J';
    charMatrix[rowIndex + 1][wIndex] = 'J';
    charMatrix[rowIndex + 2][wIndex] = 'J';
  } else if (rotation == 90) {
    for (i = (matrixHeight - 2); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i + 1][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i][wIndex + 2] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex + 1][wIndex] = 'J';
    charMatrix[rowIndex][wIndex + 1] = 'J';
    charMatrix[rowIndex][wIndex + 2] = 'J';
  } else if (rotation == 180) {
    for (i = (matrixHeight - 3); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i + 1][wIndex] == 'N') &&
          (charMatrix[i + 2][wIndex] == 'N') &&
          (charMatrix[i + 2][wIndex + 1] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex + 1][wIndex] = 'J';
    charMatrix[rowIndex + 2][wIndex] = 'J';
    charMatrix[rowIndex + 2][wIndex + 1] = 'J';
  } else if (rotation == 270) {
    for (i = (matrixHeight - 1); i >= 1; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i][wIndex + 2] == 'N') &&
          (charMatrix[i - 1][wIndex + 2] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex][wIndex + 1] = 'J';
    charMatrix[rowIndex][wIndex + 2] = 'J';
    charMatrix[rowIndex - 1][wIndex + 2] = 'J';
  }
  return false;
}

bool placeT(char **charMatrix, int rotation, int wIndex, int matrixHeight) {

  int i, rowIndex = -1;
  if (rotation == 0) {
    for (i = (matrixHeight - 1); i >= 1; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i][wIndex + 2] == 'N') &&
          (charMatrix[i - 1][wIndex + 1] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex][wIndex + 1] = 'T';
    charMatrix[rowIndex][wIndex + 2] = 'T';
    charMatrix[rowIndex - 1][wIndex + 1] = 'T';
  } else if (rotation == 90) {
    for (i = (matrixHeight - 2); i >= 1; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i + 1][wIndex + 1] == 'N') &&
          (charMatrix[i - 1][wIndex + 1] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex][wIndex + 1] = 'T';
    charMatrix[rowIndex + 1][wIndex + 1] = 'T';
    charMatrix[rowIndex - 1][wIndex + 1] = 'T';
  } else if (rotation == 180) {
    for (i = (matrixHeight - 2); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i][wIndex + 1] == 'N') &&
          (charMatrix[i][wIndex + 2] == 'N') &&
          (charMatrix[i + 1][wIndex + 1] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex][wIndex + 1] = 'T';
    charMatrix[rowIndex][wIndex + 2] = 'T';
    charMatrix[rowIndex + 1][wIndex + 1] = 'T';
  } else if (rotation == 270) {
    for (i = (matrixHeight - 3); i >= 0; i--) {
      if ((charMatrix[i][wIndex] == 'N') &&
          (charMatrix[i + 1][wIndex + 1] == 'N') &&
          (charMatrix[i + 1][wIndex] == 'N') &&
          (charMatrix[i + 2][wIndex] == 'N')) {
        rowIndex = i;
      }
    }
    if (rowIndex == -1) {
      return true;
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex + 1][wIndex + 1] = 'T';
    charMatrix[rowIndex + 1][wIndex] = 'T';
    charMatrix[rowIndex + 2][wIndex] = 'T';
  }
  return false;
}

void CreateO(bmpFileHeader *fileHeaderO, bmpInfoHeader *infoHeaderO,
             char *numePiesa) {

=======
void CreateO(bmpFileHeader *fileHeaderO, bmpInfoHeader *infoHeaderO,
             char *numePiesa) {

>>>>>>> 658ad79b07536f815853140947a2efefddf68a97
  fileHeaderO->bfSize = 4854;
  infoHeaderO->width = 40;
  infoHeaderO->height = 40;
  infoHeaderO->biSizeImage = 4800;
<<<<<<< HEAD
  bmpPixel colorO = {0, 255, 255};

  bmpPixel *bitMapO = CreateBitMap(infoHeaderO->width, infoHeaderO->height);
  Draw(bitMapO, 410, 1209, 20, 40, colorO);
=======

  bmpPixel *bitMapO = CreateBitMap(infoHeaderO->width, infoHeaderO->height);
  int i, j;
  for (i = 410; i <= 1209; i += 40) {
    for (j = i; j < (i + 20); j++) {
      (bitMapO + j)->b = 0;
      (bitMapO + j)->g = 255;
      (bitMapO + j)->r = 255;
    }
  }

>>>>>>> 658ad79b07536f815853140947a2efefddf68a97
  Write(fileHeaderO, infoHeaderO, bitMapO, numePiesa, false);
  free(bitMapO);
}

void CreateJ(bmpFileHeader *fileHeaderJ, bmpInfoHeader *infoHeaderJ) {

  fileHeaderJ->bfSize = 6054;
  infoHeaderJ->width = 40;
  infoHeaderJ->height = 50;
  infoHeaderJ->biSizeImage = 6000;
<<<<<<< HEAD
  bmpPixel colorJ = {255, 0, 255};

  bmpPixel *bitMapJ = CreateBitMap(infoHeaderJ->width, infoHeaderJ->height);
  Draw(bitMapJ, 410, 809, 20, 40, colorJ);
  Draw(bitMapJ, 820, 1619, 10, 40, colorJ);
=======

  bmpPixel *bitMapJ = CreateBitMap(infoHeaderJ->width, infoHeaderJ->height);
  int i, j;
  for (i = 410; i <= 809; i += 40) {
    for (j = i; j < (i + 20); j++) {
      (bitMapJ + j)->b = 255;
      (bitMapJ + j)->g = 0;
      (bitMapJ + j)->r = 255;
    }
  }
  for (i = 820; i <= 1619; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapJ + j)->b = 255;
      (bitMapJ + j)->g = 0;
      (bitMapJ + j)->r = 255;
    }
  }
>>>>>>> 658ad79b07536f815853140947a2efefddf68a97
  Write(fileHeaderJ, infoHeaderJ, bitMapJ, "piesa_J.bmp", false);
  free(bitMapJ);
}

void CreateL(bmpFileHeader *fileHeaderL, bmpInfoHeader *infoHeaderL) {

  fileHeaderL->bfSize = 6054;
  infoHeaderL->width = 40;
  infoHeaderL->height = 50;
  infoHeaderL->biSizeImage = 6000;
<<<<<<< HEAD
  bmpPixel colorL = {0, 140, 255};

  bmpPixel *bitMapL = CreateBitMap(infoHeaderL->width, infoHeaderL->height);
  Draw(bitMapL, 410, 809, 20, 40, colorL);
  Draw(bitMapL, 810, 1609, 10, 40, colorL);
  Write(fileHeaderL, infoHeaderL, bitMapL, "piesa_L.bmp", false);
  free(bitMapL);
}

void CreateLAndJ180(bmpFileHeader *fileHeaderLJ, bmpInfoHeader *infoHeaderLJ) {

  fileHeaderLJ->bfSize = 6054;
  infoHeaderLJ->width = 40;
  infoHeaderLJ->height = 50;
  infoHeaderLJ->biSizeImage = 6000;
  bmpPixel colorL = {0, 140, 255};
  bmpPixel colorJ = {255, 0, 255};

  bmpPixel *bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 420, 1619, 10, 40, colorL);
  Draw(bitMapLJ, 1210, 1609, 10, 40, colorL);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_L_180.bmp", false);
  free(bitMapLJ);

  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 410, 1609, 10, 40, colorJ);
  Draw(bitMapLJ, 1220, 1619, 10, 40, colorJ);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_J_180.bmp", false);
  free(bitMapLJ);
}

void CreateLAndJHoriz(bmpFileHeader *fileHeaderLJ,
                      bmpInfoHeader *infoHeaderLJ) {

  fileHeaderLJ->bfSize = 6134;
  infoHeaderLJ->width = 52;
  infoHeaderLJ->height = 40;
  infoHeaderLJ->biSizeImage = 6080;
  bmpPixel colorL = {0, 140, 255};
  bmpPixel colorJ = {255, 0, 255};

  bmpPixel *bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 530, 1049, 30, 52, colorL);
  Draw(bitMapLJ, 1070, 1589, 10, 52, colorL);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_L_270.bmp", true);
  free(bitMapLJ);
  infoHeaderLJ->width += 2;

  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 550, 1069, 10, 52, colorJ);
  Draw(bitMapLJ, 1050, 1569, 30, 52, colorJ);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_J_270.bmp", true);
  free(bitMapLJ);
  infoHeaderLJ->width += 2;

  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 530, 1049, 10, 52, colorL);
  Draw(bitMapLJ, 1050, 1559, 30, 52, colorL);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_L_90.bmp", true);
  free(bitMapLJ);
  infoHeaderLJ->width += 2;

  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 530, 1049, 30, 52, colorJ);
  Draw(bitMapLJ, 1050, 1559, 10, 52, colorJ);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_J_90.bmp", true);
  free(bitMapLJ);
}

void CreateI(bmpFileHeader *fileHeaderI, bmpInfoHeader *infoHeaderI,
             char *numePiesa) {

  fileHeaderI->bfSize = 5574;
  infoHeaderI->width = 32;
  infoHeaderI->height = 60;
  infoHeaderI->biSizeImage = 5520;
  bmpPixel colorI = {255, 0, 0};

  bmpPixel *bitMapI = CreateBitMap(infoHeaderI->width, infoHeaderI->height);
  Draw(bitMapI, 330, 1609, 10, 32, colorI);
  Write(fileHeaderI, infoHeaderI, bitMapI, numePiesa, true);
  free(bitMapI);
}

void CreateI90And270(bmpFileHeader *fileHeaderI, bmpInfoHeader *infoHeaderI) {

  fileHeaderI->bfSize = 5454;
  infoHeaderI->width = 60;
  infoHeaderI->height = 30;
  infoHeaderI->biSizeImage = 5400;
  bmpPixel colorI = {255, 0, 0};

  bmpPixel *bitMapI = CreateBitMap(infoHeaderI->width, infoHeaderI->height);
  Draw(bitMapI, 610, 1209, 40, 60, colorI);
  Write(fileHeaderI, infoHeaderI, bitMapI, "piesa_I_90.bmp", false);
  Write(fileHeaderI, infoHeaderI, bitMapI, "piesa_I_270.bmp", false);
  free(bitMapI);
}

void CreateT(bmpFileHeader *fileHeaderT, bmpInfoHeader *infoHeaderT) {

  fileHeaderT->bfSize = 6134;
  infoHeaderT->width = 52;
  infoHeaderT->height = 40;
  infoHeaderT->biSizeImage = 6080;
  bmpPixel colorT = {255, 0, 130};

  bmpPixel *bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  Draw(bitMapT, 540, 1059, 10, 52, colorT);
  Draw(bitMapT, 1050, 1569, 30, 52, colorT);
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T.bmp", true);
  free(bitMapT);
}

void CreateAllT(bmpFileHeader *fileHeaderT, bmpInfoHeader *infoHeaderT) {

  fileHeaderT->bfSize = 6134;
  infoHeaderT->width = 52;
  infoHeaderT->height = 40;
  infoHeaderT->biSizeImage = 6080;
  bmpPixel colorT = {255, 0, 130};

  bmpPixel *bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  Draw(bitMapT, 530, 1049, 30, 52, colorT);
  Draw(bitMapT, 1060, 1579, 10, 52, colorT);
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T_180.bmp", true);
  free(bitMapT);
  CreateTVert(fileHeaderT, infoHeaderT);
}

void CreateTVert(bmpFileHeader *fileHeaderT, bmpInfoHeader *infoHeaderT) {

  fileHeaderT->bfSize = 6054;
  infoHeaderT->width = 40;
  infoHeaderT->height = 50;
  infoHeaderT->biSizeImage = 6000;
  bmpPixel colorT = {255, 0, 130};

  bmpPixel *bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  Draw(bitMapT, 410, 1609, 10, 40, colorT);
  Draw(bitMapT, 820, 1219, 10, 40, colorT);
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T_270.bmp", false);
  free(bitMapT);

  bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  Draw(bitMapT, 420, 1619, 10, 40, colorT);
  Draw(bitMapT, 810, 1209, 10, 40, colorT);
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T_90.bmp", false);
  free(bitMapT);
}

void CreateZ(bmpFileHeader *fileHeaderZ, bmpInfoHeader *infoHeaderZ,
             char *numePiesa) {

  fileHeaderZ->bfSize = 6134;
  infoHeaderZ->width = 52;
  infoHeaderZ->height = 40;
  infoHeaderZ->biSizeImage = 6080;
  bmpPixel colorZ = {0, 255, 0};

  bmpPixel *bitMapZ = CreateBitMap(infoHeaderZ->width, infoHeaderZ->height);
  Draw(bitMapZ, 540, 1059, 20, 52, colorZ);
  Draw(bitMapZ, 1050, 1569, 20, 52, colorZ);
  Write(fileHeaderZ, infoHeaderZ, bitMapZ, numePiesa, true);
  free(bitMapZ);
}

void CreateZ90And270(bmpFileHeader *fileHeaderZ, bmpInfoHeader *infoHeaderZ) {

  fileHeaderZ->bfSize = 6054;
  infoHeaderZ->width = 40;
  infoHeaderZ->height = 50;
  infoHeaderZ->biSizeImage = 6000;
  bmpPixel colorZ = {0, 255, 0};

  bmpPixel *bitMapZ = CreateBitMap(infoHeaderZ->width, infoHeaderZ->height);
  Draw(bitMapZ, 410, 1209, 10, 40, colorZ);
  Draw(bitMapZ, 820, 1619, 10, 40, colorZ);
  Write(fileHeaderZ, infoHeaderZ, bitMapZ, "piesa_Z_90.bmp", false);
  Write(fileHeaderZ, infoHeaderZ, bitMapZ, "piesa_Z_270.bmp", false);
  free(bitMapZ);
}

void CreateS(bmpFileHeader *fileHeaderS, bmpInfoHeader *infoHeaderS,
             char *numePiesa) {

  fileHeaderS->bfSize = 6134;
  infoHeaderS->width = 52;
  infoHeaderS->height = 40;
  infoHeaderS->biSizeImage = 6080;
  bmpPixel colorS = {0, 0, 255};

  bmpPixel *bitMapS = CreateBitMap(infoHeaderS->width, infoHeaderS->height);
  Draw(bitMapS, 530, 1049, 20, 52, colorS);
  Draw(bitMapS, 1060, 1579, 20, 52, colorS);
  Write(fileHeaderS, infoHeaderS, bitMapS, numePiesa, true);
  free(bitMapS);
}

void CreateS90And270(bmpFileHeader *fileHeaderS, bmpInfoHeader *infoHeaderS) {

  fileHeaderS->bfSize = 6054;
  infoHeaderS->width = 40;
  infoHeaderS->height = 50;
  infoHeaderS->biSizeImage = 6000;
  bmpPixel colorS = {0, 0, 255};

  bmpPixel *bitMapS = CreateBitMap(infoHeaderS->width, infoHeaderS->height);
  Draw(bitMapS, 420, 1219, 10, 40, colorS);
  Draw(bitMapS, 810, 1609, 10, 40, colorS);
  Write(fileHeaderS, infoHeaderS, bitMapS, "piesa_S_90.bmp", false);
  Write(fileHeaderS, infoHeaderS, bitMapS, "piesa_S_270.bmp", false);
  free(bitMapS);
}

void SetDefaultValues(bmpFileHeader *fileHeader, bmpInfoHeader *infoHeader) {

  fileHeader->fileMarker1 = 'B';
  fileHeader->fileMarker2 = 'M';
  fileHeader->unused1 = 0;
  fileHeader->unused2 = 0;
  fileHeader->imageDataOffset = 54;

  infoHeader->biSize = 40;
  infoHeader->planes = 1;
  infoHeader->bitPix = 24;
  infoHeader->biCompression = 0;
  infoHeader->biXPelsPerMeter = 0;
  infoHeader->biYPelsPerMeter = 0;
  infoHeader->biClrUsed = 0;
  infoHeader->biClrImportant = 0;
}

void SetValues(bmpFileHeader *fileHeader, bmpInfoHeader *infoHeader, int width,
               int height, bool hasPadding) {

  infoHeader->height = (height + 40);
  if (hasPadding == true) {
    infoHeader->width = (width + 2);
    infoHeader->biSizeImage = ((height + 40) * width * 3) + (2 * height);
  } else {
    infoHeader->width = width;
    infoHeader->biSizeImage = ((height + 40) * width * 3);
  }
  fileHeader->bfSize = infoHeader->biSizeImage + 54;
}

bmpPixel *CreateBitMap(int width, int height) {

  bmpPixel *bitMap = (bmpPixel *)malloc(width * height * (int)sizeof(bmpPixel));
  int i;
  for (i = 0; i < (width * height); i++) {
    (bitMap + i)->b = 255;
    (bitMap + i)->g = 255;
    (bitMap + i)->r = 255;
  }
  return bitMap;
}

bmpPixel **CreateGameBitMap(int width, int height) {

  bmpPixel **bitMap =
      (bmpPixel **)malloc((height + (40 * width)) * (int)sizeof(bmpPixel));
  int i;
  for (i = 0; i < (height + (40 * width)); i++) {
    bitMap[i] = (bmpPixel *)malloc(width * (int)sizeof(bmpPixel));
  }
  bmpPixel *colorWhite = (bmpPixel *)malloc(sizeof(bmpPixel));
  colorWhite->b = 255;
  colorWhite->r = 255;
  colorWhite->g = 255;
  bmpPixel *colorBlack = (bmpPixel *)malloc(sizeof(bmpPixel));
  colorBlack->b = 0;
  colorBlack->r = 0;
  colorBlack->g = 0;
  DrawMap(bitMap, 0, height, 0, width, colorBlack);
  DrawMap(bitMap, height, (height + (40 * width) - 1), 0, width, colorWhite);
  return bitMap;
}

void ConvertMatrix(bmpPixel **bitMap, char **charMatrix, int width,
                   int height) {

  bmpPixel colorL = {0, 140, 255}, colorJ = {255, 0, 255}, colorI = {255, 0, 0},
           colorO = {0, 255, 255}, colorS = {0, 0, 255}, colorZ = {0, 255, 0},
           colorT = {255, 0, 130};
  int i, j;
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      switch (charMatrix[i][j]) {
      case 'L':
        DrawMap(bitMap, (i * 10), ((i + 1) * 10), (j * 10), ((j + 1) * 10),
                &colorL);
        break;
      case 'J':
        DrawMap(bitMap, (i * 10), ((i + 1) * 10), (j * 10), ((j + 1) * 10),
                &colorJ);
        break;
      case 'T':
        DrawMap(bitMap, (i * 10), ((i + 1) * 10), (j * 10), ((j + 1) * 10),
                &colorT);
        break;
      case 'I':
        DrawMap(bitMap, (i * 10), ((i + 1) * 10), (j * 10), ((j + 1) * 10),
                &colorI);
        break;
      case 'O':
        DrawMap(bitMap, (i * 10), ((i + 1) * 10), (j * 10), ((j + 1) * 10),
                &colorO);
        break;
      case 'S':
        DrawMap(bitMap, (i * 10), ((i + 1) * 10), (j * 10), ((j + 1) * 10),
                &colorS);
        break;
      case 'Z':
        DrawMap(bitMap, (i * 10), ((i + 1) * 10), (j * 10), ((j + 1) * 10),
                &colorZ);
        break;
      }
    }
  }
}

void Write(bmpFileHeader *fileHeader, bmpInfoHeader *infoHeader,
           bmpPixel *bitMap, char *numeFisier, bool addPadding) {

=======

  bmpPixel *bitMapL = CreateBitMap(infoHeaderL->width, infoHeaderL->height);
  int i, j;
  for (i = 410; i <= 809; i += 40) {
    for (j = i; j < (i + 20); j++) {
      (bitMapL + j)->b = 0;
      (bitMapL + j)->g = 140;
      (bitMapL + j)->r = 255;
    }
  }
  for (i = 810; i <= 1609; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapL + j)->b = 0;
      (bitMapL + j)->g = 140;
      (bitMapL + j)->r = 255;
    }
  }
  Write(fileHeaderL, infoHeaderL, bitMapL, "piesa_L.bmp", false);
  free(bitMapL);
}

void CreateLAndJ180(bmpFileHeader *fileHeaderLJ, bmpInfoHeader *infoHeaderLJ) {

  fileHeaderLJ->bfSize = 6054;
  infoHeaderLJ->width = 40;
  infoHeaderLJ->height = 50;
  infoHeaderLJ->biSizeImage = 6000;

  bmpPixel *bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  int i, j;
  for (i = 420; i <= 1619; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapLJ + j)->b = 0;
      (bitMapLJ + j)->g = 140;
      (bitMapLJ + j)->r = 255;
    }
  }
  for (i = 1210; i <= 1609; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapLJ + j)->b = 0;
      (bitMapLJ + j)->g = 140;
      (bitMapLJ + j)->r = 255;
    }
  }
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_L_180.bmp", false);
  free(bitMapLJ);

  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  for (i = 410; i <= 1609; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapLJ + j)->b = 255;
      (bitMapLJ + j)->g = 0;
      (bitMapLJ + j)->r = 255;
    }
  }
  for (i = 1220; i <= 1619; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapLJ + j)->b = 255;
      (bitMapLJ + j)->g = 0;
      (bitMapLJ + j)->r = 255;
    }
  }
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_J_180.bmp", false);
  free(bitMapLJ);
}

void CreateLAndJHoriz(bmpFileHeader *fileHeaderLJ,
                      bmpInfoHeader *infoHeaderLJ) {

  fileHeaderLJ->bfSize = 6134;
  infoHeaderLJ->width = 52;
  infoHeaderLJ->height = 40;
  infoHeaderLJ->biSizeImage = 6080;

  bmpPixel *bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  int i, j;
  for (i = 530; i <= 1049; i += 52) {
    for (j = i; j < (i + 30); j++) {
      (bitMapLJ + j)->b = 0;
      (bitMapLJ + j)->g = 140;
      (bitMapLJ + j)->r = 255;
    }
  }
  for (i = 1070; i <= 1589; i += 52) {
    for (j = i; j < (i + 10); j++) {
      (bitMapLJ + j)->b = 0;
      (bitMapLJ + j)->g = 140;
      (bitMapLJ + j)->r = 255;
    }
  }
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_L_270.bmp", true);
  free(bitMapLJ);
  infoHeaderLJ->width += 2;

  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  for (i = 550; i <= 1069; i += 52) {
    for (j = i; j < (i + 10); j++) {
      (bitMapLJ + j)->b = 255;
      (bitMapLJ + j)->g = 0;
      (bitMapLJ + j)->r = 255;
    }
  }
  for (i = 1050; i <= 1569; i += 52) {
    for (j = i; j < (i + 30); j++) {
      (bitMapLJ + j)->b = 255;
      (bitMapLJ + j)->g = 0;
      (bitMapLJ + j)->r = 255;
    }
  }
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_J_270.bmp", true);
  free(bitMapLJ);
  infoHeaderLJ->width += 2;

  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  for (i = 530; i <= 1049; i += 52) {
    for (j = i; j < (i + 10); j++) {
      (bitMapLJ + j)->b = 0;
      (bitMapLJ + j)->g = 140;
      (bitMapLJ + j)->r = 255;
    }
  }
  for (i = 1050; i <= 1559; i += 52) {
    for (j = i; j < (i + 30); j++) {
      (bitMapLJ + j)->b = 0;
      (bitMapLJ + j)->g = 140;
      (bitMapLJ + j)->r = 255;
    }
  }
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_L_90.bmp", true);
  free(bitMapLJ);
  infoHeaderLJ->width += 2;

  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  for (i = 530; i <= 1049; i += 52) {
    for (j = i; j < (i + 30); j++) {
      (bitMapLJ + j)->b = 255;
      (bitMapLJ + j)->g = 0;
      (bitMapLJ + j)->r = 255;
    }
  }
  for (i = 1050; i <= 1559; i += 52) {
    for (j = i; j < (i + 10); j++) {
      (bitMapLJ + j)->b = 255;
      (bitMapLJ + j)->g = 0;
      (bitMapLJ + j)->r = 255;
    }
  }
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_J_90.bmp", true);
  free(bitMapLJ);
}

void CreateI(bmpFileHeader *fileHeaderI, bmpInfoHeader *infoHeaderI,
             char *numePiesa) {

  fileHeaderI->bfSize = 5574;
  infoHeaderI->width = 32;
  infoHeaderI->height = 60;
  infoHeaderI->biSizeImage = 5520;

  bmpPixel *bitMapI = CreateBitMap(infoHeaderI->width, infoHeaderI->height);
  int i, j;
  for (i = 330; i <= 1609; i += 32) {
    for (j = i; j < (i + 10); j++) {
      (bitMapI + j)->b = 255;
      (bitMapI + j)->g = 0;
      (bitMapI + j)->r = 0;
    }
  }
  Write(fileHeaderI, infoHeaderI, bitMapI, numePiesa, true);
  free(bitMapI);
}

void CreateI90And270(bmpFileHeader *fileHeaderI, bmpInfoHeader *infoHeaderI) {

  fileHeaderI->bfSize = 5454;
  infoHeaderI->width = 60;
  infoHeaderI->height = 30;
  infoHeaderI->biSizeImage = 5400;

  bmpPixel *bitMapI = CreateBitMap(infoHeaderI->width, infoHeaderI->height);
  int i, j;
  for (i = 610; i <= 1209; i += 60) {
    for (j = i; j < (i + 40); j++) {
      (bitMapI + j)->b = 255;
      (bitMapI + j)->g = 0;
      (bitMapI + j)->r = 0;
    }
  }

  Write(fileHeaderI, infoHeaderI, bitMapI, "piesa_I_90.bmp", false);
  Write(fileHeaderI, infoHeaderI, bitMapI, "piesa_I_270.bmp", false);
  free(bitMapI);
}

void CreateT(bmpFileHeader *fileHeaderT, bmpInfoHeader *infoHeaderT) {

  fileHeaderT->bfSize = 6134;
  infoHeaderT->width = 52;
  infoHeaderT->height = 40;
  infoHeaderT->biSizeImage = 6080;

  bmpPixel *bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  int i, j;
  for (i = 540; i <= 1059; i += 52) {
    for (j = i; j < (i + 10); j++) {
      (bitMapT + j)->b = 255;
      (bitMapT + j)->g = 0;
      (bitMapT + j)->r = 130;
    }
  }
  for (i = 1050; i <= 1569; i += 52) {
    for (j = i; j < (i + 30); j++) {
      (bitMapT + j)->b = 255;
      (bitMapT + j)->g = 0;
      (bitMapT + j)->r = 130;
    }
  }
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T.bmp", true);
  free(bitMapT);
}

void CreateAllT(bmpFileHeader *fileHeaderT, bmpInfoHeader *infoHeaderT){

  fileHeaderT->bfSize = 6134;
  infoHeaderT->width = 52;
  infoHeaderT->height = 40;
  infoHeaderT->biSizeImage = 6080;

  bmpPixel *bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  int i, j;
  for (i = 530; i <= 1049; i += 52) {
    for (j = i; j < (i + 30); j++) {
      (bitMapT + j)->b = 255;
      (bitMapT + j)->g = 0;
      (bitMapT + j)->r = 130;
    }
  }
  for (i = 1060; i <= 1579; i += 52) {
    for (j = i; j < (i + 10); j++) {
      (bitMapT + j)->b = 255;
      (bitMapT + j)->g = 0;
      (bitMapT + j)->r = 130;
    }
  }
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T_180.bmp", true);
  free(bitMapT);
  CreateTVert(fileHeaderT, infoHeaderT);
}

void CreateTVert(bmpFileHeader *fileHeaderT, bmpInfoHeader *infoHeaderT){

  fileHeaderT->bfSize = 6054;
  infoHeaderT->width = 40;
  infoHeaderT->height = 50;
  infoHeaderT->biSizeImage = 6000;

  bmpPixel *bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  int i, j;
  for (i = 410; i <= 1609; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapT + j)->b = 255;
      (bitMapT + j)->g = 0;
      (bitMapT + j)->r = 130;
    }
  }
  for (i = 820; i <= 1219; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapT + j)->b = 255;
      (bitMapT + j)->g = 0;
      (bitMapT + j)->r = 130;
    }
  }
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T_270.bmp", false);
  free(bitMapT);

  bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  for (i = 420; i <= 1619; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapT + j)->b = 255;
      (bitMapT + j)->g = 0;
      (bitMapT + j)->r = 130;
    }
  }
  for (i = 810; i <= 1209; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapT + j)->b = 255;
      (bitMapT + j)->g = 0;
      (bitMapT + j)->r = 130;
    }
  }
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T_90.bmp", false);
  free(bitMapT);
}

void CreateZ(bmpFileHeader *fileHeaderZ, bmpInfoHeader *infoHeaderZ,
             char *numePiesa) {

  fileHeaderZ->bfSize = 6134;
  infoHeaderZ->width = 52;
  infoHeaderZ->height = 40;
  infoHeaderZ->biSizeImage = 6080;

  bmpPixel *bitMapZ = CreateBitMap(infoHeaderZ->width, infoHeaderZ->height);
  int i, j;
  for (i = 540; i <= 1059; i += 52) {
    for (j = i; j < (i + 20); j++) {
      (bitMapZ + j)->b = 0;
      (bitMapZ + j)->g = 255;
      (bitMapZ + j)->r = 0;
    }
  }
  for (i = 1050; i <= 1569; i += 52) {
    for (j = i; j < (i + 20); j++) {
      (bitMapZ + j)->b = 0;
      (bitMapZ + j)->g = 255;
      (bitMapZ + j)->r = 0;
    }
  }

  Write(fileHeaderZ, infoHeaderZ, bitMapZ, numePiesa, true);
  free(bitMapZ);
}

void CreateZ90And270(bmpFileHeader *fileHeaderZ, bmpInfoHeader *infoHeaderZ) {

  fileHeaderZ->bfSize = 6054;
  infoHeaderZ->width = 40;
  infoHeaderZ->height = 50;
  infoHeaderZ->biSizeImage = 6000;

  bmpPixel *bitMapZ = CreateBitMap(infoHeaderZ->width, infoHeaderZ->height);
  int i, j;
  for (i = 410; i <= 1209; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapZ + j)->b = 0;
      (bitMapZ + j)->g = 255;
      (bitMapZ + j)->r = 0;
    }
  }
  for (i = 820; i <= 1619; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapZ + j)->b = 0;
      (bitMapZ + j)->g = 255;
      (bitMapZ + j)->r = 0;
    }
  }

  Write(fileHeaderZ, infoHeaderZ, bitMapZ, "piesa_Z_90.bmp", false);
  Write(fileHeaderZ, infoHeaderZ, bitMapZ, "piesa_Z_270.bmp", false);
  free(bitMapZ);
}

void CreateS(bmpFileHeader *fileHeaderS, bmpInfoHeader *infoHeaderS,
             char *numePiesa) {

  fileHeaderS->bfSize = 6134;
  infoHeaderS->width = 52;
  infoHeaderS->height = 40;
  infoHeaderS->biSizeImage = 6080;

  bmpPixel *bitMapS = CreateBitMap(infoHeaderS->width, infoHeaderS->height);
  int i, j;
  for (i = 530; i <= 1049; i += 52) {
    for (j = i; j < (i + 20); j++) {
      (bitMapS + j)->b = 0;
      (bitMapS + j)->g = 0;
      (bitMapS + j)->r = 255;
    }
  }
  for (i = 1060; i <= 1579; i += 52) {
    for (j = i; j < (i + 20); j++) {
      (bitMapS + j)->b = 0;
      (bitMapS + j)->g = 0;
      (bitMapS + j)->r = 255;
    }
  }

  Write(fileHeaderS, infoHeaderS, bitMapS, numePiesa, true);
  free(bitMapS);
}

void CreateS90And270(bmpFileHeader *fileHeaderS, bmpInfoHeader *infoHeaderS) {

  fileHeaderS->bfSize = 6054;
  infoHeaderS->width = 40;
  infoHeaderS->height = 50;
  infoHeaderS->biSizeImage = 6000;

  bmpPixel *bitMapS = CreateBitMap(infoHeaderS->width, infoHeaderS->height);
  int i, j;
  for (i = 420; i <= 1219; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapS + j)->b = 0;
      (bitMapS + j)->g = 0;
      (bitMapS + j)->r = 255;
    }
  }
  for (i = 810; i <= 1609; i += 40) {
    for (j = i; j < (i + 10); j++) {
      (bitMapS + j)->b = 0;
      (bitMapS + j)->g = 0;
      (bitMapS + j)->r = 255;
    }
  }

  Write(fileHeaderS, infoHeaderS, bitMapS, "piesa_S_90.bmp", false);
  Write(fileHeaderS, infoHeaderS, bitMapS, "piesa_S_270.bmp", false);
  free(bitMapS);
}

void SetDefaultValues(bmpFileHeader *fileHeader, bmpInfoHeader *infoHeader) {

  fileHeader->fileMarker1 = 'B';
  fileHeader->fileMarker2 = 'M';
  fileHeader->unused1 = 0;
  fileHeader->unused2 = 0;
  fileHeader->imageDataOffset = 54;

  infoHeader->biSize = 40;
  infoHeader->planes = 1;
  infoHeader->bitPix = 24;
  infoHeader->biCompression = 0;
  infoHeader->biXPelsPerMeter = 0;
  infoHeader->biYPelsPerMeter = 0;
  infoHeader->biClrUsed = 0;
  infoHeader->biClrImportant = 0;
}

bmpPixel *CreateBitMap(int width, int height) {

  bmpPixel *bitMap = (bmpPixel *)malloc(width * height * (int)sizeof(bmpPixel));
  int i;
  for (i = 0; i < (width * height); i++) {
    (bitMap + i)->b = 255;
    (bitMap + i)->g = 255;
    (bitMap + i)->r = 255;
  }
  return bitMap;
}

void Write(bmpFileHeader *fileHeader, bmpInfoHeader *infoHeader,
           bmpPixel *bitMap, char *numeFisier, bool addPadding) {

>>>>>>> 658ad79b07536f815853140947a2efefddf68a97
  FILE *ffile = fopen(numeFisier, "wb");
  if (ffile != NULL) {
    fwrite(fileHeader, sizeof(bmpFileHeader), 1, ffile);
    int i, j;
    if (addPadding == false) {
      fwrite(infoHeader, sizeof(bmpInfoHeader), 1, ffile);
      for (i = 0; i < (infoHeader->width * infoHeader->height); i++) {
        fwrite((bitMap + i), sizeof(bmpPixel), 1, ffile);
      }
    } else {
      infoHeader->width = (infoHeader->width - 2);
      fwrite(infoHeader, sizeof(bmpInfoHeader), 1, ffile);
      bmpPaddingPixel(*paddingPixel) =
          (bmpPaddingPixel *)malloc(sizeof(bmpPaddingPixel));
      paddingPixel->p = 0;
      for (i = 0; i < ((infoHeader->width + 2) * (infoHeader->height));
           i += (infoHeader->width + 2)) {
        for (j = i; j <= (i + infoHeader->width - 1); j++) {
          fwrite((bitMap + j), sizeof(bmpPixel), 1, ffile);
        }
        fwrite(paddingPixel, sizeof(bmpPaddingPixel), 1, ffile);
      }
      free(paddingPixel);
    }
    fclose(ffile);
  }
}

void WriteMap(bmpFileHeader *fileHeader, bmpInfoHeader *infoHeader,
              bmpPixel **bitMap, char *numeFisier, bool addPadding) {

  FILE *ffile = fopen(numeFisier, "wb");
  if (ffile != NULL) {
    fwrite(fileHeader, sizeof(bmpFileHeader), 1, ffile);
    int i, j;
    if (addPadding == false) {
      fwrite(infoHeader, sizeof(bmpInfoHeader), 1, ffile);
      for (i = 0; i < (infoHeader->height); i++) {
        for (j = 0; j < (infoHeader->width); j++) {
          fwrite(&(bitMap[i][j]), sizeof(bmpPixel), 1, ffile);
        }
      }
    } else {
      infoHeader->width = (infoHeader->width - 4);
      fwrite(infoHeader, sizeof(bmpInfoHeader), 1, ffile);
      bmpPaddingPixel(*paddingPixel) =
          (bmpPaddingPixel *)malloc(sizeof(bmpPaddingPixel));
      paddingPixel->p = 0;
      for (i = 0; i < (infoHeader->height); i++) {
        for (j = 0; j < (infoHeader->width); j++) {
          fwrite(&(bitMap[i][j]), sizeof(bmpPixel), 1, ffile);
        }
        fwrite(paddingPixel, sizeof(bmpPaddingPixel), 1, ffile);
      }
      free(paddingPixel);
    }
  }
  fclose(ffile);
}
