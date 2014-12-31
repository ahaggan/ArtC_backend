#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#define WIN_WIDTH 1024    
#define WIN_HEIGHT 768

#define MAX_TEXT 1000
#define FONT_SIZE 16
#define BUTTON_FONT_SIZE 100

#define NO_OF_LOOPS 7

#define EDITOR_COLUMNS 100
#define EDITOR_ROWS 100


/* These are currently used by parser.c. Once parser.c has been edited to use the interface coordinates instead, move these to display.h */

typedef struct draw{
  int iterations;
  char* type[10];
  char* colour[10];
  int size[10];
  int linethickness[10];
  char* shape[10];
  int height[10];
  int divisions;
  float anglerange;
  int startx;
  int starty;
  int endx;
  int endy;
  char* move;
} Draw;

typedef struct area {
  SDL_Rect rect;
  SDL_Color col;
} Area;

typedef struct SDL_Win {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
} SDL_Win;

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

