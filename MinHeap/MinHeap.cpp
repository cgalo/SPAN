/*
 * Author: Carlos Galo
 * Created On: 4/30/2020
 * Program: SPAN
 * Class: Non-Linear Data Structures
 * File: MinHeap.cpp
 *  - Source file for the MinHeap class
 *  - MinHeap will be used a queue for the Kruskal & Prim algorithms
 *  - Called in the MinSpanTree class
 * */

#include "MinHeap.h"

MinHeap::MinHeap(int maxSize)
{
    /* Constructor, parameter(s): int <maxSize>
     * */

    this->maxSize       = maxSize;                  //Set the value of the MinHeap to the given in the parameter
    this->array         = new Node*[maxSize];       //Create an array of nodes of maxSize
    this->currentSize   = 0;                        //Set the currentSize variable to 0
}   //End of constructor

MinHeap::~MinHeap()
{
    /* Destructor, parameter(s): None
     * Objective: Perform garbage collection on the MinHeap object
     * */
    delete array;                                   //Delete the array
    this->maxSize       = 0;                        //Set the maxSize back to 0
    this->currentSize   = 0;                        //Set the currentSize back to 0
}   //End of destructor

int MinHeap::getCurrentSize()
{
    //Getter for the currentSize variable
    return currentSize;
}   //End of getCurrentSize method

int MinHeap::getMaxSize()
{
    //Getter for the maxSize variable
    return maxSize;
}   //End of getMaxSize method

void MinHeap::insert(Node* insertNode)
{
    /* insert private method, parameter(s): Node pointer <insertNode>
     * Objective: Insert the new node into the right location in the heap array
     * - Traverse and move nodes to maintain min heap order for the insertion of the new node
     * */

    int index = getCurrentSize();                               //Save the current size as index to insert the new node
    array[index] = insertNode;                                  //Insert the insertNode at the end of the heap array
    currentSize++;                                              //Increase the size of the heap for the new node
    while (index != 0 && array[(index-1)/2]->weight > array[index]->weight)
    {
        swap(&array[index], &array[(index - 1)/2]);
        index = (index - 1) / 2;                                //Update index
    }   //End of while-loop

}   //End of insert method

void MinHeap::push(int index1, int index2, int weight)
{
    /* push public method, parameter(s): int <index1>, int <index2>, int <weight>
     * Objective: Create a new node and pass it to the insert method
     * -If the heap array size equals maxSize then output overflow error message
     * -Else pass a new node to the insert method
     * */

    //Base Case
    if (getCurrentSize() == getMaxSize())                       //If the current size is equal to max size
        std::cout << "Overflow error! Can't insert to heap as it's at max size" << std::endl;   //Output error
    else                                                        //Else there is space in the heap to insert a new node
        insert(new Node(index1, index2, weight));     //Call the insert method by passing a new node
}   //End of push method

bool MinHeap::isEmpty()
{
    /* isEmpty public method, parameter(s): None
     * Objective: Check if the size of the heap is greater than 0
     *  -If the size is greater than 0 return true
     *  -Else return false
     * */

    return getCurrentSize() <= 0;
}   //End of isEmpty method

void MinHeap::swap(Node **A, Node **B)
{
    /* swap private method, parameter(s): Node pointer <a>, Node pointer <b>
     * Objective: Swap the location of the given nodes in the heap
     * */

    Node* oldA = *A;            //Remember node A before swapping
    *A = *B;                    //Set Node B to A's location
    *B = oldA;                  //Set Node A to where B was
}   //End of swap method

void MinHeap::remove()
{
    /* remove private method: parameter(s): None
     * Objective: Remove the first node in the heap/array
     * - This method is called by popMin()
     * - This method calls heapify after moving nodes locations in the array
     * */


    array[0] = array[currentSize - 1];                  //Shift the next node to the top of the array
    currentSize--;                                      //Decrease the size of the heap
    heapify(0);                                   //Call the heapify method to recurse and fix the heap structure

}   //End of remove method

void MinHeap::popMin()
{
    /* popMin public method, parameter(s): None
     * Objective: Call the remove method to delete the first node in the heap/array
     * - If the heap is currently empty then return underflow error message
     * - Else call the remove method
     * */

    //Base case
    if (isEmpty())                                      //If the heap is empty
        std::cout << "Underflow error! Heap is empty, nothing to pop" << std::endl; //Throw underflow error
    else                                                //Else the heap is NOT empty
        remove();                                       //Call the remove method
}   //End of popMin method

void MinHeap::heapify(int index)
{
    /* heapify private method, parameter(s): int <index>
     * Objective: Maintain heap order/structure after removing a node
     * */

    int smallest    = index;                            //Save the given index as 'smallest' before moving it
    int left        = 2 * index + 1;                    //Get the index location of the left child
    int right       = 2 * index + 2;                    //Get the index location of the right child

    if (left < currentSize && array[left]->weight < array[index]->weight)
        smallest = left;

    if (right < currentSize && array[right]->weight < array[smallest]->weight)
        smallest = right;

    if (smallest != index)
    {
        swap(&array[index], &array[smallest]);
        heapify(smallest);
    }
}   //End of heapify method

void MinHeap::printHeap()
{
    /* printHeap public method, parameter(s): None
     * Objective: Iterate through the heap array and print all the nodes' data
     * - If heap is empty output empty line
     * - Else traverse the array and output data
     * */

    //Base case
    if (isEmpty())                                      //If the heap is currently empty
        std::cout << std::endl;                         //Print empty line
    else                                                //Else is the heap is not empty
    {
        for (int i = 0; i < maxSize; i++)               //Loop through the array
        {
            if (array[i])                               //If there is a node in this location of the array
            {
                Node* node = array[i];                  //Get the current node in the current index
                //Now print the information inside the node
                //std::cout << "Vertices: "   << node->index1  << ", " << node->index2 << std::endl;
                std::cout << "Weight: "     << node->weight << std::endl;
                std::cout << std::endl;
            }   //End of if there is a node in this location of the array
        }   //End of for-loop
    }   //End of else, if the heap array is not empty
}  //End of printHeap method

int * MinHeap::getMinIndexes()
{
    /* getMinIndexes public method, parameter(s): None
     * Objective: return the indexes inside the first node in the heap array
     * - If the heap is empty return an nullptr
     * - Else the heap is not empty, return the indexes inside the first node in the array
     * */

    //Base case
    if (isEmpty())                                      //If the heap array is empty
        return nullptr;                                 //Return nullptr
    else                                                //Else the heap array is not empty
    {
        Node* node      = array[0];                     //Get the node in first location of the array
        int indexes []  = {node->index1, node->index2}; //Save the indexes into an int array
        return indexes;                                 //Return the indexes array
    }   //End of else, if the heap is not empty
}   //End of getMinIndexes

int MinHeap::getMinWeight()
{
    /* getMinWeight public method, parameter(s): None
     * Objective: Return the first node's weight
     *  -If the heap array is empty return -1
     *  -Else return the weight of the first node in the heap array
     * */

    //Base case
    if (isEmpty())                                  //If the heap array is empty
        return -1;                                  //Return -1
    else                                            //Else the heap array is not empty
        return array[0]->weight;                    //Return the weight of the first node in the array
}   //End of getMinWeight