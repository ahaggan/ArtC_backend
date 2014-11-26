#include "artc_sdl2.h"

void clear_area(SDL_Win *sw, Area area)
{
    SDL_SetRenderDrawColor(sw->renderer, area.colour.r, area.colour.g, area.colour.b, 255);
    SDL_RenderFillRect(sw->renderer, &area.rect);
    SDL_RenderPresent(sw->renderer);
    SDL_UpdateWindowSurface(sw->win);
}


void draw_sdl(draw *object, SDL_Win *sw, Interface interface) {
    int x, y;
    x = (interface.canvas.rect.x + (interface.canvas.rect.w / 2)) - (object->size / 2);
    y = (interface.canvas.rect.y + (interface.canvas.rect.h / 2)) - (object->size / 2);

    if (strcmp(object->colour, "blue") == 0) {
        SDL_SetRenderDrawColor(sw->renderer, 0, 0, 255, 50);
    }

    else if (strcmp(object->colour, "red") == 0) {
        SDL_SetRenderDrawColor(sw->renderer, 255, 0, 0, 50);
    }

    else if (strcmp(object->colour, "green") == 0) {
        SDL_SetRenderDrawColor(sw->renderer, 0, 255, 0, 50);
    }

    else if (strcmp(object->colour, "pink") == 0) {
        SDL_SetRenderDrawColor(sw->renderer, 180, 0, 100, 50);
    }

    else if (strcmp(object->colour, "purple") == 0) {
        SDL_SetRenderDrawColor(sw->renderer, 100, 0, 150, 50);
    }


    if (strcmp(object->shape, "square") == 0) {
        SDL_Rect rectangle;
        rectangle.w = object->size;
        rectangle.h = object->size;
        rectangle.x = x;
        rectangle.y = y;
        SDL_RenderFillRect(sw->renderer, &rectangle);

    }

    else if (strcmp(object->shape, "circle") == 0) {
        SDL_RenderFillCircle(sw->renderer, x, y, object->size / 2, 1);

    }

    else if (strcmp(object->shape, "line") == 0) {
        SDL_RenderDrawLine(sw->renderer, object->startx, object->starty, object->endx, object->endy);
    }

    else if (strcmp(object->shape, "sierpinski") == 0) {
        sierpinski(sw, interface, object->size);
    }

    SDL_RenderPresent(sw->renderer);
    SDL_UpdateWindowSurface(sw->win);
}

