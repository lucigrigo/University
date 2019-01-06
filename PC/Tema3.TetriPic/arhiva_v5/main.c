/*
              Curs: Programarea Calculatoarelor
                        Tema 3 - TetriPic
              Nume si prenume: Grigore Lucian-Florin
              Grupa si seria: 314CD
*/
#include "bmp_header.h"
#include <stdio.h>
#include <stdlib.h>

void CitireComanda(char **);
void Task1();

int main(int argc, char *argv[]) {
  argc = 1;
  CitireComanda(argv);
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
  bmpFileHeader *fileHeaderO = (bmpFileHeader *)malloc(sizeof(bmpFileHeader));
  bmpInfoHeader *infoHeaderO = (bmpInfoHeader *)malloc(sizeof(bmpInfoHeader));

  fileHeaderO->fileMarker1 = 'B';
  fileHeaderO->fileMarker2 = 'M';
  fileHeaderO->bfSize = (4800 + 54);
  fileHeaderO->unused1 = 0;
  fileHeaderO->unused2 = 0;
  fileHeaderO->imageDataOffset = 54;

  infoHeaderO->biSize = 40;
  infoHeaderO->width = 40;
  infoHeaderO->height = 40;
  infoHeaderO->planes = 1;
  infoHeaderO->bitPix = 24;
  infoHeaderO->biCompression = 0;
  infoHeaderO->biSizeImage = 4800;
  infoHeaderO->biXPelsPerMeter = 0;
  infoHeaderO->biYPelsPerMeter = 0;
  infoHeaderO->biClrUsed = 0;
  infoHeaderO->biClrImportant = 0;

  bmpPixel *bitMapO = (bmpPixel *)
                malloc(infoHeaderO -> width * infoHeaderO -> height
                * sizeof(bmpPixel));
  int i, j;
  for(i = 0; i < (infoHeaderO -> width * infoHeaderO -> height); i++){
    bitMapO[i].b = 255;
    bitMapO[i].g = 255;
    bitMapO[i].r = 255;
  }

  for(i = 49; i < 899 ; i += 30){
    for(j = i; j < (i + 20); j++){
      bitMapO[j].b = 0;
      bitMapO[j].g = 255;
      bitMapO[j].r = 255;
    }
  }

  FILE *ffile = fopen("piesa_O.bmp", "wb");
  if (ffile != NULL) {
    fwrite(fileHeaderO, sizeof(fileHeaderO), 1, ffile);
    free(fileHeaderO);
    fwrite(infoHeaderO, sizeof(infoHeaderO), 1, ffile);
    free(infoHeaderO);
    for(i = 0; i < (infoHeaderO -> width * infoHeaderO -> height); i++){
      fwrite((bitMapO + i), sizeof(bmpPixel), 1, ffile);
    }
    free(bitMapO);
    fclose(ffile);
  }
}
