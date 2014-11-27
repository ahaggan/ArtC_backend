/* Checks two word user input. Also creates an array of action structures,
*  as many as there are words in the FIRST_WORD array. 
*  It then assigns each structure's name element with a word from said array
*  It also assigns, for each action in turn, the corresponding attributes.
*  When the NEXT word is found, the assignment is moved to the next action.
*  Uses the structures to validate user inputs, making sure action linked to
*  attribute.
*
*   It creates a draw structure to then pass to the SDL draw function
*/

#include "artc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FIRST_WORD { "colour", "move", "size", "shape", "startx", "starty", "endx", "endy", "type"}
typedef enum action_word {
colour, move, size, shape, startx, starty, endx, endy, type
} action_word;
#define FIRST_WORD_SIZE 9
//STOP is stored in each structure's instruction set, NEXT notifies program to start stoting the instructions in the next action structure
//Used the "0" string to check an integer to allow for the user to enter 0 aswell as other numbers - due to the way atoi() was used.
#define SECOND_WORD { "red", "green", "blue", "pink", "purple", "STOP", "NEXT", "up", "down", "left", "right", "STOP", "NEXT", "0", "STOP", "NEXT", "circle", "square", "line", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "0", "STOP", "NEXT", "triangle", "sierpinski", "STOP", "NEXT"}
#define SECOND_WORD_SIZE 37

#define YES 1
#define NO 0
#define MAX_LENGTH 20

typedef struct action{
	char *name;
	char **instruction;
} action;

void create_struct_array(action *actions);
void clear_buffer(void);
void get_input(action *actions, char *first_input, char *second_input, draw *fractal);
void update_values(Draw *fractal, char *first_input, char *second_input);
void assign_value(Draw *fractal, action_word i, char *input);
int read_file_line(FILE *fp, action *actions, char* first_input, char* second_input);
void make_default(Draw *fractal);
