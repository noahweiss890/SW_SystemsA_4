# sw_systems_hw4

This assignment focuses on pointers and dynamic memory usage, including allocating and freeing memory. 

Our program receives input and can build a graph, add nodes to the graph (with its edges), delete nodes from the graph, find the shortest path between two nodes, and find the shortest path which visits mutiple given nodes. 

In the program, a graph is made of structs nodes and edges which are stored in linked lists, meaning memory for the edges and nodes are dynamically allocated and freed when deleted. 

When building a graph, the program deletes the previous graph if it exists and creates empty nodes and then fills them with information on edge ndpoints and edge weights. 

When inserting or creating a node, the memory space for the nodes and edges are allocated using malloc. 

When deleting a node or the whole graph, the nodes and edges are deallocated using free.

The program uses Dijkstra's algorithm, and node's parameters priority and visited in order to find the shortest path between two nodes. The algorithm finds the node with the the smallest priority integer and relaxes its edges.  

TSP:
