#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "nodes.h"

pnode get_node(pnode *head, int id) {
    if(head == NULL) {
        return NULL;
    }
    pnode curr = *head;
    while(curr != NULL && curr->node_num != id) {
        curr = curr->next;
    }
    return curr;
}

void create_node(pnode *head) {
    int new_node_id = (int)getchar() - '0';
    getchar();
    pnode new_node = get_node(head, new_node_id);
    new_node->edges = NULL;
    pedge prev = NULL;
    char dest = getchar();
    getchar();
    while(isdigit(dest)) {
        int weight = (int)getchar() - '0';
        getchar();
        pedge new_edge = (pedge)malloc(sizeof(edge));
        if(new_node == NULL) {
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
}

void add_node(pnode *head, pnode new_node) {
    printf("before head: %p\n", head);
    if(head == NULL) {
        // printf("head: %p\n", head);
        head = new_node;
        printf("new head: %p\n", head);
        // exit(0);
    }
    else {
        pnode curr = *head;
        while(curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
}
