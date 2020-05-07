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
        char data [2] = {};                         //Data for this node, char array of size 2
        Node()                                      //Basic constructor
        {
            for (char & i : this->data) i = '\0';   //Leave the data array of this node empty
        }
        explicit Node(char data[])                  //Constructor given a char array
        {
            strcpy(this->data, data);               //Copy the given data to this node's data
        }   //End of explicit Node constructor
    };  //End of struct Node

    //Variables
    LinkedList* graph;                                      //Will connect vertices pairs and their weights as a graph
    int totVertices;                                        //Total vertices/nodes in the spanning tree
    Node** vertices;                                        //Keep track of all the vertices given in the input file

    //Methods
    MinHeap* graphToQueue();                                //Create a queue utilizing the data in the graph (LL)
    void insertToGraph(int matrixLine[], int nodeIndex);    //Gets the vertices and edge weight, to insert into graph


public:
    MinSpanTree(char* file);                                //Constructor that requires a char array to point to file
    ~MinSpanTree();                                         //Destructor, for garbage collection

    //Methods
    void getKruskalMSP();                                   //Get and output the results of Kruskal's algorithm
    void getPrimMSP();                                      //Get and output the results of Prim's algorithm

};  //End of MinSpanTree class


#endif //SPAN_MINSPANTREE_H
