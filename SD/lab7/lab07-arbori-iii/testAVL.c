#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long* Item;
typedef int Info;
#include "AVLTree.h"

// -----------------------------------------------------------------------------

#define ASSERT(cond, msg) if (!(cond)) { failed(msg); return 0; }


void passed2(char* s) {
	printf("Testul %s a fost trecut cu succes!\t\t \n", s);
}

void failed(char* s) {
	printf("Testul %s NU a fost trecut!\n", s);
}

int compare(Item a, Item b){
	if(a == NULL || b == NULL) return -2;
	if( (*a) > (*b)) return 1;
	if( (*a) < (*b)) return -1;
	return 0;
}

Item allocElem(long elem){
	Item heapElem =  (Item)malloc(sizeof(long));
	*heapElem = elem;
	return heapElem;
}

void destroyElem(Item elem){
	free(elem);
}


int abs(int value){
	return (value >= 0)?value:-value;
}

int checkBalance(AVLTree* tree, AVLNode* x){
	// The tree null is balanced
	if (x == tree->nil)
		return 1;

	// check if left sub-tree is balanced
	int leftSubtreeHeight = checkBalance(tree,x->l);
	if (leftSubtreeHeight == -1) return 0;

	// check if right sub-tree is balanced
	int rightSubtreeHeight = checkBalance(tree,x->r);
	if (rightSubtreeHeight == -1) return 0;

	// if both sub-trees are balanced, check the difference of heights
	// should be less than or equal to 1
	if (abs(leftSubtreeHeight - rightSubtreeHeight) > 1)
		return 0;


	// if tree rooted at this node is balanced, return height if tree rooted at this this node
	return (max(leftSubtreeHeight, rightSubtreeHeight) + 1);
}

int isBalanced(AVLTree* tree, AVLNode* x){
	return (checkBalance(tree, x) != 0);
}

// -----------------------------------------------------------------------------

int testInit(AVLTree** tree) {                   // tests init


	(*tree) = avlCreateTree();
	ASSERT((*tree)->root != NULL, "Init-01");
	ASSERT((*tree)->nil != NULL, "Init-02");
	ASSERT((*tree)->root->l == (*tree)->nil, "Init-03");
	ASSERT((*tree)->root->r == (*tree)->nil, "Init-04");
	ASSERT(((*tree)->nil->l == (*tree)->nil), "Init-05");
	ASSERT(((*tree)->nil->r == (*tree)->nil), "Init-06");
	ASSERT(avlIsEmpty((*tree)) == 1, "IsEmpty-01");
	printf(". ");

	passed2("Init&IsEmpty");
	return 1;
}

int testInsert(AVLTree** tree) {                   // tests insert

	avlInsert(*(tree),allocElem(5l));
	ASSERT(avlIsEmpty(*tree) != 1, "Insert-01");
	ASSERT((*tree)->root->l->l == (*tree)->nil, "Insert-02");
	ASSERT((*tree)->root->l->r == (*tree)->nil, "Insert-03");

	avlInsert((*tree), allocElem(3l));
	avlInsert((*tree),  allocElem(2l));
	ASSERT(*((*tree)->root->l->l->elem) == 2l, "Insert-04");
	ASSERT(*((*tree)->root->l->r->elem) == 5l, "Insert-05");

	avlInsert((*tree), allocElem(4l));
	avlInsert((*tree), allocElem(7l));
	avlInsert((*tree), allocElem(6l));
	avlInsert((*tree), allocElem(8l));
	ASSERT(*((*tree)->root->l->r->elem) == 7l,"Insert-06");
	ASSERT(*((*tree)->root->l->r->l->elem) == 6l,"Insert-07");
	ASSERT(*((*tree)->root->l->r->r->elem) == 8l,"Insert-08");

	printf(". ");

	passed2("Insert");
	return 1;
}




int testFree(AVLTree **tree) {
	avlDestroyTree(*tree);
	printf(". ");

	passed2("Free");
	return 1;
}


typedef struct Test {
	int (*testFunction)(AVLTree** tree);
} Test;

int main(int argc, char* argv[]) {
	Test tests[] =                                    // Define the tests you want
	{
            { &testInit, 0.00 },
			{ &testInsert, 0.2 },
			{ &testFree, 0.05}
	};


	long testsNo = sizeof(tests) / sizeof(Test);
	long testIdx;
	AVLTree* tree;
	for (testIdx = 0; testIdx < testsNo; testIdx++) {
		if ((*(tests[testIdx].testFunction))(&tree)); {
		}

	}



	return 0;
}
