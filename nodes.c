#include <stdio.h>
 #include "edges.h"

 pnode get_node(pnode *head, int x) {
     pnode node;
     // Base case
     if (head == NULL)
        return NULL;
     
    // If key is present in current node, return true
    if ((*head)->node_num == x)
        return *head;
 
    // Recur for remaining list
    return search((*head)->next, x);
}