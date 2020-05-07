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

void LinkedList::insert(int index1, int index2, int weight)
{
    /* insert public method, parameter(s): char array <a>, char array <b>, int <weight>
     * Objective: Get the parameters, create a new Node, and append it in the LL
     * */

    Node* insertNode = new Node(index1, index2, weight);  //Create a new Node to insert in the LL
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

void LinkedList::print()
{
    if (isEmpty())                                          //If the LL is empty
        std::cout << "Linked List is empty" << std::endl;
    else                                                    //Else the LL is not empty
    {
        Node* node = head;                                  //Start at the head of the LL
        while (node != nullptr)                             //Iterate through the LL
        {
            std::cout << "Edge: "   << node->index1 << ", " << node->index2 << std::endl;
            std::cout << "Weight: " << node->weight << std::endl;
            std::cout << std::endl;
            node = node->next;                              //Move to the next node in the LL
        }   //End of while-loop
    }   //End of else, if the Ll is not empty
}   //End of print method

int * LinkedList::getTopIndexes()
{
    /* getTopIndexes public method, parameter(s): None
     * Objective: Return an int array containing the two indexes found in the head/top node
     * -If head is empty return nullptr
     * -Else return int array of the head's indexes
     * */

    //Base case
    if (isEmpty())                                          //If LL is empty
        return nullptr;                                     //Return nullptr
    else                                                    //Else the LL is not empty
    {
        int indexes[] = {head->index1, head->index2};       //Create int array with the head's indexes
        return indexes;                                     //Return the int array
    }   //End of else, if the LL is not empty
}   //End of getTopIndexes method

LinkedList * LinkedList::cloneLL(LinkedList *LL)
{
    /* cloneLL public method, parameter(s): LinkedList <LL>
     * Objective: Copy every node in the LL into a new LL and return the new LL
     * - If the given LL is empty return nullptr
     * - Else traverse the given LL and copy it into a new LL, return the new LL at the end
     * */

    //Base case
    if (LL->isEmpty())                                      //If the LL is empty
        return nullptr;                                     //Return nullptr
    else
    {
        LinkedList* returnLL = new LinkedList();            //Initiate an empty LL, will be filled and returned at the end
        Node* currentNode = LL->head;                       //Get the current head of the given LL
        while (currentNode != nullptr)
        {
            //Get the data inside the current node to create a new node into out returnLL
            returnLL->insert(currentNode->index1, currentNode->index2, currentNode->weight);
            currentNode = currentNode->next;                //Move to the next node in the LL
        }   //End of while-loop
        //We get here after cloning everything from LL to returnLL
        return returnLL;                                    //Return the cloned returnLL
    }   //End of else, if the LL is not empty
}   //End of clone method