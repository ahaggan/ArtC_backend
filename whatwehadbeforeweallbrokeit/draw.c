#include "display.h"

void clear_area(SDL_Win *window, Area area) {
    SDL_SetRenderDrawColor(window->renderer, area.colour.r, area.colour.g, area.colour.b, 255);
    SDL_RenderFillRect(window->renderer, &area.rect);
    SDL_RenderPresent(window->renderer);
    SDL_UpdateWindowSurface(window->win);
printf("area cleared.\n");
}

void draw_sdl(Interface interface, Draw *fractal, int x, int y, int size) 
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
        SDL_RenderDrawLine(interface.window.renderer, fractal->startx, fractal->starty, fractal->endx, fractal->endy);
    }


 //   SDL_RenderPresent(interface.window.renderer);
 //   SDL_UpdateWindowSurface(interface.window.win);
}

