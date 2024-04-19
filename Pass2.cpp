/*
Team:
Nicholas Dibello-Hitta, cssc4049, RedID: 828490930
Dylan Agoncillo, cssc4051, RedID: 824340550

*/

#include "Assembler.h"
#include "AppendixA.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

//We should pass the input file, symtab, and littab into Pass 2
void pass_2(std::string sourceFile) {
   std::cout << "In pass 2 ----------------------------------------------------------------------------" << std::endl; // just for me :)

   //open necessary files
   std::vector<std::string> currentLine(5);

   std::string tempFileName = sourceFile.substr(0, sourceFile.length() - 4) + ".temp";
   inputFile.exceptions(std::ifstream::failbit);
   inputFile.open(tempFileName);

   std::string outputFileName = sourceFile.substr(0, sourceFile.length() - 4) + ".lis";
   outputFile.exceptions(std::ofstream::failbit);
   outputFile.open(outputFileName);

   assemblerPass = 2;

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
   while(currentLine[2].find("END") == currentLine[2].npos) {
      std::cout << "processLine" << std::endl;
      processLine(currentLine);
      std::cout << "assemble_object" << std::endl;
      assemble_object(currentLine);
      std::cout << "outputToFile" << std::endl;
      outputToFile(currentLine);
      std::cout << "end of loop" << std::endl;
   }

   //housekeeping
   inputFile.close();
   outputFile.close();
   return;
}
