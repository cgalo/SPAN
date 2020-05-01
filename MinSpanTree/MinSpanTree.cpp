//
// Created by Carlos Galo on 4/30/20.
//

#include "MinSpanTree.h"

MinSpanTree::MinSpanTree(char *file)
{
    //Attempt to open the given file
    std::ifstream inFile;               //Initiate ifstream to read the given file
    inFile.open(file);                  //Open the provided file
    if (!inFile)                        //If there was an issue opening the file
    {
        std::cout << "Error! There was an issue opening file: " << file << std::endl;   //Output error message
        exit(1);                        //Exit the program with an error
    }   //End of if there was an issue opening the file
    else                                //Else we opened the file successfully
    {
        //First we get the first value in the file, this will be the total nodes in the spanning tree
        inFile >> this->totVertices;    //Save the first value as total vertices in the graph

        //Now we need to loop to get the 'data' of each node in the graph provided in the file


    }   //End of else, if there was no issue opening the file

}   //End of constructor

MinSpanTree::~MinSpanTree()
{
    //Destructor for garbage collection purposes
    this->totVertices = 0;              //Set total vertices back to 0

}   //End of destructor

MinHeap* MinSpanTree::graphToQueue()
{

}   //End of graphToQueue method

void MinSpanTree::getKruskalMSP()
{

}   //End of getKruskalMSP method

void MinSpanTree::getPrimMSP()
{

}   //End of getPrismMSP method