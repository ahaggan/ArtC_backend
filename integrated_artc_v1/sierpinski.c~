#include "display.h"

int iterate(SDL_Win *w, SDL_Rect square, int iterations, int limit);
void makesquare(SDL_Rect *square, int x, int y, int size);

void sierpinski(Interface interface, int limit)
{
    int x=interface.canvas.rect.x, y=interface.canvas.rect.y, size, iterations=0;
    size = (interface.canvas.rect.w < interface.canvas.rect.h ? 
            interface.canvas.rect.w : interface.canvas.rect.h);

    printf("Sierpinski Limit: %d\n", limit);

    SDL_Rect square;
    makesquare(&square, x, y, size);
    
    iterations = iterate(&interface.window, square, iterations+1, limit);
    printf("Sierpinski completed with %d iterations.\n", iterations);

    SDL_RenderPresent(interface.window.renderer);
    SDL_UpdateWindowSurface(interface.window.win);
    SDL_Delay(SDL_DELAY);
    clear_area(&interface.window, interface.canvas);
    SDL_SetRenderDrawColor(interface.window.renderer, 255,0,0,255);
}

int iterate(SDL_Win *w, SDL_Rect square, int iterations, int limit)
{
    SDL_Rect top, left, right;
    int size = square.w;

    if(square.w<2 || iterations == limit) {
        SDL_RenderFillRect(w->renderer, &square);
        return iterations;
    }

    makesquare(&top, square.x+(size/4), square.y, size/2);
    makesquare(&left, square.x, square.y+(size/2), size/2);
    makesquare(&right, square.x+(size/2), square.y+(size/2), size/2);

    iterate(w, top, iterations+1, limit);
    iterate(w, left, iterations+1, limit);
    return iterate(w, right, iterations+1, limit);
}

void makesquare(SDL_Rect *square, int x, int y, int size)
{
    square->x = x;
    square->y = y;
    square->h = square->w = size;
}
