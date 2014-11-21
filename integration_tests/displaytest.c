#include "neillsdl2.h"

void draw_sdl(draw *object)
{

    SDL_Simplewin sw;
    int x, y;
    x=(WWIDTH / 2) - (object->size / 2);
    y=(WHEIGHT / 2) - (object->size / 2);


    Neill_SDL_Init(&sw);

    if (strcmp(object->colour, "blue") == 0)
    {
        Neill_SDL_SetDrawColour(&sw, 0, 0, 255, 50);
    }

    else if (strcmp(object->colour, "red") == 0)
    {
        Neill_SDL_SetDrawColour(&sw, 255, 0, 0, 50);
    }

    else if (strcmp(object->colour, "green") == 0)
    {
        Neill_SDL_SetDrawColour(&sw, 0, 255, 0, 50);
    }


    if (strcmp(object->shape, "square") == 0)
    {
        SDL_Rect rectangle;
        rectangle.w = object->size;
        rectangle.h = object->size;
        rectangle.x=x;
        rectangle.y=y;
        SDL_RenderFillRect(sw.renderer, &rectangle);

    }

    else if (strcmp(object->shape, "circle") == 0)
    {
        Neill_SDL_RenderFillCircle(sw.renderer, x, y, object->size, 1);

    }


    SDL_RenderPresent(sw.renderer);
    SDL_UpdateWindowSurface(sw.win);


    while (!sw.finished)
    {

        Neill_SDL_Events(&sw);
    }

}

