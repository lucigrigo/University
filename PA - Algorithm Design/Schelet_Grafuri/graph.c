/*
*	Created by Nan Mihai on 04.04.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator - Proiectarea algoritmilor (Grafuri)
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/
#include <string.h>
#include "graph.h"

Graph initGraph(int V, int type)
{
	Graph g;
	int i;
	g = (Graph) malloc(sizeof(struct graph));
	g->V = V;
	g->adjLists = (List*) malloc(V * sizeof(List));
	g->type = type;
	for (i = 0; i < V; i++) {
		g->adjLists[i] = NULL;
	}
	g->visited = calloc(V, sizeof(int));
	g->start = malloc(V * sizeof(int));
	g->end = malloc(V * sizeof(int));
	return g;
}

Graph insertEdge(Graph g, int u, int v, int cost)
{
	Pair p;
	p.v = v;
	p.cost = cost;
	g->adjLists[u] = addLast(g->adjLists[u], p);

	if (g->type == 0) {
		Pair p1;
		p.v = u;
		p.cost = cost;
		g->adjLists[v] = addLast(g->adjLists[v], p);
	}
	return g;
}

int isArc(Graph g, int u, int v)
{
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

int getCost(Graph g, int u, int v)
{
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return tmp->data.cost;
		tmp = tmp->next;
	}
	return INFINITY;
}

void drawGraph(Graph g, char *name)
{
	int i, j;
	FILE *stream;
	char *buffer, *aux;
	List tmp;

	if (g == NULL || name == NULL)
		return;
	stream = fopen(name, "w");
	if (g->type == 0)
		fprintf(stream, "graph G {\n");
	else
		fprintf(stream, "digraph G {\n");
	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");
	for (i = 0; i < g->V; i++) {
		tmp = g->adjLists[i];
		while (tmp != NULL) {
			if (g->type == 0) {
				if (i < tmp->data.v)
					fprintf(stream, "    %d -- %d;\n", i, tmp->data.v);
			}
			else
				fprintf(stream, "    %d -> %d;\n", i, tmp->data.v);
			tmp = tmp->next;
		}
	}
	fprintf(stream, "}\n");
	fclose(stream);
	buffer = (char*) malloc(SIZE*sizeof(char));
	aux = (char*) malloc(SIZE*sizeof(char));
	strncpy(aux, name, strlen(name) - 4);
	aux[strlen(name) - 4] = '\0';
	sprintf(buffer, "dot %s | neato -n -Tpng -o %s.png", name, aux);
	system(buffer);
	free(buffer);
	free(aux);
}

void printGraph(Graph g)
{
	int i;
	if (g == NULL)
		return;
	if (g->type == 0)
		printf("Graf neorientat cu %d noduri\n", g->V);
	else
		printf("Graf orientat cu %d noduri\n", g->V);
	for (i = 0; i < g->V; i++) {
		printf("%d: ", i);
		List adj = g->adjLists[i];
		while (adj) {
			printf("(%d, %d) -> ", adj->data.v, adj->data.cost);
			adj = adj->next;
		}
		printf("NULL\n");
	}
}

Graph freeGraph(Graph graph)
{
	int i;
	if (!graph)
		return graph;
	if (graph->visited)
		free(graph->visited);
	if (graph->start)
		free(graph->start);
	if (graph->end)
		free(graph->end);
	if (graph->adjLists) {
		for (i = 0; i < graph->V; i++)
			graph->adjLists[i] = freeList(graph->adjLists[i]);
		free(graph->adjLists);
	}
	free(graph);
	return NULL;
}
