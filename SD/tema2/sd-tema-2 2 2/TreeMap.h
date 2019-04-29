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
		return 1;
	}
	if (tree->size == 0 && tree->root == NULL)
	{
		return 1;
	}
	return 0;
}

void printTreePreorder(TreeNode *node)
{
	if (node == NULL)
	{
		return;
	}
	printf("%s\n", (char *)node->elem);
	printTreePreorder(node->lt);
	printTreePreorder(node->rt);
}

void printListInorder(TreeNode *node)
{
	while (node != NULL)
	{
		printf("%s\n", (char *)node->elem);
		node = node->next;
	}
}

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

TreeNode *minimum(TreeNode *x)
{
	if(x == NULL) return NULL;
	TreeNode *nodePtr = x;
	while (nodePtr->lt != NULL)
	{
		nodePtr = nodePtr->lt;
	}
	return nodePtr;
}

TreeNode *maximum(TreeNode *x)
{
	if(x == NULL) return NULL;
	TreeNode *nodePtr = x;
	while (nodePtr->rt != NULL)
	{
		nodePtr = nodePtr->rt;
	}
	return nodePtr;
}

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

int abs(int value)
{
	return (value >= 0) ? value : -value;
}

void avlRotateLeft(TTree *tree, TreeNode *x)
{
	if(x == NULL) return;
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

void avlRotateRight(TTree *tree, TreeNode *y)
{
	if(y == NULL) return;
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

int avlGetBalance(TreeNode *x)
{
	if (x == NULL)
		return 0;
	int leftHeight = (x->lt == NULL) ? 0 : x->lt->height;
	int rightHeight = (x->rt == NULL) ? 0 : x->rt->height;
	return leftHeight - rightHeight;
}

void avlFixUp(TTree *tree, TreeNode *y, int leftRotation)
{
	updateAllHeights(tree, tree->root);
	TreeNode *nodePtr = y;
	while (nodePtr != NULL && abs(avlGetBalance(nodePtr)) < 2)
	{
		nodePtr = nodePtr->pt;
	}
	if (nodePtr == NULL)
	{
		return;
	}
	if (avlGetBalance(nodePtr) > 0)
	{
		if (leftRotation == 1)
		{
			avlRotateRight(tree, nodePtr);
		}
		else
		{
			avlRotateLeft(tree, nodePtr->lt);
			avlRotateRight(tree, nodePtr);
		}
	}
	else
	{
		if (leftRotation == 0)
		{
			avlRotateLeft(tree, nodePtr);
		}
		else
		{
			avlRotateRight(tree, nodePtr->rt);
			avlRotateLeft(tree, nodePtr);
		}
	}
	updateAllHeights(tree, tree->root);
}

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

void destroyTreeNode(TTree *tree, TreeNode *node)
{
	if (tree == NULL || node == NULL)
		return;
	if(node->elem != NULL){
		tree->destroyElement(node->elem);
	}
	if(node->info != NULL){
		tree->destroyInfo(node->info);
	}
	free(node);
}

void avlFixList(TTree *tree, TreeNode *node)
{
	if (node == NULL)
		return;
	
	avlFixList(tree, node->lt);
	avlFixList(tree, node->rt);
	
	TreeNode *auxPtr = node;
	if(node->end != node){
		if(auxPtr->next != NULL){
			while(auxPtr->next != NULL &&
					tree->compare(auxPtr->next->elem, node->elem) == 0) {
				auxPtr = auxPtr -> next;
			}
		}
	}
	auxPtr->next = (tree->compare(maximum(tree->root)->elem, node->elem) == 0) ? NULL : successor(node);
	node->prev = (tree->compare(minimum(tree->root)->elem, node->elem) == 0) ? NULL : predecessor(node);
	if(node->prev != NULL){
		if(node->prev->end != node) {
			node->prev = node->prev->end;
			node->prev->next = node;
		}
	}
}

void insert(TTree *tree, void *elem, void *info)
{
	if (tree == NULL)
	{
		return;
	}
	TreeNode *newNode = createTreeNode(tree, elem, info);
	newNode->next = newNode->prev = newNode->rt = newNode->lt = newNode->end = newNode->pt = NULL;
	newNode->end = newNode;
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
	while (1)
	{
		if (tree->compare(nodePtr->elem, elem) < 0)
		{
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
		else if(tree->compare(nodePtr->elem, elem) == 0)
		{
			duplicate = 1;
			break;
		}
	}
	if (duplicate)
	{
		TreeNode *auxPtr = nodePtr;
		while (auxPtr->next != NULL &&
			   tree->compare(auxPtr->next->elem, nodePtr->elem) == 0)
		{
			auxPtr = auxPtr->next;
		}
		newNode->next = auxPtr->next;
		if (newNode->next != NULL)
		{
			newNode->next->prev = newNode;
		}
		auxPtr->next = newNode;
		newNode->prev = auxPtr;
		nodePtr->end = newNode;
	}
	else
	{
		newNode->end = newNode;
		avlFixUp(tree, nodePtr, leftInserted);
		avlFixList(tree, tree->root);
	}
}

void removeFromList(TreeNode *node){
	if(node->prev != NULL){
		node->prev->next = node->next;
	}
	if(node->next != NULL){
		node->next->prev = node->prev;
	}
}

void delete (TTree *tree, void *elem)
{
	if (tree == NULL || elem == NULL || tree->root == NULL)
	{
		return;
	}
	TreeNode *nodePtr = tree->root;
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
		return;
	}
	if (nodePtr->end == nodePtr)
	{
		removeFromList(nodePtr);
		TreeNode *auxPtr = NULL, *initNode = nodePtr;
		if (nodePtr == tree->root)
		{
			tree->size = tree->size - 1;
			if (nodePtr->rt == NULL && nodePtr->lt == NULL)
			{
				destroyTreeNode(tree, nodePtr);
				tree->root = NULL;
				return;
			}
			auxPtr = minimum(nodePtr->rt);
			if (auxPtr == nodePtr->rt)
			{
				auxPtr->lt = NULL;
				if (auxPtr->rt == NULL)
				{
					tree->root = auxPtr;
					auxPtr->lt = nodePtr->lt;
					nodePtr->lt->pt = auxPtr;
				}
			}
			else
			{
				auxPtr->pt->lt = NULL;
				auxPtr->rt = nodePtr->rt;
				auxPtr->lt = nodePtr->lt;
				auxPtr->lt->pt = auxPtr->rt->pt = auxPtr;
				nodePtr = auxPtr->pt;
				auxPtr->pt = NULL;
				tree->root = auxPtr;
			}
			avlFixUp(tree, (nodePtr->rt == NULL) ? nodePtr : nodePtr->rt, 0);
			destroyTreeNode(tree, initNode);
			return;
		}
		int leftDeleted;
		if (nodePtr->lt == NULL && nodePtr->rt == NULL)
		{
			if (nodePtr->pt->rt == nodePtr)
			{
				nodePtr->pt->rt = NULL;
				leftDeleted = 0;
			}
			else
			{
				nodePtr->pt->lt = NULL;
				leftDeleted = 1;
			}
			auxPtr = nodePtr->pt;
		}
		else if (nodePtr->lt == NULL)
		{
			if (nodePtr->pt->rt == nodePtr)
			{
				nodePtr->pt->rt = nodePtr->rt;
				nodePtr->rt->pt = nodePtr->pt;
			}
			else
			{
				nodePtr->pt->lt = nodePtr->rt;
				nodePtr->rt->pt = nodePtr->pt;
			}
			auxPtr = nodePtr->rt;
		}
		else if (nodePtr->rt == NULL)
		{
			if (nodePtr->pt->rt == nodePtr)
			{
				nodePtr->pt->rt = nodePtr->lt;
				nodePtr->lt->pt = nodePtr->pt;
			}
			else
			{
				nodePtr->pt->lt = nodePtr->lt;
				nodePtr->lt->pt = nodePtr->pt;
			}
			auxPtr = nodePtr->lt;
		}
		if (auxPtr == tree->root)
		{
			auxPtr->pt = NULL;
			if (leftDeleted)
			{

				avlFixUp(tree, successor(auxPtr), 1);
			}
			else
			{
				avlFixUp(tree, predecessor(tree->root), 1);
			}
		}
		else
		{
			avlFixUp(tree, auxPtr, (int)(nodePtr->pt->rt == nodePtr));
		}
		destroyTreeNode(tree, initNode);
		tree->size = tree->size - 1;
	}
	else
	{
		TreeNode *auxPtr = nodePtr;
		while (auxPtr->next != NULL &&
			   tree->compare(auxPtr->next->elem, nodePtr->elem) == 0)
		{
			auxPtr = auxPtr->next;
		}
		TreeNode *newLastElem = auxPtr->prev;
		newLastElem -> next = auxPtr->next;
		if(auxPtr->next != NULL){
			auxPtr->next->prev = newLastElem;
		}
		nodePtr->end = newLastElem;
		destroyTreeNode(tree, auxPtr);
	}
}

void destroyTree(TTree *tree)
{
	if(tree == NULL) return;
	 TreeNode *nodePtr = minimum(tree->root);
	 if(nodePtr == NULL) {
		free(tree);
		return;
	 }
	 while(nodePtr != NULL){
		 TreeNode *auxPtr = nodePtr->next;
		 destroyTreeNode(tree, nodePtr);
		 nodePtr = auxPtr;
	 }
	 free(tree);
}

#endif /* TREEMAP_H_ */