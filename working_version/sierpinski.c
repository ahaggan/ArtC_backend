#include "fractals.h"

void sierpinskiiterate(Draw *fractal, SDL_Win *window, Shape current, 
                           int iterations, int limit);

void sierpinski(Draw *fractal, SDL_Win *window, int limit) {
fprintf(stderr, "sierpinski %d : ", limit);
    Shape shape;
    make_shape(&shape, fractal->startx, fractal->starty, fractal->size[0],
                   fractal->height[0], fractal->angle);

    int iterations = 1; //One iteration is just the shape.

    sierpinskiiterate(fractal, window, shape, iterations, limit);
printf("finished %d\n", limit);
    SDL_RenderPresent(window->renderer);
    SDL_UpdateWindowSurface(window->win);
}

void sierpinskiiterate(Draw *fractal, SDL_Win *window, Shape current, 
                           int iterations, int limit) {
    if (current.size < 2 || iterations == limit) {
        draw_sdl(window, fractal, current.x, current.y, 
                     current.size/2, current.rotation, iterations);
        return;
    }

    Shape top, left, right;
    float l_angle = fractal->angle - ((2*M_PI)/3.0);
    float r_angle = fractal->angle + ((2*M_PI)/3.0);

    make_shape(&top, current.x + ((current.size/4)*sin(fractal->angle)), 
                     current.y - ((current.size/4)*cos(fractal->angle)), 
                     current.size / 2, current.height/2, fractal->angle);

    make_shape(&left, current.x + ((current.size/4))*sin(l_angle),
                      current.y - ((current.size/4))*cos(l_angle), 
                      current.size/2, current.height/2, l_angle);

    make_shape(&right, current.x + ((current.size/4))*sin(r_angle),
                       current.y - ((current.size/4))*cos(r_angle),
                       current.size/2, current.height/2, r_angle);

    iterations++;

    sierpinskiiterate(fractal, window, top, iterations, limit);
    sierpinskiiterate(fractal, window, left, iterations, limit);
    sierpinskiiterate(fractal, window, right, iterations, limit);
}
