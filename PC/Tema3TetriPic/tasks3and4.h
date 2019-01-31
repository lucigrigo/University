#ifndef TASKS3AND4_H
#define TASKS3AND4_H
#include "bmp_header.h"
#include "utils.h"
#include "stdio.h"

// Functiile gasite in tasks3and4.c
bool placeI(char **, int, int, int);
bool placeO(char **, int, int);
bool placeS(char **, int, int, int);
bool placeZ(char **, int, int, int);
bool placeL(char **, int, int, int);
bool placeJ(char **, int, int, int);
bool placeT(char **, int, int, int);
void StartGame(FILE *, int, bmpPixel **, int, int, bool);

#endif
