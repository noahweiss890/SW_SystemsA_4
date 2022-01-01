#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "nodes.h"
#include "algo.h"

void build_graph_cmd(pnode *head) {
    int v = (int)getchar() - '0';
    getchar(); //skip space
    if(v == 0) {
        return;
    }
    pnode temp = (pnode)malloc(sizeof(node));
    if(temp == NULL) {
        printf("Not enough memory!");
        exit(0);
    }
    temp->node_num = 0;
    temp->next = NULL;
    *head = temp;
    pnode curr = temp;
    for (int i = 1; i < v; i++) {
        pnode new_node = (pnode)malloc(sizeof(node));
        if(new_node == NULL) {
            printf("Not enough memory!");
            exit(0);
        }
        new_node->node_num = i;
        new_node->next = NULL;
        curr->next = new_node;
        curr = curr->next;
    }
    for (int i = 0; i < v; i++) {
        char x = getchar();
        getchar(); //skip space
        while (x == 'n') {
            create_node(head); //creates node pointer to be added to graph
            x = getchar();
            getchar(); //skip space
        }
        ungetc(' ', stdin);
        ungetc(x, stdin);
    }
}

void insert_node_cmd(pnode *head) { // inserts a new node into the graph
    int id = (int)getchar() - '0';
    getchar();
    pnode old_node = get_node(head, id); // get the node with that id if it exists
    if(old_node == NULL) { // does a node with that id already exist
        pnode new_node = (pnode)malloc(sizeof(node));
        if(new_node == NULL) {
            printf("Not enough memory!");
            exit(0);
        }
        new_node->node_num = id;
        new_node->edges = NULL;
        new_node->next = NULL;
        pedge prev;
        char dest = getchar();
        getchar();
        while(isdigit(dest)) {
            int weight = (int)getchar() - '0';
            getchar();
            pedge new_edge = (pedge)malloc(sizeof(edge));
            if(new_edge == NULL) {
                printf("Not enough memory!");
                exit(0);
            }
            new_edge->endpoint = get_node(head, (int)dest - '0');
            new_edge->weight = weight;
            if(new_node->edges == NULL) {
                new_node->edges = new_edge;
                prev = new_edge;
            }
            else {
                prev->next = new_edge;
                prev = prev->next;
            }
            dest = getchar();
            getchar();
        }
        ungetc(' ', stdin);
        ungetc(dest, stdin);
        if(*head == NULL) {
            *head = new_node;
        }
        else {
            pnode curr_node = *head;
            while(curr_node->next != NULL) {
                curr_node = curr_node->next;
            }
            curr_node->next = new_node;
        }
        
    }
    else { // if it already exists then replace its out edges list
        
        pedge curr_edge = old_node->edges;
        pedge next_edge;
        while(curr_edge != NULL) {
            next_edge = curr_edge->next;
            free(curr_edge);
            curr_edge = next_edge;
        }
        
        old_node->edges = NULL;
        pedge prev = NULL;
        char dest = getchar();
        getchar();
        while(isdigit(dest)) {
            int weight = (int)getchar() - '0';
            getchar();
            pedge new_edge = (pedge)malloc(sizeof(edge));
            if(new_edge == NULL) {
                printf("Not enough memory!");
                exit(0);
            }
            new_edge->endpoint = get_node(head, (int)dest - '0');
            new_edge->weight = weight;
            new_edge->next = NULL;
            if(old_node->edges == NULL) {
                old_node->edges = new_edge;
                prev = new_edge;
            }
            else {
                prev->next = new_edge;
                prev = prev->next;
            }
            dest = getchar();
            getchar();
        }
        ungetc(' ', stdin);
        ungetc(dest, stdin);
    }
}

//deletes a specific node and all edges entering or exiting the node
void delete_node_cmd(pnode *head) {
    int counter = 0;
    if(*head == NULL){
        return;
    }
    pnode del_n = get_node(head, (int)getchar() - '0');
    getchar(); //skip spaces
    pnode next_node = NULL;
    if((*head) == del_n){ //first node in list is one to delete so unlink
        next_node = (*head)->next;
        //free(*head);
        counter++;
        *head = next_node;
    }
    else {
        pnode curr = *head;
        while (curr->next != NULL) { //go through all nodes in graph
            if (curr->next == del_n) { //this node's next is the node we are deleting so we need to update the linked list
                curr->next = curr->next->next;
            }
            curr = curr->next;
        }
    }
    pnode curr_node = *head;
    pedge curr_edge = NULL;
    pedge next_edge = NULL;
    while(curr_node != NULL) {
        if (curr_node->edges != NULL) {
            //go through nodes and check if any of the edges's endpoints are the node we are deleting
            if (curr_node->edges->endpoint == del_n) { //unlink and free edge
                next_edge = curr_node->edges->next;
                free(curr_node->edges);
                counter++;
                curr_node->edges = next_edge;
            }
            else {
                curr_edge = curr_node->edges; //edges of the node
                while (curr_edge->next != NULL) {
                    if (curr_edge->next->endpoint == del_n) { //need to free and unlink this edge
                        next_edge = curr_edge->next->next;
                        free(curr_edge->next);
                        counter++;
                        curr_edge->next = next_edge;
                        break; //wont have another edge with same endpoint so can break 
                    }
                    curr_edge = curr_edge->next; //increment the head of edges
                }
            }
        }
        curr_node = curr_node->next; //increment curr
    }
    //delete all edges of the node
    pedge curr_edge1 = del_n->edges;
    pedge next_edge1 = NULL;
    while (curr_edge1 != NULL) { 
        next_edge1 = curr_edge1->next;
        free(curr_edge1);
        curr_edge1 = next_edge1;
        counter++;
    }
    free(del_n); //delete_node(del_n);
    counter++;
    printf("\ncount: %d", counter);
}

void printGraph_cmd(pnode *head) { // prints the graph
    pnode curr_node = *head;
    while(curr_node != NULL) {
        printf("\nNode %d:\tEdges:\t", curr_node->node_num);
        pedge curr_edge = curr_node->edges;
        while(curr_edge != NULL) {
            printf("-> %d: weight %d\t", curr_edge->endpoint->node_num, curr_edge->weight);
            curr_edge = curr_edge->next;
        }
        curr_node = curr_node->next;
    }
    putchar('\n');
}

void deleteGraph_cmd(pnode* head) { // deletes the whole graph and frees all of the allocated memory
    if(*head == NULL){
        return;
    }
    int counter = 0; //to keep track of deallocation
    pnode curr_node = *head;
    pnode next_node;
    //go through nodes of graph
    while (curr_node != NULL) {
        pedge curr_edge = curr_node->edges;
        pedge next_edge;
        //unlink and free the edges of the node
        while(curr_edge != NULL) {
            next_edge = curr_edge->next;
            free(curr_edge);
            counter++;
            curr_edge = next_edge;
        }
        //unlink and free the node
        curr_edge = NULL;
        next_node = curr_node->next;
        free(curr_node);
        counter++;
        curr_node = next_node;
    }
    curr_node = NULL;
    //printf("\ncounter is: %d", counter);
}

void shortsPath_cmd(pnode head) {
    //receive source and dest from buffer
    int src = (int)getchar() - '0';
    getchar();
    int dest = (int)getchar() - '0';
    getchar();
    pnode curr = head;
    int counter = 0;
    //change priority of every node to max int except for source node priority is zero
    while(curr != NULL) {
        if(curr->node_num != src){
            curr->priority = INT_MAX;
        }
        else{
            curr->priority = 0;
        }
        curr->visited = 0;
        counter++;
        curr = curr->next;
    }
    int i = 0;
    while(i < counter){
        pnode smallest = NULL;
        int min_p = INT_MAX;
        curr = head;
        //find node with smallest priority
        while(curr != NULL) {
            if(curr->priority < min_p && curr->visited == 0) {
                min_p = curr->priority;
                smallest = curr;
            }
            curr = curr->next;
        }
        //update tag visited 
        smallest->visited = 1;
        //if the smallest priority is int_max, then there is no path betweent the src and dest node
        if(smallest->priority == INT_MAX){
            printf("Dijsktra shortest path: -1 \n");
            return;
        }
        //if the node smallest priority is the dest node then we've found our shortest path 
        if(smallest->node_num == dest){
            printf("Dijsktra shortest path: %d \n", smallest->priority);
            return;
        }
        pedge curr_edge = smallest->edges;
        //go through edges to check priority of neighboring nodes
        while(curr_edge != NULL){
            if(curr_edge->endpoint->priority > smallest->priority + curr_edge->weight){ //relaxing
                curr_edge->endpoint->priority = smallest->priority + curr_edge->weight;
            }
            curr_edge = curr_edge->next;
        }
        i++;
    }
}   

void TSP_cmd(pnode head) {
    return;
}
