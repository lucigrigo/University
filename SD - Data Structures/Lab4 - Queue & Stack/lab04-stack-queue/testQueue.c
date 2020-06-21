#include <stdio.h>
#include <stdlib.h>

/**
 *  Generic Item type definition
 */
typedef int Item ;

/**
 * The Queue interface
 */
#include "Queue.h"


//-----------------------------------------------------------------------------
#define ASSERT(cond, msg) if (!(cond)) { failed(msg); return 0; }
void passed(char* s, float score) {
  printf("Testul %s a fost trecut cu succes!\t Puncte: %.2f\n", s, score);
}

void failed(char* s) {
  printf("Testul %s NU a fost trecut!\n", s);
}
// -----------------------------------------------------------------------------
typedef struct Test {
  int (*testFunction)(void**, float);
  float score;
} Test;

// -----------------------------------------------------------------------------

int testCreate(void** queue, float score){
	ASSERT((*queue) == NULL, "Create-01");

	*queue = (void*) createQueue();

	ASSERT((*((Queue**)queue)) != NULL, "Create-02");
	ASSERT((*((Queue**)queue))->front == NULL, "Create-03");
	ASSERT((*((Queue**)queue))->rear == NULL, "Create-04");
	ASSERT((*((Queue**)queue))->size == 0, "Create-05");

	printf(". ");

	passed("Create", score);
	return 1;
}
// -----------------------------------------------------------------------------


int testIsEmpty(void** queue, float score){

	ASSERT((*queue) != NULL, "IsEmpty-01");

	ASSERT(isQueueEmpty(*queue) == 1, "IsEmpty-02");

	QueueNode aNode = {2, NULL};
	(*((Queue**)queue))->rear = &aNode;
	(*((Queue**)queue))->front = &aNode;


	ASSERT(isQueueEmpty(*((Queue**)queue)) == 0, "IsEmpty-03");
	(*((Queue**)queue))->front =  (*((Queue**)queue))->rear = NULL;

	ASSERT((*((Queue**)queue))->size == 0, "IsEmpty-04");

	printf(". ");
	passed("IsQueueEmpty", score);
	return 1;
}
// -----------------------------------------------------------------------------

int testEnqueue(void** queue, float score){

 	ASSERT((*queue) != NULL, "Enqueue-01");

 	ASSERT((*((Queue**)queue))->front == NULL, "Enqueue-02");
 	ASSERT((*((Queue**)queue))->rear == NULL, "Enqueue-03");
	ASSERT((*((Queue**)queue))->size == 0, "Enqueue-04");


	enqueue(*queue, 1);
	ASSERT((*((Queue**)queue))->front != NULL, "Enqueue-05");
	ASSERT((*((Queue**)queue))->rear != NULL, "Enqueue-06");
	ASSERT((*((Queue**)queue))->size == 1, "Enqueue-07");
	ASSERT((*((Queue**)queue))->front->elem == 1, "Enqueue-08");
	ASSERT((*((Queue**)queue))->rear->elem == 1, "Enqueue-09");
	ASSERT((*((Queue**)queue))->front->next == NULL, "Enqueue-10");

	enqueue(*queue, 2);
	ASSERT((*((Queue**)queue))->front != NULL, "Enqueue-11");
	ASSERT((*((Queue**)queue))->rear != NULL, "Enqueue-12");
	ASSERT((*((Queue**)queue))->rear != (*((Queue**)queue))->front, "Enqueue-13");
	ASSERT((*((Queue**)queue))->size == 2, "Enqueue-14");
	ASSERT((*((Queue**)queue))->rear->next == NULL, "Enqueue-15");
	ASSERT((*((Queue**)queue))->front->next->next == NULL, "Enqueue-16");
	ASSERT((*((Queue**)queue))->front->elem == 1, "Enqueue-17");
	ASSERT((*((Queue**)queue))->rear->elem == 2, "Enqueue-18");


	enqueue(*queue, 3);
	enqueue(*queue, 4);
	enqueue(*queue, 5);
	ASSERT((*((Queue**)queue))->size == 5, "Enqueue-19");
	ASSERT((*((Queue**)queue))->rear->elem == 5, "Enqueue-20");
	ASSERT((*((Queue**)queue))->front->elem == 1, "Enqueue-21");
	ASSERT((*((Queue**)queue))->front->next->next->elem == 3, "Enqueue-22");
	ASSERT((*((Queue**)queue))->front->next->next->next->elem == 4, "Enqueue-23");

	printf(". ");
	passed("Enqueue ", score);
	return 1;
}
// -----------------------------------------------------------------------------

int testFront(void** queue, float score){

 	ASSERT((*queue) != NULL, "Front-01");
 	enqueue(*queue, 6);
 	ASSERT((*((Queue**)queue))->front->elem == 1, "Front-02");
 	ASSERT((*((Queue**)queue))->rear->elem == 6, "Front-03");
 	enqueue(*queue, 7);
 	enqueue(*queue, 8);
 	ASSERT((*((Queue**)queue))->rear->elem == 8, "Front-04");
 	ASSERT((*((Queue**)queue))->front->next->next->next->next->next->elem == 6, "Front-05");

 	printf(". ");
	passed("Front    ", score);
	return 1;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

int testDequeue(void** queue, float score){

 	ASSERT((*queue) != NULL, "Dequeue-01");
 	ASSERT((*((Queue**)queue))->size == 8, "Dequeue-02");
	
	dequeue(*queue);
	dequeue(*queue);
	ASSERT((*((Queue**)queue))->size == 6, "Dequeue-03");
	ASSERT((*((Queue**)queue))->front->elem == 3, "Dequeue-04");
	ASSERT((*((Queue**)queue))->rear->elem == 8, "Dequeue-05");

	dequeue(*queue);
	dequeue(*queue);
	dequeue(*queue);
	ASSERT((*((Queue**)queue))->size == 3, "Dequeue-06");
	ASSERT((*((Queue**)queue))->front->elem == 6, "Dequeue-07");
	ASSERT((*((Queue**)queue))->rear->elem == 8, "Dequeue-08");

	enqueue(*queue,4);
	dequeue(*queue);
	ASSERT((*((Queue**)queue))->size == 3, "Dequeue-09");
	ASSERT((*((Queue**)queue))->front->elem == 7, "Dequeue-10");

	dequeue(*queue);
	dequeue(*queue);
	ASSERT((*((Queue**)queue))->front->elem == 4, "Dequeue-11");	
	ASSERT((*((Queue**)queue))->front->next == NULL, "Dequeue-12");
	ASSERT((*((Queue**)queue))->rear->next == NULL, "Dequeue-13");

	dequeue(*queue);
	ASSERT((*((Queue**)queue))->front == NULL, "Dequeue-14");	
	ASSERT((*((Queue**)queue))->rear == NULL, "Dequeue-15");	
	
	enqueue(*queue, 4);
	enqueue(*queue, 1);
	enqueue(*queue, 2);
	enqueue(*queue, 3);
	dequeue(*queue);
	ASSERT((*((Queue**)queue))->front->elem == 1, "Dequeue-16");	
	ASSERT((*((Queue**)queue))->front->next->next->next == NULL, "Dequeue-17");
	ASSERT((*((Queue**)queue))->rear->next == NULL, "Dequeue-18");
	ASSERT((*((Queue**)queue))->rear->elem == 3, "Dequeue-19");

 	printf(". ");
	passed("Dequeue", score);
	return 1;
}
// -----------------------------------------------------------------------------

int testDestroy(void** queue, float score){

 	ASSERT((*queue) != NULL, "Destroy-01");
 	destroyQueue(*queue);

 	printf(". ");
	printf("  *Destroy se va verifica cu valgrind*\t Puncte: %.2f.\n", score);
	return 1;
}
//-----------------------------------------------------------------------------

int main(int argc, char** argv) {
	Queue* queue = NULL;
	Test tests[] =  // Define the tests you want
	{
            { &testCreate, 0.03},
			{ &testIsEmpty, 0.02 },
			{ &testEnqueue, 0.1 },
			{ &testFront, 0.05 },
			{ &testDequeue, 0.1 },
			{ &testDestroy, 0.1},
	};


	float totalScore = 0.0f, maxScore = 0.0f;
	long testsNo = sizeof(tests) / sizeof(Test);
	long testIdx;

	for (testIdx = 0; testIdx < testsNo; testIdx++) {
		float score = tests[testIdx].score;
		if(tests[testIdx].testFunction(((void**) &queue),score)){
			totalScore += score;
		}
		maxScore += score;
	}
	printf("\nScor total: %.2f / %.2f\n\n", totalScore, maxScore);

	return 0;
}