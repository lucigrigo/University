#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>


/* We assume there is a defined primitive type Item. */

typedef struct {
    Item content;
    int prior;
} ItemType;

typedef struct heap {
    long int capacity;
    long int size;
    ItemType *elem;
} PriQueue, *APriQueue;


APriQueue makeQueue(int capacity) {
    APriQueue h = (APriQueue) malloc(sizeof(PriQueue));
    h->elem = (ItemType *) malloc(capacity * sizeof(ItemType));
    h->capacity = capacity;
    h->size = 0;
    return h;
}

int getLeftChild(int i) {
    return 2 * i + 1;
}

int getRightChild(int i) {
    return 2 * i + 2;
}

int getParent(int i) {
    return floor((i - 1) / 2);
}

void siftUp(APriQueue h, int idx) {
    int parent = getParent(idx);

    while (parent >= 0 && h->elem[parent].prior > h->elem[idx].prior) {
        ItemType aux = h->elem[parent];
        h->elem[parent] = h->elem[idx];
        h->elem[idx] = aux;

        idx = parent;
        parent = getParent(idx);
    }
}

void insert(APriQueue h, ItemType x) {
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->elem = (ItemType *) realloc(h->elem, h->capacity * sizeof(ItemType));
    }

    h->elem[h->size] = x;
    h->size++;
    siftUp(h, h->size - 1);
}

ItemType getMinAPriQueue h) {
    return h->elem[0];
}

void siftDown(APriQueue h, int idx) {
    int leftChild = getLeftChild(idx);
    int rightChild = getRightChild(idx);
    int smallest = idx;

    if (leftChild < h->size && h->elem[leftChild].prior < h->elem[smallest].prior) {
        smallest = leftChild;
    }

    if (rightChild < h->size && h->elem[rightChild].prior < h->elem[smallest].prior) {
        smallest = rightChild;
    }

    if (smallest != idx) {
        ItemType aux = h->elem[smallest];
        h->elem[smallest] = h->elem[idx];
        h->elem[idx] = aux;

        siftDown(h, smallest);
    }
}

ItemType removeMin(APriQueue h) {
    ItemType min = getMin(h);
    ItemType last = h->elem[h->size - 1];

    /* Remove the last elem from the vector. */
    h->size--;

    /* Set latest elem as the first and call heapify downwards. */
    h->elem[0] = last;
    siftDown(h, 0);

    return min;
}

#endif

