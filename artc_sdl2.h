#include "SDL.h"
#include "SDL_ttf.h"
#define WIN_WIDTH 1024		
#define WIN_HEIGHT 768

#define SDL_8BITCOLOUR 256

struct SDL_Win {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
};
typedef struct SDL_Win SDL_Win;

void SDL_Win_Init(SDL_Win *w, SDL_Surface *display, char win_name[20]);
void SDL_Renderer_Init(SDL_Win *w);
void SDL_Events(SDL_Win *w);
void SDL_TTF_Init();
void SDL_Load_Font(char font_path[30]);
void SDL_SetDrawColour(SDL_Win *w, Uint8 r, Uint8 g, Uint8 b);