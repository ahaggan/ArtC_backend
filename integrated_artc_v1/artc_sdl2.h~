#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <math.h>

#define WIN_WIDTH 1024		
#define WIN_HEIGHT 600

#define MAX_TEXT 1000

#define SDL_8BITCOLOUR 256

struct SDL_Win {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
};
typedef struct SDL_Win SDL_Win;

#include "input_integrated_v1.h"

void SDL_Win_Init(SDL_Win *w, char win_name[20]);
void SDL_Renderer_Init(SDL_Win *w);
void SDL_Window_Events(SDL_Win *w, SDL_Event event, Interface* interface);

void SDL_Events(SDL_Win *w, Interface* interface);

void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r, int a);
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r, int a);

void SDL_TTF_Init();
TTF_Font* SDL_Load_Font(char font_path[30], int font_size);
SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w);
void SDL_TTF_Quit(TTF_Font *font);

SDL_RWops* SDL_Open_File(char *file_name);

void draw_interface(SDL_Win *win, Interface *artc, TTF_Font *font);
void make_rect(SDL_Win *win, Area *area, 
                int x, int y, int w, int h, int r, int g, int b);
void make_text(SDL_Win *win, SDL_Rect *location, int r, int g, int b, TTF_Font *font, char* text);

void sierpinski(SDL_Win *w, Interface interface, int limit);
