#include "display.h"

int sierpinskiiterate(Draw *fractal, Interface interface, Shape shape, int iterations, int limit, char c);

void sierpinski(Draw *fractal, Interface interface, int limit) {
    Shape shape;
    make_shape(&shape, fractal->startx, fractal->starty, fractal->size[0], fractal->height[0], 0);

    int iterations = 1; //One iteration is just the shape.

    printf("Sierpinski Limit: %d\n", limit);

    iterations = sierpinskiiterate(fractal, interface, shape, iterations, limit, 't');
    printf("Sierpinski completed with %d iterations.\n", iterations);

    SDL_RenderPresent(interface.window.renderer);
    SDL_UpdateWindowSurface(interface.window.win);
    SDL_Delay(SDL_DELAY);

}

int sierpinskiiterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, char c) {
    //If the fractal shapes reach a size smaller than 2 pixels, or if we reach the desired no. of iterations
    if (current.size < 2 || iterations == limit) {
/*        float angle;
        switch (c) {
            case 't': angle = 0;
                break;
            case 'l': angle = -2.0*M_PI/3.0;
                break;
            case 'r': angle = 2.0*M_PI/3.0;
                break;
        }*/
        draw_sdl(interface, fractal, current.x, current.y, current.size, current.rotation, iterations);
        return iterations;
    }

    Shape top, left, right;
    make_shape(&top, current.x, current.y - (current.height / 4), current.size / 2, current.height / 2, 0);
    make_shape(&left, current.x - (current.size / 4), current.y + (current.size / 4), current.size / 2, current.height / 2, -2.0*M_PI/3.0);
    make_shape(&right, current.x + (current.size / 4), current.y + (current.size / 4), current.size / 2, current.height / 2, 2.0*M_PI/3.0);

    iterations++;

    sierpinskiiterate(fractal, interface, top, iterations, limit, 't');
    sierpinskiiterate(fractal, interface, left, iterations, limit, 'l');
    return sierpinskiiterate(fractal, interface, right, iterations, limit, 'r');
}
