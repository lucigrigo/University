#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode
{
	Item elem;
	struct QueueNode *next;
} QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue
{
	QueueNode *front;
	QueueNode *rear;
	long size;
} Queue;

typedef Queue TCoada;
typedef Queue *AQ;

Queue *createQueue(void)
{
	Queue *ptr = (Queue *)malloc(sizeof(Queue));
	ptr->front = NULL;
	ptr->rear = NULL;
	ptr->size = 0;
	return ptr;
}

int isQueueEmpty(Queue *q)
{
	if (q != NULL)
	{
		if (q->size == 0 && q->front == NULL && q->rear == NULL)
		{
			return 1;
		}
	}
	return 0;
}

void enqueue(Queue *q, Item elem)
{
	if (q == NULL)
	{
		return;
	}
	if (q->size == 0)
	{
		QueueNode *ptr = (QueueNode *)malloc(sizeof(QueueNode));
		ptr->elem = elem;
		ptr->next = NULL;
		q->front = ptr;
		q->rear = ptr;
		q->size = 1;
		return;
	}
	QueueNode *ptr = (QueueNode *)malloc(sizeof(QueueNode));
	ptr->elem = elem;
	ptr->next = NULL;
	q->rear->next = ptr;
	q->rear = ptr;
	q->size = q->size + 1;
}

Item front(Queue *q)
{
	return q->front->elem;
}

void dequeue(Queue *q)
{
	if (q == NULL)
	{
		return;
	}
	if (q->size == 0)
	{
		return;
	}
	if (q->size == 1)
	{
		q->rear = NULL;
		q->front = NULL;
		q->size = 0;
		return;
	}
	QueueNode *aux = q->front;
	q->front = q->front->next;
	q->size = q->size - 1;
	free(aux);
}

void destroyQueue(Queue *q)
{
	if (q == NULL)
	{
		return;
	}
	if (q->size == 0)
	{
		free(q);
		return;
	}
	QueueNode *ptr = q->front, *aux;
	while (ptr != q->rear)
	{
		aux = ptr->next;
		free(ptr);
		ptr = aux;
	}
	free(q->rear);
	free(q);
}

#endif
