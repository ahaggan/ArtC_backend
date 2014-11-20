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
    
    SDL_Rect menubar;
    make_rect(&win, &menubar, 0, 0, WIN_WIDTH, 50, 255, 64, 64);

    SDL_Rect texteditor;
    make_rect(&win, &texteditor, 0, menubar.h, WIN_WIDTH/2, WIN_HEIGHT-menubar.h-30, 128, 128, 128);
    // border of 5, button 25

    SDL_Rect canvas;
    make_rect(&win, &canvas, texteditor.w, menubar.h, texteditor.w, WIN_HEIGHT-menubar.h-30, 255, 255, 255);

    SDL_Rect drawbutton;
    make_rect(&win, &drawbutton, 100, 25, texteditor.w-drawbutton.w-5, WIN_HEIGHT-drawbutton.h-5, 255, 0, 0);

    SDL_Color textcolour = {64,255,64,255};
    SDL_Surface* text = TTF_RenderText_Solid(font, "GENERATE", textcolour);
    SDL_Texture* solid_texture = SurfaceToTexture(text, &win);
    SDL_QueryTexture(solid_texture, NULL, NULL, &drawbutton.w, &drawbutton.h);

    SDL_RenderClear(win.renderer);
    SDL_RenderCopy(win.renderer, solid_texture, NULL, &drawbutton);
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
  rect->x = x;
  rect->y = y;
  rect->w = w;
  rect->h = h;
  SDL_SetRenderDrawColor(win->renderer, r, g, b,255);
  SDL_RenderFillRect(win->renderer, rect);
}
