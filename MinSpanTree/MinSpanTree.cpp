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
    delete graph;                           //Perform garbage collection in the graph
    for (int i = 0; i < totVertices; i++)   //Traverse the array of nodes
    {
        delete vertices[i];                 //Delete the node in the current location
        delete[] graph2D[i];                //Delete the data inside the 2D matrix
    }
    delete vertices;                        //Delete the vertices array
    delete graph2D;                         //Delete the 2D graph, int array
    this->totVertices = 0;                  //Set total vertices back to 0
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

    }   //End of else, if the queue is not empty
}   //End of KruskalMST method

void MinSpanTree::getKruskalMSP()
{

}   //End of getKruskalMSP method

MinSpanTree::Node ** MinSpanTree::PrimMST(MinHeap *queue)
{
    /* PrimMST private method, parameter(s): MinHeap <queue>
     * Objective: Perform Prim's algorithm and return array of vertices
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

    }   //End of else, if the queue is not empty
}   //End of PrismMST method
void MinSpanTree::getPrimMSP()
{

}   //End of getPrismMSP method