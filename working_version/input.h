#include "display.h"
#include <time.h>

#define TAB_LENGTH 3

int parser(Draw *fractal); //SHOULD BE IN PARSE.H!!!!!!!!!!
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
void write_text_to_file(Interface* interface, char* file_name);
void handle_overwriting(Coordinates active, Interface* interface, char* overflow);

int SDL_Main_Menu_Events(Main_Menu* main_menu);
int within_button(int x, int y, SDL_Rect button);

int SDL_Challenges_Menu_Events(Challenges_Menu* challenges);



/* Text Editor */
void make_text_editor(int width, int height, Interface* interface);
void update_text_editor(int width, int height, Interface* interface);
TextNode* allocate_text_node(char* c, TextNode* previous_node, Interface* interface, int x, int y);
void print_composition(TextNode* start);

void load_text_into_text_editor(char* file_name, Interface* interface);

TextNode* handle_initial_cell(char* overflow, char* nxt, char* curr, TextNode* current);
int text_overflow(char* overflow);
void handle_overflow(char* nxt, TextNode* current, char* overflow, char* curr);
void shuffle_active_cell(char *curr, TextNode* current, char* nxt);
void shuffle_rest_of_line(Coordinates active, Interface interface, TextNode* current, char* curr, char* nxt);
int shuffle_overflow(Coordinates* over, Interface interface, char* nxt);

void handle_backwriting(Coordinates active, Interface* interface);

void handle_enter_shuffling(Coordinates active, Interface* interface);

void tab(Coordinates active, Interface* interface, int direction);
void find_next_active_node(Coordinates* active, Interface* interface);
void find_previous_active_node(Coordinates* active, Interface* interface);
int final_active_node(Coordinates active, Interface interface);

void console_text_editor(Interface interface);
