//
// Created by Carlos Galo on 4/30/20.
//

#include "MinSpanTree.h"
#include "../LinkedList/LinkedList.h"

MinSpanTree::MinSpanTree(char *file)
{
    //Attempt to open the given file
    std::ifstream inFile;                               //Initiate ifstream to read the given file
    inFile.open(file);                                  //Open the provided file
    if (!inFile)                                        //If there was an issue opening the file
    {
        std::cout << "Error! There was an issue opening file: " << file << std::endl;   //Output error message
        exit(1);                                        //Exit the program with an error
    }   //End of if there was an issue opening the file
    else                                                //Else we opened the file successfully
    {
        //First we get the first value in the file, this will be the total nodes in the spanning tree
        inFile >> this->totVertices;                    //Save the first value as total vertices in the graph
        if (totVertices == 0)                           //Check if there was an error getting total vertices in the graph
        {
            //For error handling, if there was an issue getting total vertices/nodes from the file
            std::cout << "Error getting the total nodes/vertices" << std::endl; //Output error
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
        graph = new LinkedList();                       //Initiate the LL to save the file's graph
        for (int vertIndex = 0; vertIndex < totVertices; vertIndex++)   //Loop through each
        {
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
                    indexNums++;                        //Increase the indexNums

                    if (indexNums == totVertices)       //If we have inserted the line of numbers into the array
                        break;                          //Break off the while-loop
                }   //End of if 'c' is a digit
                else                                    //Else 'c' is not a number
                    continue;                           //We don't care if it's not a number so we continue to the next char
            }   //End of while-loop
            insertToGraph(nums, vertIndex);             //Call method to check what vertices are connected to this node and insert to graph
        }   //End of for-loop
        //We get here after reading through the whole matrix and filling out our 'graph' with edges and their vertices
        graph->print();
    }   //End of else, if there was no issue opening the file
}   //End of constructor

MinSpanTree::~MinSpanTree(){
    //Destructor for garbage collection purposes
    delete graph;                           //Perform garbage collection in the graph
    for (int i = 0; i < totVertices; i++)   //Traverse the array of nodes
        delete vertices[i];                 //Delete the node in the current location
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

MinHeap* MinSpanTree::graphToQueue()
{

}   //End of graphToQueue method

void MinSpanTree::getKruskalMSP()
{

}   //End of getKruskalMSP method

void MinSpanTree::getPrimMSP()
{

}   //End of getPrismMSP method