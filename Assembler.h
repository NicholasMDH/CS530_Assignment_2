//This will hold all of our shared code and functions between both passes

#include <string>

bool validate_input(std::string passedFile); //return 0 if no issues, return 1 if it has issues
void pass_1();
void pass_2();

void checkForComments();
void instruction_formats();