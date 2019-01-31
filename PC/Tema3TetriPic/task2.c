#include "task2.h"
#include "utils.h"
#include <stdlib.h>

/*
 *    Urmatoarele functii sunt folosite la task-ul 2 pentru a crea imaginile
 *  ramase care nu sunt "simple", adica care nu au rotatia 0˚. La fel precum
 *  cele de la task-ul 1, toate urmeaza aceiasi pasi:
 *  - intai seteaza valorile pentru dimensiunea imaginii, dimensiunea
 *  fisierului, latimea si inaltimea BitMap-ului
 *  - apoi, seteaza culorile necesare pentru piesa/piesele create in functie
 *  - aloca dinamic BitMap-ul necesar (vector de pixeli)
 *  - coloreaza regiunile din vector care trebuie
 *  - scrie imaginea in fisierul [.bmp]
 *  - poate sa mai apara secventa "infoHeader->width += 2" pentru imaginile care
 *  au padding (pentru ca in functia Write() in cazul acestor imagini eu scad
 *  latimea cu 2 pixeli cand scriu fisierul [.bmp])
 *    Acesti pasi pot fi urmati de mai multe ori in cadrul unei functii, pentru
 *  o anumita piesa sau pentru mai multe piese (am incercat sa mai grupez in
 *  aceeasi functie imaginile mai asemanatoare, ca sa nu ma repet mai rau decat
 *  am facut-o deja cu codul).
 */

/*
 *  Creeaza piesele "L" si "J", la rotatie 180˚.
 */
void CreateLAndJ180(bmpFileHeader *fileHeaderLJ,
                    bmpInfoHeader *infoHeaderLJ) {
  fileHeaderLJ->bfSize = 6054;
  infoHeaderLJ->width = 40;
  infoHeaderLJ->height = 50;
  infoHeaderLJ->biSizeImage = 6000;
  bmpPixel colorL = {0, 140, 255};
  bmpPixel colorJ = {255, 0, 255};
  //  Pentru piesa L 180˚
  bmpPixel *bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 420, 1619, 10, 40, colorL);
  Draw(bitMapLJ, 1210, 1609, 10, 40, colorL);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_L_180.bmp", false);
  free(bitMapLJ);
  //  Pentru piesa J 180˚
  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 410, 1609, 10, 40, colorJ);
  Draw(bitMapLJ, 1220, 1619, 10, 40, colorJ);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_J_180.bmp", false);
  free(bitMapLJ);
}

/*
 * Creeaza, pentru fiecare din piesele "L" si "J", imaginile cu rotatiile 270˚
 * si 90˚.
 */
void CreateLAndJHoriz(bmpFileHeader *fileHeaderLJ,
                      bmpInfoHeader *infoHeaderLJ) {
  fileHeaderLJ->bfSize = 6134;
  infoHeaderLJ->width = 52;
  infoHeaderLJ->height = 40;
  infoHeaderLJ->biSizeImage = 6080;
  bmpPixel colorL = {0, 140, 255};
  bmpPixel colorJ = {255, 0, 255};
  //  Pentru piesa L 270˚
  bmpPixel *bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 530, 1049, 30, 52, colorL);
  Draw(bitMapLJ, 1070, 1589, 10, 52, colorL);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_L_270.bmp", true);
  free(bitMapLJ);
  infoHeaderLJ->width += 2;
  //  Pentru piesa J 270˚
  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 550, 1069, 10, 52, colorJ);
  Draw(bitMapLJ, 1050, 1569, 30, 52, colorJ);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_J_270.bmp", true);
  free(bitMapLJ);
  infoHeaderLJ->width += 2;
  //  Pentru piesa L 90˚
  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 530, 1049, 10, 52, colorL);
  Draw(bitMapLJ, 1050, 1559, 30, 52, colorL);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_L_90.bmp", true);
  free(bitMapLJ);
  infoHeaderLJ->width += 2;
  //  Pentru piesa J 90˚
  bitMapLJ = CreateBitMap(infoHeaderLJ->width, infoHeaderLJ->height);
  Draw(bitMapLJ, 530, 1049, 30, 52, colorJ);
  Draw(bitMapLJ, 1050, 1559, 10, 52, colorJ);
  Write(fileHeaderLJ, infoHeaderLJ, bitMapLJ, "piesa_J_90.bmp", true);
  free(bitMapLJ);
}

/*
 *  Creeaza pentru piesa "I" imaginile cu rotatiile 90˚ si 270˚(identice).
 */
void CreateI90And270(bmpFileHeader *fileHeaderI,
                     bmpInfoHeader *infoHeaderI) {
  fileHeaderI->bfSize = 5454;
  infoHeaderI->width = 60;
  infoHeaderI->height = 30;
  infoHeaderI->biSizeImage = 5400;
  bmpPixel colorI = {255, 0, 0};
  //  Pentru piesele I 90˚ si I 270˚ (identice)
  bmpPixel *bitMapI = CreateBitMap(infoHeaderI->width, infoHeaderI->height);
  Draw(bitMapI, 610, 1209, 40, 60, colorI);
  Write(fileHeaderI, infoHeaderI, bitMapI, "piesa_I_90.bmp", false);
  Write(fileHeaderI, infoHeaderI, bitMapI, "piesa_I_270.bmp", false);
  free(bitMapI);
}

/*
 * Creeaza efectiv piesa "T" cu rotatia 180˚ si apeleaza functia care creeaza,
 * pentru aceeasi piesa, imaginile cu rotatiile 90˚ si 270˚.
 */
void CreateAllT(bmpFileHeader *fileHeaderT,
                bmpInfoHeader *infoHeaderT) {
  fileHeaderT->bfSize = 6134;
  infoHeaderT->width = 52;
  infoHeaderT->height = 40;
  infoHeaderT->biSizeImage = 6080;
  bmpPixel colorT = {255, 0, 130};
  //  Pentru piesa T 180˚
  bmpPixel *bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  Draw(bitMapT, 530, 1049, 30, 52, colorT);
  Draw(bitMapT, 1060, 1579, 10, 52, colorT);
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T_180.bmp", true);
  free(bitMapT);
  CreateTVert(fileHeaderT, infoHeaderT);
}

/*
 * Creeaza pentru piesa "T" imaginile cu rotatiile 270˚ si 90˚.
 */
void CreateTVert(bmpFileHeader *fileHeaderT,
                 bmpInfoHeader *infoHeaderT) {
  fileHeaderT->bfSize = 6054;
  infoHeaderT->width = 40;
  infoHeaderT->height = 50;
  infoHeaderT->biSizeImage = 6000;
  bmpPixel colorT = {255, 0, 130};
  //  Pentru piesa T 270˚
  bmpPixel *bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  Draw(bitMapT, 410, 1609, 10, 40, colorT);
  Draw(bitMapT, 820, 1219, 10, 40, colorT);
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T_270.bmp", false);
  free(bitMapT);
  //  Pentru piesa T 90˚
  bitMapT = CreateBitMap(infoHeaderT->width, infoHeaderT->height);
  Draw(bitMapT, 420, 1619, 10, 40, colorT);
  Draw(bitMapT, 810, 1209, 10, 40, colorT);
  Write(fileHeaderT, infoHeaderT, bitMapT, "piesa_T_90.bmp", false);
  free(bitMapT);
}

/*
 * Creeaza pentru piesa "Z" imaginile cu rotatiile 90˚ si 270˚(identice).
 */
void CreateZ90And270(bmpFileHeader *fileHeaderZ,
                     bmpInfoHeader *infoHeaderZ) {
  fileHeaderZ->bfSize = 6054;
  infoHeaderZ->width = 40;
  infoHeaderZ->height = 50;
  infoHeaderZ->biSizeImage = 6000;
  bmpPixel colorZ = {0, 255, 0};
  //  Pentru piesele Z 90˚ si Z 270˚ (identice)
  bmpPixel *bitMapZ = CreateBitMap(infoHeaderZ->width, infoHeaderZ->height);
  Draw(bitMapZ, 410, 1209, 10, 40, colorZ);
  Draw(bitMapZ, 820, 1619, 10, 40, colorZ);
  Write(fileHeaderZ, infoHeaderZ, bitMapZ, "piesa_Z_90.bmp", false);
  Write(fileHeaderZ, infoHeaderZ, bitMapZ, "piesa_Z_270.bmp", false);
  free(bitMapZ);
}

/*
 * Creeaza pentru piesa "S" imaginile cu rotatiile 90˚ si 270˚(identice).
 */
void CreateS90And270(bmpFileHeader *fileHeaderS,
                     bmpInfoHeader *infoHeaderS) {
  fileHeaderS->bfSize = 6054;
  infoHeaderS->width = 40;
  infoHeaderS->height = 50;
  infoHeaderS->biSizeImage = 6000;
  bmpPixel colorS = {0, 0, 255};
  //  Pentru piesele S 90˚ si S 270˚ (identice)
  bmpPixel *bitMapS = CreateBitMap(infoHeaderS->width, infoHeaderS->height);
  Draw(bitMapS, 420, 1219, 10, 40, colorS);
  Draw(bitMapS, 810, 1609, 10, 40, colorS);
  Write(fileHeaderS, infoHeaderS, bitMapS, "piesa_S_90.bmp", false);
  Write(fileHeaderS, infoHeaderS, bitMapS, "piesa_S_270.bmp", false);
  free(bitMapS);
}
