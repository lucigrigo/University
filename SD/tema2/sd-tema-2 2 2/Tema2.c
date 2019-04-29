#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeMap.h"

/* Lungimea maxima a unui buffer pentru citire */
#define BUFLEN 1024

/* Lungimea unui element din arbore de modele (fara terminator)*/
#define ELEMENT_TREE_LENGTH 3

/* Range of models*/
typedef struct Range
{
	int *index;   // Array of models in the range
	int size;	 // Number of array elements
	int capacity; // Array capacity
} Range;

void *createStrElement(void *str)
{
	char *elem = (char *)malloc(ELEMENT_TREE_LENGTH + 1);
	strncpy(elem, (char *)str, ELEMENT_TREE_LENGTH);
	elem[ELEMENT_TREE_LENGTH] = '\0';
	return elem;
}

void destroyStrElement(void *elem)
{
	free((char *)elem);
}

void *createPriceElement(void *price)
{
	long *p = (long *)malloc(sizeof(long));
	*p = *((long *)price);
	return p;
}

void destroyPriceElement(void *price)
{
	free(price);
}

void *createIndexInfo(void *index)
{
	int *idx = (int *)malloc(sizeof(int));
	*idx = *((int *)index);
	return idx;
}

void destroyIndexInfo(void *index)
{
	free(index);
}

int compareStr(void *str1, void *str2)
{
	if (strncmp((char *)str1, (char *)str2, ELEMENT_TREE_LENGTH) > 0)
		return 1;
	else if (strncmp((char *)str1, (char *)str2, ELEMENT_TREE_LENGTH) < 0)
		return -1;
	return 0;
}

int comparePrice(void *price1, void *price2)
{
	if (*((int *)price1) > *((int *)price2))
		return 1;
	else if (*((int *)price1) < *((int *)price2))
		return -1;
	return 0;
}

void printFile(char *fileName)
{
	printf("---------\n");
	if (fileName == NULL)
		return;
	FILE *file = fopen(fileName, "r");
	if (file == NULL)
		return;

	char *buf = (char *)malloc(BUFLEN + 1);
	while (fgets(buf, BUFLEN, file) != NULL)
	{
		buf[strlen(buf) - 1] = '\0';
		printf("%s", buf);
	}
	printf("\n");
	printf("---------\n");
	free(buf);
	fclose(file);
}

void inorderModelTreePrint(TreeNode *node)
{
	if (node != NULL)
	{
		inorderModelTreePrint(node->lt);
		TreeNode *begin = node;
		TreeNode *end = node->end->next;
		while (begin != end)
		{
			printf("%d:%s  ", *((int *)begin->info), (char *)begin->elem);
			begin = begin->next;
		}
		inorderModelTreePrint(node->rt);
	}
}

void inorderPriceTreePrint(TreeNode *node)
{
	if (node != NULL)
	{
		inorderPriceTreePrint(node->lt);
		TreeNode *begin = node;
		TreeNode *end = node->end->next;
		while (begin != end)
		{
			printf("%d:%ld  ", *((int *)begin->info), *((long *)begin->elem));
			begin = begin->next;
		}
		inorderPriceTreePrint(node->rt);
	}
}

long getModelPrice(FILE *file, int index)
{
	long price = -1;
	char buf[BUFLEN + 1];
	fseek(file, index, SEEK_SET);
	if (fgets(buf, BUFLEN, file) != NULL)
	{
		strtok(buf, ",\n");
		price = atol(strtok(NULL, ",\n"));
	}
	return price;
}

void printRange(Range *range, char *fileName)
{
	if (fileName == NULL)
		return;
	FILE *file = fopen(fileName, "r");
	if (file == NULL)
		return;

	char *buf = (char *)malloc(BUFLEN + 1);

	for (int i = 0; i < range->size; i++)
	{
		fseek(file, range->index[i], SEEK_SET);
		if (fgets(buf, BUFLEN, file) != NULL)
		{
			char *model = strtok(buf, ",");
			long price = atol(strtok(NULL, ","));
			printf("%s:%ld  ", model, price);
		}
	}
	printf("\n");
	free(buf);
	fclose(file);
}

// Functia care realizeaza citirea din fisierul de input si crearea 
// celor doi arbori
void buildTreesFromFile(char *fileName, TTree *modelTree, TTree *priceTree)
{
	// deschiderea fisierului de input
	FILE *ffile = fopen(fileName, "r");
	if (ffile == NULL)
		exit(1);
	char line[BUFLEN], *delim = ",";
	// citirea fiecarei linii din fisier
	while (fgets(line, BUFLEN, ffile) != NULL)
	{
		// stabilirea indexului
		int index = ftell(ffile) - strlen(line);
		char *linePtr = NULL;
		// impartirea liniei citite dupa ','
		linePtr = (char *)strtok(line, delim);
		// inserarea in arborele cu numele modelelor
		insert(modelTree, (void *)linePtr, (void *)(&index));
		linePtr = (char *)strtok(NULL, delim);
		long modelPrice = (long)atoi(linePtr);
		// inserarea in arborele cu pretul modelelor
		insert(priceTree, (void *)(&modelPrice), (void *)(&index));
	}
	// inchiderea fisierului de input
	fclose(ffile);
}

// Functia care realizeaza cautarea dupa un anumit nume a modelelor
Range *modelGroupQuery(TTree *tree, char *q)
{
	// initializarea elementului de tip Range cu o capacitate initiala
	// de 10 elemente
	Range *range = (Range *)malloc(sizeof(Range));
	range->index = (int *)malloc(10 * sizeof(int));
	if(range->index == NULL) exit(1);
	range->capacity = 10;
	range->size = 0;
	// inceperea parcurgerii de la primul element din lista
	// adica cel mai mic nod din arbore
	TreeNode *nodePtr = minimum(tree->root);
	while (nodePtr != NULL)
	{
		// verificarea daca numele elementului actual se potriveste cautarii
		if (strncmp((char *)nodePtr->elem, q, strlen(q)) == 0)
		{
			// cazul in care nu mai este loc liber in vectorul de indecsi
			if (range->size == range->capacity)
			{
				int *temp = realloc(range->index, 2 * range->capacity);
				if (!temp)
				{
					printf("error at realloc!");
					exit(1);
				}
				else
				{
					range->index = temp;
				}
				range->capacity = range->capacity * 2;
			}
			// adaugarea indexului elementului gasit in vectorul de indecsi		
			range->index[range->size] = *(int *)(nodePtr->info);
			range->size = range->size + 1;
		}
		nodePtr = nodePtr->next;
	}
	return range;
}

// Functia care realizeaza cautarea intr-un interval de pret a produselor
Range *priceRangeQuery(TTree *tree, long q, long p)
{
	// initializarea elementului de tip Range cu o capacitate initiala
	// de 10 elemente 
	Range *range = (Range *)malloc(sizeof(Range));
	range->index = (int *)malloc(10 * sizeof(int));
	range->capacity = 10;
	range->size = 0;
	// incepe cautarea de la primul element din lista
	TreeNode *nodePtr = minimum(tree->root);
	while (nodePtr != NULL)
	{
		// verificarea daca pretul elementului curent se incadreaza
		// in intervalul specificat
		if ((tree->compare(nodePtr->elem, (void *)(&q)) >= 0) &&
			(tree->compare(nodePtr->elem, (void *)(&p)) <= 0))
		{
			// cazul in care nu mai e loc in vectorul de indecsi
			if (range->size == range->capacity)
			{
				int *temp = realloc(range->index, 2 * range->capacity);
				if (!temp)
				{
					printf("error at realloc!");
					exit(1);
				}
				else
				{
					range->index = temp;
				}
				range->capacity = range->capacity * 2;
			}
			// adaugarea indexului elementului gasit in vectorul de indecsi
			range->index[range->size] = *(int *)nodePtr->info;
			range->size = range->size + 1;
		}
		nodePtr = nodePtr->next;
	}
	return range;
}

// Functia realizeaza cautarea produselor intr-un range de nume
Range *modelRangeQuery(TTree *tree, char *q, char *p)
{
	// initializarea elementului de tip Range cu o capacitate initiala
	// de 10 elemente
	Range *range = (Range *)malloc(sizeof(Range));
	range->index = (int *)malloc(10 * sizeof(int));
	range->capacity = 10;
	range->size = 0;
	// inceperea cautarii de la primul element din lista
	TreeNode *nodePtr = minimum(tree->root);
	while (nodePtr != NULL)
	{
		// compararea numelui produsului curent cu intervalul specificat
		if ((strncmp((char *)nodePtr->elem, q, strlen(q)) >= 0) &&
			(strncmp((char *)nodePtr->elem, p, strlen(p)) <= 0))
		{
			// cazul in care nu mai e loc in vectorul de indecsi
			if (range->size == range->capacity)
			{
				int *temp = realloc(range->index, 2 * range->capacity);
				if (!temp)
				{
					printf("error at realloc!");
					exit(1);
				}
				else
				{
					range->index = temp;
				}
				range->capacity = range->capacity * 2;
			}
			// adaugarea indexului elementului gasit in vectorul de indecsi
			range->index[range->size] = *(int *)nodePtr->info;
			range->size = range->size + 1;
		}
		nodePtr = nodePtr->next;
	}
	return range;
}

// Functia realizeaza cautarea produselor atat intr-un range de nume, 
// cat si intr-un interval de preturi
Range *modelPriceRangeQuery(char *fileName, TTree *tree, char *m1, char *m2, long p1, long p2)
{
	// initializarea elementului de tip Range cu o capacitate initiala
	// de 10 elemente
	Range *range = (Range *)malloc(sizeof(Range));
	range->index = (int *)malloc(10 * sizeof(int));
	range->capacity = 10;
	range->size = 0;
	// inceperea cautarii de la primul element din lista
	TreeNode *nodePtr = minimum(tree->root);
	// deschiderea fisierului cu date pentru gasirea pretului unui element
	FILE *ffile = fopen(fileName, "r");
	while (nodePtr != NULL)
	{
		// verificarea daca numele se incadreaza in range-ul specificat
		if ((strncmp((char *)nodePtr->elem, m1, strlen(m1)) >= 0) &&
			(strncmp((char *)nodePtr->elem, m2, strlen(m2)) <= 0))
		{
			long modelPrice = getModelPrice(ffile, *(int *)(nodePtr->info));
			// verificarea daca pretul se afla in intervalul specificat
			if (modelPrice >= p1 && modelPrice <= p2)
			{
				// cazul in care nu mai e loc in vectorul de indecsi
				if (range->size == (range->capacity - 1))
				{
					int *temp = realloc(range->index, 2 * range->capacity);
					if (!temp)
					{
						printf("error at realloc!");
						exit(1);
					}
					else
					{
						range->index = temp;
					}
					range->capacity = range->capacity * 2;
				}
				// adaugarea indexului elementului gasit in vectorul de indecsi
				range->index[range->size] = *(int *)nodePtr->info;
				range->size = range->size + 1;
			}
		}
		nodePtr = nodePtr->next;
	}
	fclose(ffile);
	return range;
}

// Functie care elibereaza memoria alocata pentru un range
void destroyRange(Range *range)
{
	if (range != NULL)
	{
		if (range->index != NULL)
		{
			free(range->index);
		}
		free(range);
	}
}

int main(void)
{
	TTree *modelTree = createTree(createStrElement, destroyStrElement,
								  createIndexInfo, destroyIndexInfo, compareStr);
	if (modelTree == NULL)
		goto NullPointerException;

	TTree *priceTree = createTree(createPriceElement, destroyPriceElement,
								  createIndexInfo, destroyIndexInfo, comparePrice);
	if (priceTree == NULL)
		goto NullPointerException;

	buildTreesFromFile("input.csv", modelTree, priceTree);
	if (isEmpty(modelTree) || isEmpty(priceTree))
		goto EmptyTreeException;

	printf("Model Tree In Order:\n");
	inorderModelTreePrint(modelTree->root);
	printf("\n\n");

	printf("Price Tree In Order:\n");
	inorderPriceTreePrint(priceTree->root);
	printf("\n\n");

	printf("Group Model Search:\n");
	Range *range = modelGroupQuery(modelTree, "MG3");
	if (range == NULL)
		goto NullPointerException;
	printRange(range, "input.csv");
	printf("\n\n");
	destroyRange(range);

	printf("Price Range Search:\n");
	Range *range2 = priceRangeQuery(priceTree, 100, 400);
	if (range2 == NULL)
		goto NullPointerException;
	printRange(range2, "input.csv");
	printf("\n\n");
	destroyRange(range2);

	printf("Model Range Search:\n");
	Range *range3 = modelRangeQuery(modelTree, "L2", "M");
	if (range3 == NULL)
		goto NullPointerException;
	printRange(range3, "input.csv");
	printf("\n\n");
	destroyRange(range3);

	printf("Model Price Range Search:\n");
	Range *range4 = modelPriceRangeQuery("input.csv", modelTree, "L2", "M", 300, 600);
	if (range4 == NULL)
		goto NullPointerException;
	printRange(range4, "input.csv");
	destroyRange(range4);

	destroyTree(modelTree);
	destroyTree(priceTree);
	return 0;

NullPointerException:
	printf("NULL pointer exception!\n");
	return -1;

EmptyTreeException:
	printf("Emtpty tree exception!\n");
	return -2;
}