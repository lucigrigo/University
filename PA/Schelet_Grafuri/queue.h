#ifndef __QUEUE_H__
#define __QUEUE_H__
/*
*	Created by Nan Mihai on 04.04.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator - Proiectarea algoritmilor (Grafuri)
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/
#include <stdlib.h>

typedef int T;

typedef struct node {
	T data;
	struct node *next;
}Node;

typedef struct queue {
	Node *head, *tail;
	int size;
}*Queue;

/*
*	Funcție care inițializează o coadă și adaugă valoarea data
*/
Queue initQueue(T data);

/*
*	Functie auxiliară care inițializează un nod din coadă
*/
Node *initNode(T data);

/*
*	Funcție care adaugă valoarea data în coadă
*/
Queue enqueue(Queue queue, T data);

/*
*	Funcție care elimină primul element din coadă
*/
Queue dequeue(Queue queue);

/*
*	Funcție care determină valoarea primului element (fără a o elimina)
*/
T first(Queue queue);

/*
*	Funcție care verifică dacă o coadă este sau nu vidă
*/
int isEmptyQueue(Queue queue);

/*
*	Funcție auxiliară care dealocă memoria pentru un nod
*/
Node *freeNode(Node *node);

/*
*	Funcție care dealocă memoria pentru întreaga structură
*/
Queue freeQueue(Queue queue);

#endif /* QUEUE_H */