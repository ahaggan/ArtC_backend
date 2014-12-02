#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#define WIN_WIDTH 1024    
#define WIN_HEIGHT 768
#define MAX_TEXT 1000
/* These are currently used by parser.c. Once parser.c has been edited to use the interface coordinates instead, move these to display.h */

typedef struct draw{
  char* colour;
  char* move;
  int size;
  char* shape;
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

typedef struct interface {
  SDL_Win window;
  Area menubar;
  Area texteditor;
  char composition[MAX_TEXT];
  Area canvas;
  Area gbutton;
  Area ch1button;
  TTF_Font *font;
} Interface;
