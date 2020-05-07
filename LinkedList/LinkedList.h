/*
 * Author: Carlos Galo
 * Created On: 4/30/2020
 * Program: SPAN
 * Class: Non-Linear Data Structures
 * File: LinkedList.h
 *  - Header file for the LinkedList class
 *  - LinkedList class is used to save the data from file as a graph
 *  - This is a single LL
 * */

#ifndef SPAN_LINKEDLIST_H
#define SPAN_LINKEDLIST_H

#include <iostream>


class LinkedList {
private:
    struct Node
    {
        /* Each node contains the weight of the edge and the index of two vertices
         * We'll store the index location of the vertices, which are the keys in the MinSpanTree class
         * */

        //Variables
        int index1, index2;                             //Index location for two vertices
        int weight;                                     //Weight for this edge
        Node* next;                                     //Pointer to the next edge/node in the LL
        //Constructors
        Node()                                          //Basic constructor for Node
        {
            index1 = index2 = weight = 0;               //Set index1, index2, and weight to 0
            this->next      = nullptr;                  //Set pointer to nil
        }   //End of basic Node constructor
        explicit Node (int index1, int index2, int weight)  //Constructor given index1, index2, and weight
        {
            this->index1    = index1;                   //Set the index1 from the given index1
            this->index2    = index2;                   //Set the index2 from the given index2
            this->weight    = weight;                   //Set weight from the give weight
            this->next      = nullptr;                  //Set next node pointer to nil
        }   //End of explicit Node constructor
    };  //End of constructor
    Node* head;                                         //Top Node in the LL
    int totNodes;                                       //Total Nodes inserted
public:
    LinkedList();                                       //Basic constructor
    ~LinkedList();                                      //Destructor for garbage collection

    //Methods
    void insert(int index1, int index2, int weight);    //Create a new node/edge and insert it into the LL
    bool isEmpty();                                     //Check if the LL is empty
    int getTotNodes();                                  //Return the total Nodes inserted into the graph
    void popFront();                                    //Pop/remove the current head/top of the LL
    void print();                                       //Print every nodes' data in the LL
    int *getTopIndexes();                               //Return array of the two int indexes in the head node
    LinkedList* cloneLL(LinkedList* LL);                //Return an exact copy oof the given LL
};


#endif //SPAN_LINKEDLIST_H
