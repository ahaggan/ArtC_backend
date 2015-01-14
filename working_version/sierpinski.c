#include "fractals.h"

int sierpinskiiterate(Draw *fractal, Interface interface, Shape shape, int iterations, int limit, char c);

void sierpinski(Draw *fractal, Interface interface, int limit) {
    Shape shape;
    make_shape(&shape, fractal->startx, fractal->starty, fractal->size[0], fractal->height[0], fractal->angle);

    int iterations = 1; //One iteration is just the shape.

    printf("Sierpinski Limit: %d\n", limit);

    iterations = sierpinskiiterate(fractal, interface, shape, iterations, limit, 't');
    printf("Sierpinski completed with %d iterations.\n", iterations);

    SDL_RenderPresent(interface.window.renderer);
    SDL_UpdateWindowSurface(interface.window.win);
}

int sierpinskiiterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, char c) {
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
        draw_sdl(interface, fractal, current.x, current.y, current.size/2, current.rotation, iterations);
        return iterations;
    }

    Shape top, left, right;
    make_shape(&top, current.x + ((current.size/4)*sin(fractal->angle)), current.y - ((current.size / 4)*cos(fractal->angle)), current.size / 2, current.height / 2, fractal->angle);
    make_shape(&left, current.x + ((current.size / 4))*sin(fractal->angle - ((2*M_PI)/3.0)), current.y - ((current.size / 4))*cos(fractal->angle - ((2*M_PI)/3.0)), current.size / 2, current.height / 2, fractal->angle - ((2*M_PI)/3.0));
    make_shape(&right, current.x + ((current.size / 4))*sin(fractal->angle + ((2*M_PI)/3.0)), current.y - ((current.size / 4))*cos(fractal->angle + ((2*M_PI)/3.0)), current.size / 2, current.height / 2, fractal->angle + ((2*M_PI)/3.0));

    iterations++;

    sierpinskiiterate(fractal, interface, top, iterations, limit, 't');
    sierpinskiiterate(fractal, interface, left, iterations, limit, 'l');
    return sierpinskiiterate(fractal, interface, right, iterations, limit, 'r');
}
