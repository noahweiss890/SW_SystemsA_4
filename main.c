#include <stdio.h>
#include <string.h>
#include "algo.h"

int main() {
    pnode head = NULL;
    char chosen_option;
    chosen_option = getchar(); // get the first option from input

    while(chosen_option == 'A' || chosen_option == 'B' || chosen_option == 'D' || chosen_option == 'S' || chosen_option == 'T') {
        getchar();
        if(chosen_option == 'A') { // option for creating new graph
            deleteGraph_cmd(&head); // first we need to delete the current graph
            head = NULL; // setting the head back to null
            build_graph_cmd(&head); // create new graph
        }
        else if(chosen_option == 'B') { // option for adding a node or changing an existing one
            insert_node_cmd(&head);
        }
        else if(chosen_option == 'D') { // option for deleting a node
            delete_node_cmd(&head);
        }
        else if(chosen_option == 'S') { // option for finding the weight of the shortest path between two nodes
            shortsPath_cmd(head);
        }
        else if(chosen_option == 'T') { // option for finding the shortest path weight that travels between all of the given nodes (TSP)
            TSP_cmd(head);
        }
        chosen_option = getchar(); // input the next option
    }
    deleteGraph_cmd(&head); // before exiting the program deallocate all of the memory in the graph (nodes and edges)
    return 0;
}