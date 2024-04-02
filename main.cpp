// This will hold the main function of our assembler

//Includes
#include "Assembler.h"

int main(int argc, const char *argv[]) {
    validate_input(argc, argv); //TODO: Flesh out
    pass_1(); //TODO: Flesh out
    //call pass_2();
    return 0;
}

//TODO: Flesh out
void validate_input(int arguments, const char *argumentList[]) {
    //Check to make sure that we have at least two arguments
    //Check to make sure that the user inputted the correct type of file (.sic)
    //If everything else checks out, convert argumentList to a vector of strings
}
