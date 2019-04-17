#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeMap.h"

void* createLong(void* value){
	long *l = malloc(sizeof(long));
	*l = *((long*) (value));
	return l;
}

void destroyLong(void* value){
	free((long*)value);
}

int compareLong(void* a, void* b){
	if(*((long*)a) < *((long*)b))
		return -1;
	if(*((long*)a) > *((long*)b))
		return 1;
	return 0;
}

// -----------------------------------------------------------------------------

#define ASSERT(cond, msg) if (!(cond)) { failed(msg); return 0; }

void passed(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t Puncte: %.3f\n", s, score);
}

void passed2(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t\t Puncte: %.3f\n", s, score);
}

void passed3(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t\t\t Puncte: %.3f\n", s, score);
}

void failed(char* s) {
	printf("Testul %s NU a fost trecut!\n", s);
}

// -----------------------------------------------------------------------------

int testInit(TTree** tree,  float score) {                   // tests init


	(*tree) = createTree(createLong, destroyLong,
			createLong, destroyLong,
			compareLong);

	ASSERT((*tree) != NULL, "Init-01");
	ASSERT((*tree)->createElement != NULL, "Init-02");
	ASSERT((*tree)->createInfo != NULL, "Init-03");
	ASSERT((*tree)->destroyElement != NULL, "Init-04");
	ASSERT((*tree)->destroyInfo != NULL, "Init-05");
	ASSERT((*tree)->compare != NULL, "Init-06");
	ASSERT((*tree)->root == NULL, "Init-07");
	ASSERT((*tree)->size == 0, "Init-09");
	ASSERT(isEmpty((*tree)) == 1, "IsEmpty-01");
	printf(". ");

	passed("Create&IsEmpty", score);
	return 1;
}

int testInsert(TTree** tree,  float score) {                   // tests insert

	long values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

	// Test root
	insert(*(tree),values + 2, values + 2);
	ASSERT(isEmpty(*tree) != 1, "Insert-01");
	ASSERT((*tree)->root->lt == NULL, "Insert-02");
	ASSERT((*tree)->root->rt == NULL, "Insert-03");

	// Test Left Rotate
	insert((*tree), values+3, values+3);
	insert((*tree), values + 4, values + 4);
	ASSERT(*((long*)(*tree)->root->lt->elem) == 2l, "Insert-04");
	ASSERT(*((long*)(*tree)->root->rt->elem) == 4l, "Insert-05");

	// Test Right Rotate
	insert((*tree),values + 1, values+1);
	insert((*tree),values, values);
	ASSERT(*((long*)(*tree)->root->lt->elem) == 1l, "Insert-06");
	ASSERT(*((long*)(*tree)->root->lt->lt->elem) == 0l, "Insert-07");
	ASSERT(*((long*)(*tree)->root->lt->rt->elem) == 2l, "Insert-08");


	// Test Left Rotate
	insert((*tree),values + 5, values + 5);
	insert((*tree),values + 6, values + 6);
	ASSERT(*((long*)(*tree)->root->rt->elem) == 5l,"Insert-09");
	ASSERT(*((long*)(*tree)->root->rt->lt->elem) == 4l,"Insert-10");
	ASSERT(*((long*)(*tree)->root->rt->rt->elem) == 6l,"Insert-11");


	// Test Zig-Zag case
	insert((*tree),values + 8, values + 8);
	insert((*tree),values + 7, values + 7);
	ASSERT(*((long*)(*tree)->root->rt->rt->elem) == 7l,"Insert-09");
	ASSERT(*((long*)(*tree)->root->rt->rt->lt->elem) == 6l,"Insert-10");
	ASSERT(*((long*)(*tree)->root->rt->rt->rt->elem) == 8l,"Insert-11");


	printf(". ");

	passed2("Insert-Tree", score);

	return 1;
}

int testSearch(TTree** tree, float score) {                   // tests contains
	long value = 4;
	ASSERT((search((*tree), (*tree)->root, &value) != NULL) == 1,"Search-01");

	value = 10;
	ASSERT((search((*tree), (*tree)->root,&value) != NULL) == 0,"Search-02");

	value = 0;
	ASSERT(search((*tree), (*tree)->root,&value) != NULL,"Search-03");

	value = 3;
	ASSERT(search((*tree), (*tree)->root,&value)->lt == (*tree)->root->lt,"Search-04");
	ASSERT(search((*tree), (*tree)->root,&value)->rt == (*tree)->root->rt,"Search-05");
	printf(". ");

	passed2("Search", score);

	return 1;
}

int testMinMax(TTree* (*tree),  float score) { // test min max

	ASSERT(*((long*)minimum((*tree)->root)->elem) == 0l, "MinMax-01");
	ASSERT(minimum((*tree)->root)->lt == NULL, "MinMax-02");
	ASSERT(*((long*)minimum((*tree)->root->rt)->elem) == 4l, "MinMax-03");

	ASSERT(*((long*)maximum((*tree)->root)->elem) == 8l, "MinMax-04");
	ASSERT(maximum((*tree)->root)->rt == NULL, "MinMax-05");
	ASSERT(*((long*)maximum((*tree)->root->lt)->elem) == 2l, "MinMax-03");
	printf(". ");

	passed("Minimum&Maximium", score);

	return 1;
}


int testSuccPred(TTree* (*tree),  float score) { 						// test successor predecessor

	long value;
	ASSERT(successor(maximum((*tree)->root)) == NULL,"Successor-01");

	value = 6;
	ASSERT(*((long*)successor(search((*tree),(*tree)->root,&value))->elem) == 7l,"Successor-02");

	value = 2;
	ASSERT(*((long*)successor(search((*tree),(*tree)->root,&value))->elem) == 3l,"Successor-03");


	// ASSERT(predecessor(minimum((*tree)->root) == NULL,"Predecesor-01");

	value = 5;
	ASSERT(*((long*)predecessor(search((*tree), (*tree)->root,&value))->elem) == 4l,"Predecesor-02")

	value = 7;
	ASSERT(*((long*)predecessor(search((*tree), (*tree)->root,&value))->elem) == 6l,"Predecesor-03")

	printf(". ");
	passed("Successor&Predecessor", score);

	return 1;
}

int testDelete(TTree **tree, float score) { 						// test delete

	// Test single node delete no child
	long value = 6;
	delete((*tree),&value);
	ASSERT(*((long*)(*tree)->root->elem) == 3l, "Delete-01");
	ASSERT((*tree)->root->rt->rt->lt == NULL, "Delete-02");

	// Test left re-balance
	value = 4;
	delete((*tree),&value);
	ASSERT(*((long*)(*tree)->root->rt->elem) == 7l, "Delete-03");
	ASSERT(*((long*)(*tree)->root->rt->lt->elem) == 5l, "Delete-04");
	ASSERT(*((long*)(*tree)->root->rt->rt->elem) == 8l, "Delete-05");

	// Test splice successor
	value = 3;
	delete((*tree),&value);
	ASSERT(*((long*)(*tree)->root->elem) == 5l, "Delete-06");
	ASSERT(*((long*)(*tree)->root->rt->elem) == 7l, "Delete-07");
	ASSERT(*((long*)(*tree)->root->rt->rt->elem) == 8l, "Delete-08");
	ASSERT((*tree)->root->rt->lt == NULL, "Delete-09");

	// Test delete node with 1 child
	value = 7;
	delete((*tree),&value);
	ASSERT(*((long*)(*tree)->root->rt->elem) == 8l, "Delete-10");
	ASSERT((*tree)->root->rt->height == 1, "Delete-11");

	// Test right re-balance
	value = 8;
	delete((*tree),&value);
	ASSERT(*((long*)(*tree)->root->elem) == 1l, "Delete-12");
	ASSERT(*((long*)(*tree)->root->lt->elem) == 0l, "Delete-13");
	ASSERT(*((long*)(*tree)->root->rt->elem) == 5l, "Delete-14");
	ASSERT(*((long*)(*tree)->root->rt->lt->elem) == 2l, "Delete-15");

	//Test zig-zag re-balance
	value = 0;
	delete((*tree),&value);
	ASSERT(*((long*)(*tree)->root->elem) == 2l, "Delete-16");
	ASSERT(*((long*)(*tree)->root->lt->elem) == 1l, "Delete-17");
	ASSERT(*((long*)(*tree)->root->rt->elem) == 5l, "Delete-18");


	// Test empty tree
	value = 2;
	delete((*tree),&value);
	value = 1;
	delete((*tree),&value);
	value = 5;
	delete((*tree),&value);
	ASSERT((*tree)->root == NULL, "Delete-19");
	ASSERT((*tree)->size == 0, "Delete-20");


	printf(". ");
	passed2("Delete-Tree", score);

	return 1;
}

int testTreeListInsert(TTree **tree, float score) {

	long values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	for(int i = 0; i < sizeof(values)/sizeof(values[0]); i++)
		insert(*(tree),values + i, values + i);

	ASSERT(minimum((*tree)->root)->prev == NULL, "InsertList-01");
	ASSERT(maximum((*tree)->root)->end->next == NULL, "InsertList-02");
	ASSERT(*((long*)(*tree)->root->elem) == 3, "InsertList-03");
	ASSERT((*tree)->root == (*tree)->root->end, "InsertList-04");
	ASSERT((*tree)->root->prev == predecessor((*tree)->root), "InsertList-05");
	ASSERT((*tree)->root->next == successor((*tree)->root), "InsertList-06");

	insert(*(tree),values + 3, values + 3);
	ASSERT((*tree)->root != (*tree)->root->end, "InsertList-07");
	ASSERT((*tree)->root->next == (*tree)->root->end, "InsertList-08");
	ASSERT((*tree)->root->prev == predecessor((*tree)->root), "InsertList-09");
	ASSERT((*tree)->root->end->next == successor((*tree)->root), "InsertList-10");

	insert(*(tree),values + 3, values + 3);
	ASSERT(*((long*)(*tree)->root->elem) == *((long*)(*tree)->root->next->elem), "InsertList-11");
	ASSERT(*((long*)(*tree)->root->elem) == *((long*)(*tree)->root->next->next->elem), "InsertList-12");
	ASSERT((*tree)->root->end == (*tree)->root->next->next, "InsertList-13");
	ASSERT((*tree)->root->next->next == successor((*tree)->root)->prev, "InsertList-14");
	ASSERT((*tree)->root == predecessor((*tree)->root)->next, "InsertList-15");

	insert(*(tree),values, values);
	ASSERT( *((long*)minimum((*tree)->root)->elem) == 0 , "InsertList-16");
	ASSERT( *((long*)minimum((*tree)->root)->next->elem) == 0 , "InsertList-17");
	ASSERT( *((long*)minimum((*tree)->root)->end->next->elem) == 1 , "InsertList-18");
	ASSERT(minimum((*tree)->root)->prev == NULL , "InsertList-19");
	ASSERT(minimum((*tree)->root)->prev == NULL , "InsertList-20");
	ASSERT(minimum((*tree)->root)->next->next == minimum((*tree)->root)->end->next , "InsertList-21");


	insert(*(tree),values + 8, values + 8);
	ASSERT( *((long*)maximum((*tree)->root)->elem) == 8, "InsertList-22");
	ASSERT( *((long*)maximum((*tree)->root)->next->elem) == 8, "InsertList-23");
	ASSERT( *((long*)maximum((*tree)->root)->prev->elem) == 7l, "InsertList-24");
	ASSERT(maximum((*tree)->root)->end->next == NULL , "InsertList-25");
	ASSERT(maximum((*tree)->root)->next->next == NULL , "InsertList-26");
	ASSERT(maximum((*tree)->root)->next->next == maximum((*tree)->root)->end->next , "InsertList-27");

	printf(". ");
	passed("Tree-List-Insert", score);
	return 1;
}


int testTreeListDelete(TTree **tree, float score) {
	long value = 3;
	delete((*tree),&value);
	ASSERT(*((long*)(*tree)->root->elem) == 3l, "DeleteList-01");
	ASSERT(*((long*)(*tree)->root->next->elem) == 3l, "DeleteList-02");
	ASSERT(*((long*)(*tree)->root->end->elem) == 3l, "DeleteList-03");
	ASSERT((*tree)->root->end->elem == (*tree)->root->next->elem, "DeleteList-03");
	ASSERT(*((long*)(*tree)->root->end->next->elem) == 4l, "DeleteList-04");
	ASSERT(*((long*)(*tree)->root->prev->elem) == 2l, "DeleteList-05");

	delete((*tree),&value);
	ASSERT(*((long*)(*tree)->root->elem) == 3l, "DeleteList-06");
	ASSERT(*((long*)(*tree)->root->next->elem) == 4l, "DeleteList-07");
	ASSERT(*((long*)(*tree)->root->end->elem) == 3l, "DeleteList-08");
	ASSERT((*tree)->root->end->next == (*tree)->root->next, "DeleteList-09");
	ASSERT(*((long*)(*tree)->root->end->next->elem) == 4l, "DeleteList-10");
	ASSERT(*((long*)(*tree)->root->prev->elem) == 2l, "DeleteList-11");

	delete((*tree),&value);
	ASSERT(*((long*)(*tree)->root->elem) == 4l, "DeleteList-12");
	ASSERT(*((long*)(*tree)->root->next->elem) == 5l, "DeleteList-13");
	ASSERT(*((long*)(*tree)->root->end->elem) == 4l, "DeleteList-14");
	ASSERT((*tree)->root->end->next == (*tree)->root->next, "DeleteList-15");
	ASSERT(*((long*)(*tree)->root->end->next->elem) == 5l, "DeleteList-16");
	ASSERT(*((long*)(*tree)->root->prev->elem) == 2l, "DeleteList-17");

	value = 4;
	delete((*tree),&value);
	ASSERT(*((long*)(*tree)->root->elem) == 5l, "DeleteList-18");
	ASSERT(*((long*)(*tree)->root->next->elem) == 6l, "DeleteList-19");
	ASSERT(*((long*)(*tree)->root->end->elem) == 5l, "DeleteList-20");
	ASSERT((*tree)->root->end->next == (*tree)->root->next, "DeleteList-21");
	ASSERT(*((long*)(*tree)->root->end->next->elem) == 6l, "DeleteList-22");
	ASSERT(*((long*)(*tree)->root->prev->elem) == 2l, "DeleteList-23");

	value = 8;
	delete((*tree),&value);
	ASSERT(*((long*)maximum((*tree)->root)->elem) == 8, "DeleteList-24");
	ASSERT(*((long*)maximum((*tree)->root)->end->elem) == 8, "DeleteList-25");
	ASSERT(*((long*)maximum((*tree)->root)->prev->elem) == 7l, "DeleteList-26");
	ASSERT(maximum((*tree)->root)->end->next == NULL , "DeleteList-27");
	ASSERT(maximum((*tree)->root)->next == NULL , "DeleteList-28");


	delete((*tree),&value);
	ASSERT(*((long*)maximum((*tree)->root)->elem) == 7, "DeleteList-29");
	ASSERT(*((long*)maximum((*tree)->root)->end->elem) == 7, "DeleteList-30");
	ASSERT(*((long*)maximum((*tree)->root)->prev->elem) == 6l, "DeleteList-31");
	ASSERT(maximum((*tree)->root)->end->next == NULL , "DeleteList-32");
	ASSERT(maximum((*tree)->root)->next == NULL , "DeleteList-33");


	value = 0;
	delete((*tree),&value);
	ASSERT(*((long*)minimum((*tree)->root)->elem) == 0, "DeleteList-34");
	ASSERT(*((long*)minimum((*tree)->root)->end->elem) == 0, "DeleteList-35");
	ASSERT(*((long*)minimum((*tree)->root)->next->elem) == 1l, "DeleteList-36");
	ASSERT(minimum((*tree)->root)->prev == NULL , "DeleteList-37");


	delete((*tree),&value);
	ASSERT(*((long*)minimum((*tree)->root)->elem) == 1, "DeleteList-38");
	ASSERT(*((long*)minimum((*tree)->root)->end->elem) == 1, "DeleteList-39");
	ASSERT(*((long*)minimum((*tree)->root)->next->elem) == 2l, "DeleteList-40");
	ASSERT(minimum((*tree)->root)->prev == NULL , "DeleteList-41");



	printf(". ");
	passed("Tree-List-Delete", score);
	return 1;
}

int testFree(TTree **tree, float score) {
	destroyTree(*tree);
	printf(". Testul Destroy: *Se va verifica cu valgrind*\t\t Puncte: %.3f\n", score);
	*tree = NULL;
	return 1;
}

typedef struct Test {
	int (*testFunction)(TTree** tree, float);
	float score;
} Test;

int main(int argc, char* argv[]) {
	Test tests[] =                                    // Define the tests you want
	{
			{ &testInit, 0.05 },
			{ &testInsert, 0.1 },
			{ &testSearch, 0.05 },
			{ &testMinMax, 0.05 },
			{ &testSuccPred, 0.05 },
			{ &testDelete, 0.1 },
			{ &testTreeListInsert, 0.15},
			{ &testTreeListDelete, 0.15},
			{ &testFree, 0.1 },
	};

	float totalScore = 0.0f, maxScore = 0.0f;
	long testsNo = sizeof(tests) / sizeof(Test);
	long testIdx;
	TTree* tree;

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
