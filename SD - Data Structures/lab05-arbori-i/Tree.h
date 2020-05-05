#ifndef TREE_H_D
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct Link
{
  Item elem;
  struct Link *l;
  struct Link *r;
} TreeNode;

void Init(TreeNode **t, Item x)
{
  if (t != NULL)
  {
    (*t)->elem = x;
  }
}

void Insert(TreeNode **t, Item x)
{
  if (t == NULL)
  {
    return;
  }
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
  if (node == NULL)
  {
    return;
  }
  node->elem = x;
  node->l = NULL;
  node->r = NULL;
  if ((*t) == NULL)
  {
    (*t) = node;
    return;
  }
  if ((((*t)->l) == NULL) && (((*t)->r) == NULL))
  {
    if ((*t)->elem >= x)
    {
      (*t)->l = node;
    }
    else
    {
      (*t)->r = node;
    }
    return;
  }
  TreeNode *ptr = *t;
  while (1)
  {
    if (x > ptr->elem)
    {
      if (ptr->r == NULL)
      {
        ptr->r = node;
        return;
      }
      ptr = ptr->r;
    }
    else
    {
      if (ptr->l == NULL)
      {
        ptr->l = node;
        return;
      }
      ptr = ptr->l;
    }
  }
}

void PrintPostorder(TreeNode *t)
{
  if (t == NULL)
  {
    return;
  }
  PrintPostorder(t->l);
  PrintPostorder(t->r);
  printf("%d ", t->elem);
}

void PrintPreorder(TreeNode *t)
{
  if (t == NULL)
  {
    return;
  }
  printf("%d ", t->elem);
  PrintPreorder(t->l);
  PrintPreorder(t->r);
}

void PrintInorder(TreeNode *t)
{
  if (t == NULL)
  {
    return;
  }
  PrintInorder(t->l);
  printf("%d ", t->elem);
  PrintInorder(t->r);
}

void Free(TreeNode **t)
{
  if(t == NULL){
    return;
  }
  TreeNode *rightPtr = (*t) -> r;
  Free(rightPtr);
  TreeNode *leftPtr = (*t) -> l;
  Free(leftPtr);
}

int Size(TreeNode *t)
{
  if (t == NULL)
  {
    return 0;
  }
  else
  {
    return Size(t->l) + Size(t->r) + 1;
  }
}

int maxDepth(TreeNode *t)
{
  if (t == NULL)
  {
    return 0;
  }
  else
  {
    int rightDepth = maxDepth(t->r);
    int leftDepth = maxDepth(t->l);

    if (rightDepth > leftDepth)
    {
      return (rightDepth + 1);
    }
    else
    {
      return (leftDepth + 1);
    }
  }
}

#endif // LINKEDSTACK_H_INCLUDED
