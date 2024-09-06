General Roadmap

- [X] Finish lengthLexCompare

- [X] Write constructor(s) for vertex and edges

- [X] Write constructor for paths

- [X] Printing function for a path (and vertex/edge) (as well as  - two versions: one just prints ids of edges/vertices, one that uses the labels

- [X] Decide how to/implement storage of the adjacency matrix of the graph.

- [X] Get the constructor(s) for PathAlgebra working - in particular decide how to read in the adjacency matrix of a graph, store vertex labels, edge labels

- [X] Write the path multiplication code - should be several cases depending on whether the left/right path is a vertex or not.

- [X] Refactor multiplyPaths into a part that does multiplication and one that checks if it already exists

- [X] Implement adding/looking up paths to the path table (think about when to actually add paths to the table)

- [X] Write a version of path multiplication that performs the lookup as well.

- [X] Define function which creates a PAElement out of a path.

- [X] Define function which takes a list of indices and a list of coefficients and creates a PAElement

- [ ] Printing function for PAElements

- [ ] Implement arithmetic on PAElements (add, subtract, multiply)

- [ ] Implement FLINT aritmetic for coefficients (integers mod n, n prime)