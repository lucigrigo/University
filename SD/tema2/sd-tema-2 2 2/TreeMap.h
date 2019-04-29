#ifndef TREEMAP_H_
#define TREEMAP_H_

#include <stdlib.h>

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))

typedef struct node
{
	void *elem;		   // Node key
	void *info;		   // Node satellite information
	struct node *pt;   // Parent link
	struct node *lt;   // left child link
	struct node *rt;   // right child link
	struct node *next; // next link in the list of duplicates
	struct node *prev; // prev link in the list of duplicates
	struct node *end;  // pointer to the end of the duplicates list
	long height;
} TreeNode;

typedef struct TTree
{
	TreeNode *root;					// pointer to the root of the tree
	void *(*createElement)(void *); // create element method
	void (*destroyElement)(void *); // destroy element method
	void *(*createInfo)(void *);	// create info method
	void (*destroyInfo)(void *);	// destroy info method
	int (*compare)(void *, void *); // comparison method between elements
	long size;
} TTree;

// Functia care creeaza un nou arbore
TTree *createTree(void *(*createElement)(void *), void (*destroyElement)(void *),
				  void *(*createInfo)(void *), void (*destroyInfo)(void *),
				  int compare(void *, void *))
{
	TTree *newTTree = (TTree *)malloc(sizeof(TTree));
	newTTree->root = NULL;
	newTTree->size = 0;
	newTTree->createInfo = createInfo;
	newTTree->createElement = createElement;
	newTTree->compare = compare;
	newTTree->destroyInfo = destroyInfo;
	newTTree->destroyElement = destroyElement;
	return newTTree;
}

// Functia testeaza daca un arbore este gol
int isEmpty(TTree *tree)
{
	if (tree == NULL)
	{
		return -1;
	}
	if (tree->size == 0 && tree->root == NULL)
	{
		return 1;
	}
	return 0;
}

// Functia cauta un nod din arbore dupa o anumita valoare
TreeNode *search(TTree *tree, TreeNode *x, void *elem)
{
	if (tree == NULL || tree->root == NULL || x == NULL)
	{
		return NULL;
	}
	TreeNode *nodePtr = x;
	while (nodePtr != NULL)
	{
		if (tree->compare(nodePtr->elem, elem) < 0)
		{
			nodePtr = nodePtr->rt;
		}
		else if (tree->compare(nodePtr->elem, elem) > 0)
		{
			nodePtr = nodePtr->lt;
		}
		else
		{
			break;
		}
	}
	if (nodePtr == NULL)
	{
		return NULL;
	}
	return nodePtr;
}

// Functia intoarce minimul dintr-un arbore
TreeNode *minimum(TreeNode *x)
{
	if (x == NULL)
		return NULL;
	TreeNode *nodePtr = x;
	while (nodePtr->lt != NULL)
	{
		nodePtr = nodePtr->lt;
	}
	return nodePtr;
}

// Functia intoarce maximul dintr-un arbore
TreeNode *maximum(TreeNode *x)
{
	if (x == NULL)
		return NULL;
	TreeNode *nodePtr = x;
	while (nodePtr->rt != NULL)
	{
		nodePtr = nodePtr->rt;
	}
	return nodePtr;
}

// Functia intoarce succesorul unui nod din arbore
TreeNode *successor(TreeNode *x)
{
	if (x == NULL)
		return NULL;
	if (x->rt != NULL)
	{
		return minimum(x->rt);
	}
	TreeNode *nodePtr = x->pt;
	while ((nodePtr != NULL) && (nodePtr->rt == x))
	{
		x = nodePtr;
		nodePtr = nodePtr->pt;
	}
	return nodePtr;
}

// Functia intoarce predecesorul unui nod din arbore
TreeNode *predecessor(TreeNode *x)
{
	if (x == NULL)
		return NULL;
	if (x->lt != NULL)
	{
		return maximum(x->lt);
	}
	TreeNode *nodePtr = x->pt, *copyX = x;
	while (nodePtr != NULL && nodePtr->lt == copyX)
	{
		copyX = nodePtr;
		nodePtr = nodePtr->pt;
	}
	return nodePtr;
}

// Functia actualizeaza inaltimea unui nod din arbore
void updateHeight(TreeNode *x)
{
	int leftHeight = 0;
	int rightHeight = 0;
	if (x != NULL)
	{
		if (x->lt != NULL)
			leftHeight = x->lt->height;
		if (x->rt != NULL)
			rightHeight = x->rt->height;
		x->height = MAX(leftHeight, rightHeight) + 1;
	}
}

// Functia parcurge toate nodurile arborelui pentru a le actualiza inaltimile
void updateAllHeights(TTree *tree, TreeNode *node)
{
	if (node == NULL)
	{
		return;
	}
	updateAllHeights(tree, node->lt);
	updateAllHeights(tree, node->rt);
	updateHeight(node);
}

// Functia intoarce valoarea absoluta
int abs(int value)
{
	return (value >= 0) ? value : -value;
}

// Functia realizeaza rotatia stanga pentru un nod dat
void avlRotateLeft(TTree *tree, TreeNode *x)
{
	if (x == NULL)
		return;
	TreeNode *nodePtr = x->rt;
	if (tree->root == x)
	{
		tree->root = nodePtr;
	}
	else if (x->pt->lt == x)
	{
		x->pt->lt = nodePtr;
	}
	else if (x->pt->rt == x)
	{
		x->pt->rt = nodePtr;
	}
	TreeNode *tempBeta = nodePtr->lt;
	nodePtr->lt = x;
	x->rt = tempBeta;
	nodePtr->pt = x->pt;
	x->pt = nodePtr;
}

// Functia realizeaza rotatia dreapta pentru un nod dat
void avlRotateRight(TTree *tree, TreeNode *y)
{
	if (y == NULL)
		return;
	TreeNode *nodePtr = y->lt;
	if (tree->root == y)
	{
		tree->root = nodePtr;
	}
	else if (y->pt->lt == y)
	{
		y->pt->lt = nodePtr;
	}
	else if (y->pt->rt == y)
	{
		y->pt->rt = nodePtr;
	}
	TreeNode *tempBeta = nodePtr->rt;
	nodePtr->rt = y;
	nodePtr->pt = y->pt;
	y->lt = tempBeta;
	y->pt = nodePtr;
}

// Functia intoarce factorul de echilibru pentru un nod dat
int avlGetBalance(TreeNode *x)
{
	if (x == NULL)
		return 0;
	int leftHeight = (x->lt == NULL) ? 0 : x->lt->height;
	int rightHeight = (x->rt == NULL) ? 0 : x->rt->height;
	return leftHeight - rightHeight;
}

// Functia porneste de la un nod dat si parcurge pe linia parintilor
// pana gaseste un nod care este dezechilibrat,
// realizand si rotirile necesare mentinerii arborelui in echilibru
void avlFixUp(TTree *tree, TreeNode *y, int leftRotation)
{
	// actualizeaza inaltimile din arbore
	updateAllHeights(tree, tree->root);
	TreeNode *nodePtr = y;
	// cauta un nod care este dezechilibrat
	while (nodePtr != NULL && abs(avlGetBalance(nodePtr)) < 2)
	{
		nodePtr = nodePtr->pt;
	}
	// daca nu gaseste niciun nod -> arborele este echilibrat
	if (nodePtr == NULL)
	{
		return;
	}
	// verificarea diferitelor cazuri pentru rotiri
	if (avlGetBalance(nodePtr) > 0)
	{
		if (leftRotation == 1) // cazul stanga-stanga
		{
			avlRotateRight(tree, nodePtr);
		}
		else // cazul stanga-dreapta
		{
			avlRotateLeft(tree, nodePtr->lt);
			avlRotateRight(tree, nodePtr);
		}
	}
	else
	{
		if (leftRotation == 0) // cazul dreapta-dreapta
		{
			avlRotateLeft(tree, nodePtr);
		}
		else // cazul dreapta-stanga
		{
			avlRotateRight(tree, nodePtr->rt);
			avlRotateLeft(tree, nodePtr);
		}
	}
	// reactualizarea inaltimilor din arbore
	updateAllHeights(tree, tree->root);
}

// Functia creeaza un nou nod din arbore cu valorile specificate
// - toate linkurile nodului primesc NULL, initial
// - inaltimea nodului nou creat va fi 1
TreeNode *createTreeNode(TTree *tree, void *value, void *info)
{
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	newNode->elem = tree->createElement(value);
	newNode->info = tree->createInfo(info);
	newNode->pt = newNode->rt = newNode->lt = NULL;
	newNode->next = newNode->prev = newNode->end = NULL;
	newNode->height = 1;
	return newNode;
}

// Functia elibereaza memoria ocupata de un nod din arbore
void destroyTreeNode(TTree *tree, TreeNode *node)
{
	if (tree == NULL || node == NULL)
		return;
	if (node->elem != NULL)
	{
		tree->destroyElement(node->elem);
	}
	if (node->info != NULL)
	{
		tree->destroyInfo(node->info);
	}
	free(node);
}

// Functia reactualizeaza legaturile 'next' si 'prev' a tuturor
// nodurilor din arbore
void avlFixList(TTree *tree, TreeNode *node)
{
	if (node == NULL)
		return;
	avlFixList(tree, node->lt);
	avlFixList(tree, node->rt);
	TreeNode *auxPtr = node;
	// verificarea daca nodul curent are sau nu duplicate
	if (node->end != node)
	{
		if (auxPtr->next != NULL)
		{
			while (auxPtr->next != NULL &&
				   tree->compare(auxPtr->next->elem, node->elem) == 0)
			{
				auxPtr = auxPtr->next;
			}
		}
	}
	// actualizarea legaturilor
	auxPtr->next = (tree->compare(maximum(tree->root)->elem, node->elem) == 0) ? NULL : successor(node);
	node->prev = (tree->compare(minimum(tree->root)->elem, node->elem) == 0) ? NULL : predecessor(node);
	// cazul in care predecesorul are sau nu duplicate
	if (node->prev != NULL)
	{
		if (node->prev->end != node)
		{
			node->prev = node->prev->end;
			node->prev->next = node;
		}
	}
}

// Functia realizeaza inserarea in arbore a unui nou element
void insert(TTree *tree, void *elem, void *info)
{
	if (tree == NULL)
	{
		return;
	}
	// crearea noului element
	TreeNode *newNode = createTreeNode(tree, elem, info);
	newNode->end = newNode;
	// cazul in care arborele este gol
	if (tree->root == NULL)
	{
		tree->root = newNode;
		tree->size = 1;
		newNode->pt = NULL;
		newNode->end = newNode;
		return;
	}
	TreeNode *nodePtr = tree->root;
	int duplicate = 0, leftInserted = 0;
	// cautarea locului potrivit inserarii noului element
	while (1)
	{
		if (tree->compare(nodePtr->elem, elem) < 0)
		{
			// daca am ajuns la baza arborelui
			if (nodePtr->rt == NULL)
			{
				nodePtr->rt = newNode;
				newNode->pt = nodePtr;
				tree->size = tree->size + 1;
				leftInserted = 0;
				break;
			}
			else
			{
				nodePtr = nodePtr->rt;
				continue;
			}
		}
		else if (tree->compare(nodePtr->elem, elem) > 0)
		{
			// daca am ajuns la baza arborelui
			if (nodePtr->lt == NULL)
			{
				nodePtr->lt = newNode;
				newNode->pt = nodePtr;
				tree->size = tree->size + 1;
				leftInserted = 1;
				break;
			}
			else
			{
				nodePtr = nodePtr->lt;
				continue;
			}
		}
		// cazul in care noul nod este un duplicat
		else if (tree->compare(nodePtr->elem, elem) == 0)
		{
			duplicate = 1;
			break;
		}
	}
	if (duplicate) // daca noul nod este duplicat
	{
		TreeNode *auxPtr = nodePtr;
		// parcurgerea tuturor duplicatelor pana la ultimul
		while (auxPtr->next != NULL &&
			   tree->compare(auxPtr->next->elem, nodePtr->elem) == 0)
		{
			auxPtr = auxPtr->next;
		}
		// realizarea legatorilor cu/dinspre noul element
		newNode->next = auxPtr->next;
		if (newNode->next != NULL)
		{
			newNode->next->prev = newNode;
		}
		auxPtr->next = newNode;
		newNode->prev = auxPtr;
		nodePtr->end = newNode;
	}
	else // cazul in care noul nod nu este un duplicat
	{
		newNode->end = newNode;
		// reechilibrarea arborelui
		avlFixUp(tree, nodePtr, leftInserted);
		// refacerea legaturilor din lista (acolo unde este cazul)
		avlFixList(tree, tree->root);
	}
}

// Functia scoate din lista un element
void removeFromList(TreeNode *node)
{
	if (node->prev != NULL)
	{
		node->prev->next = node->next;
	}
	if (node->next != NULL)
	{
		node->next->prev = node->prev;
	}
}

// Functia de stergere a unui nod din arbore
void delete (TTree *tree, void *elem)
{
	if (tree == NULL || elem == NULL || tree->root == NULL)
	{
		return;
	}
	TreeNode *nodePtr = tree->root;
	// cautarea nodului care trebuie sters
	while (nodePtr != NULL)
	{
		if (tree->compare(nodePtr->elem, elem) < 0)
		{
			nodePtr = nodePtr->rt;
		}
		else if (tree->compare(nodePtr->elem, elem) > 0)
		{
			nodePtr = nodePtr->lt;
		}
		else
		{
			break;
		}
	}
	// cazul in care nu exista asemenea nod
	if (nodePtr == NULL)
	{
		return;
	}
	if (nodePtr->end == nodePtr) // cazul in care nodul nu are duplicate
	{
		removeFromList(nodePtr); // scoaterea din lista
		TreeNode *auxPtr = NULL, *initNode = nodePtr;
		if (nodePtr == tree->root) // cazul in care nodul este radacina
		{
			tree->size = tree->size - 1;
			if (nodePtr->rt == NULL && nodePtr->lt == NULL) // nu are copii
			{
				destroyTreeNode(tree, nodePtr);
				tree->root = NULL;
				return;
			}
			auxPtr = minimum(nodePtr->rt); // cautarea succesorului nodului
			if (auxPtr == nodePtr->rt)	 // succesorul este copilul dreapta
			{
				auxPtr->lt = NULL;
				if (auxPtr->rt == NULL) // succesorul nu are copii
				{
					tree->root = auxPtr;
					auxPtr->lt = nodePtr->lt;
					nodePtr->lt->pt = auxPtr;
				}
			}
			else // cazul general pentru succesor
			{
				auxPtr->pt->lt = NULL;
				auxPtr->rt = nodePtr->rt;
				auxPtr->lt = nodePtr->lt;
				auxPtr->lt->pt = auxPtr->rt->pt = auxPtr;
				nodePtr = auxPtr->pt;
				auxPtr->pt = NULL;
				tree->root = auxPtr;
			}
			// refacerea echilibrului arborelui
			avlFixUp(tree, (nodePtr->rt == NULL) ? nodePtr : nodePtr->rt, 0);
			// eliberarea memoriei ocupata de vechiul nod
			destroyTreeNode(tree, initNode);
			return;
		}
		// cazul general pentru un nod oarecare din arbore
		int leftDeleted;
		if (nodePtr->lt == NULL && nodePtr->rt == NULL) // nodul nu are copii
		{
			if (nodePtr->pt->rt == nodePtr) // nodul este copil dreapta
			{
				nodePtr->pt->rt = NULL;
				leftDeleted = 0;
			}
			else // nodul este copil stanga
			{
				nodePtr->pt->lt = NULL;
				leftDeleted = 1;
			}
			auxPtr = nodePtr->pt;
		}
		else if (nodePtr->lt == NULL) // are un singur copil->dreapta
		{
			if (nodePtr->pt->rt == nodePtr) // este copil dreapta
			{
				nodePtr->pt->rt = nodePtr->rt;
				nodePtr->rt->pt = nodePtr->pt;
			}
			else // este copil stanga
			{
				nodePtr->pt->lt = nodePtr->rt;
				nodePtr->rt->pt = nodePtr->pt;
			}
			auxPtr = nodePtr->rt;
		}
		else if (nodePtr->rt == NULL) // are un singur copil->stanga
		{
			if (nodePtr->pt->rt == nodePtr) // este copil dreapta
			{
				nodePtr->pt->rt = nodePtr->lt;
				nodePtr->lt->pt = nodePtr->pt;
			}
			else // este copil stanga
			{
				nodePtr->pt->lt = nodePtr->lt;
				nodePtr->lt->pt = nodePtr->pt;
			}
			auxPtr = nodePtr->lt;
		}
		if (auxPtr == tree->root) // daca noul nod va fi radacina arborelui
		{
			// refacerea echilibrului arborelui
			auxPtr->pt = NULL;
			if (leftDeleted) // pivot-dreapta
			{
				avlFixUp(tree, successor(auxPtr), 1);
			}
			else // pivot-stanga (netestata)
			{
				avlFixUp(tree, predecessor(tree->root), 1);
			}
		}
		else // cazul general pt noul nod
		{
			avlFixUp(tree, auxPtr, (int)(nodePtr->pt->rt == nodePtr));
		}
		// eliberarea memoriei ocupate
		destroyTreeNode(tree, initNode);
		tree->size = tree->size - 1;
	}
	else // stergerea unui duplicat
	{
		TreeNode *auxPtr = nodePtr;
		// parcurgerea elementelor duplicate pana la ultimul
		while (auxPtr->next != NULL &&
			   tree->compare(auxPtr->next->elem, nodePtr->elem) == 0)
		{
			auxPtr = auxPtr->next;
		}
		// scoaterea ultimului duplicat din lista
		TreeNode *newLastElem = auxPtr->prev;
		newLastElem->next = auxPtr->next;
		if (auxPtr->next != NULL)
		{
			auxPtr->next->prev = newLastElem;
		}
		nodePtr->end = newLastElem;
		// eliberarea memoriei ocupate
		destroyTreeNode(tree, auxPtr);
	}
}

// Functia elibereaza memoria ocupata de un arbore
void destroyTree(TTree *tree)
{
	if (tree == NULL)
		return;
	TreeNode *nodePtr = minimum(tree->root);
	// cazul in care arborele e gol
	if (nodePtr == NULL)
	{
		free(tree);
		return;
	}
	// eliberarea memoriei ocupata de fiecare nod
	while (nodePtr != NULL)
	{
		TreeNode *auxPtr = nodePtr->next;
		destroyTreeNode(tree, nodePtr);
		nodePtr = auxPtr;
	}
	free(tree);
}

#endif /* TREEMAP_H_ */