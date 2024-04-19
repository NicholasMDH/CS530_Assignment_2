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
int locctr = 0,
    programCounter = 0,
    baseRegister = 0,
    opni = 0,
    xbpe = 0,
    displacement = 0,
    objectCode = 0;
std::unordered_map<std::string, int> SYMTAB;
//column sizes
const int   address_Column = 4,
            symbol_Column = 9,
            instruction_Column = 8,
            operand_Column = 20,
            opcode_Column = 4,
            comment_Column = 20;
int assemblerPass = 0;

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
    std::cout << "Line 54" << std::endl;
    //get the first line
    std::getline(inputFile, temp);
    std::cout << "temp variable: " << temp << std::endl; //!testing, this works
    std::cout << "assemblerPass: " << std::to_string(assemblerPass) << std::endl;

    //if it's a comment, just pass it as the current line
    if (temp[0] == '.') currentLine.push_back(temp);
    //if it's a regular line, separate it into symbol, instruction, operand, and 
    else if (assemblerPass == 1) {
        currentLine.push_back(temp.substr(0, symbol_Column));
        currentLine.push_back(temp.substr(symbol_Column, instruction_Column));
        currentLine.push_back(temp.substr(symbol_Column + instruction_Column, operand_Column));
        //if format 4
        if (temp.size() > (symbol_Column + instruction_Column + operand_Column)) {
            currentLine.push_back(temp.substr(symbol_Column + instruction_Column + operand_Column));
        }
    } else if (assemblerPass == 2) {
        currentLine.push_back(temp.substr(0, address_Column));
        currentLine.push_back(temp.substr(address_Column + 1, symbol_Column)); //have to include the buffer between address and symbol
        currentLine.push_back(temp.substr(address_Column + 1 + symbol_Column, instruction_Column));
        currentLine.push_back(temp.substr(address_Column + 1 + symbol_Column + instruction_Column, operand_Column));
        //if format 4
        if (temp.size() > (address_Column + 1 + symbol_Column + instruction_Column + operand_Column)) {
            currentLine.push_back(temp.substr(address_Column + 1 + symbol_Column + instruction_Column + operand_Column));
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
//TODO: to write object code to output file (convert from string)
void outputToFile(std::vector<std::string> &currentLine) {
    //write comments straight to file
    if (currentLine[0][0] == '.') {
        outputFile << currentLine[0] << std::endl;
        return;
    }

    if (assemblerPass == 1) {
        //calculate address field //!Fix to prepend zeroes!
        outputFile << std::setw(address_Column) << std::left << std::hex << locctr;
        
        //buffer
        outputFile << ' ';

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
    }
    else if (assemblerPass == 2) {
        //calculate address field //!Fix to prepend zeroes!
        outputFile << std::setw(address_Column) << std::left << std::hex << currentLine[0];
        
        //buffer
        outputFile << ' ';

        //Symbols
        outputFile << std::setw(symbol_Column) << std::left << currentLine[1];

        //Extended format?
        if (extFormat) {
            outputFile << '+';
        } else {
            outputFile << ' ';
        }

        //Instructions
        outputFile << std::setw(instruction_Column) << std::left << currentLine[2];

        //Operand //TODO: Fix formatting for # and =
        outputFile << std::setw(operand_Column) << std::left << currentLine[3];

        //!testing, I want to see what's in currentLine
        std::cout << "printing out the value of currentLine again in outputToFile" << std::endl;
        for (int i = 0; i < currentLine.size(); i++) {
            std::cout << "currentLine[" << std::to_string(i) << "]:" << currentLine[i] << ":\n";
        }
        std::cout << "testing" << std::endl;

        //Assembled object code
        //! THIS (OBJECT CODE) NEEDS TO BE CONVERTED TO HEX
        if (objectCode) outputFile << std::setw(opcode_Column) << std::left << std::hex << std::stoi(currentLine[4]);
        std::cout << "line 148" << std::endl;
    }

    //End the line
    outputFile << std::endl;
}

//TODO: BYTE operators and handle END line
//This figure out the format of a given instruction
void instruction_formats(std::vector<std::string> currentLine) {

    if (currentLine[1][0] == '+'){
        extFormat = true;
    }
    else if (currentLine[1][0] == ' '){
        //nothing to do
    }
    else{
        //error throw?
    }

    if (AppendixA::OPTAB.find(currentLine[1]) != AppendixA::OPTAB.end()){
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
        std::cout << "THIS IS REALLY BAD AND NEEDS FIXING URGENTLY" << std::endl; //! this happens on the last line
        std::cout << "the current value of currentLine[1]:" << currentLine[1] << ": end " <<std::endl;
    }
}

//Assemble object code from a given line
void assemble_object(std::vector<std::string> &currentLine) {
    if (currentLine[0][0] == '.') { //don't assemble comments :)
        return;
    }
    objectCode = 0;
    extFormat = false;
    std::cout << "is " << currentLine[2] << " in our OPTAB? : "; //! TESTING
    //is this command in our appendix A?
    if (AppendixA::OPTAB.find(currentLine[2]) != AppendixA::OPTAB.end() || AppendixA::OPTAB.find(currentLine[2].substr(1)) != AppendixA::OPTAB.end()) {
        std::cout << "yes!" << std::endl; //! TESTING
        //set program counter & first 1 1/2 bytes
        programCounter = std::stoi(currentLine[0], nullptr, 16) + 3;
        xbpe = 0;
        if (currentLine[2][0] == '+'){ //if it's extended format remove '+' before search
            opni = AppendixA::OPTAB.at(currentLine[2].substr(1));
            programCounter += 1; //one more byte for format 4
            xbpe += 1;
            //extFormat = true;
        } else opni = AppendixA::OPTAB.at(currentLine[2]);
        
        //find symbols in SYMTAB
        if (SYMTAB.find(currentLine[3].substr(0, currentLine[3].find_first_of(", "))) != SYMTAB.end()) {
            //set displacement equal to the location of the symbol in memory
            displacement = SYMTAB.at(currentLine[3].substr(0, currentLine[3].find_first_of(", ")));
        }

        //if PC relative
        if (-2048 <= (displacement - programCounter) <= 2047) {
            std::cout << "PC Relative Addressing" << std::endl;
            displacement -= programCounter;
            xbpe += 2;
        }

        //TODO: base relative

        //Other addressing modes
        if (currentLine[3][0] == '#') {
            std::cout << "Immediate Addressing" << std::endl;
            opni += 1;
        } else if (currentLine[3][0] == '@') {
            std::cout << "Indirect Addressing" << std::endl;
            opni += 2;
        } else if (currentLine[3].substr(currentLine[3].size()-2).compare(",X") == 0) {
            std::cout << "Indexed Addressing" << std::endl;
            opni += 8;
        }
        else {
            std::cout << "Direct Addressing" << std::endl;
            opni += 3;
        }

        //assign values to objectCode
        std::cout << "opni: " << std::to_string(opni) << std::endl;
        std::cout << "xbpe: " << std::to_string(xbpe) << std::endl;
        std::cout << "displacement: " << std::to_string(displacement) << std::endl;
        
        if (extFormat) {
            objectCode += opni << 24;
            objectCode += xbpe << 20;
        } else {
            objectCode += opni << 16;
            objectCode += xbpe << 12;
        }
        objectCode += static_cast<unsigned int>(displacement & 0xFFF);
        std::cout << "Line 254" << std::endl;
    }
    else { //it's an assembler directive
        std::cout << " NO :(" << std::endl;
        //TODO:
    }

    //append assembled code to currentLine
    std::cout << "objectCode for line " << currentLine[0] << " is: " << std::to_string(objectCode) << std::endl;
    currentLine.push_back(std::to_string(objectCode));
    
    //! TESTING
    //!testing, I want to see what's in currentLine
    for (int i = 0; i < currentLine.size(); i++) {
        std::cout << "currentLine[" << std::to_string(i) << "]:" << currentLine[i] << ":\n";
    }
}