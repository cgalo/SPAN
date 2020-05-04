//
// Created by Carlos Galo on 4/30/20.
//

#include "LinkedList.h"

LinkedList::LinkedList()
{
    /* Constructor for the LinkedList class, parameter(s): None
     * Objective: Initialize all variables as null/0
     * */
    
    this->head      = nullptr;   //Set the head as null
    this->totNodes  = 0;
}   //End of constructor

LinkedList::~LinkedList() 
{
    /* Destructor for LinkedList object, parameter(s): None
     * Objective: Set all variables back to null and delete any Nodes in the LL
     * */
    
    this->totNodes  = 0;
    
    //Now delete all Nodes in the LL
    Node* currentNode = head;           //Start from the head of the LL
    while (currentNode != nullptr)      //While there are still nodes in the LL
    {
        Node* deleteNode = currentNode; //Remember this Node before moving pointers
        currentNode = currentNode->next;//Move the currentNode to the next one in the LL
        delete deleteNode;              //Delete the Node we just saw
    }   //End of while-loop
    //We get here by looping and deleting all Nodes in the LL
    this->head  = nullptr;              //Set the head of the LL back to null
}   //End of destructor

bool LinkedList::isEmpty() 
{
    /* isEmpty public method, parameter(s): None
     * Objective: Check if the LL is empty
     *  - If its empty return true, else return false
     * */
    
    return head == nullptr;
}   //End of isEmpty method

void LinkedList::insert(char *a, char *b, int weight)
{
    /* insert public method, parameter(s): char array <a>, char array <b>, int <weight>
     * Objective: Get the parameters, create a new Node, and append it in the LL
     * */

    Node* insertNode = new Node(a, b, weight);  //Create a new Node to insert in the LL
    //Base case
    if (head == nullptr)                        //If the LL is empty
        head = insertNode;                      //Insert the Node as head of the LL
    else                                        //Else the LL is not empty
    {
        Node* currentNode   = head;             //Initiate a node to start from the head of the LL
        Node* pastNode      = nullptr;          //Create a node to remember the last node we saw
        while (currentNode != nullptr)          //While we don't fall of the LL
        {
            pastNode = currentNode;             //Remember the currentNode before moving to the next node in the LL
            currentNode = currentNode->next;    //Move the currentNode pointer to the next node in the LL
        }   //End of while-loop
        //We get here after falling off the LL, we insert the new node as 'next' for the pastNode
        pastNode->next = insertNode;            //Connect the pastNode to the new insertNode
    }   //End of else, if the LL is not empty
    this->totNodes++;                           //Increase the total Nodes inserted into the LL
}   //End of insert method

void LinkedList::popFront()
{
    /* popFront public method, parameter(s): None
     * Objective: Remove the first element in the LL
     *  - If LL is empty then output error
     *  - Else set the head's next node as new head and perform garbage collection/delete the old head
     * */

    if (isEmpty())                                          //If the LL is empty
        std::cout << "LL is already empty" << std::endl;    //Output error
    else                                                    //Else the LL is not empty
    {
        Node* popNode = head;                               //Remember the head before setting a new head
        head = head->next;                                  //Set the head's next Node as new head of the LL
        delete popNode;                                     //Delete the old head, perform garbage collection
    }   //End of else
}   //End of popFront method

int LinkedList::getTotNodes()
{
    /* getTotNodes, parameter(s): None
     * Objective: Return the variable totNodes
     * */

    return totNodes;
}   //End of getTotNodes method

char ** LinkedList::getTopVertices()
{
    /* getTopVertices public method, parameter(s): None
     * Objective: return char array with the current head's chars (A & B)
     * Notes:
     *  -If LL is empty then return nullptr
     *  -Else return the head's chars
     * */

    if (isEmpty())                  //If the LL is empty
        return nullptr;             //Return a null ptr
    else                            //Else the LL is not empty
    {
        char *A = head->A;          //Get and save the head's char A
        char* B = head->B;          //Get and save the head's char B
        char * array [] = {A, B};   //Create an array that holds char A & B
        return array;               //Return the array
    }   //End of else, if the LL is not empty
}   //End of getTopVertices