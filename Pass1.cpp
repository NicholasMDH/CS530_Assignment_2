//This will hold the function definitions for the functions needed in pass 1 of the assembler

#include "Assembler.h"

//TODO: Flesh out
void pass_1() {
    //checkForComments(/*first line, intermediate file*/);
    //Find program name on START line
    //Set location counter to 0
    //Loop over lines in file
        //Set address based on value of location counter (starts at 0)
        //checkForComments(/*currentLine, intermediate file*/);
        //check for symbol declarations (call calc_symtab)
        //check what type of instruction the line is
         instruction_formats(/*input_file, intermediate file*/);
        //increment location counter based on return value
        //write to the intermediate file
    //return intermediate_file
    return; //temporary

    //Dylan's comments//
    //Start the file read
   //If "START" is found, save the value of the START operand as the starting address
      //set the LOCCTR to that starting address
      //write current line into intermediate file
      //read next line
         //end loop (if START)
   //else LOCCTR is starting at 0  
   
   //while OPCODE != "END", do
      //if not a comment line
         //begin
            //if there is a symbol/label
               //begin
                  //search SYMTAB for that label
                  //if found
                     //error (duplicate symbol)
                  //else
                     //insert (LABEL/LOCCTR) into SYMTAB
               //end

           //search OPTAB for OPCODE
           //if found
              //add 3 to LOCCTR
           //else if 'WORD'
              //add 3 to LOCCTR
           //else if 'RESW'
              //add 3 * #[OPERAND] to LOCCTR  // #[OPERAND] == constant value attached to OPERAND
           //else if 'RESB'
              //add #[OPERAND] to LOCCTR
           //else if 'BYTE'
              //begin
                 //find length of constant in bytes
                 //add length to LOCCTR
              //end (if BYTE)
           //else
              //error for invalid OPCODE
        //end (if not a comment)
     //write line to intermediate file
     //read next line
   //while loop END
   
   //write last line to intermediate file
   //save (LOCCTR - starting address) as program length
   //end of Pass 1

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