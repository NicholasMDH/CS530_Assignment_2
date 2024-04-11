//This will hold all of our shared code and functions between both passes

bool validate_input(int arguments, const char *argumentList[]); //return 0 if no issues, return 1 if issues
void pass_1();
void pass_2();

void checkForComments();
void instruction_formats();