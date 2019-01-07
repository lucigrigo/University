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
void Write(bmpFileHeader *, bmpInfoHeader *, bmpPixel *, char *, bool);
bmpPixel *CreateBitMap(int, int);

int main(int argc, char *argv[]) {
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

void CreateO(bmpFileHeader *fileHeaderO, bmpInfoHeader *infoHeaderO,
             char *numePiesa) {

  fileHeaderO->bfSize = 4854;
  infoHeaderO->width = 40;
  infoHeaderO->height = 40;
  infoHeaderO->biSizeImage = 4800;

  bmpPixel *bitMapO = CreateBitMap(infoHeaderO->width, infoHeaderO->height);
  int i, j;
  for (i = 410; i <= 1209; i += 40) {
    for (j = i; j < (i + 20); j++) {
      (bitMapO + j)->b = 0;
      (bitMapO + j)->g = 255;
      (bitMapO + j)->r = 255;
    }
  }

  Write(fileHeaderO, infoHeaderO, bitMapO, numePiesa, false);
  free(bitMapO);
}

void CreateJ(bmpFileHeader *fileHeaderJ, bmpInfoHeader *infoHeaderJ) {

  fileHeaderJ->bfSize = 6054;
  infoHeaderJ->width = 40;
  infoHeaderJ->height = 50;
  infoHeaderJ->biSizeImage = 6000;

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
  Write(fileHeaderJ, infoHeaderJ, bitMapJ, "piesa_J.bmp", false);
  free(bitMapJ);
}

void CreateL(bmpFileHeader *fileHeaderL, bmpInfoHeader *infoHeaderL) {

  fileHeaderL->bfSize = 6054;
  infoHeaderL->width = 40;
  infoHeaderL->height = 50;
  infoHeaderL->biSizeImage = 6000;

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
