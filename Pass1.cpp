//This will hold the function definitions for the functions needed in pass 1 of the assembler

#include "Assembler.h"

//TODO: Flesh out
void pass_1() {
    checkForComments(/*first line, intermediate file*/);
    //Find program name on START line
    //Set location counter to 0
    //Loop over lines in file
        //Set address based on value of location counter (starts at 0)
        checkForComments(/*currentLine, intermediate file*/);
        //check for symbol declarations (call calc_symtab)
        //check what type of instruction the line is
        instruction_formats(/*input_file, intermediate file*/);
        //increment location counter based on return value
        //write to the intermediate file
    //return intermediate_file
    return; //temporary
}

//I'm putting this function here because it's only used in pass 1
//TODO: Flesh out
void instruction_formats() {
    //check if the instruction is extended format (+)
    //Figure out if the line is a format 1-4 command
        //If it is, return the format type
        //If it isn't, return false? (some sort of error type)
    //Check for WORDs and BYTEs
        //check for special case BYTEs (C,X,D)
    //return location counter value based on symbol size
    
}