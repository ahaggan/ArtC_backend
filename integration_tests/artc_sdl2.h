#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include<math.h>

#define WIN_WIDTH 1024		
#define WIN_HEIGHT 768

#define SDL_8BITCOLOUR 256

struct SDL_Win {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
};
typedef struct SDL_Win SDL_Win;

typedef struct draw{
  char* colour;
  char* move;
  int size;
  char* shape;
}draw;

void SDL_Win_Init(SDL_Win *w, char win_name[20]);
void SDL_Renderer_Init(SDL_Win *w);
void SDL_Events(SDL_Win *w);
void SDL_TTF_Init();
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r, int a);
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r, int a);
TTF_Font* SDL_Load_Font(char font_path[30], int font_size);
SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w);
