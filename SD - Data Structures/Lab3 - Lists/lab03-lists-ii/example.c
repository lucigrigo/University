#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Maximum number of characters that can be read
 * in one go from the keyboard
 */
#define MAX_INPUT_LEN 255

/**
 *  Generic Item type definition
 */
typedef char Item;

/**
 * The Double linked list interface
 */
#include "DoubleLinkedList.h"

/**
 * Utility function prototypes for character lists
 */
void printList(List *list);
void printListReverse(List* list);

/* Main Program */
int main(void) {

	int len;
	char inputCharacters[256];
	List *list = createList();


	printf("Introduceti un sir de caractere: ");

	// Read MAX_INPUT_LEN characters from the stdout
	fgets(inputCharacters, MAX_INPUT_LEN, stdin);

	// Remove trailing CR/LF (i.e. '\r', '\n')
	inputCharacters[strcspn(inputCharacters, "\r\n")] = 0;

	// Insert the read characters in the list
	len = strlen(inputCharacters);
	for(int i = 0; i < len; i++){
		insertAt(list, inputCharacters[i],i);
	}

	// The list of characters introduced
	printf("Generated list: ");
	printList(list);
	printf("\n\n");

	// Removing first list element
	deleteOnce(list, inputCharacters[0]);

	// List after delete
	printf("List after deleting the first character: ");
	printList(list);
	printf("\n");

	// Removing last list element
	insertAt(list, inputCharacters[0], 0);
	deleteOnce(list, inputCharacters[len-1]);

	// List after delete
	printf("List after deleting the last character: ");
	printList(list);
	printf("\n");


	// Removing middle list element
	insertAt(list, inputCharacters[len-1], len-1);
	deleteOnce(list, inputCharacters[(len-1)/2]);

	// List after delete
	printf("List after deleting the middle character: ");
	printList(list);
	printf("\n");


	destroyList(list);

	return 0;
}


void printList(List *list){
	ListNode* iterator = list->first;
	printf("[");
	while(iterator != list->last){
		printf("%c, ", iterator->elem);
		iterator = iterator->next;
	}
	printf("%c]",list->last->elem);
}

void printListReverse(List* list){
	ListNode* iterator = list->last;
	printf("[");
	while(iterator != list->last){
		printf("%c ", iterator->elem);
		iterator = iterator->prev;
	}
	printf("%c]",list->last->elem);
}
