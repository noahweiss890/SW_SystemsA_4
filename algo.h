#ifndef algo
#define algo

#include "nodes.h"

pnode create_graph(int amount);
void delete_graph(pnode *head);
void printGraph_cmd(pnode head); //for self debug
int shortest_path(pnode *head);
int tsp(pnode *head);
#endif