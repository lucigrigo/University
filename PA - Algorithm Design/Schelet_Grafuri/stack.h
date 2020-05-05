#ifndef __STACK_H__
#define __STACK_H__
/*
*	Created by Nan Mihai on 04.04.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator - Proiectarea algoritmilor (Grafuri)
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/
#include <stdlib.h>

typedef int E;

typedef struct stack {
	E data;
	struct stack *next;
}*Stack;

/*
*	Funcție care inițializează o stivă și adaugă valoarea data
*/
Stack initStack(E data);

/*
*	Funcție care adaugă valoarea data în stivă
*/
Stack push(Stack s, E data);


/*
*	Funcție care elimină elementul din vârful stivei
*/
Stack pop(Stack s);

/*
*	Funcție care întoarce elementul din vârful stivei (fără a-l elimina)
*/
E top(Stack s);

/*
*	Funcție care verifică dacă o stivă este sau nu vidă
*/
int isEmptyStack(Stack s);

/*
*	Funcție care dealocă memoria pentru întreaga structură
*/
Stack freeStack(Stack s);

#endif /* STACK_H */