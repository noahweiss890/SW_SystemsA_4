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

void add_node(pnode *head, pnode new_node);
pnode get_node(pnode *head, int id);
pnode create_node(pnode *node);

#endif