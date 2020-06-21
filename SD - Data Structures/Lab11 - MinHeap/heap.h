#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct MinHeapNode
{
    int v;
    int d;
} MinHeapNode;

typedef struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **elem;
} MinHeap;

MinHeapNode *newNode(int v, int d)
{
    MinHeapNode *node = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    node->v = v;
    node->d = d;
    return node;
}

MinHeap *newQueue(int capacity)
{
    MinHeap *q = (MinHeap *)malloc(sizeof(MinHeap));
    q->capacity = capacity;
    q->elem = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode));
    q->pos = (int *)calloc(capacity, sizeof(int));
    q->size = 0;
    return q;
}

void swap(MinHeapNode **a, MinHeapNode **b)
{
    // printf("inainte de swap : a = %d si b = %d\n", (*a)->v, (*b)->v);
    MinHeapNode *temp = *a;
    a = b;
    b = &temp;
    // printf("dupa swap : a = %d si b = %d\n\n", (*a)->v, (*b)->v);
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
    return floor((i - 1) / 2);
}

void SiftDown(MinHeap *h, int idx)
{
    int leftChild = getLeftChild(h->pos[idx]);
    int rightChild = getRightChild(h->pos[idx]);
    int smallest = h->pos[idx];
    // int leftChild = getLeftChild(idx), rightChild = getRightChild(idx),
    //     smallest = idx;

    if (leftChild < h->size && h->elem[leftChild]->d > h->elem[smallest]->d)
    {
        smallest = leftChild;
    }

    if (rightChild < h->size && h->elem[rightChild]->d > h->elem[smallest]->d)
    {
        smallest = rightChild;
    }

    if (smallest != idx)
    {
        // printf("aici vreodata?\n");
        swap(&(h->elem[smallest]), &(h->elem[idx]));
        SiftDown(h, smallest);
    }
}

MinHeapNode *removeMin(MinHeap *h)
{
    MinHeapNode *min = h->elem[0];
    MinHeapNode *last = h->elem[h->size - 1];
    h->size--;
    h->elem[0] = last;
    SiftDown(h, 0);
    return min;
}

int isEmpty(MinHeap *h)
{
    if (h == NULL)
        return -1;
    if (h->size == 0)
        return 1;
    return 0;
}

void SiftUp(MinHeap *h, int v, int d)
{
    // int parent = getParent(h->pos[v]);
    int parent = getParent(v);
    d = h->elem[h->pos[v]]->d;
    while (parent >= 0 && h->elem[h->pos[parent]]->d > d)
    {
                    printf("aici vreodata? sift up\n");
        swap(&h->elem[parent], &h->elem[v]);
        v = parent;
        parent = getParent(v);
    }
}

int isInMinHeap(MinHeap *h, int v)
{
    int i;
    for (i = 0; i < h->size; i++)
    {
        if (h->elem[i]->v == v)
        {
            return 1;
        }
    }
    return 0;
}

void insert(MinHeap *h, int v, int d)
{
    if (h->size == h->capacity)
    {
        h->capacity *= 2;
        h->elem = (MinHeapNode **)realloc(h->elem, h->capacity * sizeof(MinHeapNode));
    }
    h->elem[h->size] = newNode(v, d);
    h->size = h->size + 1;
    SiftUp(h, v, d);
}

#endif
