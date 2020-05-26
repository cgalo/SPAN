# SPAN
SPAN is a [CLI App](https://learn.co/lessons/intro-to-cli-applications) developed in C++ utilizing [CLion IDE](https://www.jetbrains.com/clion/).
 
### Objective
The objective of this project is to return the [Minimum Spanning Tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree) given a graph in a text file.
 
Utilized and returned two different results using the following algorithms:
- [Kruskal's Algorithm](#kruskal-algorithm)
- [Prim's Algorithm](#prim-algorithm)

### Overview
For this project, the Input/Ouput (I/O) is handled within the [*main file*](main.cpp). This program only requires one argument in the CLI, this should be a text file that contain a graph. For examples of input files check [here.](Test-Files)The main file passes the CLI argument to the [MinSpanTree](MinSpanTree), which handles the logic for the rest of the project.

### How Does This Program Work?
After checking that the user provided one argument in the CLI, the main file will do the following:
1. Create a new object from the class (MinSpanTree)[MinSpanTree], _MST_ for short, by passing the file location provided by the user.
2. Call the public method, _getKruskalMSP()_, from the _MST_ object, which will output the results for the Kruskal's Algorithm for the given file/graph.
3. Output a line of dashes (-) to split the results for the next algorithm
4. Call the public method, _getPrimMSP()_, from the _MST_ object, which will output the results for the Prim's Algorithm for the same given file/graph.

 
#### Kruskal Algorithm
Kruskal Algorithm is a _greedy algorithm_, in which the _greedy_ choice is to pick the smallest weight edge, that does not causee a cycle.
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