/*
 * Author: Carlos Galo
 * Created On: 4/29/2020
 * Program: WordLadder
 * Class: Non-Linear Data Structures
 * File: main.cpp
 *  - CLI menu
 * */

#include <iostream>
#include <fstream>      //To open/read files

using namespace std;

int main(int argc, char** argv)
{
    //Argv0 = SPAN.exe
    //1 = Name of the file, aka file.txt


    if (argc < 1)       //If the user did not provide at least one argument
        cout << "Error! Please enter file location." << endl;

    else                //Else the user provided at least one argument
    {
        char * file  = argv[1];     //Save the file provided by the user in the argument 1
        ifstream inFile;            //Initiate a ifstream to open file
        inFile.open(file);          //Open the file given by the user
        if (!inFile)                //If we couldn't open the file
            cout << "Error! Couldn't open file: " << file <<  endl; //Output file error
        else                        //Else we could open the file
        {

        }   //End of else, if we could open the file

    }
    return 0;
}
