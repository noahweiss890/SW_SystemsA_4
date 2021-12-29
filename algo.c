#include <stdio.h>
#include "nodes.h"
#include <ctype.h>

void build_graph_cmd(pnode *head)
{
    int v = (int)getchar();
    getchar(); //skip space
    for (int i = 0; i < v; i++)
    {
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

void insert_node_cmd(pnode *head)
{
    int new_node_id = (int)getchar();
    getchar();
    pnode new_node = (pnode)malloc(sizeof(node));
    new_node->node_num = new_node_id;
    new_node->next = NULL;
    pedge curr = NULL;
    dest = getchar();
    getchar();
    while (isdigit(dest))
    {
        int weight = (int)getchar();
        getchar();
        pedge new_edge = (pedge)malloc(sizeof(edge));
    }
    if (get_node(head, new_node_id) == NULL)
    {
    }
}

void delete_node_cmd(pnode *head)
{
    pnode del_n = get_node(head, (int)getchar());
    getchar(); //skip spaces
    pnode curr = head;
    pnode temp = NULL; //used to update the linked list
    int del_id = 0;
    pedge del_e = NULL;
    while (curr->next != NULL)
    { //go through all nodes in graph
        if (curr->next == del_n)
        { //this node's next is the node we are deleting so we need to update the linked list
            temp = curr->next;
            curr->next = temp->next;
        }
        //current node's next is not the node to be deleted, must go through edges to see if its an endpoint
        pedge currEdgeHead = curr->next->edges; //edges of the node
        pedge tempEdge = NULL;
        int del_w = 0;
        pnode del_end = NULL;
        while (currEdgeHead->next != NULL)
        {
            if (currEdgeHead->next->endpoint == del_n)
            { //need to delete this edge
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
    while (edgeHead->next != NULL)
    { 
        tempEdge = edgeHead->next;
        edgeHead->next = tempEdge->next;
        free(tempEdge);
    }
    free(del_n); //delete_node(del_n);
}

void printGraph_cmd(pnode head) {

}

void deleteGraph_cmd(pnode *head) {

}

void shortsPath_cmd(pnode head) {

}

void TSP_cmd(pnode head) {

}
