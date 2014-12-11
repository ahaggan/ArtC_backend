#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#define WIN_WIDTH 1024    
#define WIN_HEIGHT 768
#define MAX_TEXT 1000
#define FONT_SIZE 20
#define NO_OF_LOOPS 7
#define EDITOR_COLUMNS 42
#define EDITOR_ROWS 19
/* These are currently used by parser.c. Once parser.c has been edited to use the interface coordinates instead, move these to display.h */

typedef struct draw{
  char* colour[10];
  char* move;
  int size;
  char* shape;
  int height;
  int startx;
  int starty;
  int endx;
  int endy;
  char* type;
  int iterations;
} Draw;

typedef struct area {
  SDL_Rect rect;
  SDL_Color colour;
} Area;

typedef struct SDL_Win {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
} SDL_Win;

typedef struct text_node {
  struct text_node* previous;
  struct text_node* next;
  //I have a feeling this needs to be a string
  char character[1];
  Area box;
  int x;
  int y;
  //if selected == 1, display cursor
  int selected;
} TextNode;

typedef struct interface {
  SDL_Win window;
  Area menubar;
  Area text_editor_panel;
  TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS];
  char composition[MAX_TEXT];
  Area text_cursor;
  Area canvas;
  Area gbutton;
  Area ch1button;
  TTF_Font *font;
} Interface;
