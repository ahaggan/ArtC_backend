/*  This module tests the users program for gramatical accuracy. 
    It will return an error if the input file(containing a program) is incorrect. 

    As the program is tested, the correct attributes are assigned to an interpreter array. 
    If the program is written correctly this array is passed to the intereter module which 
    will assign values from the user to the given fractal.
    This fractal is then passed back to the interface.
*/

#include <stdio.h>
#include "artc.h"

#define  MAX_ITERATIONS  10

//Used to define sizes of arrays.
#define  NO_OF_INSTRUCTIONS  1000
#define  MAX_WORDS  1000
#define  WORD_LENGTH  15
//Function to compare strings - looked neater/easier to read than strcmp
#define  strings_match(A, B)  (strcmp(A, B) == 0)

//Arrays used to create the action struct, add new actions or attributes here.
#define  ACTION  {"colour", "move", "size", "shape", "startx", "starty", "endx", "endy", "type", "iterations", "linethickness", "angle", "splits"}
#define  ACTION_SIZE  13
#define  ATTRIBUTE  {"black", "red", "pink", "fuchsia", "purple", "blue", "navy", "turquoise", "green", "lime", "yellow", "olive", "gold", "orange", "grey", "brown", "white", "random", "transparent", "STOP", "NEXT", "up", "down", "left", "right", "STOP", "NEXT", "small", "medium", "large", "micro", "gargantuan", "tiddly", "0", "STOP", "NEXT", "circle", "triangle", "square", "line", "image", "random", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "sierpinski", "tree", "star", "STOP", "NEXT", "0", "STOP", "NEXT", "thin", "thick", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT"}
#define  ATTRIBUTE_SIZE  75

//Struct contains an action and all instructions/attributes that are valid with said action
typedef struct action {
    char* name;
    char** instruction;
} Action;

//Contains the current program(copied from a file), an array of valid actions and an interpreter array.
//This contains all the information needed to parse and interpret any program given.
typedef struct prog {
    char words[MAX_WORDS][WORD_LENGTH];
    int current_word;
    Action actions[ACTION_SIZE];
    Draw* fractal;
    char interpreter[NO_OF_INSTRUCTIONS][WORD_LENGTH];
    int interpreter_index;
    FILE *error;
} Prog;

//Calls the functions that initialise the Prog struct's arrays
void initialise_arrays(Prog *program);

//Calls the interpreter function that writes the parsed values 
//to the fractal array
void interpreter(Prog* program);

//checks that the action used in the if statement is an action 
//that an if staement is allowed for
int check_if(char* word);

//Initialises the first char of each word in the words array 
//with the '\0' character - for checking for the end of a given file
void initialise_words_array(Prog* program);

//Initialises the first char of each word in the interpreter array 
//with the '\0' character
void initialise_interpreter_array(Prog* program);

//Begins the process of parsing the given program, check for a correct 
//start then passes to the recursive part of parser
int validate(Prog* program);

//Checks for the end of the program or else calls the function function 
int funclist(Prog* program);

//checks the possible options for our grammer( "if", "for" or nothing) 
//and calls the relevant functions
int function(Prog* program);

//Checks that "then {" follows your statement from the if function.
//Then calls funclist to check the contents of the if function
//and for an end brace.  
int conditional(Prog* program);

//Checks that the for loop has been written correctly
//It then calls the for_loop function
int loop(Prog* program);

//Adds repeated values to the interpreter array when a for loop is used
//start and end are the numbers defined by the user in their loop
int for_loop(Prog* program, int start, int end);

//Checks for a valid action attribute statement
//Calls check_action and attribute to do this
int statement(Prog* program);

//Checks that the word passed is a correct action word
int check_action(char* word);

//Checks that the current word is an attribute
//if the statement isn't part of an if or for it assigns the values to the interpreter array
int attribute(Prog* program);

//Creates an arrays of action structures with corresponding action and
//attribute words.
void create_struct_array(Action* actions);
