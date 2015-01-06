#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "display.h"

#define MAX_ITERATIONS 10
#define NO_OF_INSTRUCTIONS 60
//#define VALID_SYMBOLS A-Z, a-z, 0-9, {, }
#define MAX_WORDS 100
#define WORD_LENGTH 15
#define TRUE 1
#define FALSE 0
#define strings_match(A, B) (strcmp(A, B) == 0)
#define ACTION {"colour", "move", "size", "shape", "startx", "starty", "endx", "endy", "type", "iterations", "linethickness"}
#define ACTION_SIZE 11
#define ATTRIBUTE { "black", "red", "pink", "fuchsia", "purple", "blue", "navy", "turquoise", "green", "lime", "yellow", "olive", "gold", "orange", "grey", "brown", "white", "STOP", "NEXT", "up", "down", "left", "right", "STOP", "NEXT", "0", "STOP", "NEXT", "circle", "triangle_outline", "square", "line", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "sierpinski", "tree", "carpet", "snowflake", "star", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT"}
#define ATTRIBUTE_SIZE 63

typedef struct action {
	char* name;
	char** instruction;
} Action;

typedef struct prog {
	char words[MAX_WORDS][WORD_LENGTH];
	int current_word;
	Action actions[ACTION_SIZE];
	Draw* fractal;
	char interpreter[NO_OF_INSTRUCTIONS][WORD_LENGTH];
	int interpreter_index;
} Prog;

typedef enum action_word {
	colour, move, size, shape, startx, starty, endx, endy, type, iterations, linethickness
} Action_Word;
/*
typedef enum attribute_word{red, green, blue, pink, purple, brown, up, down, left, right, circle, triangle_outline, square, line, triangle, sierpinski, tree, carpet, snowflake, star}attribute_word;
*/
void for_loop(Prog* program, int start, int end);
int check_condition(Prog* program, int iteration);
void search_for_end(Prog* program);
void interpreter(Prog* program);
void assign_value(Prog* program, int iteration);
int check_if(char* word);
void initialise_words_array(Prog* program);
void test_interpreter(Prog* program);
void initialise_interpreter_array(Prog* program);
void make_default(Prog* program);
int validate(Prog* program);
int funclist(Prog* program);
int function(Prog* program);
int conditional(Prog* program);
int loop(Prog* program);
int statement(Prog* program);
int check_action(char* word);
int attribute(Prog* program);
void create_struct_array(Action* actions);
