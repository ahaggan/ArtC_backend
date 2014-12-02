#include "display.h"

void draw_sdl(Interface interface, Draw *fractal, int x, int y, int size, float angle) 
{

    if (strcmp(fractal->colour, "blue") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 0, 0, 255, 50);
    }

    else if (strcmp(fractal->colour, "red") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 255, 0, 0, 50);
    }

    else if (strcmp(fractal->colour, "green") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 0, 255, 0, 50);
    }

    else if (strcmp(fractal->colour, "pink") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 180, 0, 100, 50);
    }

    else if (strcmp(fractal->colour, "purple") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 100, 0, 150, 50);
    }


    if (strcmp(fractal->shape, "square") == 0) {
        SDL_Rect rectangle;
        rectangle.w = size;
        rectangle.h = size;
        rectangle.x = x - size/2;
        rectangle.y = y - size/2;
        SDL_RenderFillRect(interface.window.renderer, &rectangle);

    }

    else if (strcmp(fractal->shape, "circle") == 0) {
        SDL_RenderFillCircle(interface.window.renderer, x, y, size / 2, 1);

    }

    else if (strcmp(fractal->shape, "line") == 0) {
        SDL_RenderDrawLine(interface.window.renderer, (x-(size/2.0*sin(angle))), (y+(size/2.0*cos(angle))), (x+(size/2.0*sin(angle))), (y-(size/2.0*cos(angle))));
printf("%f|%f|%f|%f\n", (x-size/2.0)*sin(angle), (y-size/2.0)*cos(angle), (x+size/2.0)*sin(angle), (y+size/2.0)*cos(angle));
    }
}

