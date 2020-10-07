#include "utils.h"
#include "tasks.h"
#include <stdio.h>
#include <stdlib.h>

//  Citeste numarul task-ului ce trebuie rezolvat
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
  default:
    TaskBonus();
    break;
  }
}

/*
  Verifica daca pe tabla de joc (cea de char-uri) este un "loc liber" = adica
  daca nu este vreo piesa asezata la indicii respectivi.
  N - negru
  A - alb
*/
int FreeSpot(int indexH,
             int indexW,
             char **charMatrix) {
  if ((charMatrix[indexH][indexW] == 'N') ||
      ((charMatrix[indexH][indexW] == 'A'))) {
    return 1;
  }
  return 0;
}

/*
  Functia BreakingTheGame() verifica daca pe coloana/coloanele pe care coboara
  o anumita piesa, ea trece peste o patratica deja ocupata de alta piesa.
*/
int BreakingTheGame(int wIndex,
                    int columnSpanToTheRight,
                    int columnSpanToTheLeft,
                    int hIndex,
                    int matrixHeight,
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

/*
  Functia Draw() coloreaza cu o culoare data un o anumita portiune din BitMap-ul
  dat. BitMap-ul exista sub forma unui vector.
  Functia este folosita la task-urile 1 si 2.
 */
void Draw(bmpPixel *bitMap,
          int start,
          int end,
          int width,
          int lineWidth,
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

/*
  Functia DrawMap() coloreaza BitMap-ul dat cu o culoare data intre anumiti
  indici. BitMap-ul exista sub forma unei matrici.
  Functia este folosita la task-urile 3 si 4.
*/
void DrawMap(bmpPixel **bitMap,
             int startH,
             int endH,
             int startW,
             int endW,
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

// Verifica daca exista linii complete in matricea de char-uri transmisa
void CheckCompletedLines(char **charMatrix,
                         int height,
                         int width) {
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

/*
  Functia SetDefaultValues() seteaza valorile campurilor default din File Header
  si Info Header. Adica acele campuri care nu depind de dimensiunea imaginii,
  inaltime sau latime si sunt standard tuturor imaginilor de acest fel.
*/
void SetDefaultValues(bmpFileHeader *fileHeader,
                      bmpInfoHeader *infoHeader) {
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

/*
  Functia SetValues() seteaza in File Header si Info Header valorile
  caracteristice fiecarei imagini.
*/
void SetValues(bmpFileHeader *fileHeader,
               bmpInfoHeader *infoHeader,
               int width,
               int height,
               bool hasPadding) {
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

/*
  Functia CreateBitMap() creeaza un vector de pixeli care reprezinta imaginea
  de tip BitMap si il "coloreaza" cu culoarea alb (255, 255, 255).
  Functia este folosita la task-urile 1 si 2.
*/
bmpPixel *CreateBitMap(int width,
                       int height) {
  bmpPixel *bitMap = (bmpPixel *)malloc(width * height * (int)sizeof(bmpPixel));
  int i;
  for (i = 0; i < (width * height); i++) {
    (bitMap + i)->b = 255;
    (bitMap + i)->g = 255;
    (bitMap + i)->r = 255;
  }
  return bitMap;
}

/*
  Functia CreateGameBitMap() creeaza o matrice care reprezinta imaginea de tip
  BitMap.
  Functia este folosita la task-urile 3 si 4.
*/
bmpPixel **CreateGameBitMap(int width,
                            int height) {
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

/*
  Functia ConvertMatrix() transforma matricea de char-uri in cea BitMap,
  colorand fiecare patratica (10px x 10px) cu culoarea corespunzatoare.
  Functia este folosita la task-urile 3 si 4.
*/
void ConvertMatrix(bmpPixel **bitMap,
                   char **charMatrix,
                   int width,
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

/*
  Functia ConvertToMatrix() transforma imaginea BitMap data intr-una de
  char-uri.
  Functia este folosita la task-ul 4.
  L - piesa L
  O - piesa O
  J - piesa J
  S - piesa S
  Z - piesa Z
  T - piesa T
  I - piesa I
*/
void ConvertToMatrix(char **charMatrix,
                     bmpPixel **bitMap,
                     int height,
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

/*
  Functia ReadBitMap() citeste o imagine de tip [.bmp].
  Este folosita la task-urile 4 si bonus.
*/
bmpPixel **ReadBitMap(bmpFileHeader *fileHeader,
                      bmpInfoHeader *infoHeader,
                      char *fileName) {
  FILE *ffile = fopen(fileName, "rb");
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

/*
  Functia Write() scrie o imagine de tip [.bmp]. BitMap-ul transmis este sub
  forma unui vector de pixeli.
  Functia este folosita la task-urile 1 si 2.
*/
void Write(bmpFileHeader *fileHeader,
           bmpInfoHeader *infoHeader,
           bmpPixel *bitMap,
           char *numeFisier,
           bool addPadding) {
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

/*
  Functia WriteMap() scrie o imagine de tip [.bmp]. BitMap-ul transmis este sub
  forma unei matrici de pixeli.
  Functia este folosita la task-urile 3 si 4.
*/
void WriteMap(bmpFileHeader *fileHeader,
              bmpInfoHeader *infoHeader,
              bmpPixel **bitMap,
              char *numeFisier,
              bool addPadding) {
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
