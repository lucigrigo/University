/*
 * list.h
 *
 *  Created on: Mar 23, 2016
 *      Author: dan
 */

#ifndef LIST_H_
#define LIST_H_
#include <stdlib.h>

typedef struct ListNode{
	Item elem;
	struct ListNode* next;
	struct ListNode* prev;
}ListNode;


typedef struct List{
	long length;
	struct ListNode* head;
}List;

List* createList(void){
	List* newList = (List*) malloc(sizeof(List));

	newList->head = (ListNode*)malloc(sizeof(ListNode));

	newList->head->next = newList->head;
	newList->head->prev = newList->head;

	newList->length = 0;

	return newList;
}


void destroyList(List* list){

	ListNode* it = list->head->next;

	while(it != list->head){
		ListNode* deleteNode = it;
		it = it->next;
		free(deleteNode);
	}
	free(list->head);
	free(list);
}


int isEmptyList(List* list){
	return (list->head == list->head->next);
	 /* Comparatia se face cu santinela, in nici un caz cu NULL */
}

void listPushFront(List* list, Item elem){

	if(list == NULL) return;

	ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
	newNode->elem = elem;

	newNode->prev = list->head;
	newNode->next = list->head->next;

	list->head->next->prev = newNode;
	list->head->next = newNode;

	list->length++;

}

void listPopFront(List* list){
	if(isEmptyList(list)) return;

	ListNode* deleteNode = list->head->next;

	deleteNode->next->prev = list->head;
	list->head->next = deleteNode->next;

	list->length--;

	free(deleteNode);
}

void listPushBack(List* list, Item item){

	if(list == NULL) return;

	ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
	newNode->elem = item;

	newNode->next = list->head;
	newNode->prev = list->head->prev;

	list->head->prev->next = newNode;
	list->head->prev = newNode;

	list->length++;
}

void ListPopBack(List* list){
	if(isEmptyList(list)) return;
	ListNode* deleteNode = list->head->prev;
	deleteNode->prev->next = list->head;
	list->head->prev = deleteNode->prev;
	list->length--;
	free(deleteNode);
}

Item listFront(List* list){
	return list->head->next->elem;
}

Item listBack(List* list){
	return list->head->prev->elem;
}
#endif /* LIST_H_ */
