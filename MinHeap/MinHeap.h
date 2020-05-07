/*
 * Author: Carlos Galo
 * Created On: 4/30/2020
 * Program: SPAN
 * Class: Non-Linear Data Structures
 * File: MinHeap.h
 *  - Header file for the MinHeap class
 *  - MinHeap will be used a queue for the Kruskal & Prim algorithms
 *  - Called in the MinSpanTree class
 * */

#ifndef SPAN_MINHEAP_H
#define SPAN_MINHEAP_H

#include <iostream>

class MinHeap {
private:
    struct Node {
        /* Each node contains the weight of the edge and the index of two vertices
         * We'll store the index location of the vertices, which are the keys in the MinSpanTree class
         * */

        //Variables
        int index1, index2;                                 //Index location for two vertices
        int weight;                                         //Weight for this edge
        //Constructors
        Node()                                              //Basic constructor for Node
        {
            index1 = index2 = weight = 0;                   //Set index1, index2, and weight to 0
        }   //End of basic Node constructor
        explicit Node(int index1, int index2, int weight)   //Constructor given index1, index2, and weight
        {
            this->index1 = index1;                          //Set the index1 from the given index1
            this->index2 = index2;                          //Set the index2 from the given index2
            this->weight = weight;                          //Set weight from the give weight
        }   //End of explicit Node constructor
    };  //End of struct Node

    //Variables
    Node** array;                                       //Array of nodes
    int maxSize;                                        //Max size of the heap/array
    int currentSize;                                    //Current size of the heap/array

    //Methods
    void insert(Node* insertNode);                      //Order the heap to maintain min-heap structure and insert node
    void swap(Node**A , Node** B);                      //Swap locations of the nodes in the heap
    void remove();                                      //Remove the first/min node in the heap/array
    void heapify(int index);                            //Maintain heap order after removing a node

public:
    MinHeap(int maxSize);                               //Constructor, requires a maxSize in the parameter
    ~MinHeap();                                         //Destructor, for garbage collection

    //Methods
    int getCurrentSize();                               //Return the currentSize value
    int getMaxSize();                                   //Return the maxSize value
    bool isEmpty();                                     //Checks if the size of the heap is 0, if it is return true
    void push(int index1, int index2, int weight);      //Create new node with parameters and pass it to insert method
    void popMin();                                      //Call the remove method to delete the first node in the heap
    void printHeap();                                   //Print the heap array
    int* getMinIndexes();                               //Return the two indexes inside the first node in the heap array
    int getMinWeight();                                 //Return the weight of the first node in the heap array
};


#endif //SPAN_MINHEAP_H
