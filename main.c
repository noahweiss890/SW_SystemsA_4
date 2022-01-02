#include <stdio.h>
#include <string.h>
#include "algo.h"

int main() {
    pnode head = NULL;
    char chosen_option;
    chosen_option = getchar();

    while(chosen_option == 'A' || chosen_option == 'B' || chosen_option == 'D' || chosen_option == 'S' || chosen_option == 'T') {
        getchar();
        if(chosen_option == 'A') {
            deleteGraph_cmd(&head);
            head = NULL;
            build_graph_cmd(&head);
        }
        else if(chosen_option == 'B') {
            insert_node_cmd(&head);
        }
        else if(chosen_option == 'D') {
            delete_node_cmd(&head);
        }
        else if(chosen_option == 'S') {
            shortsPath_cmd(head);
        }
        else if(chosen_option == 'T') {
            TSP_cmd(head);
        }
        chosen_option = getchar();
    }
    deleteGraph_cmd(&head);
    // printf("\nhead: %p", head);
    return 0;
}