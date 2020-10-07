#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct
{
	int prior; // Item priority
	Item data; // Item d
} ItemType;

typedef struct heap
{
	long maxHeapSize; // capacity
	long size;		  // number of elements
	ItemType *elem;   // array of elements
} PriQueue, *APriQueue;

PriQueue *makeQueue(int maxHeapSize)
{
	PriQueue *newQ = (PriQueue *)malloc(sizeof(PriQueue));
	newQ->maxHeapSize = maxHeapSize;
	newQ->size = 0;
	newQ->elem = (ItemType *) malloc(maxHeapSize * sizeof(ItemType));
	return newQ;
}

int getLeftChild(int i)
{
	return 2 * i + 1;
}

int getRightChild(int i)
{
	return 2 * i + 2;
}

int getParent(int i)
{
	return (i - 1) / 2;
}

ItemType getMax(APriQueue h)
{
	return h->elem[0];
}

void siftUp(APriQueue h, int idx)
{
	while(idx >= 1){
		int pdx = (idx - 1) / 2;
		if(h->elem[pdx].prior < h->elem[idx].prior) {
			int auxData = h->elem[pdx].data;
			h->elem[pdx].data = h->elem[idx].data;
			h->elem[idx].data = auxData;
			int auxPrior = h->elem[pdx].prior;
			h->elem[pdx].prior = h->elem[idx].prior;
			h->elem[idx].prior = auxPrior;
		}
		idx = pdx;
	}
}

void insert(PriQueue *h, ItemType x)
{
	if(h->maxHeapSize == h->size){
		h->elem = realloc(h->elem, 2 * h->maxHeapSize * sizeof(ItemType));
		h->maxHeapSize = h->maxHeapSize * 2;
	}
	h->elem[h->size] = x;
	siftUp(h, h->size);
	h->size = h->size + 1;
}

void siftDown(APriQueue h, int idx)
{
	while(idx < h->size){
		int leftPrior = h->elem[getLeftChild(idx)].prior;
		int rightPrior = h->elem[getRightChild(idx)].prior;
		if(h->elem[idx].prior > leftPrior &&
			h->elem[idx].prior > rightPrior) {
				break;
		}
		int pdx;
		if(leftPrior > rightPrior) {
			pdx = getLeftChild(idx);
		} else {
			pdx = getRightChild(idx);
		}
		int auxData = h->elem[pdx].data;
		h->elem[pdx].data = h->elem[idx].data;
		h->elem[idx].data = auxData;
		int auxPrior = h->elem[pdx].prior;
		h->elem[pdx].prior = h->elem[idx].prior;
		h->elem[idx].prior = auxPrior;
		idx = pdx;
	}
}

void removeMax(APriQueue h)
{
	h->size = h->size - 1;
	int i = 0;
	while(i < h->size){
		h->elem[i] = h->elem[i + 1];
		i++;
	}
}

void freeQueue(APriQueue h)
{
	free(h->elem);
	free(h);
}

#endif
