typedef long Item; // Valorile din BST
#include "BST.h"
#include "List.h"

typedef BSTNode* Item2; // Elementele cozii sunt noduri din arbore
#include "Queue.h"


BSTree* buildTree(Item *array, long len);

// -----------------------------------------------------------------------------
List* bstToList(BSTree* tree){ 
	//TODO: Cerinta 3
	return NULL;
}
void printList(List* list){
	//TODO: Cerinta 3
}
// -----------------------------------------------------------------------------

int main(void){
	Item array[] = {5,3,2,4,7,6,8};

	BSTree *tree = buildTree(array, sizeof(array)/sizeof(Item));	

	printList(bstToList(tree));

	destroyTree(tree);

	return 0;
}

BSTree* buildTree(Item *array, long len){
	BSTree* newTree = createTree();
	for(int i = 0; i < len; i++){
		insert(newTree,array[i]);
	}
	return newTree;
}
