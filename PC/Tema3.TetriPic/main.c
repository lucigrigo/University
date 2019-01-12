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
void Task3(bool, bmpPixel **, bmpFileHeader *, bmpInfoHeader *);
void Task4();
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
void SetValues(bmpFileHeader *, bmpInfoHeader *, int, int, bool);
void Write(bmpFileHeader *, bmpInfoHeader *, bmpPixel *, char *, bool);
void WriteMap(bmpFileHeader *, bmpInfoHeader *, bmpPixel **, char *, bool);
void Draw(bmpPixel *, int, int, int, int, bmpPixel);
void DrawMap(bmpPixel **, int, int, int, int, bmpPixel *);
bmpPixel *CreateBitMap(int, int);
bmpPixel **CreateGameBitMap(int, int);
bmpPixel **ReadBitMap(bmpFileHeader *, bmpInfoHeader *);
void StartGame(FILE *, int, bmpPixel **, int, int, bool);
void ConvertMatrix(bmpPixel **, char **, int, int);
void ConvertToMatrix(char **, bmpPixel **, int, int);
void CheckCompletedLines(char **, int, int);
int FreeSpot(int, int, char **);
int BreakingTheGame(int, int, int, int, int, char **);
bool placeI(char **, int, int, int);
bool placeO(char **, int, int);
bool placeS(char **, int, int, int);
bool placeZ(char **, int, int, int);
bool placeL(char **, int, int, int);
bool placeJ(char **, int, int, int);
bool placeT(char **, int, int, int);

int main(int argc, char *argv[]) {
  if (argc == 2) {
    CitireComanda(argv);
  }
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
  case 3:
    Task3(true, NULL, NULL, NULL);
    break;
  case 4:
    Task4();
    break;
  }
}

int FreeSpot(int indexH, int indexW, char **charMatrix) {
  if ((charMatrix[indexH][indexW] == 'N') ||
      ((charMatrix[indexH][indexW] == 'A'))) {
    return 1;
  }
  return 0;
}

int BreakingTheGame(int wIndex, int columnSpanToTheRight,
                    int columnSpanToTheLeft, int hIndex, int matrixHeight,
                    char **charMatrix) {
  int i;
  for (i = (hIndex + 1); i < (matrixHeight + 1); i++) {
    if (((charMatrix[hIndex][wIndex] != 'N') &&
        (charMatrix[hIndex][wIndex] != 'A')) ||
        ((charMatrix[hIndex][wIndex + columnSpanToTheRight] != 'N') &&
        (charMatrix[hIndex][wIndex + columnSpanToTheRight] != 'A')) ||
        ((charMatrix[hIndex][wIndex - columnSpanToTheLeft] != 'N') &&
        (charMatrix[hIndex][wIndex - columnSpanToTheLeft] != 'A'))) {
      return 1;
    }
  }
  return 0;
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

void Task3(bool newMap, bmpPixel **givenBitMap, bmpFileHeader *givenFileHeader,
           bmpInfoHeader *givenInfoHeader) {
  if (newMap == true) {
    FILE *ffile;
    ffile = fopen("cerinta3.in", "r");
    if (ffile != NULL) {
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
      StartGame(ffile, N, bitMap, H, L, false);
      WriteMap(fileHeader, infoHeader, bitMap, "task3.bmp", hasPadding);
      int i;
      for (i = 0; i < (infoHeader->height); i++) {
        free(bitMap[i]);
      }
      free(bitMap);
      free(fileHeader);
      free(infoHeader);
      fclose(ffile);
    }
  } else {
    bool hasPadding = false;
    if (((givenInfoHeader->width) % 4) != 0) {
      hasPadding = true;
    }
    int N;
    FILE *ffile;
    ffile = fopen("cerinta4.in", "r");
    if (ffile != NULL) {
      fscanf(ffile, "%d\n", &N);
      StartGame(ffile, N, givenBitMap, (givenInfoHeader->height / 10),
                (givenInfoHeader->width) / 10, true);
      if (hasPadding == true) {
        givenInfoHeader->width += 4;
      }
      WriteMap(givenFileHeader, givenInfoHeader, givenBitMap, "task4.bmp",
               hasPadding);
      fclose(ffile);
    }
  }
}

void Task4() {
  bmpFileHeader *fileHeader = (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
  bmpInfoHeader *infoHeader = (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));
  bmpPixel(**bitMap) = ReadBitMap(fileHeader, infoHeader);
  Task3(false, bitMap, fileHeader, infoHeader);
  int i;
  for (i = 0; i < (infoHeader->height); i++) {
    free(bitMap[i]);
  }
  free(bitMap);
  free(infoHeader);
  free(fileHeader);
}

void StartGame(FILE *ffile, int numberOfPieces, bmpPixel **bitMap, int height,
               int width, bool preLoadedMap) {

  int i, j, k;
  char **charMatrix;
  if(preLoadedMap == true){
    height -= 4;
    charMatrix = (char **)malloc((height) * width * (int)sizeof(char));
  } else {
    charMatrix = (char **)malloc((height + 10) * width * (int)sizeof(char));
  }
  for (i = 0; i < (height + 4); i++) {
    charMatrix[i] = (char *)malloc(width * (int)sizeof(char));
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
  if (preLoadedMap == true) {
    ConvertToMatrix(charMatrix, bitMap, height, width);
  }
  k = 0;
  while (k < numberOfPieces) {
    int widthIndex, rotation;
    char pieceIndex = '\0';
    bool endGame = false;
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
    CheckCompletedLines(charMatrix, height, width);
    if (endGame == true) {
      break;
    }
    k++;
  }
  ConvertMatrix(bitMap, charMatrix, width, height);
  for (i = 0; i < (height + 3); i++) {
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
      int k;
      for (k = i; k < (height - 1); k++) {
        for (j = 0; j < width; j++) {
          charMatrix[k][j] = charMatrix[k + 2][j];
        }
      }
      for (k = 0; k < width; k++) {
        charMatrix[height - 1][k] = 'N';
        charMatrix[height - 2][k] = 'N';
      }
    }
  }
}

bool placeI(char **charMatrix, int rotation, int wIndex, int matrixHeight) {

  int i, rowIndex = -1;
  if ((rotation == 0) || (rotation == 180)) {
    for (i = matrixHeight; i >= 0; i--) {
      if (FreeSpot(i, wIndex, charMatrix) &&
          !(BreakingTheGame(wIndex, 0, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 0, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    for (i = rowIndex; i < (rowIndex + 4); i++) {
      charMatrix[i][wIndex] = 'I';
    }
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 4) < 0)) {
      return true;
    }
  } else if ((rotation == 90) || (rotation == 270)) {
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
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 1) < 0)) {
      return true;
    }
  }
  return false;
}

bool placeO(char **charMatrix, int wIndex, int matrixHeight) {
  int i, rowIndex = -1;
  for (i = matrixHeight; i >= 0; i--) {
    if ((FreeSpot(i, wIndex, charMatrix)) &&
        (FreeSpot(i, (wIndex + 1), charMatrix)) &&
        (FreeSpot((i + 1), wIndex, charMatrix)) &&
        (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
        (!BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
      rowIndex = i;
    }
    if(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)){
      break;
    }
  }
  charMatrix[rowIndex][wIndex] = 'O';
  charMatrix[rowIndex][wIndex + 1] = 'O';
  charMatrix[rowIndex + 1][wIndex] = 'O';
  charMatrix[rowIndex + 1][wIndex + 1] = 'O';
  if ((rowIndex == -1) || ((matrixHeight - rowIndex - 2) < 0)) {
    return true;
  }
  return false;
}

bool placeS(char **charMatrix, int rotation, int wIndex, int matrixHeight) {
  int i, rowIndex = -1;
  if ((rotation == 0) || (rotation == 180)) {
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, (i+1), matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 2, 0, (i+1), matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'S';
    charMatrix[rowIndex][wIndex + 1] = 'S';
    charMatrix[rowIndex + 1][wIndex + 1] = 'S';
    charMatrix[rowIndex + 1][wIndex + 2] = 'S';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if ((rotation == 90) || (rotation == 270)) {
    for (i = matrixHeight; i >= 1; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'S';
    charMatrix[rowIndex + 1][wIndex] = 'S';
    charMatrix[rowIndex][wIndex + 1] = 'S';
    charMatrix[rowIndex - 1][wIndex + 1] = 'S';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  }
  return false;
}

bool placeZ(char **charMatrix, int rotation, int wIndex, int matrixHeight) {
  int i, rowIndex = -1;
  if ((rotation == 0) || (rotation == 180)) {
    for (i = matrixHeight; i >= 1; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'Z';
    charMatrix[rowIndex][wIndex + 1] = 'Z';
    charMatrix[rowIndex - 1][wIndex + 1] = 'Z';
    charMatrix[rowIndex - 1][wIndex + 2] = 'Z';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if ((rotation == 90) || (rotation == 270)) {
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 2), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, (i + 1), matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 1, 0, (i + 1), matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'Z';
    charMatrix[rowIndex + 1][wIndex] = 'Z';
    charMatrix[rowIndex + 1][wIndex + 1] = 'Z';
    charMatrix[rowIndex + 2][wIndex + 1] = 'Z';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  }
  return false;
}

bool placeL(char **charMatrix, int rotation, int wIndex, int matrixHeight) {
  int i, rowIndex = -1;
  if (rotation == 0) {
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i + 2), wIndex, charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex + 1][wIndex] = 'L';
    charMatrix[rowIndex + 2][wIndex] = 'L';
    charMatrix[rowIndex][wIndex + 1] = 'L';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  } else if (rotation == 90) {
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 2), charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex + 1][wIndex] = 'L';
    charMatrix[rowIndex + 1][wIndex + 1] = 'L';
    charMatrix[rowIndex + 1][wIndex + 2] = 'L';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if (rotation == 180) {
    for (i = matrixHeight; i >= 2; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i - 2), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex][wIndex + 1] = 'L';
    charMatrix[rowIndex - 1][wIndex + 1] = 'L';
    charMatrix[rowIndex - 2][wIndex + 1] = 'L';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  } else if (rotation == 270) {
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'L';
    charMatrix[rowIndex][wIndex + 1] = 'L';
    charMatrix[rowIndex][wIndex + 2] = 'L';
    charMatrix[rowIndex + 1][wIndex + 2] = 'L';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  }
  return false;
}

bool placeJ(char **charMatrix, int rotation, int wIndex, int matrixHeight) {
  int i, rowIndex = -1;
  if (rotation == 0) {
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 2), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 2), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex][wIndex + 1] = 'J';
    charMatrix[rowIndex + 1][wIndex + 1] = 'J';
    charMatrix[rowIndex + 2][wIndex + 1] = 'J';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  } else if (rotation == 90) {
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex + 1][wIndex] = 'J';
    charMatrix[rowIndex][wIndex + 1] = 'J';
    charMatrix[rowIndex][wIndex + 2] = 'J';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if (rotation == 180) {
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i + 2), wIndex, charMatrix)) &&
          (FreeSpot((i + 2), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex + 1][wIndex] = 'J';
    charMatrix[rowIndex + 2][wIndex] = 'J';
    charMatrix[rowIndex + 2][wIndex + 1] = 'J';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  } else if (rotation == 270) {
    for (i = matrixHeight; i >= 1; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 2), charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'J';
    charMatrix[rowIndex][wIndex + 1] = 'J';
    charMatrix[rowIndex][wIndex + 2] = 'J';
    charMatrix[rowIndex - 1][wIndex + 2] = 'J';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 1) < 0)) {
      return true;
    }
  }
  return false;
}

bool placeT(char **charMatrix, int rotation, int wIndex, int matrixHeight) {
  int i, rowIndex = -1;
  if (rotation == 0) {
    for (i = matrixHeight; i >= 1; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex][wIndex + 1] = 'T';
    charMatrix[rowIndex][wIndex + 2] = 'T';
    charMatrix[rowIndex - 1][wIndex + 1] = 'T';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if (rotation == 90) {
    for (i = matrixHeight; i >= 1; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i - 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex][wIndex + 1] = 'T';
    charMatrix[rowIndex + 1][wIndex + 1] = 'T';
    charMatrix[rowIndex - 1][wIndex + 1] = 'T';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  } else if (rotation == 180) {
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot(i, (wIndex + 2), charMatrix)) &&
          (FreeSpot(i, (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          !(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 2, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex][wIndex + 1] = 'T';
    charMatrix[rowIndex][wIndex + 2] = 'T';
    charMatrix[rowIndex + 1][wIndex + 1] = 'T';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 2) < 0)) {
      return true;
    }
  } else if (rotation == 270) {
    for (i = matrixHeight; i >= 0; i--) {
      if ((FreeSpot(i, wIndex, charMatrix)) &&
          (FreeSpot((i + 1), wIndex, charMatrix)) &&
          (FreeSpot((i + 1), (wIndex + 1), charMatrix)) &&
          (FreeSpot((i + 2), wIndex, charMatrix)) &&
          (!BreakingTheGame(wIndex, 1, 0, (i + 1), matrixHeight, charMatrix))) {
        rowIndex = i;
      }
      if(BreakingTheGame(wIndex, 1, 0, i, matrixHeight, charMatrix)){
        break;
      }
    }
    charMatrix[rowIndex][wIndex] = 'T';
    charMatrix[rowIndex + 1][wIndex + 1] = 'T';
    charMatrix[rowIndex + 1][wIndex] = 'T';
    charMatrix[rowIndex + 2][wIndex] = 'T';
    if ((rowIndex == -1) || ((matrixHeight - rowIndex - 3) < 0)) {
      return true;
    }
  }
  return false;
}

void CreateO(bmpFileHeader *fileHeaderO, bmpInfoHeader *infoHeaderO,
             char *numePiesa) {
  fileHeaderO->bfSize = 4854;
  infoHeaderO->width = 40;
  infoHeaderO->height = 40;
  infoHeaderO->biSizeImage = 4800;
  bmpPixel colorO = {0, 255, 255};

  bmpPixel *bitMapO = CreateBitMap(infoHeaderO->width, infoHeaderO->height);
  Draw(bitMapO, 410, 1209, 20, 40, colorO);
  Write(fileHeaderO, infoHeaderO, bitMapO, numePiesa, false);
  free(bitMapO);
}

void CreateJ(bmpFileHeader *fileHeaderJ, bmpInfoHeader *infoHeaderJ) {
  fileHeaderJ->bfSize = 6054;
  infoHeaderJ->width = 40;
  infoHeaderJ->height = 50;
  infoHeaderJ->biSizeImage = 6000;
  bmpPixel colorJ = {255, 0, 255};

  bmpPixel *bitMapJ = CreateBitMap(infoHeaderJ->width, infoHeaderJ->height);
  Draw(bitMapJ, 410, 809, 20, 40, colorJ);
  Draw(bitMapJ, 820, 1619, 10, 40, colorJ);
  Write(fileHeaderJ, infoHeaderJ, bitMapJ, "piesa_J.bmp", false);
  free(bitMapJ);
}

void CreateL(bmpFileHeader *fileHeaderL, bmpInfoHeader *infoHeaderL) {
  fileHeaderL->bfSize = 6054;
  infoHeaderL->width = 40;
  infoHeaderL->height = 50;
  infoHeaderL->biSizeImage = 6000;
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
    infoHeader->biSizeImage =
        ((height + 40) * (width - 2) * 3) + (2 * (height + 40));
    infoHeader->width = (width + 2);
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
      (bmpPixel **)malloc(((height + 40) * width) * (int)sizeof(bmpPixel));
  int i;
  for (i = 0; i < ((height + 40)); i++) {
    bitMap[i] = (bmpPixel *)malloc(width * (int)sizeof(bmpPixel));
  }
  bmpPixel *colorWhite = (bmpPixel *)malloc(sizeof(bmpPixel));
  colorWhite->b = 255;
  colorWhite->g = 255;
  bmpPixel *colorBlack = (bmpPixel *)malloc(sizeof(bmpPixel));
  colorBlack->b = 0;
  colorBlack->r = 0;
  colorBlack->g = 0;
  DrawMap(bitMap, 0, height, 0, width, colorBlack);
  DrawMap(bitMap, height, (height + 40), 0, width, colorWhite);
  return bitMap;
}

void ConvertMatrix(bmpPixel **bitMap, char **charMatrix, int width,
                   int height) {
  bmpPixel colorL = {0, 140, 255}, colorJ = {255, 0, 255}, colorI = {255, 0, 0},
           colorO = {0, 255, 255}, colorS = {0, 0, 255}, colorZ = {0, 255, 0},
           colorT = {255, 0, 130}, colorWhite = {255, 255, 255};
  int i, j;
  for (i = 0; i < (height + 4); i++) {
    for (j = 0; j < width; j++) {
      switch (charMatrix[i][j]) {
      case 'L':
        DrawMap(bitMap, (i * 10), ((i + 1) * 10), (j * 10), ((j + 1) * 10),
                &colorL);
        break;
        case 'A':
          DrawMap(bitMap, (i * 10), ((i + 1) * 10), (j * 10), ((j + 1) * 10),
                  &colorWhite);
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

void ConvertToMatrix(char **charMatrix, bmpPixel **bitMap, int height,
                     int width) {

  bmpPixel colorL = {0, 140, 255}, colorJ = {255, 0, 255}, colorI = {255, 0, 0},
           colorO = {0, 255, 255}, colorS = {0, 0, 255}, colorZ = {0, 255, 0},
           colorT = {255, 0, 130};
  int i, j;
  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      if (bitMap[i * 10][j * 10].b == colorL.b) {
        if (bitMap[i * 10][j * 10].g == colorL.g) {
          charMatrix[i][j] = 'L';
        } else if ((bitMap[i * 10][j * 10].g == colorS.g) &&
                   (bitMap[i * 10][j * 10].r == colorS.r)) {
          charMatrix[i][j] = 'S';
        } else if ((bitMap[i * 10][j * 10].g == colorZ.g) &&
                   (bitMap[i * 10][j * 10].r == colorZ.r) &&
                   (bitMap[i * 10][j * 10].b == colorZ.b)) {
          charMatrix[i][j] = 'Z';
        } else if (bitMap[i * 10][j * 10].g == colorO.g) {
          charMatrix[i][j] = 'O';
        }
      } else if (bitMap[i * 10][j * 10].b == colorT.b) {
        if ((bitMap[i * 10][j * 10].g == colorT.g) &&
            (bitMap[i * 10][j * 10].r == colorT.r)) {
          charMatrix[i][j] = 'T';
        } else if ((bitMap[i * 10][j * 10].g == colorJ.g) &&
                   (bitMap[i * 10][j * 10].r == colorJ.r)) {
          charMatrix[i][j] = 'J';
        } else if ((bitMap[i * 10][j * 10].g == colorI.g) &&
                   (bitMap[i * 10][j * 10].r == colorI.r)) {
          charMatrix[i][j] = 'I';
        }
      }
    }
  }
}

bmpPixel **ReadBitMap(bmpFileHeader *fileHeader, bmpInfoHeader *infoHeader) {

  FILE *ffile = fopen("cerinta4.bmp", "rb");
  if (ffile != NULL) {
    bool hasPadding = false;
    fread(fileHeader, sizeof(bmpFileHeader), 1, ffile);
    fread(infoHeader, sizeof(bmpInfoHeader), 1, ffile);
    if ((infoHeader->width % 4) != 0) {
      hasPadding = true;
    }
    bmpPixel(**bitMap) = (bmpPixel **)malloc(
        infoHeader->height * (int)sizeof(bmpPixel) * infoHeader->width);
    int i;
    for (i = 0; i < (infoHeader->height); i++) {
      bitMap[i] = (bmpPixel *)malloc(infoHeader->width * (int)sizeof(bmpPixel));
    }
    fseek(ffile, fileHeader->imageDataOffset, SEEK_SET);
    int j;
    for (i = 0; i < (infoHeader->height); i++) {
      for (j = 0; j < (infoHeader->width); j++) {
        fread(&bitMap[i][j], sizeof(bmpPixel), 1, ffile);
      }
      if (hasPadding == true) {
        fseek(ffile, 2, SEEK_CUR);
      }
    }
    fclose(ffile);
    return bitMap;
  }
  fclose(ffile);
  return NULL;
}

void Write(bmpFileHeader *fileHeader, bmpInfoHeader *infoHeader,
           bmpPixel *bitMap, char *numeFisier, bool addPadding) {
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
