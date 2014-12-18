#include "artc.h"
#include <math.h>

#define MIN_WIDTH 800
#define MIN_HEIGHT 600

#define SDL_8BITCOLOUR 256
#define SDL_DELAY 750

#define TOOLBAR_HEIGHT 10

#define TOOLBAR_BUTTON_Y 6
#define TOOLBAR_BUTTON_WIDTH 10
#define TOOLBAR_BUTTON_HEIGHT 1.5

#define BOTTOM_TOOLBAR_HEIGHT 18

#define TEXT_ED_WIDTH 2.435

#define HOME_X_SPACE 70
#define HELP_X_SPACE 1.13

#ifndef  M_PI
 #define M_PI  3.14159265358979323846
#endif  

#define EMPTY_CELL "|-"

typedef enum interface_action {
	generate_clicked = 1,
	text_edited,
	back_to_menu
} Interface_Action;

typedef struct interface {
  SDL_Win window;
  Interface_Action action;
  Area menubar;
  Area menu_bottom;
  Area text_editor_panel;
  TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS];
  char composition[MAX_TEXT];
  Area text_cursor;
  Area canvas; 
  Area reset_button;
  Area generate_button;
  Area menu_button;
  Area help_button;
  TTF_Font *font;
  TTF_Font *button_font;
  Coordinates active_txt;
  int editor_rows;
  int editor_columns;
} Interface;	

typedef struct txt_node {
	struct txt_node* previous;
	struct txt_node* next;
	//I have a feeling this needs to be a string
	char* character;
	//if selected == 1, display cursor
	int selected;
} Txt_node;

typedef struct shape {
    int x;
    int y;
    int size;
    int height;
    float rotation;
} Shape;


void SDL_Win_Init(SDL_Win *w, char* win_name);
void SDL_Renderer_Init(SDL_Win *w);

void display_interface(Interface *interface);
void make_rect(SDL_Win *win, Area *area, int x, int y, int w, int h, int r, int g, int b);
void make_text(SDL_Win *win, SDL_Rect *location, int r, int g, int b, TTF_Font *font, char* text);

int triangle(Draw *fractal, Interface interface);
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r);
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r);

void SDL_TTF_Init();
TTF_Font* SDL_Load_Font(char* font_path, int font_size);
SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w);
void SDL_TTF_Quit(TTF_Font *font);

void clear_area(SDL_Win *window, Area area);

void draw_sdl(Interface interface, Draw *fractal, int x, int y, int size, float angle, int i);
void SDL_Line(SDL_Renderer* renderer, int xs, int ys, int xe, int ye, int thickness, float angle);
int input(Interface interface, Draw *fractal);

void generate_fractal(Draw *fractal, Interface interface, int i);
void make_shape(Shape *shape, int x, int y, int size, int height, float angle);
void sierpinski(Draw *fractal, Interface interface, int limit);
void tree(Draw *fractal, Interface interface, int limit);
void carpet(Draw *fractal, Interface interface, int limit);
void star(Draw *fractal, Interface interface, int limit);

void make_text_editor(int width, int height, Interface* interface);
void update_text_editor(int width, int height, Interface* interface);
TextNode* allocate_text_node(char* c, TextNode* previous_node, Interface* interface, int x, int y);
void print_composition(TextNode* start);

void free_text_nodes(TextNode* head);

/* Menu Additions */
typedef enum challenges_choice {
	beginner = 1,
	intermediate,
	expert,
	main_menu
} Challenges_Choice;

typedef struct challenges_menu {
	SDL_Win window;
	Challenges_Choice state;
	TTF_Font* font;
	TTF_Font* button_font; 
	Area background;
	Area header;
	Area beginner;
	Area intermediate;
	Area expert;
	Area main_menu;
} Challenges_Menu;

typedef enum menu_choice {
	canvas = 1,
	challenges_menu,
	options_menu,
	quit
} Menu_Choice;

typedef struct main_menu {
	SDL_Win window;
	Menu_Choice state;
	TTF_Font* font;
	TTF_Font* button_font; 
	Area background;
	Area logo;
	Area canvas_button;
	Area challenges_button;
	Challenges_Menu challenges;
	Area options_button;
	Area quit_button;
} Main_Menu;

#define LOGO_WIDTH 3
#define LOGO_HEIGHT 6
#define LEFT_MARGIN 15
#define TOP_MARGIN 20

#define MENU_BUTTON_WIDTH 5
#define MENU_BUTTON_HEIGHT 10
#define MENU_BUTTON_DIST 15

void display_main_menu(Main_Menu* main_menu);
void draw_challenges_menu(Main_Menu* main_menu, Challenges_Menu* challenges_menu);
void update_main_menu(Main_Menu *main_menu);
void render_update_clear(SDL_Win window);

TextNode* make_cell(int width, int height, Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current);

