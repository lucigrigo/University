#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode
{
	Item elem;
	struct StackNode *next;
} StackNode;

typedef StackNode TCelSt;  // Redenumirea unui nod la notatiile din curs
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack
{
	StackNode *head; // Varful stivei
	long size;		 // Numarul de elemente din stiva
} Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;   //  // Redenumirea unui pointer la stiva la notatiile din curs

Stack *createStack(void)
{
	Stack *ptr = (Stack *)malloc(sizeof(Stack));
	ptr->head = NULL;
	ptr->size = 0;
	return ptr;
}

int isStackEmpty(Stack *stack)
{
	if (stack != NULL)
	{
		if ((stack->head == NULL) && (stack->size == 0))
		{
			return 1;
		}
	}
	return 0;
}

void push(Stack *stack, Item elem)
{
	if (stack == NULL)
	{
		return;
	}
	if (stack->size == 0)
	{
		StackNode *ptr = (StackNode *)malloc(sizeof(StackNode));
		ptr->elem = elem;
		ptr->next = NULL;
		stack->head = ptr;
		stack->size = 1;
		return;
	}
	StackNode *ptr = (StackNode *)malloc(sizeof(StackNode));
	ptr->elem = elem;
	ptr->next = stack->head;
	stack->size = stack->size + 1;
	stack->head = ptr;
}

Item top(Stack *stack)
{
	return stack->head->elem;
}

void pop(Stack *stack)
{
	if (stack == NULL)
	{
		return;
	}
	if (stack->size == 0)
	{
		return;
	}
	if (stack->size == 1)
	{
		stack->head = NULL;
		stack->size = 0;
		return;
	}
	stack->head = stack->head->next;
	stack->size = stack->size - 1;
}

void destroyStack(Stack *stack)
{
	if (stack == NULL)
	{
		return;
	}
	if (stack->size == 0)
	{
		free(stack);
		return;
	}
	int t = 0, l = stack->size;
	StackNode *ptr = stack->head, *aux;
	while (t < l)
	{
		aux = ptr->next;
		free(ptr);
		ptr = aux;
		t += 1;
	}
	free(stack);
}

#endif
