#pragma once
//This will hold all of our shared code and functions between both passes

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <vector>

bool validate_input(std::string passedFile); //return 0 if no issues, return 1 if it has issues
void pass_1(std::string sourceFile);
void pass_2();

void checkForComments();

extern std::unordered_map<std::string, int> SYMTAB;
extern std::unordered_map<std::string, int> LITTAB;
extern std::ifstream inputFile;
extern std::ofstream outputFile;