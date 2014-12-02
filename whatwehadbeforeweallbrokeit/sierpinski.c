#include "display.h"

typedef struct shape {
    int x;
    int y;
    int size;
} shape;

int iterate(Draw *fractal, Interface interface, shape shape, int iterations, int limit);
void makeshape(shape *shape, int x, int y, int size);

void sierpinski(Draw *fractal, Interface interface, int limit)
{
    shape shape;
    shape.x=fractal->startx;
    shape.y=fractal->starty;
    shape.size=fractal->size;
    int iterations=1; // One iteration is just the shape.

    printf("Sierpinski Limit: %d\n", limit);

    iterations = iterate(fractal, interface, shape, iterations, limit);
    printf("Sierpinski completed with %d iterations.\n", iterations);

    SDL_RenderPresent(interface.window.renderer);
    SDL_UpdateWindowSurface(interface.window.win);
    SDL_Delay(SDL_DELAY);

}

int iterate(Draw *fractal, Interface interface, shape oldshape, int iterations, int limit)
{
    if(oldshape.size<2 || iterations == limit) {
        draw_sdl(interface, fractal, oldshape.x, oldshape.y, oldshape.size);
        return iterations;
    }

    shape top, left, right;

    makeshape(&top, oldshape.x, oldshape.y - (oldshape.size/4), oldshape.size/2);
    makeshape(&left, oldshape.x-(oldshape.size/4), oldshape.y+(oldshape.size/4), oldshape.size/2);
    makeshape(&right, oldshape.x+(oldshape.size/4), oldshape.y+(oldshape.size/4), oldshape.size/2);

    iterate(fractal, interface, top, iterations+1, limit);
    iterate(fractal, interface, left, iterations+1, limit);
    return iterate(fractal, interface, right, iterations+1, limit);
}

void makeshape(shape *shape, int x, int y, int size)
{
    shape->x = x;
    shape->y = y;
    shape->size = size;
}
