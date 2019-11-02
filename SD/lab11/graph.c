#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

#define MAX_INT 2147

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
	TGraphL *next;
} TGraphL;

void alloc_list(TGraphL *G, int n)
{
	int i;
	G->nn = n;
	G->adl = (ATNode *)malloc((n + 1) * sizeof(ATNode));
	for (i = 0; i < n; i++)
		G->adl[i] = NULL;
}

void free_list(TGraphL *G)
{
	int i;
	ATNode it;
	for (i = 1; i < G->nn; i++)
	{
		it = G->adl[i];
		while (it != NULL)
		{
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
	TNode *t;
	t = (ATNode)malloc(sizeof(TNode));
	t->v = v2;
	t->c = c;
	t->next = G->adl[v1];
	G->adl[v1] = t;
	t = (ATNode)malloc(sizeof(TNode));
	t->v = v1;
	t->c = c;
	t->next = G->adl[v2];
	G->adl[v2] = t;
}

void printCost(int *costs, int s, int n)
{
	int i;
	printf("Printing costs for node %d:\n", s);
	for (i = 0; i < n; i++)
	{
		printf("\tto node %d : cost %d\n", i, costs[i]);
	}
}

void dijkstra(TGraphL G, int s)
{
	MinHeap *h = newQueue(G.nn);
	int *costVect = (int *)malloc(G.nn * sizeof(int)), i;
	for (i = 0; i < G.nn; i++)
	{
		insert(h, i, MAX_INT);
		costVect[i] = MAX_INT;
	}
	costVect[s] = 0;
	while (!isEmpty(h))
	{
		MinHeapNode *a = removeMin(h);
		TNode *nodePtr = G.adl[a->v];
		printf("parcurg in ordinea %d\n", a->v);
		while (nodePtr != NULL)
		{
			if (isInMinHeap(h, nodePtr->v) &&
				costVect[nodePtr->v] > costVect[a->v] + nodePtr->c)
			{
				costVect[nodePtr->v] = costVect[a->v] + nodePtr->c;
			}
			nodePtr = nodePtr->next;
		}
		// printf("to node %d cost is %d\n", a->v, costVect[a->v]);
	}
	printCost(costVect, s, G.nn);
	free(costVect);
}

void Prim(TGraphL G)
{
	int *visited = (int *)calloc(G.nn, sizeof(int)), *parents = (int *)calloc(G.nn, sizeof(int));
	int i, count = 0;
	visited[0] = 1;
	while (1)
	{
		int min = MAX_INT, index = -1, parent = -1;
		for (i = 0; i < G.nn; i++)
		{
			if (visited[i] == 1)
			{
				TNode *nodePtr = G.adl[i];
				while (nodePtr != NULL)
				{
					if (nodePtr->c < min && visited[nodePtr->v] == 0)
					{
						min = nodePtr->c;
						index = nodePtr->v;
						parent = i;
					}
					nodePtr = nodePtr->next;
				}
			}
		}
		visited[index] = 1;
		parents[index] = parent;
		count++;
		if (count == G.nn)
			break;
	}
	printf("\n\nParinte:\tVarf:\n");
	for (i = 0; i < G.nn; i++)
	{
		printf("%d\t\t%d\n", parents[i], i);
	}
}

int main()
{
	int i, v1, v2, c;
	int V, E;
	TGraphL G;
	ATNode t;
	freopen("graph.in", "r", stdin);
	scanf("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i = 1; i <= E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
		insert_edge_list(&G, v1, v2, c);
	}

	for (i = 0; i < G.nn; i++)
	{
		printf("%d : ", i);
		for (t = G.adl[i]; t != NULL; t = t->next)
			printf("%d ", t->v);
		printf("\n");
	}
	dijkstra(G, 0);
	Prim(G);

	return 0;
}
