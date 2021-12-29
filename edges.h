#ifndef edge_
#define edge_

#include "nodes.h"

typedef struct edge_ {
    int weight;
    pnode endpoint;
    pedge next;
} edge, *pedge;

void add_edge(int, pnode dest, pedge nextEdge);
void delete_edge(pnode dest);

#endif