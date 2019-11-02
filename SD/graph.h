#ifndef GRAPH_H
#define GRAPH_H

typedef struct TNode
{
    int v;
    float t;
    struct TNode *next;
} TNode, *ATNode;

typedef struct TGraph
{
    int nn;
    ATNode *adl;
} TGraph;

void init_graph(TGraph *g, int nn);
void add_arc(TGraph *g, int u, int v, float cost);

#endif