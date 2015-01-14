#include "fractals.h"

void stariterate(Draw *fractal, Interface interface, Shape current, 
                     int iterations, int limit, float angle);

void star(Draw *fractal, Interface interface, int limit) {
    Shape centre;
    make_shape(&centre, fractal->startx, fractal->starty, 
                   fractal->size[0]/2, fractal->height[0]/2, fractal->angle);

    int iterations = 1;

    for(int i=0; i<10; i++) {
        fractal->splits[i] = 6;
    }

    stariterate(fractal, interface, centre, iterations, limit, fractal->angle);
  
    SDL_RenderPresent(interface.window.renderer);
    SDL_UpdateWindowSurface(interface.window.win);
}

void stariterate(Draw *fractal, Interface interface, Shape current, 
                     int iterations, int limit, float angle) {
    draw_sdl(interface, fractal, current.x, current.y, 
                 current.size, angle, iterations);

    if(current.size < 1 || iterations == limit) {
        return;
    }

    int x, y; 
    float newangle;
    Shape *shapes = malloc(fractal->splits[iterations]*sizeof(Shape)); 

    iterations++;

    for(int i=0; i<fractal->splits[iterations]; i++) {
        newangle = ((i*2.0*M_PI)/fractal->splits[iterations]) + fractal->angle;
        x = current.x + (current.size*sin(newangle)/sqrt(2));
        y = current.y - (current.size*cos(newangle)/sqrt(2));
        make_shape(&shapes[i], x, y, current.size/fractal->splits[iterations], 
                       current.height/fractal->splits[iterations], newangle);
        stariterate(fractal, interface, shapes[i], iterations, limit, newangle);
    }
    free(shapes);
}
