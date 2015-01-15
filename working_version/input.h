#include "interface.h"

#define  EMPTY_CELL  "¬"
#define  TAB_LENGTH  3

int within_button(int x, int y, SDL_Rect button);

int SDL_Text_Editor_Events(SDL_Event event, Interface* interface);

void mouse_move_to_cell(Interface* interface, int mouse_x, int mouse_y);
void find_previous_cell_on_row(TextNode* current, Interface* interface);
int inside_cell(TextNode current, int mouse_x, int mouse_y);

void find_next_active_node(Coordinates* active, Interface* interface);
void find_previous_active_node(Coordinates* active, Interface* interface);
int final_active_node(Coordinates active, Interface interface);
void set_active_text_cell(int row, int column, Interface* interface);

int inside_text_editor(Interface* interface, int mouse_x, int mouse_y);
void console_text_editor(Interface interface);

int first_cell(Coordinates active);
int last_cell(Coordinates active, Interface interface);
int top_row(Coordinates active);
int bottom_row(Coordinates active, Interface interface);
int start_column(Coordinates active);
int end_column(Coordinates active, Interface interface);


void handle_overwriting(Coordinates active, Interface* interface, 
                          char* overflow);
void handle_backwriting(Coordinates active, Interface* interface);
void handle_enter_shuffling(Coordinates active, Interface* interface);

void tab(Coordinates active, Interface* interface, int direction);
void wipe_text_editor(Interface* interface);
