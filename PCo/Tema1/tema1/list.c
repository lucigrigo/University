#include "list.h"
#include <stdlib.h>

list cons(void *element, list l)
{
	list temp = malloc(sizeof(struct cell));
	temp->element = element;
	temp->next = l;
	return temp;
}

list cdr_and_free(list l)
{
	list temp = l->next; 
	free(l);
	return temp;
}
