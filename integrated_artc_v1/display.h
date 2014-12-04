#include "artc.h"
#include <math.h>

#define SDL_8BITCOLOUR 256
#define SDL_DELAY 750
#define MENU_OFFSET 12
#ifndef  M_PI
 #define M_PI  3.14159265358979323846
 #endif  

typedef struct txt_node {
	struct txt_node* previous;
	struct txt_node* next;
	//I have a feeling this needs to be a string
	char* character;
	//if selected == 1, display cursor
	int selected;
} Txt_node;

typedef struct shape {
    int x;
    int y;
    int size;
    int height;
} Shape;

void SDL_Win_Init(SDL_Win *w, char win_name[20]);
void SDL_Renderer_Init(SDL_Win *w);

void draw_interface(Interface *interface);
void make_rect(SDL_Win *win, Area *area, int x, int y, int w, int h, int r, int g, int b);
void make_text(SDL_Win *win, SDL_Rect *location, int r, int g, int b, TTF_Font *font, char* text);

int triangle(Draw *fractal, Interface interface);
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r);
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r);

void SDL_TTF_Init();
TTF_Font* SDL_Load_Font(char font_path[30], int font_size);
SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w);
void SDL_TTF_Quit(TTF_Font *font);

void clear_area(SDL_Win *window, Area area);

void draw_sdl(Interface interface, Draw *fractal, int x, int y, int size, float angle);
int input(Interface interface, Draw *fractal);

void generate_fractal(Draw *fractal, Interface interface);
void make_shape(Shape *shape, int x, int y, int size, int height);
void sierpinski(Draw *fractal, Interface interface, int limit);
void tree(Draw *fractal, Interface interface, int limit);
void carpet(Draw *fractal, Interface interface, int limit);
TextNode* allocate_text_node(char* c, TextNode* previous_node, TextNode* next_node, Interface* interface, int x, int y);
