#ifndef TREEMAP_H_
#define TREEMAP_H_

#include <stdlib.h>

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))

//-------------------------------------------------------------------------

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

int isEmpty(TTree *tree)
{
	if (tree == NULL)
	{
		return 0;
	}
	if (tree->size == 0 && tree->root == NULL)
	{
		return 1;
	}
	return 0;
}

TreeNode *search(TTree *tree, TreeNode *x, void *elem)
{
	if (tree == NULL || tree->root == NULL || x == NULL)
	{
		return NULL;
	}
	TreeNode *nodePtr = tree->root;
	while (nodePtr != NULL)
	{
		if (tree->compare(nodePtr->elem, elem) > 0)
		{
			nodePtr = nodePtr->rt;
		}
		else if (tree->compare(nodePtr->elem, elem) < 0)
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
	while (nodePtr != NULL && nodePtr != x)
	{
		nodePtr = nodePtr->next;
	}
	return nodePtr;
}

TreeNode *minimum(TreeNode *x)
{
	TreeNode *nodePtr = x, *auxPtr = nodePtr;
	while (nodePtr != NULL)
	{
		if(nodePtr->info < auxPtr -> info) {
			auxPtr = nodePtr;
		}
		nodePtr = nodePtr->next;
	}
	return nodePtr;
}

TreeNode *maximum(TreeNode *x)
{
	TreeNode *nodePtr = x, *auxPtr = nodePtr;
	while (nodePtr != NULL)
	{
		if(nodePtr->info > auxPtr -> info) {
			auxPtr = nodePtr;
		}
		nodePtr = nodePtr->next;
	}
	return nodePtr;
}

TreeNode *successor(TreeNode *x)
{
	if (x == NULL || x->next == NULL)
	{
		return NULL;
	}
	return x->next;
}

TreeNode *predecessor(TreeNode *x)
{
	if (x == NULL || x->prev == NULL)
	{
		return NULL;
	}
	return x->prev;
}

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

void avlRotateLeft(TTree *tree, TreeNode *x)
{
	// TODO: Cerinta 1
}

void avlRotateRight(TTree *tree, TreeNode *y)
{
	// TODO: Cerinta 1
}

/* Get AVL balance factor for node x */
int avlGetBalance(TreeNode *x)
{
	if (x == NULL)
		return 0;
	int leftHeight = (x->lt == NULL) ? 0 : x->lt->height;
	int rightHeight = (x->rt == NULL) ? 0 : x->rt->height;
	return leftHeight - rightHeight;
}

void avlFixUp(TTree *tree, TreeNode *y)
{

	// TODO: Cerinta 1
}

TreeNode *createTreeNode(TTree *tree, void *value, void *info)
{
	// Allocate node
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

	// Set its element field
	newNode->elem = tree->createElement(value);

	//Set its info
	newNode->info = tree->createInfo(info);

	// Set its tree links
	newNode->pt = newNode->rt = newNode->lt = NULL;

	// Set its list links
	newNode->next = newNode->prev = newNode->end = NULL;

	/*
	 *  The height of a new node is 1,
	 *  while the height of NULL is 0
	 */
	newNode->height = 1;

	return newNode;
}

void destroyTreeNode(TTree *tree, TreeNode *node)
{
	// Check arguments
	if (tree == NULL || node == NULL)
		return;

	// Use object methods to de-alocate node fields
	tree->destroyElement(node->elem);
	tree->destroyInfo(node->info);

	// De-allocate the node
	free(node);
}

void insert(TTree *tree, void *elem, void *info)
{
	// TODO: Cerinta 1
}

void delete (TTree *tree, void *elem)
{
	// TODO: Cerinta 1
}

void destroyTree(TTree *tree)
{
	// TODO: Cerinta 1
	/*
	 * Note: You can use the tree list to
	 * deallocate the hole tree.
	 */
}

#endif /* TREEMAP_H_ */
