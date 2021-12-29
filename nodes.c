#include <stdio.h>
#include "nodes.h"

pnode get_node(pnode *head, int x) {
    pnode node;
    // Base case
    if (head == NULL)
    return NULL;
    // If key is present in current node, return true
    if ((*head)->node_num == x)
        return *head;
    // Recur for remaining list
    return get_node((*head)->next, x);
}

pnode create_node(pnode *head) {
    int new_node_id = (int)getchar();
    getchar();
    pnode new_node = (pnode)malloc(sizeof(node));
    if(new_node == NULL) {
        printf("Not enough memory!");
        exit(0);
    }
    new_node->node_num = new_node_id;
    new_node->edges = NULL;
    pedge prev = NULL;
    char dest = getchar();
    getchar();
    while(isdigit(dest)) {
        int weight = (int)getchar();
        getchar();
        pedge new_edge = (pedge)malloc(sizeof(edge));
        if(new_node == NULL) {
            printf("Not enough memory!");
            exit(0);
        }
        new_edge->endpoint = get_node(head, (int)getchar());
        getchar();
        new_edge->weight = (int)getchar();
        getchar();
        if(prev == NULL) {
            new_node->edges = new_edge;
            prev = new_node->edges;
        }
        else {
            prev->next = new_edge;
        }
        prev = prev->next;
        dest = getchar();
        getchar();
    }
    ungetc(dest, stdin);
    return new_node;
}

void add_node(pnode *head, pnode new_node) {
    pnode curr = head;
    while(curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_node;
}
