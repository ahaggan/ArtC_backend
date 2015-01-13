#include "artc.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <math.h>

#define WIN_WIDTH 1366
#define WIN_HEIGHT 768
#define MIN_WIDTH 800
#define MIN_HEIGHT 600

#define LOGO_WIDTH 761
#define LOGO_HEIGHT 263
#define LEFT_MARGIN 15
#define TOP_MARGIN 20

#define MENU_BUTTON_WIDTH 237
#define MENU_BUTTON_HEIGHT 91
#define MENU_BUTTON_DIST 20

#define BUTTON_HEIGHT 18
#define BUTTON_FONT_SIZE 50
#define TEXT_ED_WIDTH 3.015

#define EDITOR_COLUMNS 100
#define EDITOR_ROWS 100

#define MAX_CHALLENGE_LEN 69

#define CHALLENGE_FONT 16
#define FONT_SIZE 15

#define PREV_NEXT_BUTTON 4 

#define LEVEL_NUM 4

typedef struct SDL_Win {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
} SDL_Win;

typedef struct area {
  SDL_Rect rect;
  SDL_Color col;
} Area;

typedef enum menu_choice {
	canvas = 1,
	challenges_menu,
	options_menu,
	quit,

  beginner = 1,
  intermediate,
  expert,
  main_menu
} Menu_Choice;

typedef struct menu {
	SDL_Win window;
	Menu_Choice state;
	TTF_Font* menu_font; 
	Area background;
	Area logo;
	Area canvas_button;
	Area challenges_button;
	Area menu_help_button;
	Area quit_button;

  Area header;
  Area beginner;
  Area intermediate;
  Area expert;
  Area main_menu;
} Menu;

typedef enum mode {
   challenge_mode,
   canvas_mode
} Mode;

typedef struct coordinates {
  int row;
  int column;
} Coordinates;

typedef struct text_node {
  struct text_node* previous;
  struct text_node* next;
  char character[1];
  Area box;
  Coordinates text_cell;
  Coordinates location;
  int w;
  int h;
} TextNode;
typedef TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS];

typedef enum interface_action {
	generate_clicked = 1,
	text_edited,
	back_to_menu,
  change_position
} Interface_Action;

typedef struct interface {
  SDL_Win window;
  Interface_Action action;
  Area toolbar;
  Area text_editor_panel;
  TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS];

  Coordinates click_location;

  Area text_cursor;
  Area canvas; 
  Area reset_button;
  Area generate_button;
  Area menu_button;
  Area learn_button;
  Area help_button;
  Area previous_button;
  Area current_challenge;
  Area current_challenge_text;
  Area next_button;
  
  TTF_Font* text_ed_font;
  TTF_Font* button_font;
  TTF_Font* challenge_font;
  Coordinates active_txt;
  int editor_rows;
  int editor_columns;
 
  
  Area toolbar_bottom_divider;
  Area menu_learn_divider;
  Area learn_help_divider;
  Area reset_generate_divider;
  Area reset_generate_top_border;
  Area prev_divider;
  Area next_divider;
 
  char challenges[LEVEL_NUM][MAX_CHALLENGE_LEN];

  Mode mode;

} Interface;	

typedef struct shape {
    int x;
    int y;
    int size;
    int height;
    float rotation;
} Shape;

// Located to draw attention to this issue with MACS.
void fix_mac_flickering(Interface* interface, Mode mode);


// MACS ARE TERRIBLE.
int challenge_menu(Menu* challenges);

int SDL_Main_Menu_Events(Menu* main_menu);
void main_menu_actions(Menu* main);

int SDL_Challenges_Menu_Events(Menu* challenges);
void challenge_menu_actions(Menu* challenges);

int interface(Menu* main, Mode mode, char* file_name);

void SDL_Win_Init(SDL_Win *w, char* win_name);
void SDL_TTF_Init();
TTF_Font* SDL_Load_Font(char* font_path, int font_size);
void render_update_clear(SDL_Win window);

void clear_area(SDL_Win *window, Area area);
SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w);
void SDL_TTF_Quit(TTF_Font *font);
SDL_Texture* load_image(char* filename, SDL_Win* window);
SDL_Texture* surface_to_texture(SDL_Surface* surface, SDL_Win* window);

void initialise_main_menu(Menu* main);
// Functions that display main menu things.
void display_menu_background(int win_width, int win_height, Menu* main_menu);
void display_logo(int win_width, int win_height, Menu* main_menu);
void display_canvas_button(int win_width, int win_height, Menu* main_menu);
void display_challenges_button(int win_width, int win_height, Menu* main_menu);
void display_menu_help_button(int win_width, int win_height, Menu* main_menu);
void display_quit_button(int win_width, int win_height, Menu* main_menu);

void initialise_challenges_menu(Menu* challenges_menu);
// Functions that display challenge menu things.
void display_challenges_background(int win_width, int win_height, Menu* challenges);
void display_header(int win_width, int win_height, Menu* challenges_menu);
void display_beginner_button(int win_width, int win_height, Menu* challenges_menu);
void display_intermediate_button(int win_width, int win_height, Menu* challenges_menu);
void display_expert_button(int win_width, int win_height, Menu* challenges_menu);
void display_main_menu_button(int win_width, int win_height, Menu* challenges_menu);

void initialise_interface(Menu* main, Interface* interface, Mode mode);
// Functions that display interface things.
void display_toolbar(int win_width, int win_height, Interface* interface, Mode mode);
void display_menu_button(int win_width, int win_height, Interface* interface, Mode mode);
void display_help_button(int win_width, int win_height, Interface* interface, Mode mode);
void display_reset_button(int win_width, int win_height, Interface* interface, Mode mode);
void display_generate_button(int win_width, int win_height, Interface* interface);
void display_canvas(int win_width, int win_height, Interface* interface, Mode mode);
void display_text_editor(int win_width, int win_height, Interface* interface);
void display_learn_button(int win_width, int win_height, Interface* interface);
void display_previous_button(int win_width, int win_height, Interface* interface);
void display_current_challenge(int win_width, int win_height, Interface* interface);
void display_next_button(int win_width, int win_height, Interface* interface);
void display_dividers(int win_width, int win_height, Interface* interface, Mode mode);


void make_rect(SDL_Win *win, Area *area, int x, int y, int w, int h, int r, int g, int b);
void make_text(SDL_Win *win, SDL_Rect *location, int r, int g, int b, TTF_Font *font, char* text);

void text_align_central(char centred_string[MAX_CHALLENGE_LEN], char* challenge);
