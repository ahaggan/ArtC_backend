#include "display.h"
#include <unistd.h>
#include <time.h>

#define  ERROR_MAX  100

void initialise_text_editor(Interface* interface, Mode mode, char* file_name);
void make_text_editor(int width, int height, Interface* interface);
void update_text_editor(int width, int height, Interface* interface);
void write_text_to_file(Interface* interface, char* file_name);
void load_text_into_text_editor(char* file_name, Interface* interface);

int parser(Draw *fractal, char *file_name);

void generate_fractal(Draw *fractal, Interface interface, int i);

int Interface_Events(Interface* interface);

void display_error(Interface* interface);
