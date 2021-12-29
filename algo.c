#include <stdio.h>
#include <ctype.h>
#include "nodes.h"

void build_graph_cmd(pnode *head) {
    int v = (int)getchar();
    getchar(); //skip space
    for (int i = 0; i < v; i++) {
        char x = getchar();
        getchar(); //skip space
        while(x == 'n'){
            add_node((*head));
        }
    }
}

void insert_node_cmd(pnode *head) { // inserts a new node into the graph
    pnode new_node = create_node(); // create a new node
    pnode old_node = get_node(head, new_node->node_num); // get the node that id if it exists
    if(old_node == NULL) { // does a node with that id already exist
        add_node(new_node); // if not then add to the graph
    }
    else { // if it already exists then replace its out edges list
        old_node->edges = new_node->edges;
        // pnode curr_node = head;
        // while(curr != NULL) {
        //     pedge curr_edge = curr_node->edges;
        //     while(curr_edge != NULL) {
        //         if(curr_edge->endpoint == old_node) {
        //             curr_edge->endpoint = new_node;
        //         }
        //         curr_edge = curr_edge->next;
        //     }
        //     curr_node = curr_node->next;
        // }
    }
}

void delete_node_cmd(pnode *head) {

}

void printGraph_cmd(pnode head) { // prints the graph
    pnode curr_node = head;
    while(curr_node != NULL) {
        printf("\nNode %d:\tEdges:\t", curr_node->node_num);
        pedge curr_edge = curr_node->edges;
        while(curr_edge != NULL) {
            printf("-> %d:weight %d\t", curr_edge->endpoint, curr_edge->weight);
            curr_edge = curr_edge->next;
        }
        curr_node = curr_node->next;
    }
}

void deleteGraph_cmd(pnode* head) { // deletes the whole graph and frees all of the allocated memory
    pnode curr_node = head;
    pnode next_node;
    while (curr_node != NULL) {
        pedge curr_edge = curr_node->edges;
        pedge next_edge;
        while(curr_edge != NULL) {
            next_edge = curr_edge->next;
            free(curr_edge);
            curr_edge = next_edge;
        }
        next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
    }
}

void shortsPath_cmd(pnode head) {

}

void TSP_cmd(pnode head) {

}