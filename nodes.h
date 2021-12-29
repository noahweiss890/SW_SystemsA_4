#ifndef GRAPH_NODE_
#define GRAPH_NODE_

typedef struct edge_ {
    int weight;
    pnode endpoint;
    pedge next;
} edge, *pedge;

typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    pnode next;
} node, *pnode;

pnode get_node(pnode *head, int x);
void add_node(pnode *head);

#endif