//This function will hold the definitions for the functions required for pass 2 of the assembler

#include "Assembler.h"

//? Should this loop over every line in the intermediate file? -- yes
//We should pass the input file, symtab, and littab into Pass 2
void pass_2() {
    //checkForComments(/*inputFile, outputFile*/);
    //figure out format type (reuse instruction_formats()?)
    //Figure out //!LEFT OFF HERE
    //call process_vars()
    //call assembler_directives()
    //return output_file
    return; //temporary
    
    //**Dylan's Commented Logic**
    //initialize variables
       //ex: programCounter, operand, lineNumber
       //int OPERAND = 0, lineNumber = 0, programCounter
       //bool extendedFormat
    //read through intermediate file
    //if OPCODE = "START" and while OPCODE != "END"
       //increment lineNumber by 1
       //Write current lineNumber into listing file
    
       //if instruction is NOT a comment (meaning there is no "." in front)
          //if instruction has a label
             //write label to listing file

       //if there is OPCODE, search OPTAB for OPCODE
          //if "START" or if "END"
	     //Write OPCODE and OPERAND to listing file
	  //else if opcode is in SYMTAB
	     //if instruction has an OPERAND
	        //check for addressing mode
		   //immediate
		      //check for "#" before OPERAND
		   //indirect
		      //check for "@"
		   //otherwise, direct
		   //then, check xbpe flags
		   //check for extended format (format 4)
		      //look for "+" before instruction name
	        //calculate displacement or address based on addressing mode
		//if format 1 or 2
		   //calculate object code for format 1/2
		//else if format 3 or 4
		   //calculate object code accordingly
    //          //Write OPCODE, object code, and operand to listing file
    //       //else (no operand)
    //          //if format 1 or 2
    //             //calculate object code accordingly
    //
    //
    //
    //
    //if OPCODE = "START" and While OPCODE != "END"
       //Write opcode and operand to listing file
       //if comment (== "."), write comment line to listing file
       //if line has OPCODE, search OPTAB for OPCODE
          //if there is a symbol in OPERAND field, then
	     //search SYMTAB for that symbol/OPERAND
	        //store symbol value as OPERAND address
	  //else
	     //store 0 as OPERAND address
       //

}
