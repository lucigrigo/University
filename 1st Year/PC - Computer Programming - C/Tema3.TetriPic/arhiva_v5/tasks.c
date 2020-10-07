#include "tasks.h"
#include "task1.h"
#include "task2.h"
#include "taskbonus.h"
#include "tasks3and4.h"
#include <stdlib.h>

//  Functia principala pentru task-ul 1
void Task1() {
  //  Alocarea dinamica si setarea valorilor pentru File Header si Info Header
  bmpFileHeader *fileHeader = (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
  bmpInfoHeader *infoHeader = (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));
  SetDefaultValues(fileHeader, infoHeader);
  //  Apelarea functiilor necesare pentru crearea pieselor "simple"
  CreateO(fileHeader, infoHeader, "piesa_O.bmp");
  CreateJ(fileHeader, infoHeader);
  CreateL(fileHeader, infoHeader);
  CreateS(fileHeader, infoHeader, "piesa_S.bmp");
  CreateZ(fileHeader, infoHeader, "piesa_Z.bmp");
  CreateT(fileHeader, infoHeader);
  CreateI(fileHeader, infoHeader, "piesa_I.bmp");
  //  Elibereaza memoria ocupata
  free(fileHeader);
  free(infoHeader);
}

//  Functia principala pentru task-ul 2
void Task2() {
  //  Alocarea dinamica si setarea valorilor pentru File Header si Info Header
  bmpFileHeader *fileHeader = (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
  bmpInfoHeader *infoHeader = (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));
  SetDefaultValues(fileHeader, infoHeader);
  /*
   *  Apelarea functiilor necesare atat crearii imaginilor simple, cat si a
   *  celorlalte.
   */
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
  //  Elibereaza memoria ocupata
  free(fileHeader);
  free(infoHeader);
}

//  Functia principala pentru task-ul 3
void Task3(bool newMap,
           bmpPixel **givenBitMap,
           bmpFileHeader *givenFileHeader,
           bmpInfoHeader *givenInfoHeader) {
  if (newMap == true) {
    /*
     * Se intra pe ramura asta a if-ului in cazul task-ului 3. newMap este true
     * atunci cand se vrea crearea unui BitMap nou, si nu citirea unei imagini
     * deja existente.
     */
    FILE *ffile;
    ffile = fopen("cerinta3.in", "r");
    if (ffile != NULL) {
      int N, H, L, height, width;
      bool hasPadding = false;
      //  Citirea dimensiunilor imaginii si a numarului de piese
      fscanf(ffile, "%d %d %d\n", &N, &H, &L);
      width = L * 10;
      height = H * 10;
      if ((width % 4) != 0) {
        //  Verifica daca e nevoie de padding pentru imagine
        hasPadding = true;
        width += 2;
      }
      /*
       *  Alocarea dinamica si setarea valorilor pentru File Header si Info
       *  Header
       */
      bmpFileHeader *fileHeader =
          (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
      bmpInfoHeader *infoHeader =
          (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));
      SetDefaultValues(fileHeader, infoHeader);
      /*
       *  Seteaza valorile care nu sunt standard (inaltimea, latimea,
       *  dimensiunea imaginii si dimensiunea fisierului)
       */
      SetValues(fileHeader, infoHeader, width, height, hasPadding);
      //  Aloca dinamic BitMap-ul dupa dimensiunile primite
      bmpPixel(**bitMap) = CreateGameBitMap(width, height);
      //  Apeleaza functia de initiere a jocului :)
      StartGame(ffile, N, bitMap, H, L, false);
      //  Scrie fisierul [.bmp], dupa terminarea jocului
      WriteMap(fileHeader, infoHeader, bitMap, "task3.bmp", hasPadding);
      //  Elibereaza memoria ocupata
      int i;
      for (i = 0; i < (infoHeader->height); i++) {
        free(bitMap[i]);
      }
      free(bitMap);
      free(fileHeader);
      free(infoHeader);
      //  Inchide fisierul de input
      fclose(ffile);
    }
  } else {
    /*
     *  Se intra pe ramura asta daca functia e apelata din cadrul functiei
     *  principale a task-ului 4. Adica atunci cand newMap == false, BitMap-ul
     *  pe care se va desfasura jocul este citit dintr-o imagine.
     */
    bool hasPadding = false;
    if (((givenInfoHeader->width) % 4) != 0) {
      //  Verifica daca e nevoie de padding pentru imagine
      hasPadding = true;
    }
    int N;
    FILE *ffile;
    ffile = fopen("cerinta4.in", "r");
    if (ffile != NULL) {
      //  Citirea numarului de piese
      fscanf(ffile, "%d\n", &N);
      //  Apeleaza functia de initiere a jocului :)
      StartGame(ffile, N, givenBitMap, (givenInfoHeader->height / 10),
                (givenInfoHeader->width) / 10, true);
      if (hasPadding == true) {
        /*
         *  Ca sa explic acest "givenInfoHeader -> width += 4":
         *  Cand faceam debugging ca nu imi scria imaginile bine (in principal
         *  cele cu padding), am descoperit in functia WriteMap() ca eu aveam
         *  latimea imaginii cu 4 mai mare decat trebuia sa fie, pentru un alt
         *  apel. Asa ca atunci cand am scris partea asta de cod, am pus
         *  direct latimea cu 4 mai mare, pentru ca stiam ca oricum se scade in
         *  WriteMap() ca sa nu ma complic.
         */
        givenInfoHeader->width += 4;
      }
      //  Scrie fisierul [.bmp], dupa terminarea jocului
      WriteMap(givenFileHeader, givenInfoHeader, givenBitMap, "task4.bmp",
               hasPadding);
      // Inchiderea fisierului de input
      fclose(ffile);
    }
  }
}

//  Functia principala pentru task-ul 4
void Task4() {
  // Alocarea dinamica si setarea valorilor pentru File Header si Info Header
  bmpFileHeader *fileHeader = (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
  bmpInfoHeader *infoHeader = (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));
  //  Citirea imaginii
  bmpPixel(**bitMap) = ReadBitMap(fileHeader, infoHeader, "cerinta4.bmp");
  //  Se intoarce in functia task-ului 3 pe ramura (newMap == true)
  Task3(false, bitMap, fileHeader, infoHeader);
  //  Elibereaza memoria ocupata
  int i;
  for (i = 0; i < (infoHeader->height); i++) {
    free(bitMap[i]);
  }
  free(bitMap);
  free(infoHeader);
  free(fileHeader);
}

//  Functia principala pentru task-ul bonus
void TaskBonus() {
  // Alocarea dinamica si setarea valorilor pentru File Header si Info Header
  bmpFileHeader *fileHeader = (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
  bmpInfoHeader *infoHeader = (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));
  //  Citirea imaginii
  bmpPixel(**bitMap) = ReadBitMap(fileHeader, infoHeader, "bonus.bmp");
  //  Regleaza dimensiunile pentru crearea matricii de char-uri
  infoHeader->height /= 10;
  infoHeader->width /= 10;
  infoHeader->height -= 4;
  //  Aloca dinamic matricea de char-uri
  char **charMatrix = (char **) malloc(infoHeader->height * infoHeader->width *
                                      (int)sizeof(char));
  int i, j;
  for (i = 0; i < (infoHeader->height + 4); i++) {
    charMatrix[i] = (char *)malloc(infoHeader->width * (int)sizeof(char));
  }
  for (i = 0; i < infoHeader->height; i++) {
    for (j = 0; j < infoHeader->width; j++) {
      //  N - negru
      charMatrix[i][j] = 'N';
    }
  }
  for (i = infoHeader->height; i < (infoHeader->height + 4); i++) {
    for (j = 0; j < infoHeader->width; j++) {
      //  A - alb
      charMatrix[i][j] = 'A';
    }
  }
  //  Transforma BitMap-ul in matricea de char-uri (unde sunt piesele)
  ConvertToMatrix(charMatrix, bitMap, infoHeader->height, infoHeader->width);
  //  Apeleaza functia principala pentru identificarea pieselor
  StartBonus(charMatrix, infoHeader->height, infoHeader->width);
  //  Elibereaza memoria ocupata
  for (i = 0; i < (infoHeader->height + 4); i++) {
    free(charMatrix[i]);
  }
  free(charMatrix);
  free(fileHeader);
  for (i = 0; i < (infoHeader->height); i++) {
    free(bitMap[i]);
  }
  free(bitMap);
  free(infoHeader);
}
