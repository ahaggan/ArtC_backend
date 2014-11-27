#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <math.h>

#define WIN_WIDTH 1024		
#define WIN_HEIGHT 600

#define MAX_TEXT 1000

#define SDL_8BITCOLOUR 256
#define SDL_DELAY 1000

struct SDL_Win {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
};
typedef struct SDL_Win SDL_Win;

#include "parser.h"

void SDL_Win_Init(SDL_Win *w, char win_name[20]);
void SDL_Renderer_Init(SDL_Win *w);

int triangle(draw *object, SDL_Win *sw, Interface interface);
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r, int a);
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r, int a);

void SDL_TTF_Init();
TTF_Font* SDL_Load_Font(char font_path[30], int font_size);
SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w);
void SDL_TTF_Quit(TTF_Font *font);

void draw_interface(SDL_Win *win, Interface *artc);
void make_rect(SDL_Win *win, Area *area, int x, int y, int w, int h, int r, int g, int b);
void make_text(SDL_Win *win, SDL_Rect *location, int r, int g, int b, TTF_Font *font, char* text);

void sierpinski(SDL_Win *w, Interface interface, int limit);
