/*
#include "display.h"

int iterate(Draw *fractal, Interface interface, Shape shape, int iterations, int limit, char c);

int iterate_carpet(Draw *fractal, Interface interface, Shape shape, int iterations, int limit, char c);

void carpet(Draw *fractal, Interface interface, int limit) {
    Shape shape;
    make_shape(&shape, fractal->startx, fractal->starty, fractal->size, fractal->height);

    int iterations = 1; //One iteration is just the shape.

    printf("Sierpinski Limit: %d\n", limit);

    iterations = iterate_carpet(fractal, interface, shape, iterations, limit, 'a');
    printf("Sierpinski completed with %d iterations.\n", iterations);

    SDL_RenderPresent(interface.window.renderer);
    SDL_UpdateWindowSurface(interface.window.win);
    SDL_Delay(SDL_DELAY);

}

int iterate_carpet(Draw *fractal, Interface interface, Shape current, int iterations, int limit, char c) {
    //If the fractal shapes reach a size smaller than 2 pixels, or if we reach the desired no. of iterations
    if (current.size < 2 || iterations == limit) {
        float angle;
        switch (c) {
            case 'a': 
                angle = 0;
                break;
            case 'b': 
                angle = 0;
                break;
            case 'c': 
                angle = 0;
                break;
            case 'd': 
                angle = 0;
                break;
            case 'e': 
                angle = 0;
                break;
            case 'f': 
                angle = 0;
                break;
            case 'g': 
                angle = 0;
                break;
            case 'h': 
                angle = 0;
                break;
            case 'i': 
                angle = 0;
                break:           
        }
        draw_sdl(interface, fractal, current.x, current.y, current.size, angle);
        return iterations;
    }

    Shape a, b, c, d, e, f, g, h, i;
    //YOU NEED TO EDIT THE FUNCTION CALLS BELOW
    make_shape(&top, current.x, current.y - (current.height / 4), current.size / 2, current.height / 2);
    make_shape(&left, current.x - (current.size / 4), current.y + (current.size / 4), current.size / 2, current.height / 2);
    make_shape(&right, current.x + (current.size / 4), current.y + (current.size / 4), current.size / 2, current.height / 2);

    iterations++;

    iterate(fractal, interface, top, iterations, limit, 't');
    iterate(fractal, interface, left, iterations, limit, 'l');
    return iterate(fractal, interface, right, iterations, limit, 'r');
}


void carpet(Draw *fractal, Interface interface, int limit){
}*/
