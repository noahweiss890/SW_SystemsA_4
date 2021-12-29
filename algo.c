#include <stdio.h>
#include <ctype.h>
#include "nodes.h"

void build_graph_cmd(pnode *head)
{
    int v = (int)getchar();
    getchar(); //skip space
    for (int i = 0; i < v; i++) {
        char x = getchar();
        getchar(); //skip space
        while (x == 'n')
        {
            pnode new_node = create_node(); //creates node pointer to be added to graph
            pnode curr = head;
            while (curr->next != NULL)
            { //iterating to last spot
                curr = curr->next;
            }
            curr->next = new_node; //add node to linked list of nodes
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
    pnode del_n = get_node(head, (int)getchar());
    getchar(); //skip spaces
    pnode curr = head;
    pnode temp = NULL; //used to update the linked list
    int del_id = 0;
    pedge del_e = NULL;
    while (curr->next != NULL) { //go through all nodes in graph
        if (curr->next == del_n) { //this node's next is the node we are deleting so we need to update the linked list
            temp = curr->next;
            curr->next = temp->next;
        }
        //current node's next is not the node to be deleted, must go through edges to see if its an endpoint
        pedge currEdgeHead = curr->next->edges; //edges of the node
        pedge tempEdge = NULL;
        int del_w = 0;
        pnode del_end = NULL;
        while (currEdgeHead->next != NULL) {
            if (currEdgeHead->next->endpoint == del_n) { //need to delete this edge
                tempEdge = currEdgeHead->next;
                currEdgeHead->next = tempEdge->next;
                free(tempEdge);
            }
            currEdgeHead = currEdgeHead->next; //increment the head
        }
        curr = curr->next;
    }
    //delete all edges of the node
    int del_w = 0;
    pnode del_end = NULL;
    pedge edgeHead = del_n->edges;
    pedge tempEdge = NULL;
    while (edgeHead->next != NULL) { 
        tempEdge = edgeHead->next;
        edgeHead->next = tempEdge->next;
        free(tempEdge);
    }
    free(del_n); //delete_node(del_n);
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
