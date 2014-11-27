#include "display.h"

void clear_area(SDL_Win *sw, Area area)
{
    SDL_SetRenderDrawColor(sw->renderer, area.colour.r, area.colour.g, area.colour.b, 255);
    SDL_RenderFillRect(sw->renderer, &area.rect);
    SDL_RenderPresent(sw->renderer);
    SDL_UpdateWindowSurface(sw->win);
}


void draw_sdl(draw *fractal, SDL_Win *sw, Interface interface) {
    int x, y;
    x = (interface.canvas.rect.x + (interface.canvas.rect.w / 2)) - (fractal->size / 2);
    y = (interface.canvas.rect.y + (interface.canvas.rect.h / 2)) - (fractal->size / 2);

    if (strcmp(fractal->colour, "blue") == 0) {
        SDL_SetRenderDrawColor(sw->renderer, 0, 0, 255, 50);
    }

    else if (strcmp(fractal->colour, "red") == 0) {
        SDL_SetRenderDrawColor(sw->renderer, 255, 0, 0, 50);
    }

    else if (strcmp(fractal->colour, "green") == 0) {
        SDL_SetRenderDrawColor(sw->renderer, 0, 255, 0, 50);
    }

    else if (strcmp(fractal->colour, "pink") == 0) {
        SDL_SetRenderDrawColor(sw->renderer, 180, 0, 100, 50);
    }

    else if (strcmp(fractal->colour, "purple") == 0) {
        SDL_SetRenderDrawColor(sw->renderer, 100, 0, 150, 50);
    }


    if (strcmp(fractal->shape, "square") == 0) {
        SDL_Rect rectangle;
        rectangle.w = fractal->size;
        rectangle.h = fractal->size;
        rectangle.x = x;
        rectangle.y = y;
        SDL_RenderFillRect(sw->renderer, &rectangle);

    }

    else if (strcmp(fractal->shape, "circle") == 0) {
        SDL_RenderFillCircle(sw->renderer, x, y, fractal->size / 2, 1);

    }

    else if (strcmp(fractal->shape, "line") == 0) {
        SDL_RenderDrawLine(sw->renderer, fractal->startx, fractal->starty, fractal->endx, fractal->endy);
    }

    if (strcmp(fractal->type, "sierpinski") == 0) {
        sierpinski(sw, interface, fractal->size);
    }

    SDL_RenderPresent(sw->renderer);
    SDL_UpdateWindowSurface(sw->win);
}

