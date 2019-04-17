#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeMap.h"

/* Lungimea maxima a unui buffer pentru citire */
#define BUFLEN 1024

/* Lungimea unui element din arbore de modele (fara terminator)*/
#define ELEMENT_TREE_LENGTH 3

/* Range of models*/
typedef struct Range{
	int *index; // Array of models in the range
	int size; // Number of array elements
	int capacity; // Array capacity
}Range;

void* createStrElement(void* str){
	char* elem = (char*)malloc(ELEMENT_TREE_LENGTH + 1);
	strncpy(elem, (char*)str, ELEMENT_TREE_LENGTH);
	elem[ELEMENT_TREE_LENGTH] = '\0';
	return elem;
}

void destroyStrElement(void* elem){
	free((char*)elem);
}


void* createPriceElement(void* price){
	long *p = (long*) malloc(sizeof(long));
	*p = *((long*) price);
	return p;
}

void destroyPriceElement(void* price){
	free(price);
}

void* createIndexInfo(void* index){
	int *idx = (int*) malloc(sizeof(int));
	*idx = *((int*) index);
	return idx;
}

void destroyIndexInfo(void* index){
	free(index);
}

int compareStr(void* str1, void* str2){
	if(strncmp((char*)str1,(char*)str2,ELEMENT_TREE_LENGTH) > 0)
		return 1;
	else if(strncmp((char*) str1,(char*) str2, ELEMENT_TREE_LENGTH) < 0)
		return -1;
	return 0;
}

int comparePrice(void* price1, void* price2){
	if(*((int*) price1) > *((int*) price2))
		return 1;
	else if(*((int*) price1) < *((int*) price2))
		return -1;
	return 0;
}

void printFile(char* fileName){
	printf("---------\n");
	if(fileName == NULL) return;
	FILE * file = fopen(fileName,"r");
	if (file == NULL)
		return;

	char *buf = (char*) malloc(BUFLEN+1);
	while(fgets(buf,BUFLEN,file) != NULL){
		buf[strlen(buf) - 1] = '\0';
		printf("%s",buf);
	}
	printf("\n");
	printf("---------\n");
	free(buf);
	fclose(file);
}

void inorderModelTreePrint(TreeNode* node){
	if(node != NULL){
		inorderModelTreePrint(node->lt);
		TreeNode* begin = node;
		TreeNode* end = node->end->next;
		while(begin != end){
			printf("%d:%s  ",*((int*)begin->info),(char*)begin->elem);
			begin = begin->next;
		}
		inorderModelTreePrint(node->rt);
	}
}

void inorderPriceTreePrint(TreeNode* node){
	if(node != NULL){
		inorderPriceTreePrint(node->lt);
		TreeNode* begin = node;
		TreeNode* end = node->end->next;
		while(begin != end){
			printf("%d:%ld  ",*((int*)begin->info),*((long*)begin->elem));
			begin = begin->next;
		}
		inorderPriceTreePrint(node->rt);
	}
}

void printRange(Range* range, char* fileName){
	if(fileName == NULL) return;
	FILE * file = fopen(fileName,"r");
	if (file == NULL) return;

	char *buf = (char*) malloc(BUFLEN+1);

	for(int i = 0; i < range->size;i++){
		fseek(file,range->index[i],SEEK_SET);
		if(fgets(buf,BUFLEN,file) != NULL){
			char* model = strtok(buf,",");
			long price = atol(strtok(NULL,","));
			printf("%s:%ld  ", model, price);
		}
	}
	printf("\n");
	free(buf);
	fclose(file);
}

//-------TODO: Cerinta 2: You can use auxilary functions where needed----------
void buildTreesFromFile(char* fileName, TTree* modelTree, TTree* priceTree){
	// TODO: Cerinta 2a
}


Range* modelGroupQuery(TTree* tree, char* q){
	// TODO: Cerinta 2b
	
	return NULL;
}

Range* priceRangeQuery(TTree* tree, long q, long p){
	// TODO: Cerinta 2c
	
	return NULL;
}

Range* modelRangeQuery(TTree* tree, char* q, char* p){
	// TODO: Cerinta 2d
	
	return NULL;
}



long getModelPrice(FILE* file, int index){
	long price = -1;
	char buf[BUFLEN+1];
	fseek(file, index, SEEK_SET);
	if(fgets(buf,BUFLEN,file) != NULL){
		strtok(buf, ",\n");
		price = atol(strtok(NULL,",\n"));
	}
	return price;
}



Range* modelPriceRangeQuery(char* fileName, TTree* tree, char* m1, char* m2, long p1, long p2){
	// TODO: Cerinta 2e

	return NULL;
}

int main(void) {

	TTree* modelTree = createTree(createStrElement, destroyStrElement,
	 createIndexInfo, destroyIndexInfo, compareStr);
	if(modelTree == NULL) goto NullPointerException;

	TTree* priceTree = createTree(createPriceElement, destroyPriceElement, 
		createIndexInfo, destroyIndexInfo, comparePrice);
	if(priceTree == NULL) goto NullPointerException;

	buildTreesFromFile("input.csv", modelTree, priceTree);
	if(isEmpty(modelTree) || isEmpty(priceTree)) goto EmptyTreeException;

	printf("Model Tree In Order:\n");
	inorderModelTreePrint(modelTree->root);
	printf("\n\n");

	printf("Price Tree In Order:\n");
	inorderPriceTreePrint(priceTree->root);
	printf("\n\n");

	printf("Group Model Search:\n");
	Range *range = modelGroupQuery(modelTree,"MG3");
	if(range == NULL) goto NullPointerException;
	printRange(range,"input.csv");
	printf("\n\n");

	printf("Price Range Search:\n");
	Range *range2 = priceRangeQuery(priceTree,100,400);
	if(range2 == NULL) goto NullPointerException;
	printRange(range2,"input.csv");
	printf("\n\n");

	printf("Model Range Search:\n");
	Range *range3 = modelRangeQuery(modelTree,"L2","M");
	if(range3 == NULL) goto NullPointerException;
	printRange(range3,"input.csv");
	printf("\n\n");

	printf("Model Price Range Search:\n");
	Range *range4 = modelPriceRangeQuery("input.csv",modelTree,"L2","M", 300, 600);
	if(range4 == NULL) goto NullPointerException;
	printRange(range4,"input.csv");


	// TODO: DO NOT FORGET TO DE-ALLOCATE EVERYTHING

	return 0;

NullPointerException:
	printf("NULL pointer exception!\n");
	return -1;

EmptyTreeException:
	printf("Emtpty tree exception!\n");
	return -2;
}
