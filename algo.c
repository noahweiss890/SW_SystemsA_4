#include <stdio.h>
#include "nodes.h"
#include <ctype.h>

void build_graph_cmd(pnode *head) {
    int v = (int)getchar();
    getchar(); //skip space
    for (int i = 0; i < v; i++)
    {
        char x = getchar();
        getchar(); //skip space
        while(x == 'n'){
            add_node((*head));
        }
    }
}

void insert_node_cmd(pnode *head) {

}

void delete_node_cmd(pnode *head) {

}

void printGraph_cmd(pnode head) {

}

void deleteGraph_cmd(pnode* head) {

}

void shortsPath_cmd(pnode head) {

}

void TSP_cmd(pnode head) {

}