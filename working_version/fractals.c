#include "fractals.h"

void generate_fractal(Draw *fractal, SDL_Win *window, int i) 
{
    if(strcmp(fractal->type[i], "sierpinski") == 0){
        sierpinski(fractal, window, i);
    }
    else if(strcmp(fractal->type[i], "tree") == 0){
        tree(fractal, window, i);
    }
    else if(strcmp(fractal->type[i], "sierpinski_square") == 0){
        carpet(fractal, window, i);
    }
    else if(strcmp(fractal->type[i], "star") == 0){
        star(fractal, window, i);
    }
}

void make_shape(Shape *shape, int x, int y, int size, int height, float angle) {
    shape->x = x;
    shape->y = y;
    shape->size = size;
  
    shape->height = height;
    shape->rotation = angle;
}
