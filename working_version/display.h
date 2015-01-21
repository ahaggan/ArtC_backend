/*  This module contains all the functions that display created artwork
    and user interface menus. This module uses the manageSDL functions 
    to write to the display
*/
#include "artc.h"
//Contains helper functions for displaying SDL
#include "manageSDL.h"

#define  LEFT_MARGIN  15
#define  TOP_MARGIN  20

#define  LOGO_WIDTH  380
#define  LOGO_HEIGHT  131
#define  MENU_BUTTON_WIDTH  237
#define  MENU_BUTTON_HEIGHT  91
#define  MENU_BUTTON_DIST  20
#define  BACK_BUTTON_WIDTH  156
#define  BACK_BUTTON_HEIGHT  60
#define  BACK_BUTTON_MARGIN  60
#define  MENU_POPUP_WIDTH  600
#define  MENU_POPUP_HEIGHT  91

#define  BUTTON_HEIGHT  18
#define  BUTTON_FONT_SIZE  40

#define  TEXT_ED_WIDTH  3.015
#define  EDITOR_COLUMNS  100
#define  EDITOR_ROWS  100

#define  MAX_CHALLENGE_LEN  69
#define  MAX_FILE  100

#define  CHALLENGE_FONT_SIZE  16
#define  FONT_SIZE  15

#define  PREV_NEXT_BUTTON  4 

#define  BEGINNER  "program_txt_files/challenges/beginner_default.txt"
#define  INTERMEDIATE  "program_txt_files/challenges/intermediate_default.txt"
#define  EXPERT  "program_txt_files/challenges/expert_default.txt"

#define  LEVEL_NUM  4

#define  CANVAS_MODE_TEXTBOX  20
#define  CHALLENGE_MODE_TEXTBOX  12
#define  RESET_GENERATE_TEXTBOX  16
#define  PREV_NEXT_TEXTBOX  9
#define  ERROR_TEXTBOX  45

//Refers to where the user is in the program
typedef enum mode {
    challenge_mode,
    canvas_mode
} Mode;

//To refer to buttons the user presses
typedef enum menu_choice {
    canvas = 1,
    challenges_menu_choice,
    options_menu_choice,
    quit,
    beginner,
    intermediate,
    expert,
    main_menu,
    back
} Menu_Choice;

//Structure contains variables needed when constructing user menus
typedef struct menu {
    SDL_Win window;
    Menu_Choice state;
    Menu_Choice hover;
    TTF_Font* menu_font; 
    Area background;
    Area logo;
    Area canvas_button;
    Area canvas_text;
    Area challenges_button; 
    Area challenges_text;
	Area menu_help_button;
	Area quit_button;
    Area header;
    Area beginner;
    Area beginner_text;
    Area intermediate;
    Area intermediate_text;
    Area expert;
    Area expert_text;
    Area main_menu;
    Area help_screen;
    Area back_button;
} Menu;

//Contains current position coordinates something 
typedef struct coordinates {
    int row;
    int column;
} Coordinates;

//Contains information about a particular cell in the text editor
typedef struct text_node {
    struct text_node* previous;
    struct text_node* next;
    char character[1];
    Area box;
    Coordinates text_cell;
    Coordinates location;
} TextNode;

//WHAT IS THIS DOING??
typedef TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS];

//Refers to what the user has clicked in the interface
typedef enum interface_action {
    generate_clicked = 1,
    text_edited,
    back_to_menu,
    change_position,
    load_challenge,
    load_help
} Interface_Action;

//Contains all information related to the user interface display
typedef struct interface {
    SDL_Win window;

    Interface_Action action;
    //Boxes on screen
    Area toolbar;
    Area canvas; 
    Area reset_button;
    Area generate_button;
    Area menu_button;
    Area learn_button;
    Area help_button;
    Area current_challenge;
    Area current_challenge_text;
    Area next_button;
    Area previous_button;

    Area toolbar_bottom_divider;
    Area menu_learn_divider;
    Area learn_help_divider;
    Area reset_generate_divider;
    Area reset_generate_top_border;
    Area prev_divider;
    Area next_divider;
    
    //Text on screen
    Area text_editor_panel;
    TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS];
    Coordinates click_location;
    Area text_cursor;
    Coordinates active_txt;
    int editor_rows;
    int editor_columns;
  
    TTF_Font* text_ed_font;
    TTF_Font* button_font;
    TTF_Font* challenge_font;
    
    //Information about challenges
    char default_file[MAX_FILE];
    char code_file[MAX_FILE];
    char challenges[LEVEL_NUM][MAX_CHALLENGE_LEN];
    int challenge_num;
  
    Mode mode;
} Interface;	

//Contains information about a particular shape that will be drawn
//as part of a fractal
typedef struct shape {
    int x;
    int y;
    int size;
    int height;
    float rotation;
} Shape;
/*

    Main Menu

*/
//Calls the functions that display logos and buttons for the main menu screen
void display_main_menu(Menu* main_menu);
//Sets the colour for the background of the main menu
void display_menu_background(int win_width, int win_height, Menu* main_menu);
//positions and places "Art.c" logo on the screen
void display_logo(int win_width, int win_height, Menu* main_menu);
//Displays the button that links to the canvas screen
void display_canvas_button(int win_width, int win_height, Menu* main_menu);
//Displays the button that links to the challenges screen
void display_challenges_button(int win_width, int win_height, Menu* main_menu);
//Displays the button that links to the help screen
void display_menu_help_button(int win_width, int win_height, Menu* main_menu);
//Displays the button that quits the program
void display_quit_button(int win_width, int win_height, Menu* main_menu);
/*

    Challenges Menu
    
*/
//Calls the functions that display the Challenges menu
void display_challenges_menu(Menu* challenges);
//Sets the background of the challenges menu
void display_challenges_background(int win_width, int win_height, 
                                     Menu* challenges);
//Displays the "Challenges" logo in the corner of the challenges menu
void display_header(int win_width, int win_height, Menu* challenges_menu);
//Displays the button that links to the beginner challenges
void display_beginner_button(int win_width, int win_height, 
                               Menu* challenges_menu);
//Displays the button that links to the intermediate challenges
void display_intermediate_button(int win_width, int win_height, 
                                   Menu* challenges_menu);
//Displays the button that links to the expert challenges
void display_expert_button(int win_width, int win_height, 
                             Menu* challenges_menu);
//Displays the button that return the user to the main menu
void display_main_menu_button(int win_width, int win_height, 
                                Menu* challenges_menu);

int help_menu(Menu* help);
void display_help_menu(Menu* help_menu);
void display_popup_text(Menu* menu);
void display_canvas_text(Menu* main_menu);
void display_challenges_text(Menu* main_menu);
void display_beginner_text(Menu* challenges);
void display_intermediate_text(Menu* challenges);
void display_expert_text(Menu* challenges);

void display_help_screen(Menu* help_menu, int win_width, int win_height);
void display_back_button(Menu* help_menu, int win_width, int win_height);

void display_interface(Interface *interface, Mode mode, int refresh_canvas);
void display_toolbar(int win_width, int win_height, 
                       Interface* interface, Mode mode);
void display_reset_button(int win_width, int win_height, 
                            Interface* interface, Mode mode);
void display_generate_button(int win_width, int win_height, 
                               Interface* interface);
void display_menu_button(int win_width, int win_height, 
                           Interface* interface, Mode mode);
void display_learn_button(int win_width, int win_height, Interface* interface);
void display_help_button(int win_width, int win_height, 
                           Interface* interface, Mode mode);
void display_canvas(int win_width, int win_height, 
                      Interface* interface, Mode mode);
void display_text_editor(int win_width, int win_height, Interface* interface);
void display_current_challenge(int win_width, int win_height, 
                                 Interface* interface);
void display_previous_button(int win_width, int win_height, 
                               Interface* interface);
void display_next_button(int win_width, int win_height, Interface* interface);
void display_dividers(int win_width, int win_height, 
                        Interface* interface, Mode mode);

void display_error_message(Interface* interface);
void read_write_error(char* align_message_top, char* align_message_bottom);

void text_align_central(char* centred_string, char* challenge, 
                          int textbox_width);
void make_text(SDL_Win *win, SDL_Rect *location, TTF_Font *font, char* text, 
                 int r, int g, int b);

void make_rect(SDL_Win *win, Area *area, int x, int y, int w, int h, 
                 int r, int g, int b);
