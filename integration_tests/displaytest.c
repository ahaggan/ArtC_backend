#include "artc_sdl2.h"

void draw_sdl(draw *object)
{

    SDL_Win sw;
    int x, y;
    char win_name[20];
    x = (WIN_WIDTH / 2) - (object->size / 2);
    y = (WIN_HEIGHT / 2) - (object->size / 2);
    win_name[0] = 'I';
    win_name[1] = ' ';

    SDL_Win_Init(&sw, win_name);

    if (strcmp(object->colour, "blue") == 0)
    {
        SDL_SetRenderDrawColor(sw.renderer, 0, 0, 255, 50);
    }

    else if (strcmp(object->colour, "red") == 0)
    {
        SDL_SetRenderDrawColor(sw.renderer, 255, 0, 0, 50);
    }

    else if (strcmp(object->colour, "green") == 0)
    {
        SDL_SetRenderDrawColor(sw.renderer, 0, 255, 0, 50);
    }

    else if (strcmp(object->colour, "pink") == 0)
    {
        SDL_SetRenderDrawColor(sw.renderer, 180, 0, 100, 50);
    }

    else if (strcmp(object->colour, "purple") == 0)
    {
        SDL_SetRenderDrawColor(sw.renderer, 100, 0, 150, 50);
    }


    if (strcmp(object->shape, "square") == 0)
    {
        SDL_Rect rectangle;
        rectangle.w = object->size;
        rectangle.h = object->size;
        rectangle.x = x;
        rectangle.y = y;
        SDL_RenderFillRect(sw.renderer, &rectangle);

    }

    else if (strcmp(object->shape, "circle") == 0)
    {
        SDL_RenderFillCircle(sw.renderer, x, y, object->size, 1);

    }

    else if (strcmp(object->shape, "line") == 0)
    {
        SDL_RenderDrawLine(sw.renderer, x, WIN_HEIGHT / 2, x + (object->size) , WIN_HEIGHT / 2);

    }


    SDL_RenderPresent(sw.renderer);
    SDL_UpdateWindowSurface(sw.win);


    while (!sw.finished)
    {

        SDL_Events(&sw);
    }

}

