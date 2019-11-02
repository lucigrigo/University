#ifndef BST_H_
#define BST_H_

#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just assume
  some type T was previously defined.
 */

// -----------------------------------------------------------------------------

/*
 * !!!!ATENTION!!!!
 * 1. This implementation uses two sentinels (dummy nodes) root and nil.
 * 2. The convetion is that we always root the tree at root->l (the left of the root sentinel)
 */

typedef struct BSTNode
{
	Item elem;
	struct BSTNode *p; // parent - not really needed, but simplifies implementation.
	struct BSTNode *l; // left child.
	struct BSTNode *r; // right child.
} BSTNode;

typedef struct BSTree
{
	long size;	 // This inintially is 0, and is updated by insert/delete
	BSTNode *root; // The sentinel root (a sentinel not the actual root). The actual root node is root->l !
	BSTNode *nil;  // The nil sentinel to avoid checks for NULL
} BSTree;

// TODO: Cerinta 1 si 2

/*
 * IMPLEMENTATION ORDER:
 * 1.  createTree
 * 2.  isEmpty
 * 3.  insert
 * 4.  search
 * 5.  minimum
 * 6.  maximum
 * 7.  successor 
 * 8.  predecessor
 * 9.  destroyTree
 */

BSTree *createTree()
{
	BSTree *tree = (BSTree *)malloc(sizeof(BSTree));
	tree->nil = (BSTNode *)malloc(sizeof(BSTNode));
	tree->root = (BSTNode *)malloc(sizeof(BSTNode));
	tree->root->l = tree->nil;
	tree->root->r = tree->nil;
	tree->root->p = tree->nil;
	tree->nil->l = tree->nil;
	tree->nil->r = tree->nil;
	tree->nil->p = tree->nil;
	tree->size = 0;
	return tree;
}

int isEmpty(BSTree *tree)
{
	if (tree->root->l == tree->nil)
	{
		return 1;
	}
	return 0;
}

void insert(BSTree *tree, Item elem)
{
	if (tree == NULL)
		return;
	if (tree->root == NULL)
		return;
	BSTNode *newNodePtr = (BSTNode *)malloc(sizeof(BSTNode));
	newNodePtr->r = tree->nil;
	newNodePtr->l = tree->nil;
	newNodePtr->elem = elem;
	BSTNode *nodePtr = tree->root->l;
	if (nodePtr == tree->nil)
	{
		newNodePtr->p = tree->root;
		tree->root->l = newNodePtr;
		tree->size = tree->size + 1;
		return;
	}
	while (1)
	{
		if (nodePtr->elem > elem)
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
				return;
			}
		}
		if (nodePtr->elem < elem)
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
				return;
			}
		}
		if (nodePtr->elem == elem)
		{
			return;
		}
	}
}

BSTNode *search(BSTree *tree, Item elem)
{
	if (tree == NULL)
	{
		return NULL;
	}

	if (tree->root == NULL)
	{
		return NULL;
	}
	BSTNode *nodePtr = tree->root->l;
	if (nodePtr == NULL)
	{
		return NULL;
	}
	while (nodePtr != tree->nil)
	{
		if (nodePtr->elem > elem)
		{
			nodePtr = nodePtr->l;
		}
		else if (nodePtr->elem < elem)
		{
			nodePtr = nodePtr->r;
		}
		else if (nodePtr->elem == elem)
		{
			return nodePtr;
		}
	}
	return NULL;
}

BSTNode *minimum(BSTree *tree, BSTNode *node)
{
	if (tree == NULL)
	{
		return NULL;
	}
	if (tree->root == NULL)
	{
		return NULL;
	}
	BSTNode *nodePtr = node;
	if (nodePtr == NULL)
	{
		return NULL;
	}
	while (nodePtr->l != tree->nil)
	{
		nodePtr = nodePtr->l;
	}
	return nodePtr;
}

BSTNode *maximum(BSTree *tree, BSTNode *node)
{
	if (tree == NULL)
	{
		return NULL;
	}
	if (tree->root == NULL)
	{
		return NULL;
	}
	BSTNode *nodePtr = node;
	if (nodePtr == NULL)
	{
		return NULL;
	}
	while (nodePtr->r != tree->nil)
	{
		nodePtr = nodePtr->r;
	}
	return nodePtr;
}

BSTNode *successor(BSTree *tree, BSTNode *node)
{
	/*
	if (tree == NULL)
		return NULL;
	if (node == NULL)
		return NULL;
	if(node == tree->root->l) {
		return NULL;
	}
	// if(maximum(tree,node) == node) {
	// 	return NULL;
	// }
	if (node->r == tree->nil)
	{
		BSTNode *nodePtr = node;
		while (node->p->r == node)
		{
			node = node->p;
		}
		return node->p;
	}
	else
	{
		BSTNode *nodePtr = node->r;
		if (nodePtr == tree->nil)
		{
			return NULL;
		}
		while (nodePtr->l != tree->nil)
		{
			nodePtr = nodePtr->l;
		}
		return nodePtr;
	}
	*/
	if(node -> r != tree->nil) {
		return minimum(tree,node -> r);
	}
	BSTNode *parent = node -> p;
	while(parent != tree->root->l && parent -> r == node) {
		node = parent;
		parent = parent -> p;
	}
	return parent;
}

BSTNode *predecessor(BSTree *tree, BSTNode *node)
{
	if (tree == NULL)
		return NULL;
	if (node == NULL)
		return NULL;
	if (node->l == tree->nil)
	{
		BSTNode *nodePtr = node;
		while (node->p->l == node)
		{
			node = node->p;
		}
		return node->p;
	}
	else
	{
		BSTNode *nodePtr = node->l;
		if (nodePtr == tree->nil)
		{
			return NULL;
		}
		while (nodePtr->r != tree->nil)
		{
			nodePtr = nodePtr->r;
		}
		return nodePtr;
	}
}

void destroyTree(BSTree *tree)
{
	;
}

void delete (BSTree *tree, Item elem)
{
	BSTNode *z; // node to be deleted
	BSTNode *y; // Node that is spliced out
	BSTNode *x; // The child of the sliced out node

	// Needed to maintain a similar interface as in the previous labs
	if ((z = search(tree, elem)) == tree->nil)
		return;

	/*
	 * Note:
	 * Case 1: The node has no children
	 * Case 2: The node has one child
	 * Case 3: The node has two children
	 */

	// Are we in cases 1,2 or in case 3
	y = ((z->l == tree->nil) || (z->r == tree->nil)) ? z : successor(tree, z);

	// Set x to the child of y
	x = (y->l == tree->nil) ? y->r : y->l;

	/*
	 * Note:
	 * There is no need to check if x is a valid pointer, we have the sentinels!
	 */
	if (tree->root == (x->p = y->p)) // assignment of y->p to x->p is intentional
		tree->root->l = x;
	else if (y == y->p->l)
		y->p->l = x;
	else
		y->p->r = x;

	if (y != z)
	{

		/*
		 * Note:
		 * The data type T might be a very big structure, thus copying the key
		 * from one node to another might be very inefficient. It is better to
		 * modify the actual links.
		 */

		// y is the node to splice out and x is its child
		y->l = z->l;
		y->r = z->r;
		y->p = z->p;
		z->l->p = z->r->p = y;
		if (z == z->p->l)
			z->p->l = y;
		else
			z->p->r = y;
		free(z);
	}
	else
	{
		free(y);
	}

	tree->size--;
}

#endif /* BST_H_ */
