#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode {
  Item elem;             // Stored node value
  struct ListNode *next; // link to next node
  struct ListNode *prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List {
  ListNode *first; // link to the first node
  ListNode *last;  // link to the last node
} List;
// -----------------------------------------------------------------------------

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List *createList(void) {
  // TODO: Cerinta 1a
  List *ptr = (List *)malloc(sizeof(List));
  ptr->first = NULL;
  ptr->last = NULL;
  return ptr;
}
// -----------------------------------------------------------------------------

/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list) {
  // TODO: Cerinta 1b
  if (list != NULL) {
    if (list->last == NULL && list->first == NULL) {
      return 1;
    }
  }
  return 0;
}
// -----------------------------------------------------------------------------

/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem) {
  if (list == NULL) {
    return 0;
  }
  if (list->first != NULL) {
    ListNode *ptr = list->first;
    while (ptr->next != NULL) {
      if (ptr->elem == elem) {
        return 1;
      }
      ptr = ptr->next;
    }
    if (ptr->elem == elem) {
      return 1;
    }
  }
  return 0;
}
// -----------------------------------------------------------------------------

/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAt(List *list, Item elem, int pos) {
  // Guard against young player errors
  if (list == NULL) {
    return;
  }
  if (list->first == NULL) {
    if (pos == 0) {
      ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
      newElem->elem = elem;
      newElem->prev = NULL;
      newElem->next = NULL;
      list->first = newElem;
      list->last = newElem;
    }
    return;
  }
  if (pos == 0) {
    ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
    newElem->elem = elem;
    newElem->prev = NULL;
    newElem->next = list->first;
    list->first->prev = newElem;
    list->first = newElem;
    return;
  }
  if (pos < 0) {
    return;
  }
  int t = 0;
  ListNode *ptr = list->first;
  while (ptr->next != NULL) {
    if (t == (pos - 1)) {
      break;
    }
    t++;
    ptr = ptr->next;
  }
  if ((t != (pos - 1)) && (ptr->next == NULL)) {
    return;
  }
  if ((ptr->next == NULL) && (t == (pos - 1))) {
    ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
    newElem->elem = elem;
    newElem->next = NULL;
    newElem->prev = ptr;
    ptr->next = newElem;
    list->last = newElem;
    return;
  }
  ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
  newElem->elem = elem;
  newElem->next = ptr->next;
  newElem->prev = ptr;
  ptr->next->prev = newElem;
  ptr->next = newElem;
}
// -----------------------------------------------------------------------------

/**
 * Delete the first element instance from a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem) {
  if (list == NULL) {
    return;
  }
  if (list->first == NULL) {
    return;
  }
  if (list->first == list->last && list->first->elem == elem) {
    free(list->first);
    list->first = NULL;
    list->last = NULL;
    return;
  }

  ListNode *ptr = list->first;
  while (ptr->next != NULL) {
    if (ptr->elem == elem) {
      break;
    }
    ptr = ptr->next;
  }

  if (ptr->elem == elem) {
    if (ptr == list->first) {
      list->first = ptr->next;
      list->first->prev = NULL;
      if (ptr != NULL) {
        free(ptr);
      }
    } else if (ptr == list->last) {
      list->last = ptr->prev;
      list->last->next = NULL;
      if (ptr != NULL) {
        free(ptr);
      }
    } else {
      ptr->prev->next = ptr->next;
      ptr->next->prev = ptr->prev;
      if (ptr != NULL) {
        free(ptr);
      }
    }
  }
}
// -----------------------------------------------------------------------------

/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list) {
  // Guard against young player errors
  if (list == NULL)
    return 0;
  // TODO: Cerinta 1f
  if (list->first == NULL) {
    return 0;
  }
  int l = 1;
  ListNode *ptr = list->first;
  while (ptr->next != NULL) {
    ptr = ptr->next;
    l++;
  }
  return l;
}
// -----------------------------------------------------------------------------

/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
void destroyList(List *list) {
  if (list == NULL) {
    return;
  }
  if (list->first == NULL) {
    free(list);
    return;
  }
  ListNode *ptr = list->first, *aux;
  while (ptr != NULL) {
		if(ptr -> next != NULL){
			aux = ptr->next;
		} else {
      break;
    }
    free(ptr);
    ptr = aux;
  }
  free(list);
}
// -----------------------------------------------------------------------------

#endif //_DOUBLE_LINKED_LIST_H_
