#include <stdio.h>
#include "edges.h"

pnode get_node(pnode *head, int x){
    // Base case
    if (head == NULL)
        return -1;
     
    // If key is present in current node, return true
    if ((*head)->node_num == x)
        
 
    // Recur for remaining list
    return search((*head)->next, x);
}
}



