/*
Module controls general interface commands; 
it calls parser and fractal functions, taking a users code and, 
if written correctly, displaying the user's fractal on the canvas.
*/

#include "display.h"
#include <unistd.h>

#define  ERROR_MAX  100
//Initialises the text editor/canvas screen
void initialise_interface(Menu* main_menu, Interface* interface, Mode mode);

//Controls the animation of a chosen fractal
void generating(Draw *fractal, Interface *interface);

//Selects the file/text to be displayed in the text editor
void set_code_file(Interface *interface, Mode mode, char* file_name);
//Chooses which challenge level needs to be displayed from user input
void set_challenges_based_on_level(char* file_name, Interface* interface);
/*
    The following write the respective challenge text into the text editor
*/
void beginner_challenges(Interface *interface);
void intermediate_challenges(Interface *interface);
void expert_challenges(Interface *interface);


Interface_Action Interface_Events(Interface* interface);
void initialise_text_editor(Interface* interface, Mode mode, char* file_name);
void update_text_editor(int width, int height, Interface* interface);
void write_text_to_file(Interface* interface, char* file_name);
void generate_fractal(Draw *fractal, SDL_Win *window, int i);
