#include "display.h"
#include <unistd.h>


#define  ERROR_MAX  100

void initialise_text_editor(Interface* interface, Mode mode, char* file_name);
void make_text_editor(int width, int height, Interface* interface);
void update_text_editor(int width, int height, Interface* interface);
void write_text_to_file(Interface* interface, char* file_name);
void load_text_into_text_editor(char* file_name, Interface* interface);

void generate_fractal(Draw *fractal, SDL_Win *window, int i);

int Interface_Events(Interface* interface);

void set_challenges_based_on_level(char* file_name, Interface* interface);
void display_error(Interface* interface);

