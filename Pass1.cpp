//This will hold the function definitions for the functions needed in pass 1 of the assembler

#include "Assembler.h"
#include "utils.h"
#include "AppendixA.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

//global variables
std::ifstream inputFile;
std::ofstream outputFile;
bool extFormat = false;
int locctr = 0;
std::unordered_map<std::string, int> SYMTAB;
//column sizes
static const int address_Column = 4,
   symbol_Column = 9,
   instruction_Column = 8,
   operand_Column = 20,
   opcode_Column = 4,
   comment_Column = 20;


void remove_whiteSpaces(std::vector<std::string> &currentLine) {
   for (int i = 0; i < currentLine.size(); i++) {
      int start = currentLine[i].find_first_not_of(" \t\n\r\f\v");
      size_t end = currentLine[i].find_last_not_of(" \t\n\r\f\v");
      if (start != currentLine[i].npos) { //only strip whitespaces if the line isn't blank
         currentLine[i] = currentLine[i].substr(start, end - start + 1);
      }
   }
}

//I'm putting these functions here because it's only used in pass 1
void processLine(std::vector<std::string> &currentLine) {
   currentLine.clear();
   std::string temp;
   
   //TODO: bounds/error checking?
   
   //get the first line
   std::getline(inputFile, temp);
   std::cout << "temp variable: " << temp << std::endl; //!testing, this works

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

   //remove whitespaces
   remove_whiteSpaces(currentLine);

   //!testing, I want to see what's in currentLine
   for (int i = 0; i < currentLine.size(); i++) {
      std::cout << "currentLine[" << std::to_string(i) << "]:" << currentLine[i] << ":\n";
   }
}

//I want this to mirror processLine
void outputToFile(std::vector<std::string> &currentLine) {
   //write comments straight to file
   if (currentLine[0][0] == '.') {
      outputFile << currentLine[0] << std::endl;
      return;
   }

   //calculate address field //!Fix to prepend zeroes!
   outputFile << std::setw(address_Column) << std::left << std::hex << locctr;
   
   outputFile << " "; //buffer

   //Symbols
   outputFile << std::setw(symbol_Column) << std::left << currentLine[0];

   //Extended format?
   if (extFormat) {
      outputFile << '+';
   } else {
      outputFile << ' ';
   }

   //Instructions
   outputFile << std::setw(instruction_Column) << std::left << currentLine[1];

   //Operand //TODO: Fix formatting
   outputFile << currentLine[2];

   //End the line
   outputFile << std::endl;
}

//TODO: BYTE operators and handle END line
void instruction_formats(std::vector<std::string> currentLine) {
   //Logic:
      //check if the instruction is extended format (+)
      //Figure out if the line is a format 1-4 command
         //If it is, return the format type
         //If it isn't, return false? (some sort of error type)
      //Check for WORDs and BYTEs
         //check for special case BYTEs (C,X,D)
      //return location counter value based on symbol size
   
   //int locctr = 0;
   
   if (currentLine[1][0] == '+'){
      extFormat = true;
   }
   else if (currentLine[1][0] == ' '){
      //nothing to do
   }
   else{
      //error throw?
   }
   
   //currentLine[1] = currentLine[1].substr(1);

   if (AppendixA::OPTAB.find(currentLine[1]) != AppendixA::OPTAB.end()){ //! TESTING USED TO BE 1
      if (extFormat = true){
         locctr += 4;
      }
      else{
         locctr += 3;
      }
   }
   else if (currentLine[1].compare("RESW") == 0){
      locctr += 3 * std::stoi(currentLine[2]);
   }
   else if (currentLine[1].compare("RESB") == 0){
      locctr += std::stoi(currentLine[2]);
   }
   else if (currentLine[1].compare("WORD") == 0){
      locctr += 3;
   }
   else if (currentLine[1].compare("BYTE") == 0){
      //TODO: Flesh out
      //if C, X, or D
   }
   else{
      std::cout << "THIS IS REALLY BAD AND NEEDS FIXING URGENTLY" << std::endl; //! THIS IS ALWAYS HAPPENING WE NEED TO FIX THIS
      std::cout << "the current value of currentLine[1]:" << currentLine[1] << ": end " <<std::endl;
   }
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

   int address;

   //SETUP
   //TODO: pass first comment line to temp file
   processLine(currentLine);
   outputToFile(currentLine);

   //get next line
   std::cout << "testing" << std::endl;
   processLine(currentLine);
   outputToFile(currentLine);

   if (currentLine[1].find("START") != currentLine[1].npos){
      address = std::stoi(currentLine[2]);
      locctr = address;
      outputToFile(currentLine);
      processLine(currentLine);

   }
   else{
      locctr = 0;
   }
   //at this point, locctr is accurate (I think)

   //MAIN LOOP
   while(currentLine[1].find("END") == currentLine[1].npos){
      //SYMTAB STUFF
      address = locctr;
      extFormat = false;
      if (currentLine[0][0] != '.'){
         if (SYMTAB.find(currentLine[0]) == SYMTAB.end()){
            SYMTAB.emplace(currentLine[0], address);
         }
         else{
            //TODO: Duplicate symbol error (duplicate symbol in SYMTAB)
         }
      }

      //regular code processing
      outputToFile(currentLine); //! testing
      processLine(currentLine);
      //We call instruction_formats after calling the writer to keep locctr accurate
      instruction_formats(currentLine);

   }
   

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
      //set the locctr to that starting address
      //write current line into intermediate file
      //read next line
         //end loop (if START)
   //else locctr is starting at 0  

   //while OPCODE != "END", do
      //if not a comment line
         //begin
            //if there is a symbol/label
               //begin
                  //search SYMTAB for that label
                  //if found
                     //error (duplicate symbol)
                  //else
                     //insert (LABEL/locctr) into SYMTAB
               //end

            //search OPTAB for OPCODE
            //if found
               //add 3 to locctr
            //else if 'WORD'
               //add 3 to locctr
            //else if 'RESW'
               //add 3 * #[OPERAND] to locctr  // #[OPERAND] == constant value attached to OPERAND
            //else if 'RESB'
               //add #[OPERAND] to locctr
            //else if 'BYTE'
               //begin
                  //find length of constant in bytes
                  //add length to locctr
               //end (if BYTE)
            //else
               //error for invalid OPCODE
         //end (if not a comment)
      //write line to intermediate file
      //read next line
   //while loop END

   //write last line to intermediate file
   //save (locctr - starting address) as program length
   //end of Pass 1
   inputFile.close();
   outputFile.close();
   return;
}
