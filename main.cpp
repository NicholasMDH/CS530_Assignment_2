/*
Team:
Nicholas Dibello-Hitta, cssc4049, RedID: 828490930
Dylan Agoncillo, cssc4051, RedID: 824340550

*/

#include "Assembler.h"
#include <iostream>
#include <vector>
#include <string>


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
            std::string sourceFile = files.at(i); //current file we're working with
            std::cout << "processing file: " + sourceFile << std::endl;

            //validate input, exit gracefully if we encounter any errors
            if (validate_input(sourceFile)) return 1;

            pass_1(sourceFile);
            pass_2(sourceFile);
        }
        return 0;
    } else { //the user didn't supply a source file
        std::cout << "No source file detected." << std::endl;
        return 1;
    }
}
