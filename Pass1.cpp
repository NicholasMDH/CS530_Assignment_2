#include "Assembler.h"
#include "AppendixA.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

void pass_1(std::string sourceFile) {
   //open necessary files
   std::vector<std::string> currentLine;
   inputFile.exceptions(std::ifstream::failbit);
   inputFile.open(sourceFile);

   std::string outputFileName = sourceFile.substr(0, sourceFile.length() - 4) + ".temp";
   outputFile.exceptions(std::ofstream::failbit);
   outputFile.open(outputFileName);

   int address;
   assemblerPass = 1;

   //*SETUP
   //pass first comment line to temp file
   processLine(currentLine);
   outputToFile(currentLine);

   //next line should be start
   processLine(currentLine);
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

   //*MAIN LOOP
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
      outputToFile(currentLine);
      processLine(currentLine);
      //We call instruction_formats after calling the writer to keep locctr accurate
      instruction_formats(currentLine);

   }
   
   inputFile.close();
   outputFile.close();
   return;
}
