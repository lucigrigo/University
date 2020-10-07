#ifndef __GRAPH_H__
#define __GRAPH_H__
/*
*	Created by Nan Mihai on 04.04.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator - Proiectarea algoritmilor (Grafuri)
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "heap.h"

#define SIZE 200
#define INFINITY 999999

typedef struct graph {
	int V; // nr de noduri din graf
	int type; // 0 - neorientat ; 1 - orientat
	List *adjLists; // vectorul cu listele de adiacență
	int *visited; // vector pentru marcarea nodurilor vizitate
	int *start, *end;
}*Graph;

typedef struct edge {
	int u, v, cost;
} Edge;

/*
*	Inițializează o structură de tip graf cu maximum V noduri (indexate de la 0)
*	Dacă graful este neorientat, atunci type = 0, altfel, el este orientat
*/
Graph initGraph(int V, int type);

/*
*	Funcție care adaugă o muchie între u și v având costul cost
*	Dacă graful nu este ponderat => cost = 0
*	Dacă graful este neorientat, adaugă și muchia (v, u)
*/
Graph insertEdge(Graph g, int u, int v, int cost);

/*
*	Funcție care afișează un graf
*/
void printGraph(Graph g);

/*
*	Funcție care desenează graful
*/
void drawGraph(Graph g, char *name);

/*
*	Funcție care verifică dacă există muchie între u și v
*		- result = 0 => nu există muchie
*		- result = 1 => există muchie
*/
int isArc(Graph g, int u, int v);

/*
*	Funcție care va retuna costul dintre u și v
*		- Va întoarce INFINITY dacă nu sunt conectate
*/
int getCost(Graph g, int u, int v);

/*
*	Funcție care dealocă întreagă memorie a structurii
*/
Graph freeGraph(Graph graph);

#endif /* GRAPH_H */
