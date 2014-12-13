#include "display.h"

#define TAB_LENGTH 3

int parse(Interface interface, Draw *fractal[NO_OF_LOOPS]); //SHOULD BE IN PARSE.H!!!!!!!!!!

int SDL_Events(Interface* interface);
void SDL_Window_Events(SDL_Event event, Interface* interface);

int SDL_Text_Editor_Events(SDL_Event event, Interface* interface);

int top_row(Coordinates active);
int bottom_row(Coordinates active);
int start_column(Coordinates active);
int end_column(Coordinates active);

int first_cell(Coordinates active);
int last_cell(Coordinates active);

void set_active_text_cell(int row, int column, Interface* interface);

FILE* open_file(char *file_name);

FILE* make_file(char *file_name);
void write_text_to_file(TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS]);
typedef enum events{ 
	generate_clicked = 1,
	text_edited
} Events;
