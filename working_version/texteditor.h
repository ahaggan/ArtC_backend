#include "input.h"

TextNode* allocate_text_node(char* c, TextNode* previous_node, Interface* interface, int x, int y);

TextNode* handle_initial_cell(char* overflow, char* nxt, char* curr, TextNode* current);
int text_overflow(char* overflow);
void handle_overflow(char* nxt, TextNode* current, char* overflow, char* curr);
void shuffle_active_cell(char *curr, TextNode* current, char* nxt);
void shuffle_rest_of_line(Coordinates active, Interface interface, TextNode* current, char* curr, char* nxt);
int shuffle_overflow(Coordinates* over, Interface interface, char* nxt);

FILE* open_file(char *file_name);
FILE* make_file(char *file_name);


void free_text_nodes(TextNode* head);
TextNode* make_cell(int width, int height, Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current);
void make_first_cell(Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current);
void make_middle_cells(Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current);
void make_last_cell(Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current);
void update_text_node(TextNode* current, Interface* interface);
int character_provided(TextNode* cell, char* character);

void set_node_attributes(Interface* interface, int row, int column, TextNode* new_node);
void set_node_text(Interface* interface, char* text, TextNode* new_node);

void write_text_to_cell(Interface* interface, FILE* file_name, int row, int column);

void handle_enter_shuffling(Coordinates active, Interface* interface);
void enter_shuffle(Coordinates active, Interface* interface, char copy[interface->editor_columns][3], char nxt[interface->editor_columns][3]);

int rest_of_row_empty(Coordinates active, Interface* interface);
int entire_row_empty(int row, Interface* interface);

void store_row_backup(Coordinates active, Interface* interface, char backup[interface->editor_columns][3]);
void shift_cells_back_one(Coordinates active,  Interface* interface, char backup[interface->editor_columns][3]);

TextNode* load_text_into_cell(char c, int* row, int* column, Interface* interface, TextNode* current);
void concatenate_to_previous_text(Coordinates active, Coordinates cell, Interface* interface, char copy[interface->editor_columns][3]);
void shift_rows_back_one(Coordinates active, Interface* interface);

void text_after_active_column(Coordinates active, Coordinates cell, Interface* interface, char copy[interface->editor_columns][3]);

void shift_row_up(Coordinates active, Coordinates cell, Interface* interface, char copy[interface->editor_columns][3]);
void shift_row_down(Coordinates active, Coordinates cell, Interface* interface, char move[interface->editor_columns][3], char copy[interface->editor_columns][3]);

void check_row_above(Coordinates active, Coordinates* cell, Interface* interface);
void hold_row_to_be_moved(Interface* interface, char move[interface->editor_columns][3], Coordinates active, Coordinates cell);
void hold_backup_of_next_row(Interface* interface, char copy[interface->editor_columns][3], Coordinates active);
void move_row(Interface* interface, Coordinates active, char move[interface->editor_columns][3]);
void empty_active_row(Interface* interface, Coordinates active);
void shift_rows_down_one(Interface* interface, Coordinates active, Coordinates cell, char move[interface->editor_columns][3], char copy[interface->editor_columns][3]);
void tab_save_row_backup(Interface* interface, Coordinates active, Coordinates cell, char copy[interface->editor_columns][3]);

void add_tab_space(Interface* interface, Coordinates active, int tab);
void tab_shift_row(Interface* interface, Coordinates active, char copy[interface->editor_columns][3], int tab);
void tab_unindent_garbage_fix(Interface* interface, Coordinates active, int tab);
