/*
 * Author: Carlos Galo
 * Created On: 4/30/2020
 * Program: SPAN
 * Class: Non-Linear Data Structures
 * File: MinSpanTree.h
 *  - Header file for the MinSpanTree class
 *  - This class will handle most of the logic, utilizes classes:
 *      -- LinkedList to save the graph's edges and vertices
 *      -- MinHeap to save the graph's data into a queue and perform Kruskal & Prism algorithms
 * */

#ifndef SPAN_MINSPANTREE_H
#define SPAN_MINSPANTREE_H

#include <iostream>
#include <fstream>                                          //To open and read from files
#include "../LinkedList/LinkedList.h"                       //LinkedList class
#include "../MinHeap/MinHeap.h"                             //MinHeap class

class MinSpanTree {
private:
    struct Node
    {
        //Will use this struct to save an array of characters
        char data [2] = {};                                     //Data for this node, char array of size 2
        Node()                                                  //Basic constructor
        {
            for (char & i : this->data) i = '\0';               //Leave the data array of this node empty
        }
        explicit Node(char data[])                              //Constructor given a char array
        {
            strcpy(this->data, data);                           //Copy the given data to this node's data
        }   //End of explicit Node constructor
    };  //End of struct Node
    struct set
    {
        //set struct is utilized for the Kruskal algorithm, this is used in method: KruskalMST()
        int *parent, *rank;
        int num;
        set(int num)                                            //Constructor for set, requires an int in parameter
        {
            this->num       = num;                              //Set the num to the given one
            this->parent    = new int [num + 1];                //Set the size of parent array to num + 1
            this->rank      = new int [num + 1];                //Set the size of rank array to num + 1
            for (int i = 0; i <= num; i++)                      //Loop through all the ranks
                rank[i] = 0, parent[i] = i;                     //Set all ranks to 0 and parents to point to themselves
        }
        ~set()                                                  //Destructor for set
        {
            //Objective: Perform garbage collection
            for (int i = 0 ; i < num + 1; i++)                  //Loop through the arrays of parents and rank
                rank[i] = parent[i] = 0;                        //Set all elements back to 0
            delete parent;                                      //Delete the parent array
            delete rank;                                        //Delete the rank array
            num = 0;                                            //Set 'num' back to 0
        }   //End of destructor
        int findSet(int vertex)
        {
            /* findSet private method, parameter(s): int <vertex>
             * Objective: looks through the sets it is maintaining, and determines which set/parent 'x' belongs to
             * - This is a recursive method
             * */

            if (parent[vertex] != vertex)
                parent[vertex] = findSet(parent[vertex]);
            return parent[vertex];                              //Return the parent element located in index vertex
        }   //End of findSet method

        void Union(int u, int v)
        {
            /* Union private method, parameter(s): int array <set>, int <index1>, int <index2>
            * Objective: merges two sets (one containing u and the other containing v) into one set (u)
            * */

            u = findSet(u);                                     //Find the set for 'u'
            v = findSet(v);                                     //Find the set for 'v'

            if (rank[u] > rank[v])                              //If the rank of 'u' is higher than 'v'
                parent[v] = u;                                  //Make 'u' the parent of 'v'
            else                                                //Else rank of 'u' is less than 'v'
                parent[u] = v;                                  //Make 'v' the parent of 'u'
            if (rank[u] == rank[v])                             //If both have the same rank
                rank[v]++;                                      //Increase the rank of v by 1
        }   //End of Union method
    };  //End of struct set

    //Variables
    LinkedList* graph;                                      //Will connect vertices pairs and their weights as a graph
    int totVertices;                                        //Total vertices/nodes in the spanning tree
    Node** vertices;                                        //Keep track of all the vertices given in the input file
    int ** graph2D;                                         //Graphed saved in a 2D array
    //Methods
    MinHeap* buildQueue();                                  //Create a queue utilizing the data in the LL 'graph'
    void insertToGraph(int matrixLine[], int nodeIndex);    //Gets the vertices and edge weight, to insert into graph
    MinHeap* KruskalMST(MinHeap* queue);                    //Perform Kruskal's Algorithm and return set of vertices
    MinHeap* PrimMST();                                     //Perform Prim's Algorithm and return queue of vertices
    int getMinIndex(int arr[], bool set[]);                 //Return the index of the smallest value in the array
    void printMST(MinHeap* MST);                            //Print the results of the MinHeap

public:
    MinSpanTree(char* file);                                //Constructor that requires a char array to point to file
    ~MinSpanTree();                                         //Destructor, for garbage collection

    //Methods
    void getKruskalMSP();                                   //Get and output the results of Kruskal's algorithm
    void getPrimMSP();                                      //Get and output the results of Prim's algorithm
};  //End of MinSpanTree class


#endif //SPAN_MINSPANTREE_H