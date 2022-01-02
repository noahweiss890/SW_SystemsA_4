#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "nodes.h"
#include "algo.h"

//builds a graph of nodes and edges
void build_graph_cmd(pnode *head) {
    int v = (int)getchar() - '0'; //receive amount of nodes from buffer
    getchar(); //skip space
    if(v == 0) { //if no nodes, return
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
    //create v amount of empty nodes (v was received from buffer)
    for (int i = 1; i < v; i++) {
        pnode new_node = (pnode)malloc(sizeof(node));
        if(new_node == NULL) {
            printf("Not enough memory!");
            exit(0);
        }
        //assign id to be i and next to be null
        new_node->node_num = i;
        new_node->next = NULL;
        curr->next = new_node;

        curr = curr->next; //increment curr
    }
    //now get n value v amount of times
    for (int i = 0; i < v; i++) {
        char x = getchar();
        getchar(); //skip space
        while (x == 'n') {
            create_node(head); //creates node pointer to be added to graph
            x = getchar();
            getchar(); //skip space
        }
        //if x is not 'n', put back in buffer
        ungetc(' ', stdin);
        ungetc(x, stdin);
    }
}

void insert_node_cmd(pnode *head) { // inserts a new node into the graph
    int id = (int)getchar() - '0';
    getchar();
    pnode old_node = get_node(head, id); // get the node with that id if it exists
    if(old_node == NULL) { // does a node with that id already exist, if so, create new node and assign the parameters
        pnode new_node = (pnode)malloc(sizeof(node)); 
        if(new_node == NULL) {
            printf("Not enough memory!");
            exit(0);
        } //assign new_node id and edges and next to be null
        new_node->node_num = id;
        new_node->edges = NULL;
        new_node->next = NULL;
        pedge prev;
        char dest = getchar();
        getchar();
        while(isdigit(dest)) {
            //get weight from buffer
            int weight = (int)getchar() - '0';
            getchar();
            pedge new_edge = (pedge)malloc(sizeof(edge));
            if(new_edge == NULL) {
                printf("Not enough memory!");
                exit(0);
            }
             //assign parameters
            new_edge->endpoint = get_node(head, (int)dest - '0');
            new_edge->weight = weight;
            //if first edge to link, make it the head 
            if(new_node->edges == NULL) {
                new_node->edges = new_edge;
                prev = new_edge;
            }
            else {
                //link this edge to the end of the linked list
                prev->next = new_edge;
                prev = prev->next;
            }
            dest = getchar(); //get dest from buffer
            getchar();
        }
        // puts space and char back in buffer because its on to new command
        ungetc(' ', stdin);
        ungetc(dest, stdin);
        //if linked list is empty, make new node the head
        if(*head == NULL) {
            *head = new_node;
        }
        //link the new node to the linked list of nodes
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
        //free the edges of the node so they can be replaced
        while(curr_edge != NULL) {
            next_edge = curr_edge->next;
            free(curr_edge);
            curr_edge = next_edge;
        }
        
        old_node->edges = NULL;
        pedge prev = NULL;
        char dest = getchar();
        getchar();
        while(isdigit(dest)) { //as long as the input received is a digit
            int weight = (int)getchar() - '0'; //get weight from buffer
            getchar(); //skip spaces
            pedge new_edge = (pedge)malloc(sizeof(edge));
            if(new_edge == NULL) {
                printf("Not enough memory!");
                exit(0);
            }
            //assign parameters
            new_edge->endpoint = get_node(head, (int)dest - '0');
            new_edge->weight = weight;
            new_edge->next = NULL;
            if(old_node->edges == NULL) { //old node had no edges
                old_node->edges = new_edge; //make new edge head of the list 
                prev = new_edge;
            }
            else { //link to end of linked list
                prev->next = new_edge;
                prev = prev->next;
            }
            dest = getchar(); //receive dest from buffer
            getchar(); //skip spaces
        }
        //if value received is not a digit, return it to buffer
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
}

void printGraph_cmd(pnode head) { // prints the graph
    pnode curr_node = head;
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
            if(curr->priority <= min_p && curr->visited == 0) {
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

//finds the shortest path distance that visists specific nodes on the graph
void TSP_cmd(pnode head) {
    int size = (int)getchar() - '0'; //get size of "list" of cities from buffer
    getchar(); //skip spaces
    int cities[size]; //declare size of list of nodes to visit
    for(int i = 0; i < size; i++) { //loop size amount of times im order to add the nodes to be visited to cities
        cities[i] = (int)getchar() - '0';
        getchar(); //skip spaces
    }
    int min_weight = INT_MAX; //originally declare min_weight to be the highest it can be
    for(int i = 0; i < size; i++) { //runs through every option of starter nodes
        int new_cities[size-1];
        int j = 0;
        for(int k = 0; k < size; k++) {
            if(i != k) { //j moves forward only when something is inserted, meaning i != k
                new_cities[j++] = cities[k]; //copy over to new array
            }
        }
        int weight = tsp_helper(head, cities[i], new_cities, size-1);
        if(weight == -1) { //no path exists
            continue;
        }
        if(weight < min_weight) { //we have found a smaller weight so update min_weight
            min_weight = weight;
        }
    }
    if(min_weight != INT_MAX) { //if min_weight was changed throughout the function, that is the shortest path for TSP
        printf("TSP shortest path: %d \n", min_weight);
    }
    else { //if min_weight was not changed, no such path exists that visits each node in cities
        printf("TSP shortest path: -1 \n");
    }
}

//TSP helper function that ginds the shortest path between two nodes. similar to shortest_path_cmd
int get_shortest_path_dist(pnode head, int src, int dest) {
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
            if(curr->priority <= min_p && curr->visited == 0) {
                min_p = curr->priority;
                smallest = curr;
            }
            curr = curr->next;
        }
        //update tag visited 
        smallest->visited = 1;
        //if the smallest priority is int_max, then there is no path betweent the src and dest node
        if(smallest->priority == INT_MAX){
            return -1;
        }
        //if the node smallest priority is the dest node then we've found our shortest path 
        if(smallest->node_num == dest){
            return smallest->priority;
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
    return -1;
}

//TSP recursive helper function
int tsp_helper(pnode head, int src, int *cities, int size) {
    if(size == 0) { //base case, no more options to check
        return 0;
    }
    int min_weight = INT_MAX;
    //now checking all options with specific starter node
    for(int i = 0; i < size; i++) {
        int new_cities[size-1];
        int j = 0;
        for(int k = 0; k < size; k++) {
            if(i != k) {
                new_cities[j++] = cities[k];
            }
        }
        int edge_weight = get_shortest_path_dist(head, src, cities[i]);
        if(edge_weight == -1) { //no path between src and dest, go to next iteration
            continue;
        }
        int res = tsp_helper(head, cities[i], new_cities, size-1); //call recursively to find shortest path visiting each node in new_cities
        if(res == -1) {
            continue;
        }
        int weight = edge_weight + res; //distance from starter node to first node in new_cities + cost of path visiting each node in new_cities
        if(weight < min_weight) { //found a smaller cost
            min_weight = weight; //update weight
        }
    }
    //min_weight was not changed so no path exists that covers every node in new_cities
    if(min_weight == INT_MAX) {
        return -1;
    }
    return min_weight; //return TSP shortes path
}