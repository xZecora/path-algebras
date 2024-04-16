General Roadmap

1. Finish lengthLexCompare
2. Write constructor(s) for vertex and edge
3. Write constructor for paths
4. Printing function for a path (and vertex/edge) (as well as  - two versions: one just prints ids of edges/vertices, one that uses the labels
5. Decide how to/implement storage of the adjacency matrix of the graph.
6. Get the constructor(s) for PathAlgebra working - in particular decide how to read in the adjacency matrix
   of a graph, store vertex labels, edge labels
7. Write the path multiplication code - should be several cases depending on whether the left/right
   path is a vertex or not.
8. Implement adding/looking up paths to the path table (think about when to actually add paths to the table)
9. Write a version of path multiplication that performs the lookup as well.
10. Define function which creates a PAElement out of a path.
11. Define function which takes a list of indices and a list of coefficients and creates a PAElement
12. Implement arithmetic on PAElements (add, subtract, multiply)