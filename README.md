# SPAN
SPAN is a [Console App](https://en.wikipedia.org/wiki/Console_application) created with [CLion IDE](https://www.jetbrains.com/clion/) using C++.
 
### Objective
The objective of this project is to return the [Minimum Spanning Tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree) given a graph in a text file.
 
Utilized and returned two different results using the following algorithms:
- [Kruskal's Algorithm](#kruskal-algorithm)
- [Prim's Algorithm](#prim-algorithm)
 
#### Kruskal Algorithm
Kruskal Algorithm is a _greedy algorithm_, in which the 'greedy' choice is to pick the smallest weight edge, that does not causee a cycle.
##### How it works
1. Sort all edges, in non-decreasing order, by their weight
2. Pick the smallest edge, if the edge is not a cycle then add this edge
3. Repeat step #2 until we reach (V-1) edges in the spanning tree
 
##### Demo
![KruskalDemo](https://upload.wikimedia.org/wikipedia/commons/b/bb/KruskalDemo.gif "Kruskal Demo")*
 
#### Prim Algorithm
Prim's Algorithm is a _greedy algorithm_, starts by creating an empty spanning tree
 
##### How it works
1. Choose a random vertex
2. Find all the edges that connect the tree to new vertices, find the minimum and add it to the tree
3. Keep repeating step #2 until we get a minimum spanning tree
 
 
##### Demo
![Prims Demo](https://upload.wikimedia.org/wikipedia/commons/9/9b/PrimAlgDemo.gif "Prim Demo")*