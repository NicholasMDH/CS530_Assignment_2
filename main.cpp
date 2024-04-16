// This will hold the main function of our assembler

//Includes
#include "Assembler.h"
#include <iostream>
#include <vector>
#include <string>

//TODO: Flesh out
int main(int argc, const char *argv[]) {
    //Loop over all provided files, as long as the user actually provided files
    if (argc >= 2) {
        //copy input files to a vector of strings
        std::vector<std::string> files(argv, argv + argc);

        //remove first item in array since it will always be "asxe"
        files.erase(files.begin());

        //Loop over all input files
        for (int i=0; i < files.size(); i++) {
            std::cout << "Loop " + std::to_string(i) << std::endl; //* testing
            //variables:
            std::string inputFile = files.at(i); //current file we're working with
            std::cout << "processing file: " + inputFile << std::endl;

            //validate input, exit gracefully if we encounter any errors
            if (validate_input(inputFile)) return 1;

            //TODO - from here onwards
            //Create input and output file objects
            //pass_1(/*inputFile*/);
            //call pass_2();
        }
        return 0;
    } else { //the user didn't supply a source file
        std::cout << "No source file detected." << std::endl;
        return 1;
    }
}

//TODO: Flesh out
bool validate_input(const std::string passedFile) {
    //Check to make sure that the user inputted the correct type of file (.sic)
    std::cout << "file extension: " + passedFile.substr(passedFile.length() - 4) << std::endl; //TESTING
    if (".sic" != passedFile.substr(passedFile.length() - 4)) {
        std::cout << "incompatible file extension, exiting program" << std::endl;
        return 1;
    }
    return 0;
}
