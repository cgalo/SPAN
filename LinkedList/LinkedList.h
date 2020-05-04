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

#include <iostream> //For strcpy


class LinkedList {
private:
    struct Node
    {
        //Each Node contains a pair of vertices (char array of max two characters), a weight, and pointer to another edge
        char* A, *B;    //Vertices of this edge/node
        int weight;     //Weight for this edge
        Node* next;     //Pointer to the next edge/node in the LL

        Node()          //Basic constructor for Node
        {
            for (int i = 0; i < 1; i++)     //Set both arrays, of max element of 2
                A[i] = B[i] = '\0';         //Set all characters in the arrays to empty chars
            this->weight    = 0;            //Set the weight to 0
            this->next      = nullptr;      //Set pointer to nil
        }   //End of basic Node constructor
        explicit Node (char* A, char* B, int weight)
        {
            this->A         = A;            //Set the given A as this node's A
            this->B         = B;            //Set the given B as this node's B
            this->weight    = weight;       //Set weight
            this->next      = nullptr;      //Set next node pointer to null
        }   //End of explicit Node constructor
    };
    Node* head;                 //Top Node in the LL
    int totNodes;               //Total Nodes inserted
public:
    LinkedList();               //Basic constructor
    ~LinkedList();              //Destructor for garbage collection

    //Methods
    void insert(char* a, char * b, int weight);
    bool isEmpty();             //Check if the LL is empty
    int getTotNodes();          //Return the total Nodes inserted into the graph
    void popFront();            //Pop/remove the current head/top of the LL
    char** getTopVertices();    //Return the chars(A & B) of the current head


};


#endif //SPAN_LINKEDLIST_H
