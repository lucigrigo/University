#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Maximum number of characters that can be read
 * in one go from the keyboard
 */
#define MAX_INPUT_LEN 255

/**
 *  Generic Item type definition
 */
typedef char Item;

/**
 * The Double linked list interface
 */
#include "DoubleLinkedList.h"


// -----------------------------------------------------------------------------
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

int testCreate(void** list, float score){
	ASSERT((*list) == NULL, "Create-01");

	*list = (void*) createList();

	ASSERT((*((List**)list)) != NULL, "Create-02");
	ASSERT((*((List**)list))->first == NULL, "Create-03");
	ASSERT((*((List**)list))->last == NULL, "Create-04");
	printf(". ");

	passed("Create", score);
	return 1;
}

int testIsEmpty(void** list, float score){

	ASSERT((*list) != NULL, "IsEmpty-01");

	ASSERT(isEmpty(*((List**)list)) == 1, "IsEmpty-02");

	ListNode aNode = {'x', NULL, NULL};
	(*((List**)list))->first = (*((List**)list))->last = &aNode;

	ASSERT(isEmpty(*((List**)list)) == 0, "IsEmpty-03");

	(*((List**)list))->first = (*((List**)list))->last = NULL;
	ASSERT(isEmpty(*((List**)list)) == 1, "IsEmpty-04");

	printf(". ");
	passed("IsEmpty", score);
	return 1;
}


int testContains(void** list, float score){

	ASSERT((*list) != NULL, "Contains-01");

	ASSERT(contains((*((List**)list)),'x') == 0, "Contains-02");
	ASSERT(contains((*((List**)list)),'y') == 0, "Contains-03");
	ASSERT(contains((*((List**)list)),'z') == 0, "Contains-04");
	ASSERT(contains((*((List**)list)),'-') == 0, "Contains-05");

	ListNode nodes[] = {
			{'x', NULL, NULL},
			{'y', NULL, NULL},
			{'z', NULL, NULL}
	};
	(*((List**)list))->first = nodes;
	(*((List**)list))->last = (nodes + 2);

	nodes->next = (nodes+1);
	(nodes+2)->prev = (nodes+1);
	(nodes+1)->next = (nodes+2);
	(nodes+1)->prev = nodes;

	ASSERT(contains((*((List**)list)),'x') == 1, "Contains-06");
	ASSERT(contains((*((List**)list)),'y') == 1, "Contains-07");
	ASSERT(contains((*((List**)list)),'z') == 1, "Contains-08");
	ASSERT(contains((*((List**)list)),'z') == 1, "Contains-08");
	ASSERT((*((List**)list))->first->prev == NULL, "Insert-09");
	ASSERT((*((List**)list))->last->next == NULL, "Insert-10");

	(*((List**)list))->first = (*((List**)list))->last = NULL;

	printf(". ");
	passed("Contains", score);
	return 1;
}



int testInsert(void** list, float score){

	ASSERT((*list) != NULL, "Insert-01");

	insertAt((*((List**)list)), 'x', -1);
	ASSERT(isEmpty(*((List**)list)) == 1, "Insert-02");


	insertAt((*((List**)list)), 'x', 1);
	ASSERT(isEmpty(*((List**)list)) == 1, "Insert-03");

	insertAt((*((List**)list)), 'x', 0);
	ASSERT(isEmpty(*((List**)list)) == 0, "Insert-04");
	ASSERT((*((List**)list))->first->elem == 'x', "Insert-05");
	ASSERT((*((List**)list))->last->elem == 'x', "Insert-06");
	ASSERT((*((List**)list))->first == (*((List**)list))->last, "Insert-07");

	insertAt((*((List**)list)), 'x', -1);
	ASSERT((*((List**)list))->first->next == NULL, "Insert-08");
	ASSERT((*((List**)list))->last->prev == NULL, "Insert-09");


	insertAt((*((List**)list)), 'x', 2);
	ASSERT((*((List**)list))->first->next == NULL, "Insert-08");
	ASSERT((*((List**)list))->last->prev == NULL, "Insert-09");

	insertAt((*((List**)list)), 'y', 0);
	ASSERT((*((List**)list))->first->elem == 'y', "Insert-10");
	ASSERT((*((List**)list))->last->elem == 'x', "Insert-11");
	ASSERT((*((List**)list))->last->next == NULL, "Insert-12");
	ASSERT((*((List**)list))->first->prev == NULL, "Insert-13");

	insertAt((*((List**)list)), 'z', 2);
	ASSERT((*((List**)list))->first->elem == 'y', "Insert-14");
	ASSERT((*((List**)list))->last->elem == 'z', "Insert-15");
	ASSERT((*((List**)list))->first->next->elem == 'x', "Insert-16");
	ASSERT((*((List**)list))->last->next == NULL, "Insert-17");
	ASSERT((*((List**)list))->first->prev == NULL, "Insert-18");

	insertAt((*((List**)list)), 'y', 2);
	ASSERT((*((List**)list))->first->next->elem == 'x', "Insert-19");
	ASSERT((*((List**)list))->last->elem == 'z', "Insert-20");
	ASSERT((*((List**)list))->first->next->next == (*((List**)list))->last->prev, "Insert-21");
	ASSERT((*((List**)list))->last->prev->prev == (*((List**)list))->first->next, "Insert-22");
	ASSERT((*((List**)list))->last->prev->prev->prev->elem == 'y', "Insert-23");
	ASSERT((*((List**)list))->last->next == NULL, "Insert-24");
	ASSERT((*((List**)list))->first->prev == NULL, "Insert-25");

	printf(". ");
	passed("Insert", score);
	return 1;
}

int testDeleteOnce(void** list, float score){

	ASSERT((*list) != NULL, "DeleteOnce-01");
	ASSERT((*((List**)list))->first != NULL, "DeleteOnce-01");
	ASSERT((*((List**)list))->last != NULL, "DeleteOnce-02");

	deleteOnce((*((List**)list)), 'x');
	ASSERT(contains((*((List**)list)),'x') == 0, "DeleteOnce-03");
	ASSERT(contains((*((List**)list)),'z') == 1, "DeleteOnce-04");
	ASSERT((*((List**)list))->first->next->elem == 'y', "DeleteOnce-05");

	deleteOnce((*((List**)list)), 'y');
	ASSERT((*((List**)list))->first->elem == 'y', "DeleteOnce-06");
	ASSERT((*((List**)list))->first->prev == NULL, "DeleteOnce-07");
	ASSERT((*((List**)list))->first->next->elem == 'z', "DeleteOnce-08");


	deleteOnce((*((List**)list)), 'z');
	ASSERT((*((List**)list))->first->elem == 'y', "DeleteOnce-09");
	ASSERT((*((List**)list))->first->prev == NULL, "DeleteOnce-10");
	ASSERT((*((List**)list))->first->next == NULL, "DeleteOnce-11");
	ASSERT((*((List**)list))->last->prev == NULL, "DeleteOnce-12");
	ASSERT((*((List**)list))->last->next == NULL, "DeleteOnce-13");

	deleteOnce((*((List**)list)), 'y');
	ASSERT((*((List**)list))->first == NULL, "DeleteOnce-14");
	ASSERT((*((List**)list))->last == NULL, "DeleteOnce-15");


	insertAt((*((List**)list)), 'x', -1);
	ASSERT((*((List**)list)) != NULL, "DeleteOnce-16");
	ASSERT((*((List**)list))->first == NULL, "DeleteOnce-17");
	ASSERT((*((List**)list))->last == NULL, "DeleteOnce-18");


	deleteOnce((*((List**)list)), 'y');
	ASSERT((*((List**)list))->first == NULL, "DeleteOnce-19");
	ASSERT((*((List**)list))->last == NULL, "DeleteOnce-20");


	insertAt((*((List**)list)), 'x', 0);
	ASSERT((*((List**)list))->last != NULL, "DeleteOnce-21");
	ASSERT((*((List**)list))->last == (*((List**)list))->first, "DeleteOnce-22");

	insertAt((*((List**)list)), 'y', 0);
	ASSERT((*((List**)list))->first != NULL, "DeleteOnce-23");
	ASSERT((*((List**)list))->last != NULL, "DeleteOnce-24");
	ASSERT((*((List**)list))->last != (*((List**)list))->first, "DeleteOnce-25");

	insertAt((*((List**)list)), 'y', 2);
	insertAt((*((List**)list)), 'z', 3);

	printf(". ");
	passed("DeleteOnce", score);
	return 1;
}

int testLength(void** list, float score){

	ASSERT((*list) != NULL, "Length-01");
	ASSERT(isEmpty(*((List**)list)) == 0, "Length-02");

	ASSERT(length(*((List**)list)) == 4, "Length-03");

	deleteOnce((*((List**)list)), '-');
	ASSERT(length(*((List**)list)) == 4, "Length-04");


	deleteOnce((*((List**)list)), 'x');
	ASSERT(length(*((List**)list)) == 3, "Length-05");


	deleteOnce((*((List**)list)), 'y');
	deleteOnce((*((List**)list)), 'y');
	deleteOnce((*((List**)list)), 'z');
	ASSERT(length(*((List**)list)) == 0, "Length-06");

	printf(". ");
	passed("Length", score);
	return 1;
}

int testDestroy(void** list, float score){
	destroyList(*((List**)list));
	printf(". ");

	printf("  *Destroy se va verifica cu valgrind*\t Puncte: %.2f.\n", score);
	return 1;
}

/**
 * Utility function for printing character lists
 */
void printList(List *list){
	ListNode* iterator = list->first;
	printf("[");
	while(iterator != list->last){
		printf("%c, ", iterator->elem);
		iterator = iterator->next;
	}
	printf("%c]",list->last->elem);
}

void printListReverse(List* list){
	ListNode* iterator = list->last;
	printf("[");
	while(iterator != list->last){
		printf("%c ", iterator->elem);
		iterator = iterator->prev;
	}
	printf("%c]",list->last->elem);
}

int main(int argc, char** argv) {
	List *list = NULL;
	Test tests[] =  // Define the tests you want
	{
            { &testCreate, 0.05},
			{ &testIsEmpty, 0.05 },
			{ &testContains, 0.1 },
			{ &testInsert, 0.2},
			{ &testDeleteOnce, 0.2},
			{ &testLength, 0.1},
			{ &testDestroy, 0.1},
	};


	float totalScore = 0.0f, maxScore = 0.0f;
	long testsNo = sizeof(tests) / sizeof(Test);
	long testIdx;

	for (testIdx = 0; testIdx < testsNo; testIdx++) {
		float score = tests[testIdx].score;
		if(tests[testIdx].testFunction(((void**) &list),score)){
			totalScore += score;
		}
		maxScore += score;
	}
	printf("\nScor total: %.2f / %.2f\n\n", totalScore, maxScore);

	return 0;
}
