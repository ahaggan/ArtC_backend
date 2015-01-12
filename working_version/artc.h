#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#define BUTTON_FONT_SIZE 50

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

<<<<<<< HEAD
typedef struct text_node {
  struct text_node* previous;
  struct text_node* next;
  char character[2];
  Area box;
  Coordinates text_cell;
  Coordinates location;
  int w;
  int h;
} TextNode;
=======
typedef struct menu {
	SDL_Win window;
	Menu_Choice state;
	TTF_Font* menu_font; 
	Area background;
	Area logo;
	Area canvas_button;
	Area challenges_button;
	Area options_button;
	Area quit_button;
>>>>>>> FETCH_HEAD

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

void initialise_main_menu(Menu* main);
void display_main_menu(Menu* main_menu);
int SDL_Main_Menu_Events(Menu* main_menu);
void main_menu_actions(Menu* main);

int interface(Menu* main, Mode mode, char* file_name);
int challenges(Menu* main);

void initialise_challenges_menu(Menu* main);
void display_challenges_menu(Menu* challenges_menu);
int SDL_Challenges_Menu_Events(Menu* challenges);
void challenge_menu_actions(Menu* challenges);

void SDL_Win_Init(SDL_Win *w, char* win_name);
void SDL_TTF_Init();
TTF_Font* SDL_Load_Font(char* font_path, int font_size);
void render_update_clear(SDL_Win window);

