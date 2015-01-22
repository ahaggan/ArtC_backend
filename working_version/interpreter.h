/*
Module takes an interpreter array, contructed in the parser and assigns values from it to the draw fractal structure. 
This is used to draw the fractal image on the canvas.
*/

#include "parser.h"

//Searches for the end of the interpreter array
void search_for_end(Prog* program);

//Assigns the current instruction to a given iteration of the fractal structure
void assign_value(Prog* program, int iteration);

//Checks for an if statement about the current iteration
int check_condition(Prog* program, int iteration);

/*
Interprets the word values for size and line thickness
*/
void interpret_size_word(Prog *program, int iteration);
void interpret_thick_word(Prog *program, int iteration);
