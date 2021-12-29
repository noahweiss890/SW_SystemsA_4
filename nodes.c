#include <stdio.h>
#include <nodes.h>

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

void add_node(pnode *head){
    return NULL;
}
