#ifndef UTILS_H
#define UTILS_H
#include "bmp_header.h"

//  Mi-am definit eu un tip boolean
typedef enum { true, false } bool;
// Functiile gasite in utils.c
void SetDefaultValues(bmpFileHeader *, bmpInfoHeader *);
void SetValues(bmpFileHeader *, bmpInfoHeader *, int, int, bool);
void Write(bmpFileHeader *, bmpInfoHeader *, bmpPixel *, char *, bool);
void WriteMap(bmpFileHeader *, bmpInfoHeader *, bmpPixel **, char *, bool);
void Draw(bmpPixel *, int, int, int, int, bmpPixel);
void DrawMap(bmpPixel **, int, int, int, int, bmpPixel *);
bmpPixel *CreateBitMap(int, int);
bmpPixel **CreateGameBitMap(int, int);
bmpPixel **ReadBitMap(bmpFileHeader *, bmpInfoHeader *, char *);
int FreeSpot(int, int, char **);
int BreakingTheGame(int, int, int, int, int, char **);
void ConvertMatrix(bmpPixel **, char **, int, int);
void ConvertToMatrix(char **, bmpPixel **, int, int);
void CheckCompletedLines(char **, int, int);
void CitireComanda(char **);

#endif
