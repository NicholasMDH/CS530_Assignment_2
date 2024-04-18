// #includes
#include "Assembler.h"
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
const int   address_Column = 4,
            symbol_Column = 9,
            instruction_Column = 8,
            operand_Column = 20,
            opcode_Column = 4,
            comment_Column = 20;

bool validate_input(const std::string passedFile) {
    //Check to make sure that the user inputted the correct type of file (.sic)
    std::cout << "file extension: " + passedFile.substr(passedFile.length() - 4) << std::endl; //TESTING
    if (".sic" != passedFile.substr(passedFile.length() - 4)) {
        std::cout << "incompatible file extension, exiting program" << std::endl;
        return 1;
    }
    return 0;
}

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