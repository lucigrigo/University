#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 *  Generic Item type definition
 */
typedef int Item ;

/**
 * The Stack interface
 */
#include "Stack.h"


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

int testCreate(void** stack, float score){
	ASSERT((*stack) == NULL, "Create-01");

	*stack = (void*) createStack();

	ASSERT((*((Stack**)stack)) != NULL, "Create-02");
	ASSERT((*((Stack**)stack))->head == NULL, "Create-03");

	ASSERT((*((Stack**)stack))->size == 0, "Create-04");

	printf(". ");

	passed("Create", score);
	return 1;
}
// -----------------------------------------------------------------------------

int testIsEmpty(void** stack, float score){

	ASSERT((*stack) != NULL, "IsEmpty-01");

	ASSERT(isStackEmpty(*((Stack**)stack)) == 1, "IsEmpty-02");

	StackNode aNode = {2, NULL};
	(*((Stack**)stack))->head = &aNode;
	ASSERT(isStackEmpty(*((Stack**)stack)) == 0, "IsEmpty-03");
	(*((Stack**)stack))->head = NULL;

	ASSERT((*((Stack**)stack))->size == 0, "IsEmpty-04");

	printf(". ");
	passed("IsStackEmpty", score);
	return 1;
}
// -----------------------------------------------------------------------------

int testPush(void** stack, float score){

 	ASSERT((*stack) != NULL, "Push-01");

 	ASSERT((*((Stack**)stack))->head == NULL, "Push-02");
	ASSERT((*((Stack**)stack))->size == 0, "Push-03");


	push(*stack, 1);
	ASSERT((*((Stack**)stack))->head != NULL, "Push-04");
	ASSERT((*((Stack**)stack))->size == 1, "Push-05");
	ASSERT((*((Stack**)stack))->head->elem == 1, "Push-06");
	ASSERT((*((Stack**)stack))->head->next == NULL, "Push-07");

	push(*stack, 2);
	ASSERT((*((Stack**)stack))->head != NULL, "Push-08");
	ASSERT((*((Stack**)stack))->size == 2, "Push-09");
	ASSERT((*((Stack**)stack))->head->next->next == NULL, "Push-10");
	ASSERT((*((Stack**)stack))->head->next->elem == 1, "Push-11");
	ASSERT((*((Stack**)stack))->head->elem == 2, "Push-12");


	push(*stack, 3);
	push(*stack, 4);
	push(*stack, 5);
	ASSERT((*((Stack**)stack))->size == 5, "Push-13");
	ASSERT((*((Stack**)stack))->head->elem == 5, "Push-14");
	ASSERT((*((Stack**)stack))->head->next->next->elem == 3, "Push-14");
	ASSERT((*((Stack**)stack))->head->next->next->next->elem == 2, "Push-15");

	printf(". ");
	passed("Push   ", score);
	return 1;
}
// -----------------------------------------------------------------------------

int testTop(void** stack, float score){

 	ASSERT((*stack) != NULL, "Top-01");
 	push(*stack, 6);
 	ASSERT((*((Stack**)stack))->head->elem == 6, "Top-02");
 	push(*stack, 7);
 	push(*stack, 8);
 	ASSERT((*((Stack**)stack))->head->elem == 8, "Top-03");

 	printf(". ");
	passed("Top    ", score);
	return 1;
}
// -----------------------------------------------------------------------------

int testPop(void** stack, float score){

 	ASSERT((*stack) != NULL, "Pop-01");
 	ASSERT((*((Stack**)stack))->size == 8, "Pop-02");
	
	pop(*stack);
	pop(*stack);
	ASSERT((*((Stack**)stack))->size == 6, "Pop-03");
	ASSERT((*((Stack**)stack))->head->elem == 6, "Pop-04");

	pop(*stack);
	pop(*stack);
	pop(*stack);
	ASSERT((*((Stack**)stack))->size == 3, "Pop-05");
	ASSERT((*((Stack**)stack))->head->elem == 3, "Pop-06");

	push(*stack,4);
	pop(*stack);
	ASSERT((*((Stack**)stack))->size == 3, "Pop-07");
	ASSERT((*((Stack**)stack))->head->elem == 3, "Pop-08");

	pop(*stack);
	pop(*stack);
	ASSERT((*((Stack**)stack))->head->elem == 1, "Pop-09");	
	ASSERT((*((Stack**)stack))->head->next == NULL, "Pop-10");

	pop(*stack);
	ASSERT((*((Stack**)stack))->head == NULL, "Pop-11");	
	

	push(*stack, 3);
	push(*stack, 2);
	push(*stack, 1);
	push(*stack, 4);
	pop(*stack);

	ASSERT((*((Stack**)stack))->head->elem == 1, "Pop-12");	
	ASSERT((*((Stack**)stack))->head->next->next->next == NULL, "Pop-13");


 	printf(". ");
	passed("Pop    ", score);
	return 1;
}
// -----------------------------------------------------------------------------



int testDestroy(void** stack, float score){

 	ASSERT((*stack) != NULL, "Destroy-01");
 	destroyStack(*stack);

 	printf(". ");
	printf("  *Destroy se va verifica cu valgrind*\t Puncte: %.2f.\n", score);
	return 1;
}
// -----------------------------------------------------------------------------



int main(int argc, char** argv) {
	Stack *stack = NULL;
	Test tests[] =  // Define the tests you want
	{
            { &testCreate, 0.03},
			{ &testIsEmpty, 0.02 },
			{ &testPush, 0.1 },
			{ &testTop, 0.05 },
			{ &testPop, 0.1 },
			{ &testDestroy, 0.1},
	};


	float totalScore = 0.0f, maxScore = 0.0f;
	long testsNo = sizeof(tests) / sizeof(Test);
	long testIdx;

	for (testIdx = 0; testIdx < testsNo; testIdx++) {
		float score = tests[testIdx].score;
		if(tests[testIdx].testFunction(((void**) &stack),score)){
			totalScore += score;
		}
		maxScore += score;
	}
	printf("\nScor total: %.2f / %.2f\n\n", totalScore, maxScore);

	return 0;
}