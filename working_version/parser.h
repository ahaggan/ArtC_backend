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
#define ACTION {"colour", "move", "size", "shape", "startx", "starty", "endx", "endy", "type", "iterations"}
#define ACTION_SIZE 10
#define ATTRIBUTE { "red", "green", "blue", "pink", "purple", "brown", "STOP", "NEXT", "up", "down", "left", "right", "STOP", "NEXT", "0", "STOP", "NEXT", "circle", "triangle_outline", "square", "line", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "sierpinski", "tree", "carpet", "snowflake", "star", "STOP", "NEXT", "0", "STOP", "NEXT"}
#define ATTRIBUTE_SIZE 45

typedef struct action{
	char *name;
	char **instruction;
} action;

typedef struct prog{
    char words[MAX_WORDS][WORD_LENGTH];
    int current_word;
    action actions[ACTION_SIZE];
    Draw *fractal;
    char interpreter[NO_OF_INSTRUCTIONS][WORD_LENGTH];
    int interpreter_index;
    
}prog;

typedef enum action_word {
colour, move, size, shape, startx, starty, endx, endy, type, iterations
} action_word;
/*
typedef enum attribute_word{red, green, blue, pink, purple, brown, up, down, left, right, circle, triangle_outline, square, line, triangle, sierpinski, tree, carpet, snowflake, star}attribute_word;
*/
void for_loop(prog *program, int start, int end);
int check_condition(prog *program, int iteration);
void search_for_end(prog *program);
void interpreter(prog *program);
void assign_value(prog *program, int iteration);
int check_if(char *word);
void initialise_words_array(prog *program);
void test_interpreter(prog *program);
void initialise_interpreter_array(prog *program);
void make_default(prog *program);
int validate(prog *program);
int funclist(prog *program);
int function(prog *program);
int conditional(prog *program);
int loop(prog *program);
int statement(prog *program);
int check_action(char *word);
int attribute(prog *program);
void create_struct_array(action *actions);
