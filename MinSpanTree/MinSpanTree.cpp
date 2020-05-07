//
// Created by Carlos Galo on 4/30/20.
//

#include "MinSpanTree.h"
#include "../LinkedList/LinkedList.h"

MinSpanTree::MinSpanTree(char *file)
{
    /* Constructor, parameter(s) char array <file>
     * Objective: Read given file, that contains graph information, and save the graph and its information
     * */

    //Attempt to open the given file
    std::ifstream inFile;                               //Initiate ifstream to read the given file
    inFile.open(file);                                  //Open the provided file
    if (!inFile)                                        //If there was an issue opening the file
    {
        std::cerr << "Error! There was an issue opening file: " << file << std::endl;   //Output error message
        exit(1);                                        //Exit the program with an error
    }   //End of if there was an issue opening the file
    else                                                //Else we opened the file successfully
    {
        //First we get the first value in the file, this will be the total nodes in the spanning tree
        inFile >> this->totVertices;                    //Save the first value as total vertices in the graph
        if (totVertices == 0)                           //Check if there was an error getting total vertices in the graph
        {
            //For error handling, if there was an issue getting total vertices/nodes from the file
            std::cerr << "Error getting the total nodes/vertices" << std::endl; //Output error
            exit(1);                                    //Exit the program with error code
        }   //End of if totVertices is 0
        vertices = new Node *[totVertices];             //Create array of nodes of the size given from the file (totVertices)

        for (int i = 0; i < totVertices; i++)           //Now loop the file to get the vertices/node names from the graph
        {
            char vertex[] = {'\0','\0'};                //Initiate an empty char array
            inFile >> vertex;                           //Read the file's line, up to 2 characters
            vertices[i] = new Node (vertex);            //Insert a new node with the char array into the vertices array
        }   //End of for-loop
        //We get here by filling the array of vertices of size totVertices
        //Now get the data of each vertex in the matrix, matrix is size totVertices * totVertices
        graph   = new LinkedList();                     //Initiate the LL to save the file's graph
        graph2D = new int *[totVertices];               //Initialize a 2D int array to save the graph
        for (int vertIndex = 0; vertIndex < totVertices; vertIndex++)   //Loop through each
        {
            graph2D[vertIndex] = new int[totVertices];  //Initialize a new int array in the 2D graph
            int nums[totVertices];                      //Initiate an int array of size of totVertices for this
            int indexNums = 0;                          //Keep track of how many numbers we've seen
            char c;                                     //Use to read character by character in the file
            while (inFile >>std::noskipws>> c)          //Read the next char and save it in 'c'
            {
                if (isdigit(c))                         //If 'c' is a number
                {
                    char * numArr = new char[2];        //Initiate an empty char array of size 2
                    numArr[0] = c;                      //Insert 'c' as first char in the array

                    //We need to check if the next char in the file is a digit
                    char nextC;                         //Initiate another char to read the next char in the file
                    inFile >>  std::noskipws >> nextC;  //Get the next char in the file
                    if (isdigit(nextC))                 //If the next char was a digit then it's is a digit of num
                        numArr[1] = nextC;              //Append 'nextC' into the numArr

                    int num = atoi(numArr);             //Convert the char array into an int using atoi, save it as int
                    nums[indexNums] = num;              //Insert num in the nums array
                    graph2D[vertIndex][indexNums] = num;
                    indexNums++;                        //Increase the indexNums

                    if (indexNums == totVertices)       //If we have inserted the line of numbers into the array
                        break;                          //Break off the while-loop
                }   //End of if 'c' is a digit
                else                                    //Else 'c' is not a number
                    continue;                           //We don't care if it's not a number so we continue to the next char
            }   //End of while-loop
            insertToGraph(nums, vertIndex);             //Call method to check what vertices are connected to this node and insert to graph
            //testGraph[vertIndex] = new int[totVertices];
            //testGraph[vertIndex] = nums;
        }   //End of for-loop
        //We get here after reading through the whole matrix and filling out our 'graph' with edges and their vertices
    }   //End of else, if there was no issue opening the file
}   //End of constructor

MinSpanTree::~MinSpanTree(){
    //Destructor for garbage collection purposes
    delete graph;                                       //Perform garbage collection in the graph
    for (int i = 0; i < totVertices; i++)               //Traverse the array of nodes
    {
        delete vertices[i];                             //Delete the node in the current location
        delete[] graph2D[i];                            //Delete the data inside the 2D matrix
    }
    delete vertices;                                    //Delete the vertices array
    delete graph2D;                                     //Delete the 2D graph, int array
    this->totVertices = 0;                              //Set total vertices back to 0
}   //End of destructor

void MinSpanTree::insertToGraph(int *matrixLine, int vertIndex)
{
    /* insertToGraph private method, parameter(s): int array <matrixLine>, int <vertIndex>
     * Objective: Given the array, figure what node's have an edge to the node in vertIndex, and insert to graph
     * */

    //Loop through the matrixLine, which has a length of totVertices
    for (int index = 0; index < totVertices; index++)   //Loop through the matrixLine int array
    {
        int currNum = matrixLine[index];                //Save the current value in matrixLine as currNum
        if (currNum == 0)                               //If currNum is 0
            continue;                                   //Then we continue to the next loop
        else                                            //Else currNum is NOT 0
        {                                               //We insert a new node to the LL
            int weight = currNum;                       //The currNum is the weight of the edge
            graph->insert(vertIndex, index, weight);    //Insert edge and vertices's indexes to the graph as a node
        }   //End of else,if the currNum is NOT 0
    }   //End of for-loop
}   //End of insertToGraph method

MinHeap* MinSpanTree::buildQueue()
{
    /* buildQueue private method, parameter(s): None
     * Objective: Create and return a MinHeap with the data inside of the LL 'graph'
     * -If graph is empty, output error as the graph should never be empty
     * -Else iterate through the graph and create the MinHeap/queue
     * */

    //Base case, for error handling
    if (graph->isEmpty())                                       //If the graph is empty
    {
        //Output error message
        std::cerr << "Error! There was an issue saving the graph" << std::endl;
        exit(1);                                                //Exit program with error
    }   //End of if the graph is empty
    else
    {
        //We'll create a clone of the graph so that we don't manipulate any data to reuse again
        LinkedList* localGraph = graph->cloneLL(graph);         //Create a copy of the graph
        MinHeap* queue = new MinHeap(graph->getSize()); //Create a queue with size of total nodes in the graph
        while (!localGraph->isEmpty())                          //Loop the cloned graph until it's empty
        {
            //First lets get the indexes from the graph
            int* indexes = localGraph->getTopIndexes();         //Get the indexes from the top node in the graph
            int index1 = indexes[0];                            //Save the first index as index1
            int index2 = indexes[1];                            //Save the second index as index2
            //Now lets get the weight
            int weight = localGraph->getTopWeight();            //Get the weight of the top node/edge in the graph
            //Now remove the top node of the graph
            localGraph->popFront();                             //Remove the top node inside the graph
            //Now insert new node into queue
            queue->push(index1, index2, weight);                //Insert the data into the queue
        }   //End of while-lop
        //We get here after inserting all the graph data the queue/MinHeap
        delete localGraph;                                      //Perform garbage collection on the LL, 'localGraph'
        return queue;                                           //Return the full queue
    }   //End of else, if the graph is not empty
}   //End of graphToQueue method

MinSpanTree::Node ** MinSpanTree::KruskalMST(MinHeap *queue)
{
    /* KruskalMST private method, parameter(s): MinHeap <queue>
     * Objective: Perform Kruskal's algorithm and return array of vertices
     * - If the queue is empty before performing an algorithm then exit with error
     * - Else perform algorithm
     * */

    //Base case
    if (queue->isEmpty())                                       //If the queue is empty before starting
    {
        std::cerr << "Error! There was an issue building queue" << std::endl;   //Output error
        exit(1);                                                //Exit the program with error
    }
    else                                                        //Else the queue is not empty
    {
        Node** MST = new Node* [totVertices-1];                 //Initiate an array of size vertices-1

        return MST;
    }   //End of else, if the queue is not empty
}   //End of KruskalMST method

void MinSpanTree::getKruskalMSP()
{

}   //End of getKruskalMSP method

MinHeap* MinSpanTree::PrimMST()
{
    /* PrimMST private method, parameter(s): None
     * Objective: Perform Prim's algorithm and return MinHeap ordered by the index1 in the matrix
     * */

    //Initiate variables, with their values, for the algorithm
    MinHeap* MST = new MinHeap(totVertices-1);                  //Create a MinHeap, called MST, to return at the end
    int lclVertices[totVertices];                               //Initiate a char array
    int minWeights[totVertices];                                //Array To keep track of min weight edges
    bool set[totVertices];                                      //Create a set, bool array, to keep track of vertices
    for (int i = 0; i < totVertices; i++)                       //Loop to set values in all keys and seen array
    {
        minWeights[i] = INT_MAX;                                //Set key to the max an int can hold using INT_MAX
        set[i] = false;                                         //Set all values in the set to false
    }   //End of for-loop
    //We get here after setting up all the variables needed for the algorithm
    //Start of the Prim's Algorithm
    minWeights[0]   = 0;                                        //Start by an arbitrary vertex
    lclVertices[0]  = -1;                                       //Start by an arbitrary vertex
    for (int i = 0; i < totVertices - 1; i++)                   //Start looping through every row in the matrix
    {
        int index1 = getMinIndex(minWeights, set);              //Pick the minimum key vertex and save it as index1
        set[index1] = true;                                     //Mark this index as seen in the set
        for (int index2 = 0; index2 < totVertices; index2++)    //Loop through each column in the current row of the matrix
        {
            int currentVal = graph2D[index1][index2];           //Get the current value inside the matrix
            //If there is a value in the currentVal, and if index2 is not in the set, and if currentVal < minWeight at index2
            if (currentVal && !set[index2] && currentVal < minWeights[index2])
            {
                lclVertices[index2] = index1;                   //Save the index1 in the lclVerices array
                minWeights[index2] = currentVal;                //Save the currentVal in the minWeights
            }   //End of if
        }   //End of for-loop, looping through every column in the current row
    }   //End of for-loop, looping through every row in the matrix/graph2D
    //Now insert the data of indexes/vertices into the MinHeap 'MST', where the weight will be first index
    for (int i = 1; i < totVertices; i++)                       //Loop through the lclVertices array
        MST->push(lclVertices[i], i, lclVertices[i]);           //Insert the data into the MST/MinHeap
    return MST;                                                 //Return the completed MST
}   //End of PrismMST method

int MinSpanTree::getMinIndex(int *arr, bool *set)
{
    /* minKey private method, parameter(s): int array <arr>, bool array <set>
     * Objective: Return the smallest index in the array that is not already in the set
     * - If all the values in the array are already in the set then we return -1
     * - Else we return the index(minIndex) to the smallest value in the array
     * */

    int min = INT_MAX;                                  //Min int variable to track the smallest value
    int minIndex;                                       //minIndex to keep track of index of the min variable
    for (int index = 0; index < totVertices; index++)   //Loop through the array 'arr'
    {
        int currentVal = arr[index];                    //Current value inside the array
        if (!set[index] && currentVal < min)            //If the currentVal is not in the set and is smaller than our current min
        {
            min = currentVal;                           //Set the currentVal as new min
            minIndex = index;                           //Set the current index as minIndex
        }   //End of if we have not seen the index in the set & the currentVal is smaller than the min
        else                                            //Else we have seen this vertex or the currenVal > min
            continue;                                   //We continue through the loop
    }   //End of for-loop
    return minIndex;                                    //Return the minIndex
}   //End of getMinIndex method

void MinSpanTree::getPrimMSP()
{
    /* getPrimMSP public method, parameter(s): None
     * Objective: Output the final results of the PrimMST method, which comes in as a MinHeap/queue
     * - If the queue is empty before reading through it then output error
     * - Else output the results from the queue
     * */

    MinHeap* MST = PrimMST();                                   //Call and get the results of Prim's Algorithm
    if (MST->isEmpty())                                         //If the MST is empty
    {
        std::cerr << "Error in performing Prim's Algorithm!" << std::endl;  //Output error message
        exit(1);                                                //Exit program with error code 1
    }   //End of if the MSP is empty
    else                                                        //Else the MST is NOT empty
    {
        while (!MST->isEmpty())                                 //Traverse the MST queue/MinHeap
        {
            int* indexes = MST->getMinIndexes();                //Get the indexes from the first node in the heap
            int index1 = indexes[0];                            //Save the first index as index1
            int index2 = indexes[1];                            //Save the second index as index2
            int weight = graph2D[index1][index2];               //Get and save the weight of the edge from the graph
            MST->popMin();                                      //Pop the first/top node in the heap
            //Now output the results
            std::cout << vertices[index1]->data << "-" << vertices[index2]->data << ": " << weight << std::endl;
        }   //End of while-loop
        //We get here after output all the results for the Prim's algorithm, the MST heap is now empty
    }   //End of else, if the MST heap is not empty
}   //End of getPrismMSP method