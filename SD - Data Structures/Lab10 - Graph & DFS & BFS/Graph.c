#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"
#include "Graph.h"

TGraphL *createGraphAdjList(int numberOfNodes)
{
	TGraphL *newGraph = (TGraphL *)malloc(sizeof(TGraphL));
	newGraph->nn = numberOfNodes;
	newGraph->adl = (ATNode *)malloc(numberOfNodes * sizeof(ATNode));
	for (int i = 0; i < numberOfNodes; i++)
	{
		newGraph->adl[i] = NULL;
	}
	return newGraph;
}

void addEdgeList(TGraphL *graph, int v1, int v2)
{
	TNode *newNode1 = (TNode *)malloc(sizeof(TNode)),
		  *newNode2 = (TNode *)malloc(sizeof(TNode));
	newNode1->c = 1;
	newNode2->c = 1;
	newNode1->v = v1;
	newNode2->v = v2;
	newNode2->next = graph->adl[v1];
	newNode1->next = graph->adl[v2];
	graph->adl[v1] = newNode2;
	graph->adl[v2] = newNode1;
}

List *dfsIterative(TGraphL *graph, int s)
{
	List *newList = createList();
	int *visited = (int *)calloc(graph->nn, sizeof(int)), i;
	Stack *stack = createStack();
	push(stack, s);
	visited[s] = 1;
	while (!isStackEmpty(stack))
	{
		i = top(stack);
		pop(stack);
		TNode *auxPtr = graph->adl[i];
		while (auxPtr != NULL)
		{
			if (visited[auxPtr->v] == 0)
			{
				push(stack, auxPtr->v);
				visited[auxPtr->v] = 1;
			}
			auxPtr = auxPtr->next;
		}
		enqueue(newList, i);
		visited[i] = 1;
	}
	destroyStack(stack);
	free(visited);
	return newList;
}

void dfsRecHelper(TGraphL *graph, int *visited, List *path, int s)
{
	if(visited[s] == 0) {
		visited[s] = 1;
		enqueue(path, s);
		TNode *auxPtr = graph->adl[s];
		while(auxPtr != NULL){
			dfsRecHelper(graph, visited, path, auxPtr->v);
			auxPtr = auxPtr->next;
		}
	}
}

List *dfsRecursive(TGraphL *graph, int s)
{
	int *visited = (int *)calloc(graph->nn, sizeof(int));
	List *newList = createList();
	//enqueue(newList, s);
	dfsRecHelper(graph, visited, newList, s);
	// dequeue(newList);
	free(visited);
	return newList;
}

List *bfs(TGraphL *graph, int s)
{
	List *newList = createList();
	if (s > graph->nn || s < 0)
		return NULL;
	int listLength = 1, i = s;
	Queue *queue = createQueue();
	push(queue, s);
	int *visited2 = (int *)malloc(graph->nn * sizeof(int));
	for (int p = 0; p < graph->nn; p++)
	{
		visited2[p] = 0;
	}
	while (!isStackEmpty(queue))
	{
		i = front(queue);
		dequeue(queue);
		if (visited2[i] == 0)
		{
			TNode *auxPtr = graph->adl[i];
			while (auxPtr != NULL)
			{
				push(queue, auxPtr->v);
				auxPtr = auxPtr->next;
			}
			enqueue(newList, i);
			visited2[i] = 1;
		}
	}
	destroyStack(queue);
	free(visited2);
	return newList;
}

void destroyGraphAdjList(TGraphL *graph)
{
	for(int i = 0; i < graph->nn; i++){
		TNode *aux1 = graph->adl[i];
		while(aux1 != NULL){
			TNode *aux2 = aux1 -> next;
			free(aux1);
			aux1 = aux2;
		}
	}
	free(graph);
}

void removeEdgeList(TGraphL *graph, int v1, int v2)
{
	TNode *it = graph->adl[v1];
	TNode *prev = NULL;
	while (it != NULL && it->v != v2)
	{
		prev = it;
		it = it->next;
	}

	if (it == NULL)
		return;

	if (prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while (it != NULL && it->v != v1)
	{
		prev = it;
		it = it->next;
	}
	if (it == NULL)
		return;
	if (prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL *graph, int v)
{
	for (int i = 0; i < graph->nn; i++)
	{
		removeEdgeList(graph, v, i);
	}
}
