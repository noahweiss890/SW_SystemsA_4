#ifndef NODES_H
#define NODES_H

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    int priority;
    int visited;
} node, *pnode;

// void add_node(pnode *head, pnode new_node);
pnode get_node(pnode *head, int id);
void create_node(pnode *node);

#endif