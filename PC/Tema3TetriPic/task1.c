#include "task1.h"
#include "utils.h"
#include <stdlib.h>

/*
 *    Functiile urmatoare, folosite la task-urile 1 si 2, creeaza imaginile
 *  "simple", adica cele care contin doar cate o piesa cu rotatia 0˚.
 *    Dat fiind faptul ca toate fac acelasi lucru, voi explica doar o data modul
 *  lor de functionare. Singurele diferente intre ele sunt latimea, inaltimea,
 *  dimensiunea imaginii create, numele fisierului in care e scrisa imaginea si
 *  culoarea acesteia.
 *    Pentru ca pentru task-urile 1 si 2 am folosit un vector alocat dinamic
 *  pentru a reprezenta BitMap-ul, indicii de pozitie ai fiecarui pixel, la
 *  aceste functii, sunt un pic mai "urati".
 *    In fiecare functie au loc urmatoarele procese:
 *  - sunt stabilite latimea, inaltimea si dimensiunea atat a imaginii, cat si
 *  a fisierului de tip [.bmp]
 *  - este "creat" vectorul pentru imaginea BitMap prin apelarea functiei
 *  CreateBitMap()
 *  - este "colorat" vectorul intre anumiti indici, cu culoarea potrivita.
 *  Functia Draw() poate fi apelata de una sau doua ori, in functie de tipul
 *  pisei.
 *  - este scris fisierul [.bmp] corespunzator si se da free() la BitMap
 */

//  Pentru piesa "O"
void CreateO(bmpFileHeader *fileHeaderO,
             bmpInfoHeader *infoHeaderO,
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

//  Pentru piesa "J"
void CreateJ(bmpFileHeader *fileHeaderJ,
             bmpInfoHeader *infoHeaderJ) {
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

//  Pentru piesa "L"
void CreateL(bmpFileHeader *fileHeaderL,
             bmpInfoHeader *infoHeaderL) {
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

//  Pentru piesa "I"
void CreateI(bmpFileHeader *fileHeaderI,
             bmpInfoHeader *infoHeaderI,
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

//  Pentru piesa "T"
void CreateT(bmpFileHeader *fileHeaderT,
             bmpInfoHeader *infoHeaderT) {
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

//  Pentru piesa "Z"
void CreateZ(bmpFileHeader *fileHeaderZ,
             bmpInfoHeader *infoHeaderZ,
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

//  Pentru piesa "S"
void CreateS(bmpFileHeader *fileHeaderS,
             bmpInfoHeader *infoHeaderS,
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
