#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"

//returns node from linked list with given id 
pnode get_node(pnode *head, int id) {
    if(head == NULL) {
        return NULL;
    }
    pnode curr = *head;
    while(curr != NULL && curr->node_num != id) { //update only if node does not have given id and is not null
        curr = curr->next;
    }
    return curr;
}

//creates the edges of the node with weights 
void create_node(pnode *head) {
    int new_node_id;
    scanf("%d ", &new_node_id); //receive which node to work with from buffer
    pnode new_node = get_node(head, new_node_id); //get node with that ID
    new_node->edges = NULL;
    pedge prev = NULL; //in order to add on to end of edge linked list
    int dest, is_int = 0;
    if(scanf("%d ", &dest)) { // if the input is an int
        is_int = 1;
    }
    while(is_int) { //until we've gotten to a value that is not a digit
        int weight;
        scanf("%d ", &weight); //get weight from buffer
        pedge new_edge = (pedge)malloc(sizeof(edge)); //create new edge
        if(new_node == NULL) {
            printf("Not enough memory!");
            exit(0);
        }
        new_edge->endpoint = get_node(head, dest); //assign endpoint of edge to be the node with id dest
        new_edge->weight = weight; //set weight of edge to be weight we received from buffer
        new_edge->next = NULL;
        if(new_node->edges == NULL) { //if no edges already, make new_edge the head of edges
            new_node->edges = new_edge;
            prev = new_edge;
        }
        else { //the node already has edges, add to end fo linked list
            prev->next = new_edge;
            prev = prev->next;
        }
        is_int = 0;
        if(scanf("%d ", &dest)) { // if the input is an int
            is_int = 1;
        }
    }
}
