#include "Assembler.h"
#include "AppendixA.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

//We should pass the input file, symtab, and littab into Pass 2
void pass_2(std::string sourceFile) {
   //open necessary files
   std::vector<std::string> currentLine;

   std::string tempFileName = sourceFile.substr(0, sourceFile.length() - 4) + ".temp";
   inputFile.exceptions(std::ifstream::failbit);
   inputFile.open(tempFileName);

   std::string outputFileName = sourceFile.substr(0, sourceFile.length() - 4) + ".lis";
   outputFile.exceptions(std::ofstream::failbit);
   outputFile.open(outputFileName);

   assemblerPass = 2;

   std::cout << "In pass 2" << std::endl; // just for me :)

   //*SETUP
   //pass first comment line to temp file
   processLine(currentLine);
   outputToFile(currentLine);

   //next line should be start
   processLine(currentLine);
   if (currentLine[2].find("START") != currentLine[2].npos){
      outputToFile(currentLine);
   }

   //* Main loop


   //**Dylan's Commented Logic**
   //initialize variables
      //ex: programCounter, baseRegister
      //int OPERAND = 0, programCounter
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
            //Write OPCODE, object code, and operand to listing file
         //else (no operand)
            //if format 1 or 2
               //calculate object code accordingly 

   //housekeeping
   inputFile.close();
   outputFile.close();
   return;
}
