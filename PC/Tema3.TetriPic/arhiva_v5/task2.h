#ifndef TASK2_H
#define TASK2_H
#include "bmp_header.h"

//  Functiile gasite in task2.c
void CreateLAndJ180(bmpFileHeader *, bmpInfoHeader *);
void CreateLAndJHoriz(bmpFileHeader *, bmpInfoHeader *);
void CreateS90And270(bmpFileHeader *, bmpInfoHeader *);
void CreateZ90And270(bmpFileHeader *, bmpInfoHeader *);
void CreateAllT(bmpFileHeader *, bmpInfoHeader *);
void CreateTVert(bmpFileHeader *, bmpInfoHeader *);
void CreateI90And270(bmpFileHeader *, bmpInfoHeader *);

#endif
