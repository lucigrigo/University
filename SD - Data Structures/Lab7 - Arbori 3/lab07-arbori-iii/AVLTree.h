
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <stdlib.h>

// An AVL tree node
typedef struct AVLNode
{
	Item elem;
	int height;
	struct AVLNode *l;
	struct AVLNode *r;
	struct AVLNode *p;

} AVLNode;

typedef struct AVLTree
{
	long size;
	AVLNode *root;
	AVLNode *nil;
	int (*comp)(Item a, Item b);
} AVLTree;

AVLTree *avlCreateTree()
{
	AVLTree *newTree = (AVLTree *)malloc(sizeof(AVLTree));
	newTree->comp = NULL;
	newTree->nil = (AVLNode *)malloc(sizeof(AVLNode));
	newTree->nil->p = newTree->nil->l = newTree->nil->r = newTree->nil;
	newTree->nil->height = 0;
	newTree->root = (AVLNode *)malloc(sizeof(AVLNode));
	newTree->root->p = newTree->root->l = newTree->root->r = newTree->nil;
	newTree->root->height = 0;
	newTree->size = 0;

	return newTree;
}

int avlIsEmpty(AVLTree *tree)
{
	return (tree->root->l == tree->nil);
}

AVLNode *avlNewNode(AVLTree *tree)
{
	AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
	// Initialize the new node to be used in the tree
	newNode->p = newNode->r = newNode->l = tree->nil;
	newNode->height = 1;

	return newNode;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
	return (a > b) ? a : b;
}

int height(AVLTree *tree, AVLNode *node)
{
	AVLNode *nodePtr = tree->root->l;
	while (nodePtr != tree->nil)
	{
		if (node->elem > nodePtr->elem)
		{
			nodePtr = nodePtr->r;
		}
		else if (node->elem < nodePtr->elem)
		{
			nodePtr = nodePtr->l;
		}
		else if (node->elem == nodePtr->elem)
		{
			return nodePtr->height;
		}
	}
	return -1;
}

int updateAllHeights(AVLTree *tree, AVLNode *node)
{
	if (node == tree->nil)
		return 0;
	updateAllHeights(tree, node->l);
	updateAllHeights(tree, node->r);
	node->height = max(node->l->height, node->r->height) + 1;
	return 0;
}

// A utility function to right rotate subtree rooted with y
void avlRightRotate(AVLTree *tree, AVLNode *y)
{
	AVLNode *nodePtr = y->l;
	Item *elemPtr = y->elem;
	y->elem = nodePtr->elem;
	nodePtr->elem = elemPtr;
	y->l = y->r;
	y->r = nodePtr;
	AVLNode *aux = nodePtr->l;
	nodePtr->l = nodePtr->r;
	nodePtr->r = aux;
	aux = y->l;
	y->l = nodePtr->r;
	nodePtr->r = aux;
	nodePtr->l->p = nodePtr->r->p = nodePtr;
	y->l->p = y->r->p = y;
}

// A utility function to left rotate subtree rooted with x
void avlLeftRotate(AVLTree *tree, AVLNode *x)
{
	AVLNode *nodePtr = x->r;
	Item *elemPtr = x->elem;
	x->elem = nodePtr->elem;
	nodePtr->elem = elemPtr;
	AVLNode *aux = x->l;
	x->l = x->r;
	x->r = aux;
	aux = nodePtr->l;
	nodePtr->l = nodePtr->r;
	nodePtr->r = aux;
	aux = x->r;
	x->r = nodePtr->l;
	nodePtr->l = aux;
	nodePtr->l->p = nodePtr->r->p = nodePtr;
	x->l->p = x->r->p = x;
}

// Get Balance factor of node x
int avlGetBalance(AVLNode *x)
{
	if (x == NULL)
		return 0;
	return x->l->height - x->r->height;
}

AVLNode *avlMinimum(AVLTree *tree, AVLNode *x)
{
	while (x->l != tree->nil)
		x = x->l;
	return x;
}

AVLNode *avlMaximum(AVLTree *tree, AVLNode *x)
{
	while (x->r != tree->nil)
	{
		x = x->r;
	}
	return x;
}

void avlInsert(struct AVLTree *tree, Item elem)
{
	if (tree == NULL)
		return;
	if (tree->root == NULL)
		return;
	AVLNode *newNodePtr = (AVLNode *)malloc(sizeof(AVLNode));
	newNodePtr->r = tree->nil;
	newNodePtr->l = tree->nil;
	newNodePtr->elem = elem;
	newNodePtr->height = 1;
	AVLNode *nodePtr = tree->root->l;
	int leftRotation;
	if (nodePtr == tree->nil)
	{
		newNodePtr->p = tree->root;
		tree->root->l = newNodePtr;
		tree->size = tree->size + 1;
		return;
	}
	while (1)
	{
		if (*(nodePtr->elem) > (*elem))
		{
			if (nodePtr->l != tree->nil)
			{
				nodePtr = nodePtr->l;
				continue;
			}
			else
			{
				nodePtr->l = newNodePtr;
				newNodePtr->p = nodePtr;
				tree->size = tree->size + 1;
				break;
			}
		}
		if (*(nodePtr->elem) < (*elem))
		{
			if (nodePtr->r != tree->nil)
			{
				nodePtr = nodePtr->r;
				continue;
			}
			else
			{
				nodePtr->r = newNodePtr;
				newNodePtr->p = nodePtr;
				tree->size = tree->size + 1;
				break;
			}
		}
		if (nodePtr->elem == (*elem))
		{
			return;
		}
	}
	nodePtr = newNodePtr;
	int a = updateAllHeights(tree, tree->root->l);
	while ((nodePtr != tree->root) &&
		   (abs(avlGetBalance(nodePtr)) < 2))
	{
		if (nodePtr->l->p == nodePtr)
		{
			leftRotation = 1;
		}
		else
		{
			leftRotation = 0;
		}
		nodePtr = nodePtr->p;
	}
	if (nodePtr == tree->root)
	{
		return;
	}
	if (avlGetBalance(nodePtr) > 0)
	{
		if (leftRotation == 1)
		{
			avlRightRotate(tree, nodePtr);
		}
		else
		{
			avlLeftRotate(tree, nodePtr->l);
			avlRightRotate(tree, nodePtr);
		}
	}
	else
	{
		if (leftRotation == 1)
		{
			avlLeftRotate(tree, nodePtr);
		}
		else
		{
			avlRightRotate(tree, nodePtr->r);
			avlLeftRotate(tree, nodePtr);
		}
	}
	a = updateAllHeights(tree, tree->root->l);
}

void avlDeleteNode(AVLTree *tree, AVLNode *node)
{
	//destroyElem(node->elem);
	free(node);
}

void avlDestroyTreeHelper(AVLTree *tree, AVLNode *x)
{
	if (x != tree->nil)
	{
		avlDestroyTreeHelper(tree, x->l);
		avlDestroyTreeHelper(tree, x->r);
		avlDeleteNode(tree, x);
	}
}

void avlDestroyTree(AVLTree *tree)
{
	avlDestroyTreeHelper(tree, tree->root->l);
	free(tree->root);
	free(tree->nil);
	free(tree);
}

#endif /* AVLTREE_H_ */
