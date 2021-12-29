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
    int new_node_id = (int)getchar();
    getchar();
    pnode new_node = (pnode)malloc(sizeof(node));
    new_node->node_num = new_node_id;
    new_node->next = NULL;
    pedge curr = NULL;
    dest = getchar();
    getchar();
    while(isdigit(dest)) {
        int weight = (int)getchar();
        getchar();
        pedge new_edge = (pedge)malloc(sizeof(edge));
    }
    if(get_node(head, new_node_id) == NULL) {
        
    }
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