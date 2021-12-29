#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "algo.h"

int main() {
    
    pnode *head;
    char chosen_option;
    chosen_option = getchar();
    getchar();

    while(chosen_option != '\n') {
        if(chosen_option == 'A') {
            build_graph_cmd(&head);
        }
        else if(chosen_option == 'B') {
            insert_node_cmd(&head);
        }
        else if(chosen_option == 'D') {
            delete_node_cmd(&head);
        }
        else if(chosen_option == 'S') {
            shortsPath_cmd(&head);
        }
        else if(chosen_option == 'T') {
            TSP_cmd(&head);
        }
        chosen_option = getchar();
        getchar();
    }
    deleteGraph_cmd(head);
    return 0;
}