#include "display.h"

int parse(Interface interface, Draw *fractal[NO_OF_LOOPS]); //SHOULD BE IN PARSE.H!!!!!!!!!!
void SDL_Window_Events(SDL_Event event, Interface* interface);
int SDL_Events(Interface* interface);
int SDL_Text_Editor_Events(SDL_Event event, Interface* interface);
typedef enum events{ 
	generate_clicked = 1,
	text_edited
} Events;
