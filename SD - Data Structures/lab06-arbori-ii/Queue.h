#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	Item2 value;
	struct Node* next;
}Node;

typedef struct Queue{
	Node* front;
	Node* rear;
}Queue;


void initQueue(Queue **q){
	(*q) = (Queue *) malloc(sizeof(Queue));
	(*q)->front = NULL;
	(*q)->rear = NULL;
}

int isEmptyQueue(Queue *q){
	return (q->front == NULL);
}

void enqueue(Queue *q, Item2 x){
	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode->value = x;

	if(isEmptyQueue(q)){
		q->front = newNode;
		q->rear = newNode;
	}else{
		q->rear->next = newNode;
		q->rear = newNode;
	}
}

void dequeue(Queue *q){
	if(isEmptyQueue(q))
		return;

	Node *del = q->front;
	if( q->front == q->rear )
		q->front = q->rear = NULL;
	else
		q->front = q->front->next;
	free(del);
}

Item2 front(Queue *q){
	return q->front->value;
}

void destroyQueue(Queue *q){
	while(!isEmptyQueue(q)){
		dequeue(q);
	}
	free(q);
}
#endif
