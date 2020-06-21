#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Util.h"

// -----------------------------------------------------------------------------
void buildGraphsFromFile(TGraphL** gl);
void printPath(List* path);
void printGraphList(TGraphL* graph);
// -----------------------------------------------------------------------------

#define ASSERT(cond, msg) if (!(cond)) { failed(msg); return 0; }

void passed(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t Puncte: %.2f\n", s, score);
}

void passed2(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t\t Puncte: %.2f\n", s, score);
}

void passed3(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t\t\t Puncte: %.2f\n", s, score);
}

void failed(char* s) {
	printf("Testul %s NU a fost trecut!\n", s);
}

// -----------------------------------------------------------------------------

int testCreate(TGraphL** gl, float score){
	int numOfVertices;

	scanf ("%d", &numOfVertices);

	(*gl) = createGraphAdjList(numOfVertices);
	ASSERT((*gl) != NULL,"Create-01");
	ASSERT((*gl)->nn == numOfVertices,"Create-02");
	ASSERT((*gl)->adl != NULL,"Create-03");
	ASSERT((*gl)->adl[numOfVertices-1] == NULL,"Create-04");

	passed("Create",score);
	printGraphList((*gl));

	return 1;
}

int testAddEdges(TGraphL** gl, float score){
	int v1, v2, numOfEdges;

	scanf("%d",&numOfEdges);

	for (int i=0; i < numOfEdges; i++){
		scanf("%d %d", &v1, &v2);
		addEdgeList(*gl,v1,v2);
	}
	ASSERT((*gl)->adl[0]->v == 4, "AddEdges-01");
	ASSERT((*gl)->adl[0]->next->v == 1, "AddEdges-02");
	ASSERT((*gl)->adl[1]->next->next->v == 2, "AddEdges-03");
	ASSERT((*gl)->adl[1]->next->v == 3, "AddEdges-04");
	ASSERT((*gl)->adl[5]->v == 1, "AddEdges-05");
	ASSERT((*gl)->adl[2]->next->v == 1, "AddEdges-06");

	passed2("Add Graph Edges", score);

	printGraphList((*gl));

	return 1;
}

int testDestroy(TGraphL** gl, float score){
	destroyGraphAdjList(*gl);
	printf(". Testul Destroy: *Se va verifica cu valgrind*\t\t\t Puncte: %.2f.\n", score);
	return 1;
}

int testDFSIter(TGraphL** gl, float score){
	List* path = dfsIterative(*gl, 0);

	ASSERT(!isListEmpty(path),"DFSIterGM-01");
	ASSERT(path->head->next->key == 4,"DFSIterGM-02");
	ASSERT(path->head->prev->key == 0,"DFSIterGM-03");
	ASSERT(path->head->next->next->key == 5,"DFSIterGM-04");
	ASSERT(path->head->prev->prev->key == 1,"DFSIterGM-05");
	ASSERT(path->head->next->next->next->key == 3,"DFSIterGM-06");
	ASSERT(path->head->prev->prev->prev->key == 2,"DFSIterGM-07");

	passed("DFS Iterative Adj Matrix",score);
	// printPath(path);

	destroyList(path);
	return 1;
}

int testDFSRec(TGraphL** gl, float score){
	List* path = dfsRecursive(*gl, 0);

	ASSERT(!isListEmpty(path),"DFSRecGL-01");
	ASSERT(path->head->next->key == 5,"DFSRecGL-02");
	ASSERT(path->head->prev->key == 0,"DFSRecGL-03");
	ASSERT(path->head->next->next->key == 1,"DFSRecGL-04");
	ASSERT(path->head->prev->prev->key == 4,"DFSRecGL-05");
	ASSERT(path->head->next->next->next->key == 2,"DFSRecGL-06");
	ASSERT(path->head->prev->prev->prev->key == 3,"DFSRecGL-07");
	passed2("DFS Recursive Adj List",score);

	destroyList(path);
	return 1;
}

int testBFS(TGraphL** gl, float score){
	// printGraphList((*gl));
	List* path = bfs(*gl, 0);
	printPath(path);
	ASSERT(!isListEmpty(path),"BFSGL-01");
	ASSERT(path->head->next->key == 2,"BFSGL-02");
	ASSERT(path->head->prev->key == 0,"BFSGL-03");
	ASSERT(path->head->next->next->key == 5,"BFSGL-04");
	ASSERT(path->head->prev->prev->key == 4,"BFSGL-05");
	ASSERT(path->head->next->next->next->key == 3,"BFSGL-06");
	ASSERT(path->head->prev->prev->prev->key == 1,"BFSGL-07");
	passed3("BFS Adj List",score);
	// printPath(path);
	destroyList(path);
	return 1;
}
typedef struct Test {
	int (*testFunction)(TGraphL** gl, float);
	float score;
} Test;

int main(int argc, char* argv[]) {
	freopen ("graph.in", "r", stdin);
	Test tests[] =
	{
			{ &testCreate, 1.0 },
			{ &testAddEdges, 0.5 },
			{ &testDFSIter, 2.5 },
			{ &testDFSRec, 2.5 },
			{ &testBFS, 2.5 },
			{ &testDestroy, 1.0 }
	};

	float totalScore = 0.0f, maxScore = 0.0f;
	long testsNo = sizeof(tests) / sizeof(Test);
	long testIdx;

	TGraphL *gl;


	for (testIdx = 0; testIdx < testsNo; testIdx++) {
		float score = tests[testIdx].score;
		if ((*(tests[testIdx].testFunction))(&gl, score)) {
			totalScore += score;
		}
		maxScore += score;

	// 	if((tests[testIdx].testFunction) == testDestroy){
	// 		gl = NULL;
	// 		fclose(stdin);
	// 		freopen ("graph.in", "r", stdin);
	// 		buildGraphsFromFile(&gl);
	// 	}
	}
	// printf("\nScor total: %.2f / %.2f\n\n", totalScore, maxScore);

	// destroyGraphAdjList(gl);
	// fclose(stdin);
	return 0;
}

void buildGraphsFromFile(TGraphL** gl){
	int numOfVertices, numOfEdges;
	int v1, v2;
	scanf ("%d", &numOfVertices);
	scanf ("%d", &numOfEdges);

	(*gl) = createGraphAdjList(numOfVertices);

	for (int i = 0; i < numOfEdges; i++){
		scanf("%d %d", &v1, &v2);
		addEdgeList(*gl,v1,v2);
	}
}

void printPath(List* path){
	printf("Path: ");
	ListNode* it = path->head->prev;
	while(it != path->head){
		printf("%d ",it->key);
		it = it->prev;
	}
	printf("\n");
}


void printGraphList(TGraphL* graph){
	printf("Graph Adjacency Lists:\n");
	for(int i = 0; i < graph->nn; i++){
		printf("%2d: [ ",i);
		for(TNode* it = graph->adl[i]; it != NULL; it = it->next){
			printf("%d ", it->v);
		}
		printf("]\n");
	}
	printf("\n");
}
