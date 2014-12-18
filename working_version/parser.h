#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"display.h"
#define MAX_ITERATIONS 10
//#define VALID_SYMBOLS A-Z, a-z, 0-9, {, }
#define MAX_WORDS 100
#define WORD_LENGTH 15
#define TRUE 1
#define FALSE 0
#define strings_match(A, B) (strcmp(A, B) == 0)
#define ACTION {"colour", "move", "size", "shape", "startx", "starty", "endx", "endy", "type", "iterations"}
#define ACTION_SIZE 10
#define ATTRIBUTE { "red", "green", "blue", "pink", "purple", "brown", "STOP", "NEXT", "up", "down", "left", "right", "STOP", "NEXT", "0", "STOP", "NEXT", "circle", "triangle_outline", "square", "line", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "triangle", "sierpinski", "tree", "carpet", "snowflake", "star", "STOP", "NEXT", "0", "STOP", "NEXT"}
#define ATTRIBUTE_SIZE 46
#define YES 0
#define NO 1
/*
typedef struct draw{
  char* colour[MAX_ITERATIONS];
  char* move;
  int size;
  char* shape[MAX_ITERATIONS];
  int height;
  int startx;
  int starty;
  int endx;
  int endy;
  char* type[MAX_ITERATIONS];
  int iterations;
} Draw;
*/
typedef struct action{
	char *name;
	char **instruction;
} action;

typedef struct prog{
    char words[MAX_WORDS][WORD_LENGTH];
    int current_word;
    action actions[ACTION_SIZE];
    Draw *fractal;
    int if_check;
    int for_check;
    int start_iteration;
    int end_iteration;
}prog;

typedef enum action_word {
colour, move, size, shape, startx, starty, endx, endy, type, iterations
} action_word;

void check_if(prog *program);
void initialise_words_array(prog *program);
void test_interpreter(prog *program);
void assign_value(prog *program, action_word i);
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
