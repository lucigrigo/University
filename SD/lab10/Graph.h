/*
 * graph.h
 *
 *  Created on: May 9, 2016
 *      Author: dan
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include "Util.h"

typedef int TCost; // Cost(weight) of path to a specific node (NOT USED IN THIS LAB)

typedef struct TNode{
	int v; // Destination node index
	TCost c; // Cost of the edge associated with the nodes - (NOT USED IN THIS LAB)
	struct TNode *next; // Link to the next node in the list
}TNode, *ATNode;

typedef struct{
	int nn; // Number of nodes in the graph
	ATNode *adl; // Adjancey list (TNode**)
}TGraphL;


TGraphL* createGraphAdjList(int numberOfNodes);

void addEdgeList(TGraphL* graph, int v1, int v2);
void removeEdgeList(TGraphL* graph, int v1, int v2);
void removeNodeList(TGraphL* graph, int v);

List* dfsIterative(TGraphL* graph, int s);
List* dfsRecursive(TGraphL* G, int s);
List* bfs(TGraphL* graph, int s);

void destroyGraphAdjList(TGraphL* graph);


#endif /* GRAPH_H_ */
