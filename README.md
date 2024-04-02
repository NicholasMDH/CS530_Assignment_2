# CS530_Assignment_2
This will create an assembler for the SIC/XE family of machines, which converts assembler source files into assembled listing files.

## RESEARCH FOR ASSIGNMENT #2
What is a SYMTAB?
-> A SYMTAB (Symbol Table) is a data structure used to keep track of symbols (labels) and their corressponding memory addresses or values.

How do we generate a SMYTAB?
1. Parse the source code
   1. Read the source file, identify the labels, instructions, and operands (the value/quantity associated with the instruction)
2. Add information to the table
   1. When a label is encountered alongside its address or value, add it to the SYMTAB (Ex: "LABEL1 RESW 1" // "LABEL1" is the symbol, and "RESW 1" tells us one word of memory is to be allocated. The assembler would record "LABEL1" in the SYMTAB with its coressponding memory address)
3. Example SYMTAB:

| SYMBOL | ADDRESS |
| ---    | ---  |
| START  | 0000 |
| LABEL1 | 0003 |
| LABEL2 | 0006 |

Which assembler directives are processed during each pass?
1. During pass one, information is collected by the assembler about each directive in preparing for the second pass
2.  The second pass is where the actual object code generation and address calculation is resolved
3.  We will likely only be processing the START directive in pass one

What is an intermediate file? What is A listing file?
1. An intermediate file is a temporary file that contained the processed information that was parsed during the first pass. It is a rough draft of the final listing file. It will most likely contain the memory address of each instruction (first column), the label (if exists), the opcode/directive itself (next column), operand (if exists), and any other information that was processed during pass one. This will be the file that will be used as input during the second pass.
2. The second pass then uses this intermediate file as input to generate the listing final (the final draft)
3. The listing file, simply put, looks like the original SIC source file, but with the memory addresses and object code added

What does it mean to process BYTE/WORD directives?
1. The BYTE and WORD directives are used to allocate space in memory and define the initial values of data in the program. (Syntax Structure: "LABEL BYTE <data>") Note: BYTE also has flags to indicate data format. C = Character, X = Hexadecimal, B = Binary, D = Decimal, O = Octal
2. When processing these directives: calculate the size of the data, reserve memory space, and initialize the allocated memory with the specified data values

## Other Questions:
- How to generate object code?
