#include "artc_sdl2.h"

void triangle(draw *object)
{
    object->startx = 0;
    object->starty = WIN_HEIGHT;
    object->endx = WIN_WIDTH/2;
    object->endy = 0;
    draw_sdl(object);
    object->startx = WIN_WIDTH/2;
    object->starty = 0;
    object->endx = WIN_WIDTH;
    object->endy = WIN_HEIGHT;
    draw_sdl(object);
    object->startx = WIN_WIDTH;
    object->starty = WIN_HEIGHT;
    object->endx = 0;
    object->endy = WIN_HEIGHT;
    draw_sdl(object);
}
