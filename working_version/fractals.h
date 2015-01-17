#include "draw.h"

void sierpinski(Draw *fractal, SDL_Win *window, int limit);
void tree(Draw *fractal, SDL_Win *window, int limit);
void star(Draw *fractal, SDL_Win *window, int limit);
void carpet(Draw *fractal, SDL_Win *window, int limit);

void make_shape(Shape *shape, int x, int y, int size, int height, float angle);
