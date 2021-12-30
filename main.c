#include <stdio.h>
#include <string.h>
#include "algo.h"

int main() {
    pnode head = NULL;
    char chosen_option;
    chosen_option = getchar();

    while(chosen_option != '\n' && chosen_option != EOF) {
        getchar();
        if(chosen_option == 'A') {
            // deleteGraph_cmd(&head);
            printf("\nhead in %p", head);
            build_graph_cmd(&head);
            printf("\nhead in %p", head);
            printGraph_cmd(&head);
            deleteGraph_cmd(&head);
            head = NULL;
            printGraph_cmd(&head);
            // head = NULL;
            printf("\nhead in %p", head);
            return 0;
        }
        else if(chosen_option == 'B') {
            insert_node_cmd(&head);
            // printGraph_cmd(&head);
            // return 0;
            // printf("\nDONEZA");
            // exit(0);
        }
        else if(chosen_option == 'D') {
            // delete_node_cmd(&head);
        }
        else if(chosen_option == 'S') {
            // shortsPath_cmd(&head);
        }
        else {
            return 0;
        }
        chosen_option = getchar();
        printGraph_cmd(&head);
    }
    deleteGraph_cmd(&head);
    printf("\nhead: %p", head);
    return 0;
}