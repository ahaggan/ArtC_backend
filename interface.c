#include "artc_sdl2.h"

void make_rect(SDL_Win *win, SDL_Rect *rect, 
                int x, int y, int w, int h, 
                int r, int g, int b);
int main()
{
    SDL_Win win;
    SDL_Win_Init(&win, "Art-C interface");
    SDL_TTF_Init();
    TTF_Font *font = SDL_Load_Font("font/FreeSans.ttf", 25);
    
    SDL_Rect menubar, texteditor, canvas, gbutton;
    make_rect(&win, &menubar, 0, 0, WIN_WIDTH, 50, 255, 64, 64);
    // Height of 50, coloured red.
    make_rect(&win, &texteditor, 0, menubar.h, WIN_WIDTH/2, WIN_HEIGHT-menubar.h-30, 128, 128, 128);
    // border of 5, button 25, coloured grey.
    make_rect(&win, &canvas, texteditor.w, menubar.h, WIN_WIDTH/2, WIN_HEIGHT-menubar.h-30, 255, 255, 255);
    // coloured white.
    make_rect(&win, &gbutton, texteditor.w-100-5, WIN_HEIGHT-25-5, 100, 25, 255, 0, 0);

    SDL_Color textcolour = {64,255,64,255};
    SDL_Surface* textsurface = TTF_RenderText_Solid(font, "GENERATE", textcolour);
    SDL_Texture* texttexture = SurfaceToTexture(textsurface, &win);

    SDL_RenderCopy(win.renderer, texttexture, NULL, &gbutton);
    SDL_RenderPresent(win.renderer);
    SDL_UpdateWindowSurface(win.win);

    // Pass texteditor rect to texteditor module so it knows where it is.

    while(!win.finished) {
        SDL_Events(&win);
    }
    return 0;
}

void make_rect(SDL_Win *win, SDL_Rect *rect, 
                int x, int y, int w, int h, 
                int r, int g, int b)
{
  rect->w = w;
  rect->h = h;
  rect->x = x;
  rect->y = y;
  SDL_SetRenderDrawColor(win->renderer, r, g, b,255);
  SDL_RenderFillRect(win->renderer, rect);
}
