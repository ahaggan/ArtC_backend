#include "interface.h"

// These functions are dependent on user input, e.g. clicks, hovering, keys.

void main_menu_hover(int x, int y, Menu *main_menu);
int main_menu_click(int x, int y, Menu *main_menu);

void challenges_menu_hover(int x, int y, Menu *challenges);
int challenges_menu_click(int x, int y, Menu *challenges);

int decide_menu_hover(Menu *menu, Menu_Choice choice);

int interface_click(int x, int y, Interface *interface);


int SDL_Text_Editor_Events(SDL_Event event, Interface* interface);
void Text_Editor_text_input(Interface *interface, char* text,
                                int x, int y, Coordinates active);
void Text_Editor_keydown(Interface *interface, int key,
                             int x, int y, Coordinates active);

void load_text_into_text_editor(char* file_name, Interface* interface);
void mouse_move_to_cell(Interface* interface, int mouse_x, int mouse_y);
void set_cursor(Interface *interface, int x, int y);

// These functions return values dependent on where the cursor is.
int within_button(int x, int y, SDL_Rect button);
int inside_cell(TextNode current, int mouse_x, int mouse_y);
int inside_text_editor(Interface* interface, int mouse_x, int mouse_y);
int inside_canvas(Interface* interface, int mouse_x, int mouse_y);
