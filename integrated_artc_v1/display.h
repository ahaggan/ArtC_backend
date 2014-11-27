#include "artc.h"
#include <math.h>

#define WIN_WIDTH 1024		
#define WIN_HEIGHT 600

#define SDL_8BITCOLOUR 256
#define SDL_DELAY 1000

void SDL_Win_Init(SDL_Win *w, char win_name[20]);
void SDL_Renderer_Init(SDL_Win *w);
void SDL_Events(SDL_Win *w, Interface* interface);
void SDL_Window_Events(SDL_Win *w, SDL_Event event, Interface* interface);

void draw_interface(SDL_Win *win, Interface *artc);
void make_rect(SDL_Win *win, Area *area, int x, int y, int w, int h, int r, int g, int b);
void make_text(SDL_Win *win, SDL_Rect *location, int r, int g, int b, TTF_Font *font, char* text);


int triangle(draw *object, SDL_Win *sw, Interface interface);
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r, int a);
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r, int a);

void SDL_TTF_Init();
TTF_Font* SDL_Load_Font(char font_path[30], int font_size);
SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w);
void SDL_TTF_Quit(TTF_Font *font);

void clear_area(SDL_Win *sw, Area area);
void draw_sdl(draw *object, SDL_Win *sw, Interface interface);
int input(SDL_Win *sw, Interface interface);

void sierpinski(SDL_Win *w, Interface interface, int limit);
