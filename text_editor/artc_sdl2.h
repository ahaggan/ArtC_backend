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

void SDL_Win_Init(SDL_Win *w, char win_name[20]);
void SDL_Events(SDL_Win *w, char *composition);
void SDL_TTF_Init();
void SDL_SetDrawColour(SDL_Win *w, Uint8 r, Uint8 g, Uint8 b);