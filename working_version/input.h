/*
Module contains functions that handle user inputs, 
such as clicks, hovering and key presses
*/

#include "interface.h"
//Checks where the mouse is, if on a button calls functions to act accordingly
void main_menu_hover(int x, int y, Menu *main_menu);

//Handles mouse clicks on buttons on the main menu
Menu_Choice main_menu_click(int x, int y, Menu *main_menu);
//Handles which, if any, challenge level button the mouse is hovering over
void challenges_menu_hover(int x, int y, Menu *challenges);

//Handles mouse click on buttons when in challenge mode
Menu_Choice challenges_menu_click(int x, int y, Menu *challenges);
//Assigns menu->hover value if different to current value
int decide_menu_hover(Menu *menu, Menu_Choice choice);

//Handles clicks within canvas/text editor mode
Interface_Action interface_click(int x, int y, Interface *interface);

//Calls functions to handle various user inputs within the text editor
Interface_Action Text_Editor_Events(SDL_Event event, Interface* interface);

//Calls function in text_editor.c  which handles text input
void Text_Editor_text_input(Interface *interface, char* text,
                                int x, int y, Coordinates active);
                                
void Text_Editor_keydown(Interface *interface, int key,
                             int x, int y, Coordinates active);

//Calls function in text_editor.c which displays chosen .txt file in the editor
void load_text_into_text_editor(char* file_name, Interface* interface);
void mouse_move_to_cell(Interface* interface, int mouse_x, int mouse_y);
//Handles the positioning of the cursor in the text editor
void set_cursor(Interface *interface, int x, int y);

/*
These functions return true if the cursor is within a particular element
*/

//Returns 1 if given coordinates are within a given button
int within_button(int x, int y, SDL_Rect button);

//Checks if the mouse if within a given node of the text editor
int inside_cell(TextNode current, int mouse_x, int mouse_y);

//Records where the mouse is when inside the text editor
int inside_text_editor(Interface* interface, int mouse_x, int mouse_y);

//Records where the mouse is when inside the canvas
int inside_canvas(Interface* interface, int mouse_x, int mouse_y);
