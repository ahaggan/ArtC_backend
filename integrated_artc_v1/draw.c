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
/*
        double j=y+(size/2)-(size*cos(angle));
        for(double i=x-(size/2.0); i<=(x-(size/2.0)+(size*sin(angle))); i+=) {
            SDL_RenderDrawLine(interface.window.renderer, i, j, i+(size*sin(angle)), j+(size*cos(angle)));
            j+=sin(angle)/size;
        }*/
    }

    else if (strcmp(fractal->shape, "circle") == 0) {
        SDL_RenderFillCircle(interface.window.renderer, x, y, size / 2);

    }

    else if (strcmp(fractal->shape, "line") == 0) {
        SDL_RenderDrawLine(interface.window.renderer, (x-(size/2.0*sin(angle))), (y+(size/2.0*cos(angle))), (x+(size/2.0*sin(angle))), (y-(size/2.0*cos(angle))));
//printf("%f|%f|%f|%f\n", (x-size/2.0)*sin(angle), (y-size/2.0)*cos(angle), (x+size/2.0)*sin(angle), (y+size/2.0)*cos(angle));
    }

    else if(strcmp(fractal->shape, "triangle_outline") == 0) {
    angle = 0; // THIS MAKES THE TRIANGLES ALL DRAW STRAIGHT FOR NOW.
    int c1x = x+((size/2.0)*sin(angle)), c1y = y-((size/2.0)*cos(angle));
    int c2x = x+((size/2.0)*sin(angle+(M_PI*(2.0/3.0)))), c2y = y-((size/2.0)*cos(angle+(M_PI*(2.0/3.0))));
    int c3x = x+((size/2.0)*sin(angle-(M_PI*(2.0/3.0)))), c3y = y-((size/2.0)*cos(angle-(M_PI*(2.0/3.0))));

    SDL_RenderDrawLine(interface.window.renderer, c1x, c1y, c2x, c2y);
    SDL_RenderDrawLine(interface.window.renderer, c2x, c2y, c3x, c3y);
    SDL_RenderDrawLine(interface.window.renderer, c3x, c3y, c1x, c1y);
    }
}

