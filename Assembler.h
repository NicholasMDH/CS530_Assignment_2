#pragma once
//This will hold all of our shared code and functions between both passes

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <vector>

bool validate_input(const std::string passedFile); //return 0 if no issues, return 1 if it has issues
void pass_1(std::string sourceFile);
void pass_2(std::string sourceFile);

//utility functions
void remove_whiteSpaces(std::vector<std::string> &currentLine);
void processLine(std::vector<std::string> &currentLine);
void outputToFile(std::vector<std::string> &currentLine);
void instruction_formats(std::vector<std::string> currentLine);

//global variables
extern std::ifstream inputFile;
extern std::ofstream outputFile;
extern bool extFormat;
extern int locctr;
extern std::unordered_map<std::string, int> SYMTAB;
extern const int address_Column, symbol_Column, instruction_Column, operand_Column, opcode_Column, comment_Column;