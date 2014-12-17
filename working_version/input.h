#include "display.h"
#include <time.h>

#define TAB_LENGTH 3

int parse(Interface interface, Draw *fractal); //SHOULD BE IN PARSE.H!!!!!!!!!!
int Interface_Events(Interface* interface);
void SDL_Window_Events(SDL_Event event, Interface* interface);
int SDL_Text_Editor_Events(SDL_Event event, Interface* interface);
int top_row(Coordinates active);
int bottom_row(Coordinates active, Interface interface);
int start_column(Coordinates active);
int end_column(Coordinates active, Interface interface);
int first_cell(Coordinates active);
int last_cell(Coordinates active, Interface interface);
void set_active_text_cell(int row, int column, Interface* interface);
FILE* open_file(char *file_name);
FILE* make_file(char *file_name);
void write_text_to_file(TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS]);
void handle_overwriting(Coordinates active, Interface* interface, char overflow[3]);

typedef enum events{
	generate_clicked = 1,
	text_edited,
	main_menu
} Events;

int SDL_Menu_Events(Main_Menu* main_menu);
int within_button(int x, int y, SDL_Rect button);

int interface(SDL_Win* window, TTF_Font* font, TTF_Font* button_font);
