// This will hold the main function of our assembler

//Includes
#include "Assembler.h"
#include <iostream>
#include <vector>

//TODO: Flesh out
int main(int argc, const char *argv[]) {
    //Loop over all inputted documents, as long as the user actually inputted documents
    if (argc >= 2) {
        //copy input files to a vector of strings
        std::vector<std::string> files( argv, argv + argc );

        //Loop over all input files
        for (int i=0; i < files.size(); i++) {
            //variables:
            std::string inputFile = files.at(i); //current file we're working with

            //validate input, exit gracefully if we encounter any errors
            if (validate_input(argc, argv)) return 1;
            //Create input and output file objects
            //pass_1(/*inputFile*/);
            //call pass_2();
        }
        return 0;
    } else { //the user didn't supply a source file
        std::cout << "argc: " + std::to_string(argc) << std::endl;
        std::cout << "No source file detected." << std::endl;
        return 1;
    }
}

//TODO: Flesh out
bool validate_input(int arguments, const char *argumentList[]) {
    //Check to make sure that the user inputted the correct type of file (.sic)
    //If everything else checks out, convert argumentList to a vector of strings
    return false;
}
