//This will hold the function definitions for the functions needed in pass 1 of the assembler

#include "Assembler.h"
#include "utils.h"
#include <fstream>
#include <vector>

//global variables
std::ifstream inputFile;
std::ofstream outputFile;

//I'm putting these functions here because it's only used in pass 1
void processLine(std::vector<std::string> &currentLine) {
   currentLine.clear();
   std::string temp;
   //column sizes
   static const int address_Column = 4,
      symbol_Column = 9,
      instruction_Column = 8,
      operand_Column = 20,
      opcode_Column = 4,
      comment_Column = 20;

   //TODO: bounds/error checking?
   
   //get the first line
   std::getline(inputFile, temp);
   std::cout << "temp variable: " << temp << std::endl; //testing, this works

   //if it's a comment, just pass it as the current line
   if (temp[0] == '.') currentLine.push_back(temp);
   //if it's a regular line, separate it into symbol, instruction, operand, and 
   else {
      currentLine.push_back(temp.substr(0, symbol_Column));
      currentLine.push_back(temp.substr(symbol_Column, instruction_Column));
      currentLine.push_back(temp.substr(symbol_Column + instruction_Column, operand_Column));
      //if format 4
      if (temp.size() > (symbol_Column + instruction_Column + operand_Column)) {
         currentLine.push_back(temp.substr(symbol_Column + instruction_Column + operand_Column));
      }
   }

   //testing, I want to see what's in currentLine
   for (int i = 0; i < currentLine.size(); i++) {
      std::cout << "currentLine[" << std::to_string(i) << "]: " << currentLine[i] << std::endl;
   }
}

//void outputToFile() //! LEFT OFF HERE, START WRITING WRITER FUNCTION

//TODO: Flesh out
int instruction_formats() {
   //check if the instruction is extended format (+)
   //Figure out if the line is a format 1-4 command
      //If it is, return the format type
      //If it isn't, return false? (some sort of error type)
   //Check for WORDs and BYTEs
      //check for special case BYTEs (C,X,D)
   //return location counter value based on symbol size
   return 0;
}

//TODO: Flesh out
void pass_1(std::string sourceFile) {
   //open necessary files
   std::vector<std::string> currentLine;
   inputFile.exceptions(std::ifstream::failbit);
   inputFile.open(sourceFile);

   std::string outputFileName = sourceFile.substr(0, sourceFile.length() - 4) + ".temp";
   outputFile.exceptions(std::ofstream::failbit);
   outputFile.open(outputFileName);

   //TODO: test reader with writer


   //checkForComments(/*first line, intermediate file*/);
   //Find program name on START line
   //Set location counter to 0
   //Loop over lines in file
      //Set address based on value of location counter (starts at 0)
      //checkForComments(/*currentLine, intermediate file*/);
      //check for symbol declarations (call calc_symtab)
      //check what type of instruction the line is
      //int temp = instruction_formats(/*input_file, intermediate file*/); //this needs to be defined up above if we're going to use it
      //increment location counter based on return value
      //write to the intermediate file
   //return intermediate_file

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
   //inputFile.close(); //!
   return; //temporary
}
