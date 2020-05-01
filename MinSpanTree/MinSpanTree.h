/*
 * Author: Carlos Galo
 * Created On: 4/30/2020
 * Program: SPAN
 * Class: Non-Linear Data Structures
 * File: MinSpanTree.h
 *  - Header file for the MinSpanTree class
 *  - MinSpanTre
 * */

#ifndef SPAN_MINSPANTREE_H
#define SPAN_MINSPANTREE_H

#include <fstream>                      //To open and read from files
#include <iostream>                     //For basic cout and cin
#include "../LinkedList/LinkedList.h"   //LinkedList class
#include "../MinHeap/MinHeap.h"         //MinHeap class

class MinSpanTree {
private:
    //Variables
    LinkedList* graph;              //Will connect vertices pairs and their weights as a graph
    int totVertices;                //Total vertices/nodes in the spanning tree

    //Methods
    MinHeap* graphToQueue();        //Create a queue utilizing the data in the graph (LL)



public:
    MinSpanTree(char* file);        //Constructor
    ~MinSpanTree();                 //Destructor

    //Methods
    void getKruskalMSP();
    void getPrimMSP();


};


#endif //SPAN_MINSPANTREE_H
