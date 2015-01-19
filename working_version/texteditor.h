#include "input.h"

#define CURSOR_X 9
#define CURSOR_Y 24
#define CURSOR_W 1
#define CURSOR_H 19

#define TEXT_CELL_W 9
#define TEXT_CELL_H 24

/* Text Editor Data Structure */
TextNode* make_cell(int width, int height, Coordinates curr, Interface* interface, 
                    TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], 
                    TextNode* current);
void make_first_cell(Coordinates curr, Interface* interface, 
                    TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], 
                    TextNode* current);
void make_middle_cells(Coordinates curr, Interface* interface, 
                    TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], 
                    TextNode* current);
void make_last_cell(Coordinates curr, Interface* interface, 
                    TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], 
                    TextNode* current);

void update_text_cursor(Interface* interface);

TextNode* allocate_text_node(char* c, TextNode* previous_node, 
                    Interface* interface, int x, int y);
void update_text_node(TextNode* current, Interface* interface);

void set_node_attributes(Interface* interface, int row, int column, 
                         TextNode* new_node);
void set_node_text(Interface* interface, char* text, TextNode* new_node);

/* Text File Handling */ 

FILE* open_file(char *file_name);
FILE* make_file(char *file_name);

void write_text_to_cell(Interface* interface, FILE* file_name, int row, 
                    int column);
TextNode* load_text_into_cell(char c, int* row, int* column, Interface* interface, 
                    TextNode* current);

/* Text Manipulation */

//Carriage Return
void shift_row_down(Coordinates active, Coordinates cell, Interface* interface, 
                    char move[interface->editor_columns][3], 
                    char copy[interface->editor_columns][3]);
void hold_row_to_be_moved(Interface* interface, char move[interface->editor_columns][3], 
                    Coordinates active, Coordinates cell);
void hold_backup_of_next_row(Interface* interface, char copy[interface->editor_columns][3], 
                    Coordinates active);
void replace_row_below(Interface* interface, Coordinates active, 
                    char move[interface->editor_columns][3]);
void set_row_to_empty(Interface* interface, Coordinates active);
void shift_rows_down_one(Interface* interface, Coordinates active, Coordinates cell, 
                    char move[interface->editor_columns][3], 
                    char copy[interface->editor_columns][3]);

//Backspace
void shift_row_up(Coordinates active, Coordinates cell, Interface* interface, 
                    char copy[interface->editor_columns][3]);
void check_row_above(Coordinates active, Coordinates* cell, Interface* interface);
void text_after_active_column(Coordinates active, Coordinates cell, 
                    Interface* interface, char copy[interface->editor_columns][3]);
void store_row_backup(Coordinates active, Interface* interface, 
                    char backup[interface->editor_columns][3]);
void shift_cells_back_one(Coordinates active, Interface* interface, 
                    char backup[interface->editor_columns][3]);
void concatenate_to_previous_text(Coordinates active, Coordinates cell, 
                    Interface* interface, char copy[interface->editor_columns][3]);
void shift_rows_back_one(Coordinates active, Interface* interface);

//Tab
void tab_save_row_backup(Interface* interface, Coordinates active, Coordinates cell, 
                    char copy[interface->editor_columns][3]);
void add_tab_space(Interface* interface, Coordinates active, int tab);
void tab_shift_row(Interface* interface, Coordinates active, char copy[interface->editor_columns][3], int tab);
void tab_unindent_garbage_fix(Interface* interface, Coordinates active, int tab);

//Overwriting (shuffling cells along by one owing to text input)
TextNode* handle_initial_cell(char* overflow, char* nxt, char* curr, TextNode* current);
void shuffle_active_cell(char *curr, TextNode* current, char* nxt);
void shuffle_rest_of_line(Coordinates active, Interface interface, 
                    TextNode* current, char* curr, char* nxt);
int text_overflow(char* overflow);
int shuffle_overflow(Coordinates* over, Interface interface, char* nxt);
void handle_overflow(char* nxt, TextNode* current, char* overflow, char* curr);

/* Helper Functions */
int rest_of_row_empty(Coordinates active, Interface* interface);
int entire_row_empty(int row, Interface* interface);
int is_empty_cell(char* character);
