/*
*	Created by Nan Mihai on 04.04.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator - Proiectarea algoritmilor (Grafuri)
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/
#include "heap.h"

Heap initHeap(int (*compare_func) (const void*, const void*))
{
	Heap h = (Heap)malloc(sizeof(struct heap));
	h->size = 0;
	h->capacity = SIZE;
	h->compare_func = compare_func;
	return h;
}

Heap siftDown(Heap h, int index)
{
	int maxIndex = index;

	int l = index * 2 + 1;
	if(l < h->size && h->compare_func(&h->vector[l], &h->vector[maxIndex]) > 0) maxIndex = l;
	int r = index * 2 + 2;
	if(r < h->size && h->compare_func(&h->vector[r], &h->vector[maxIndex]) > 0) maxIndex = r;
	if(index != maxIndex)
	{
		Type aux = h->vector[index];
		h->vector[index] = h->vector[maxIndex];
		h->vector[maxIndex] = aux;
		h = siftDown(h, maxIndex);
	}
	return h;
}

Heap siftUp(Heap h, int index)
{
	while (index >= 0 && h->compare_func(&h->vector[(index - 1) / 2], &h->vector[index]) < 0)
	{
		Type aux = h->vector[(index - 1) / 2];
		h->vector[(index - 1) / 2] = h->vector[index];
		h->vector[index] = aux;
		index = (index - 1) / 2;
	}
	return h;
}

Heap swapAndSiftDown(Heap h, int parent, int child)
{
	if (!h) return NULL;
	if (h->compare_func(&h->vector[parent], &h->vector[child]) > 0)
	{
		Type aux = h->vector[parent];
		h->vector[parent] = h->vector[child];
		h->vector[child] = aux;
	}
	return h;
}

Heap insertHeap(Heap h, Type element)
{
	h->vector[h->size] = element;
	h = siftUp(h, h->size);
	h->size++;
	return h;
}

Type extractMax(Heap h)
{
	Type max;
	if(h && h->size >= 0)
	{
		max = h->vector[0];
		h->vector[0] = h->vector[h->size - 1];
		h->size--;
		h = siftDown(h, 0);
		return max;
	}
	return NULL;
}

Heap freeHeap(Heap h)
{
	free(h);
	return NULL;
}
