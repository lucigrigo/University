/*
 ============================================================================
 Name        : sdlab09.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef int Item;
#include "Heap.h"
ItemType elements[] = {{4,4},{2,2}, {8,8}, {7,7}};
int len = 4;

// -----------------------------------------------------------------------------

#define ASSERT(cond, msg) if (!(cond)) { failed(msg); return 0; }

void passed(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t Puncte: %.2f\n", s, score);
}

void passed2(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t\t Puncte: %.2f\n", s, score);
}

void failed(char* s) {
	printf("Testul %s NU a fost trecut!\n", s);
}

void swap(ItemType *a, ItemType* b){
	ItemType aux;
	aux.prior = a->prior;
	a->prior = b->prior;
	b->prior = aux.prior;
}

int testMakeQueue(PriQueue** pq,  float score) {


	(*pq) = makeQueue(len/2);
	ASSERT((*pq) != NULL, "MakeQueue-01");
	ASSERT((*pq)->elem != NULL, "MakeQueue-02");
	ASSERT((*pq)->maxHeapSize == len/2, "MakeQueue-02");
	ASSERT((*pq)->size == 0, "MakeQueue-03");
	printf(". ");

	passed2("MakeQueue", score);
	return 1;
}

int testGetParent(PriQueue** pq,  float score) {                   // tests insert

	ASSERT(getParent(2) == 0, "GetParent-01");
	ASSERT(getParent(9) == 4, "GetParent-02");
	ASSERT(getParent(4) == 1, "GetParent-03");
	printf(". ");

	passed2("GetParent", score);
	return 1;
}


int testGetLeftChild(PriQueue** pq,  float score) {

	ASSERT(getLeftChild(0) == 1, "GetLeftChild-01");
	ASSERT(getLeftChild(2) == 5, "GetLeftChild-02");
	ASSERT(getLeftChild(3) == 7, "GetLeftChild-03");
	ASSERT(getLeftChild(6) == 13, "GetLeftChild-04");
	printf(". ");

	passed2("GetLeftChild", score);
	return 1;
}

int testGetRightChild(PriQueue** pq,  float score) {

	ASSERT(getRightChild(0) == 2, "GetRightChild-01");
	ASSERT(getRightChild(2) == 6, "GetRightChild-02");
	ASSERT(getRightChild(3) == 8, "GetRightChild-03");
	ASSERT(getRightChild(6) == 14, "GetRightChild-04");
	printf(". ");

	passed2("getRightChild", score);
	return 1;
}


int testSiftUp(PriQueue** pq,  float score) {

	(*pq)->elem[0].prior = 4;
	siftUp((*pq), 0);
	ASSERT((*pq)->elem[0].prior = 4, "ShiftUp-01");


	(*pq)->elem[1].prior = 2;
	siftUp((*pq), 1);
	ASSERT((*pq)->elem[0].prior == 4, "ShiftUp-02");
	printf(". ");


	passed2("testSiftUp", score);
	return 1;
}

int testInsert(PriQueue** pq,  float score) {

	for(int i = 0; i < len; i++)
		insert(*pq, elements[i]);

	ASSERT((*pq)->maxHeapSize > 2, "Insert-01");
	ASSERT((*pq)->size == 4, "Insert-02");
	ASSERT((*pq)->elem[0].prior == 8, "Insert-03");

	ASSERT((*pq)->elem[1].prior == 7, "Insert-04");
	ASSERT((*pq)->elem[2].prior == 4, "Insert-05");
	ASSERT((*pq)->elem[3].prior == 2, "Insert-06");
	printf(". ");


	passed2("testInsert", score);
	return 1;
}



int testGetMax(PriQueue** pq,  float score) {
	ASSERT(getMax(*pq).prior == 8, "GetMax-01");
	printf(". ");

	passed2("testGetMax", score);
	return 1;
}

int testSiftDown(PriQueue** pq,  float score) {

	swap((*pq)->elem, (*pq)->elem + (*pq)->size - 1);
	siftDown(*pq, 0);
	ASSERT(getMax(*pq).prior == 7, "ShiftDown-01");

	siftUp(*pq, (*pq)->size - 3);
	ASSERT((*pq)->elem[0].prior == 8 , "ShiftDown-02");
	ASSERT((*pq)->elem[1].prior == 7 , "ShiftDown-03");
	ASSERT((*pq)->elem[2].prior == 4 , "ShiftDown-04");
	ASSERT((*pq)->elem[3].prior == 2 , "ShiftDown-05");

	swap((*pq)->elem + 1, (*pq)->elem + (*pq)->size - 1);
	siftDown(*pq, 1);
	ASSERT((*pq)->elem[0].prior == 8 , "ShiftDown-06");
	ASSERT((*pq)->elem[1].prior == 7 , "ShiftDown-07");
	ASSERT((*pq)->elem[2].prior == 4 , "ShiftDown-08");
	ASSERT((*pq)->elem[3].prior == 2 , "ShiftDown-09");
	printf(". ");

	passed2("testSiftDown", score);
	return 1;
}

int testRemoveMax(PriQueue** pq,  float score) {
	removeMax(*pq);
	ASSERT(getMax(*pq).prior == 7, "RemoveMax-01");

	removeMax(*pq);
	ASSERT(getMax(*pq).prior == 4, "RemoveMax-02");

	removeMax(*pq);
	ASSERT(getMax(*pq).prior == 2, "RemoveMax-03");
//
//	removeMax(*pq);
//	ASSERT(getMax(*pq).prior == 9, "RemoveMax-04");

	printf(". ");
	passed2("testRemoveMax", score);
	return 1;
}


int testFreeQueue(PriQueue **pq, float score) {
	freeQueue(*pq);
	printf(". Testul FreeQueue: *Se va verifica cu valgrind*\t Puncte: %.2f.\n", score);
	*pq = NULL;
	return 1;
}

typedef struct Test {
	int (*testFunction)(PriQueue** tree, float);
	float score;
} Test;

int main(int argc, char* argv[]) {
	Test tests[] =                                    // Define the tests you want
	{
			{ &testMakeQueue, 0.1 },
			{ &testGetParent, 0.05 },
			{ &testGetLeftChild, 0.05 },
			{ &testGetRightChild, 0.05 },
			{ &testSiftUp, 0.2},
			{ &testInsert, 0.1 },
			{ &testGetMax, 0.05 },
			{ &testSiftDown, 0.2 },
			{ &testRemoveMax, 0.1 },
			{ &testFreeQueue, 0.1 },
	};

	float totalScore = 0.0f, maxScore = 0.0f;
	long testsNo = sizeof(tests) / sizeof(Test);
	long testIdx;
	//  SortedList** testLists = (SortedList**) malloc(sizeof(SortedList*) * testsNo);
	PriQueue* pq = NULL;

	for (testIdx = 0; testIdx < testsNo; testIdx++) {
		float score = tests[testIdx].score;
		if ((*(tests[testIdx].testFunction))(&pq, score)) {
			totalScore += score;
		}
		maxScore += score;
	}
	printf("\nScor total: %.2f / %.2f\n\n", totalScore, maxScore);

	return 0;
}
