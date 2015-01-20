#include "draw.h"

void make_shape(Shape *shape, int x, int y, int size, int height, float angle);

void tree(Draw *fractal, SDL_Win *window, int limit);
void treeiterate(Draw *fractal, SDL_Win *window, Shape current,
                     int iterations, int limit, float angle, int bx, int by);

void sierpinski(Draw *fractal, SDL_Win *window, int limit);
void sierpinskiiterate(Draw *fractal, SDL_Win *window, Shape current, 
                           int iterations, int limit);

void star(Draw *fractal, SDL_Win *window, int limit);
void stariterate(Draw *fractal, SDL_Win *window, Shape current, 
                     int iterations, int limit, float angle);

