/* 
This module chooses which fractal to draw and calls the relevant fractal function. These fractal functions control how the fractal,draw structure, elements are drawn in the particular fractal type.
*/

#include "draw.h"

//Contains information about a particular shape that will be drawn
//as part of a fractal
typedef struct shape {
    int x;
    int y;
    int size;
    int height;
    float rotation;
} Shape;

/*
Function is called by each of the fractal drawing functions to create the shape it is about to draw.
*/
void make_shape(Shape *shape, int x, int y, int size, int height, float angle);

/*
The following functions contain the logic to draw their specific fractal, each function draws the first iteration of the fractal and then calls the respective iterate function to produce the other iterations of the fractal
*/
void tree(Draw *fractal, SDL_Win *window, int limit);
void sierpinski(Draw *fractal, SDL_Win *window, int limit);
void star(Draw *fractal, SDL_Win *window, int limit);

/*
These are the iterate functions called by the fractal functions above
*/
void treeiterate(Draw *fractal, SDL_Win *window, Shape current,
                     int iterations, int limit, float angle, int bx, int by);

void sierpinskiiterate(Draw *fractal, SDL_Win *window, Shape current, 
                           int iterations, int limit);

void stariterate(Draw *fractal, SDL_Win *window, Shape current, 
                     int iterations, int limit, float angle);
