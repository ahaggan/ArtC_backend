#include "display.h"

#ifndef  M_PI
 #define M_PI  3.14159265358979323846
#endif  

void draw_sdl(Interface interface, Draw *fractal, int x, int y, int size, float angle, int i);

void SDL_Line(SDL_Renderer* renderer, int xs, int ys, int xe, int ye, int thickness, float angle);
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r);
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r);
