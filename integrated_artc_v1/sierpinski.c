#include "display.h"
typedef struct shape {
int x;
int y;
int size;
} Shape;
int iterate(Draw *fractal, Interface interface, Shape shape, int iterations, int limit);
void make_shape(Shape *shape, int x, int y, int size);
void sierpinski(Draw *fractal, Interface interface, int limit) {
Shape shape;
//Create shape based on information assigned to the fractal structure.
shape.x = fractal->startx;
shape.y = fractal->starty;
shape.size = fractal->size;
int iterations = 1; //One iteration is just the shape.
printf("Sierpinski Limit: %d\n", limit);
iterations = iterate(fractal, interface, shape, iterations, limit);
printf("Sierpinski completed with %d iterations.\n", iterations);
SDL_RenderPresent(interface.window.renderer);
SDL_UpdateWindowSurface(interface.window.win);
SDL_Delay(SDL_DELAY);
}
int iterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit) {
//If the fractal shapes reach a size smaller than 2 pixels, or if we reach the desired no. of iterations
if (current.size < 2 || iterations == limit) {
draw_sdl(interface, fractal, current.x, current.y, current.size);
return iterations;
}
Shape top, left, right;
make_shape(&top, current.x, current.y - (current.size / 4), current.size / 2);
make_shape(&left, current.x - (current.size / 4), current.y + (current.size / 4), current.size / 2);
make_shape(&right, current.x + (current.size / 4), current.y + (current.size / 4), current.size / 2);
iterations++;
iterate(fractal, interface, top, iterations, limit);
iterate(fractal, interface, left, iterations, limit);
return iterate(fractal, interface, right, iterations, limit);
}
void make_shape(Shape *shape, int x, int y, int size) {
shape->x = x;
shape->y = y;
shape->size = size;
}