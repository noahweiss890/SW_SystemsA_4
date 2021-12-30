#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "nodes.h"

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

void delete_node_cmd(pnode *head) {
    pnode del_n = get_node(head, (int)getchar() - '0');
    getchar(); //skip spaces
    pnode curr = *head;
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
    pnode curr_node = *head;
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
    printf("\nhead in %p", head);
}

void shortsPath_cmd(pnode head) {
    return;
}

void TSP_cmd(pnode head) {
    return;
}
