/*
              Curs: Programarea Calculatoarelor
                        Tema 3 - TetriPic
              Nume si prenume: Grigore Lucian-Florin
              Grupa si seria: 314CD
*/
#include "bmp_header.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {true,false} bool;

void CitireComanda(char **);
void Task1();
void CreateO(bmpFileHeader *, bmpInfoHeader *);
void CreateJ(bmpFileHeader *, bmpInfoHeader *);
void CreateL(bmpFileHeader *, bmpInfoHeader *);
void CreateS(bmpFileHeader *, bmpInfoHeader *);
void CreateZ(bmpFileHeader *, bmpInfoHeader *);
void CreateT(bmpFileHeader *, bmpInfoHeader *);
void CreateI(bmpFileHeader *, bmpInfoHeader *);
void SetDefaultValues(bmpFileHeader *, bmpInfoHeader *);
void Write(bmpFileHeader *, bmpInfoHeader *, bmpPixel *,char *, bool);
bmpPixel *CreateBitMap(int, int);


int main(int argc, char *argv[]) {
  if(argc == 2){
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
  }
}

void Task1() {

  bmpFileHeader *fileHeader = (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
  bmpInfoHeader *infoHeader = (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));
  SetDefaultValues(fileHeader, infoHeader);
  CreateO(fileHeader, infoHeader);
  CreateJ(fileHeader, infoHeader);
  CreateL(fileHeader, infoHeader);
  CreateS(fileHeader, infoHeader);
  CreateZ(fileHeader, infoHeader);
  CreateT(fileHeader, infoHeader);
  CreateI(fileHeader, infoHeader);
  free(fileHeader);
  free(infoHeader);
}

void CreateO(bmpFileHeader *fileHeaderO,
             bmpInfoHeader *infoHeaderO){

   fileHeaderO->bfSize = 4854;
   infoHeaderO->width = 40;
   infoHeaderO->height = 40;
   infoHeaderO->biSizeImage = 4800;

  bmpPixel *bitMapO = CreateBitMap(infoHeaderO->width, infoHeaderO->height);
  int i,j;
  for(i = 410; i <= 1209 ; i += 40){
    for(j = i; j <  (i + 20); j++){
      (bitMapO + j) -> b = 0;
      (bitMapO + j) -> g = 255;
      (bitMapO + j) -> r = 255;
    }
  }

  Write(fileHeaderO, infoHeaderO, bitMapO,"piesa_O.bmp", false);
}

void CreateJ(bmpFileHeader *fileHeaderJ,
             bmpInfoHeader *infoHeaderJ){

   fileHeaderJ->bfSize = 6054;
   infoHeaderJ->width = 40;
   infoHeaderJ->height = 50;
   infoHeaderJ->biSizeImage = 6000;

   bmpPixel *bitMapJ = CreateBitMap(infoHeaderJ->width, infoHeaderJ->height);
   int i,j;
   for(i = 410; i <= 809 ; i += 40){
     for(j = i; j <  (i + 20); j++){
       (bitMapJ + j) -> b = 255;
       (bitMapJ + j) -> g = 0;
       (bitMapJ + j) -> r = 255;
     }
   }
   for(i = 820; i <= 1619 ; i += 40){
     for(j = i; j <  (i + 10); j++){
       (bitMapJ + j) -> b = 255;
       (bitMapJ + j) -> g = 0;
       (bitMapJ + j) -> r = 255;
     }
   }
   Write(fileHeaderJ, infoHeaderJ, bitMapJ,"piesa_J.bmp", false);
}

void CreateL(bmpFileHeader *fileHeaderL,
             bmpInfoHeader *infoHeaderL){

  fileHeaderL->bfSize = 6054;
  infoHeaderL->width = 40;
  infoHeaderL->height = 50;
  infoHeaderL->biSizeImage = 6000;

  bmpPixel *bitMapL = CreateBitMap(infoHeaderL->width, infoHeaderL->height);
  int i,j;
  for(i = 410; i <= 809 ; i += 40){
    for(j = i; j <  (i + 20); j++){
      (bitMapL + j) -> b = 0;
      (bitMapL + j) -> g = 140;
      (bitMapL + j) -> r = 255;
    }
  }
  for(i = 810; i <= 1609 ; i += 40){
    for(j = i; j <  (i + 10); j++){
      (bitMapL + j) -> b = 0;
      (bitMapL + j) -> g = 140;
      (bitMapL + j) -> r = 255;
    }
  }
  Write(fileHeaderL, infoHeaderL, bitMapL,"piesa_L.bmp", false);
}

void CreateI(bmpFileHeader *fileHeaderI,
             bmpInfoHeader *infoHeaderI){

  fileHeaderI->bfSize = 5574;
  infoHeaderI->width = 32;
  infoHeaderI->height = 60;
  infoHeaderI->biSizeImage = 5520;

  bmpPixel *bitMapI = CreateBitMap(infoHeaderI -> width, infoHeaderI->height);
  int i,j;
  for(i = 330; i <= 1609 ; i += 32){
    for(j = i; j <  (i + 10); j++){
      (bitMapI + j) -> b = 255;
      (bitMapI + j) -> g = 0;
      (bitMapI + j) -> r = 0;
    }
  }
  Write(fileHeaderI, infoHeaderI, bitMapI, "piesa_I.bmp", true);
}

void CreateT(bmpFileHeader *fileHeaderT,
             bmpInfoHeader *infoHeaderT){

  fileHeaderT->bfSize = 6134;
  infoHeaderT->width = 52;
  infoHeaderT->height = 40;
  infoHeaderT->biSizeImage = 6080;

  bmpPixel *bitMapT = CreateBitMap(infoHeaderT -> width, infoHeaderT->height);
  int i,j;
  for(i = 540; i <= 1059 ; i += 52){
    for(j = i; j <  (i + 10); j++){
      (bitMapT + j) -> b = 255;
      (bitMapT + j) -> g = 0;
      (bitMapT + j) -> r = 130;
    }
  }
  for(i = 1050; i <= 1569 ; i += 52){
    for(j = i; j <  (i + 30); j++){
      (bitMapT + j) -> b = 255;
      (bitMapT + j) -> g = 0;
      (bitMapT + j) -> r = 130;
    }
  }
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T.bmp", true);
}

void CreateZ(bmpFileHeader *fileHeaderZ,
             bmpInfoHeader *infoHeaderZ){

  fileHeaderZ->bfSize = 6134;
  infoHeaderZ->width = 52;
  infoHeaderZ->height = 40;
  infoHeaderZ->biSizeImage = 6080;

  bmpPixel *bitMapZ = CreateBitMap(infoHeaderZ -> width, infoHeaderZ -> height);
  int i,j;
  for(i = 540; i <= 1059 ; i += 52){
    for(j = i; j <  (i + 20); j++){
      (bitMapZ + j) -> b = 0;
      (bitMapZ + j) -> g = 255;
      (bitMapZ + j) -> r = 0;
    }
  }
  for(i = 1050; i <= 1569 ; i += 52){
    for(j = i; j <  (i + 20); j++){
      (bitMapZ + j) -> b = 0;
      (bitMapZ + j) -> g = 255;
      (bitMapZ + j) -> r = 0;
    }
  }
  Write(fileHeaderZ, infoHeaderZ, bitMapZ, "piesa_Z.bmp", true);
}

void CreateS(bmpFileHeader *fileHeaderS,
             bmpInfoHeader *infoHeaderS){

  fileHeaderS->bfSize = 6134;
  infoHeaderS->width = 52;
  infoHeaderS->height = 40;
  infoHeaderS->biSizeImage = 6080;

  bmpPixel *bitMapS = CreateBitMap(infoHeaderS -> width, infoHeaderS -> height);
  int i,j;
  for(i = 530; i <= 1049 ; i += 52){
    for(j = i; j <  (i + 20); j++){
      (bitMapS + j) -> b = 0;
      (bitMapS + j) -> g = 0;
      (bitMapS + j) -> r = 255;
    }
  }
  for(i = 1060; i <= 1579 ; i += 52){
    for(j = i; j <  (i + 20); j++){
      (bitMapS + j) -> b = 0;
      (bitMapS + j) -> g = 0;
      (bitMapS + j) -> r = 255;
    }
  }
  Write(fileHeaderS, infoHeaderS, bitMapS, "piesa_S.bmp", true);
}

void SetDefaultValues(bmpFileHeader *fileHeader,
                      bmpInfoHeader *infoHeader){

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

bmpPixel *CreateBitMap(int width, int height){

  bmpPixel *bitMap = (bmpPixel *)
                malloc(width * height * (int)sizeof(bmpPixel));
  int i;
  for(i = 0; i < (width * height); i++){
    (bitMap + i) -> b = 255;
    (bitMap + i) -> g = 255;
    (bitMap + i) -> r = 255;
  }
  return bitMap;
}

void Write(bmpFileHeader *fileHeader,
           bmpInfoHeader *infoHeader,
           bmpPixel *bitMap,
           char *numeFisier,
           bool addPadding){

   FILE *ffile = fopen(numeFisier, "wb");
   if (ffile != NULL) {
     fwrite(fileHeader, sizeof(bmpFileHeader), 1, ffile);
     int i,j;
     if(addPadding == false){
       fwrite(infoHeader, sizeof(bmpInfoHeader), 1, ffile);
       for(i = 0; i < (infoHeader -> width * infoHeader -> height); i++){
         fwrite((bitMap + i), sizeof(bmpPixel), 1, ffile);
       }
     } else {
       infoHeader -> width = (infoHeader -> width - 2);
       fwrite(infoHeader, sizeof(bmpInfoHeader), 1, ffile);
       bmpPaddingPixel (*paddingPixel) = (bmpPaddingPixel *) malloc(sizeof(bmpPaddingPixel));
       paddingPixel -> p = 0;
       for(i = 0; i < ((infoHeader -> width + 2) * (infoHeader -> height)); i += (infoHeader -> width + 2)){
         for(j = i; j <= (i + infoHeader -> width - 1) ; j++){
           fwrite((bitMap + j), sizeof(bmpPixel), 1, ffile);
         }
         fwrite(paddingPixel, sizeof(bmpPaddingPixel), 1, ffile);
       }
       free(paddingPixel);
     }
     free(bitMap);
     fclose(ffile);
   }
}
