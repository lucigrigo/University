#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long Item;
#include "BST.h"

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

// -----------------------------------------------------------------------------

int testInit(BSTree** tree,  float score) {                   // tests init


	(*tree) = createTree();
	ASSERT((*tree)->root != NULL, "Init-01");
	ASSERT((*tree)->nil != NULL, "Init-02");
	ASSERT((*tree)->root->l == (*tree)->nil, "Init-03");
	ASSERT((*tree)->root->r == (*tree)->nil, "Init-04");
	ASSERT(((*tree)->nil->l == (*tree)->nil), "Init-05");
	ASSERT(((*tree)->nil->r == (*tree)->nil), "Init-06");
	ASSERT(isEmpty((*tree)) == 1, "IsEmpty-01");
	printf(". ");

	passed2("Init&IsEmpty", score);
	return 1;
}

int testInsert(BSTree** tree,  float score) {                   // tests insert

	insert(*(tree),5l);
	ASSERT(isEmpty(*tree) != 1, "Insert-01");
	ASSERT((*tree)->root->l->l == (*tree)->nil, "Insert-02");
	ASSERT((*tree)->root->l->r == (*tree)->nil, "Insert-03");

	insert((*tree), 3l);
	insert((*tree), 2l);
	ASSERT((*tree)->root->l->l->elem == 3l, "Insert-04");
	ASSERT((*tree)->root->l->l->l->elem == 2l, "Insert-05");

	insert((*tree), 2l);
	insert((*tree), 5l);
	ASSERT((*tree)->size == 3l, "Insert-06");

	insert((*tree),4l);
	insert((*tree),7l);
	insert((*tree),6l);
	insert((*tree),8l);
	ASSERT((*tree)->root->l->r->elem == 7l,"Insert-07");
	ASSERT((*tree)->root->l->r->l->elem == 6l,"Insert-08");
	ASSERT((*tree)->root->l->r->r->elem == 8l,"Insert-09");
	printf(". ");

	passed2("Insert", score);
	return 1;
}

int testSearch(BSTree** tree, float score) {                   // tests contains

	ASSERT((search(*tree,4l) != NULL) == 1,"Search-01");
	ASSERT((search(*tree,10l) != NULL) == 0,"Search-02");

	ASSERT(search((*tree),0) == NULL,"Search-03");
	ASSERT(search((*tree),5)->l == (*tree)->root->l->l,"Search-04");
	ASSERT(search((*tree),5)->r == (*tree)->root->l->r,"Search-05");
	printf(". ");

	passed2("Search", score);

	return 1;
}

int testMinMax(BSTree* (*tree),  float score) { // test min max

	ASSERT(minimum((*tree),(*tree)->root->l)->elem == 2l, "MinMax-01");
	ASSERT(minimum((*tree),(*tree)->root->l)->l == (*tree)->nil, "MinMax-02");
	ASSERT(minimum((*tree),(*tree)->root->l)->r == (*tree)->nil, "MinMax-03");
	
	ASSERT(maximum((*tree),(*tree)->root->l)->elem == 8l, "MinMax-04");
	ASSERT(maximum((*tree),(*tree)->root->l)->l == (*tree)->nil, "MinMax-05");
	ASSERT(maximum((*tree),(*tree)->root->l)->r == (*tree)->nil, "MinMax-06");
	printf(". ");

	passed("Minimum&Maximium", score);

	return 1;
}


int testSuccPred(BSTree* (*tree),  float score) { 						// test successor predecessor

	ASSERT(successor((*tree),maximum((*tree),(*tree)->root->l)) == NULL,"Successor-01");
	ASSERT(successor((*tree),search((*tree),6l))->elem == 7l,"Successor-02");
	ASSERT(successor((*tree),search((*tree),2l))->elem == 3l,"Successor-03");

	ASSERT(predecessor((*tree),minimum((*tree),(*tree)->root->l)) == NULL,"Predecesor-01")
	ASSERT(predecessor((*tree),search((*tree),5l))->elem == 4l,"Predecesor-02")
	ASSERT(predecessor((*tree),search((*tree),7l))->elem == 6l,"Predecesor-03")

	printf(". ");
	passed("Successor&Predecessor", score);

	return 1;
}

//int testDelete(BSTree **tree, float score) { 						// test delete
//
//
//	delete((*tree),5);
//	ASSERT((*tree)->root->l->elem == 6l, "Delete-01");
//
//	delete((*tree),7l);
//	ASSERT((*tree)->root->l->r->elem == 8l, "Delete-02");
//
//	delete((*tree),8l);
//	ASSERT((*tree)->root->l->r == (*tree)->nil, "Delete-03");
//
//	printf(". ");
//	passed2("Delete", score);
//
//	return 1;
//}


int testFree(BSTree **tree, float score) {
	destroyTree(*tree);
	printf(". Testul Destroy: *Se va verifica cu valgrind*\t\t Puncte: %.2f.\n", score);
	return 1;
}


typedef struct Test {
	int (*testFunction)(BSTree** tree, float);
	float score;
} Test;

int main(int argc, char* argv[]) {
	Test tests[] =                                    // Define the tests you want
	{
			{ &testInit, 0.05 },
			{ &testInsert, 0.1 },
			{ &testSearch, 0.1 },
			{ &testMinMax, 0.1 },
			{ &testSuccPred, 0.15 },
			{ &testFree, 0.1}
	};

	float totalScore = 0.0f, maxScore = 0.0f;
	long testsNo = sizeof(tests) / sizeof(Test);
	long testIdx;
	//  SortedList** testLists = (SortedList**) malloc(sizeof(SortedList*) * testsNo);
	BSTree* tree;

	for (testIdx = 0; testIdx < testsNo; testIdx++) {
		float score = tests[testIdx].score;
		if ((*(tests[testIdx].testFunction))(&tree, score)) {
			totalScore += score;
		}
		maxScore += score;
	}
	printf("\nScor total: %.2f / %.2f\n\n", totalScore, maxScore);

	return 0;
}
