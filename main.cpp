/*
 * Author: Carlos Galo
 * Created On: 4/29/2020
 * Program: SPAN
 * Class: Non-Linear Data Structures
 * File: main.cpp
 *  - CLI menu
 * */

#include "MinSpanTree/MinSpanTree.h"    //MinSpanTree class, where most of the logic will be handled
using namespace std;

int main(int argc, char** argv)
{
    //Argv0 = SPAN.exe
    //1 = Name of the file, aka file.txt

    if (argc <= 1)                                              //If the user did not provide at least one argument
        cout << "Error! Please enter file location." << endl;   //Output error

    else                                                        //Else the user provided at least one argument
    {
        char * file  = argv[1];                                 //Save the file provided by the user in the argument 1
        MinSpanTree* MSP = new MinSpanTree(file);               //Initiate the MinSpanTree object
        MSP->getKruskalMSP();                                   //Output the results of Kruskal's Algorithm
        cout << "------------------------------------" << endl; //Separate the result between the two algorithms
         MSP->getPrimMSP();                                      //Output the results of Prim's Algorithm
        delete MSP;                                             //Garbage collection on the MinSpanTree object
    }   //End of else, if the user provided at least one argument
    return 0;
}   //End of main function