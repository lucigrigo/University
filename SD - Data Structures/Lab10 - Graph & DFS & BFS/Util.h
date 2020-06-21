/*
 * Util.h
 *
 *  Created on: May 3, 2016
 *      Author: dan
 */

#ifndef UTIL_H_
#define UTIL_H_

typedef struct ListNode{
	int key;
	struct ListNode *next;
	struct ListNode *prev;
}ListNode;

typedef struct List{
	ListNode* head;
}List;

typedef List Stack;
typedef List Queue;

List* createList(void);
void destroyList(List* list);
int isListEmpty(List *list);

Stack* createStack(void);
void destroyStack(Stack* stack);
void push(Stack* stack, int key);
void pop(Stack* stack);
int isStackEmpty(Stack* stack);
int top(Stack* stack);


Queue* createQueue(void);
void destroyQueue(Queue* queue);
void enqueue(Queue* queue, int key);
void dequeue(Queue* queue);
int isQueueEmpty(Queue *queue);
int front(Queue* queue);

#endif /* UTIL_H_ */
