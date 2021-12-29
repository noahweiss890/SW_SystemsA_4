#ifndef algo
#define algo

#include "nodes.h"

pnode create_empty_graph(int amount);
void add_node(int id, pedge outedges, pnode nextNode);
void delete_graph(pnode *head);
void printGraph_cmd(pnode head); //for self debug
int shortest_path(int src, int dest);
int tsp(char *string);
#endif