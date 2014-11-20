#include "artc_sdl2.h"

int main()
{
    SDL_Win win;
    SDL_Win_Init(&win, "Art-C interface");
    SDL_TTF_Init();
    TTF_Font *font = SDL_Load_Font("font/FreeSans.ttf", 25);

    SDL_Rect menubar;
    menubar.x = 0;
    menubar.y = 0;
    menubar.w = WIN_WIDTH;
    menubar.h = 50;
    SDL_SetRenderDrawColor(win.renderer, 255,128,128,255);
    SDL_RenderFillRect(win.renderer, &menubar);

    SDL_Rect texteditor;
    texteditor.x = 0;
    texteditor.y = menubar.h;
    texteditor.w = WIN_WIDTH/2;
    texteditor.h = WIN_HEIGHT-menubar.h-5-25; 
        // border of 5, button 25
    SDL_SetRenderDrawColor(win.renderer, 128,128,128,255);
    SDL_RenderFillRect(win.renderer, &texteditor);

    SDL_Rect canvas;
    canvas.x = texteditor.w;
    canvas.y = menubar.h;
    canvas.w = texteditor.w;
    canvas.h = WIN_HEIGHT-menubar.h-5-25;
    SDL_SetRenderDrawColor(win.renderer, 255,255,255,255);
    SDL_RenderFillRect(win.renderer, &canvas);

    SDL_Rect drawbutton;
    drawbutton.w = 100;
    drawbutton.h = 25;
    drawbutton.x = texteditor.w - drawbutton.w - 5;
    drawbutton.y = WIN_HEIGHT - drawbutton.h - 5;
    SDL_SetRenderDrawColor(win.renderer, 255,64,64,255);
    SDL_RenderFillRect(win.renderer, &drawbutton);

    SDL_Color generatecolour = {64,255,64,255};
    SDL_Surface* generate = TTF_RenderText_solid(font, "GENERATE", generatecolour);
    SDL_Texture* solid_texture = SurfaceToTexture(generate, &win);
    SDL_QueryTexture(solid_texture, NULL, NULL, &drawbutton.w, &drawbutton.h);

    SDL_RenderClear(win.renderer);
    SDL_RenderCopy(win. renderer);
    SDL_RenderPresent(win.renderer);
    SDL_UpdateWindowSurface(win.win);

    // Pass texteditor rect to texteditor module.
    while(!win.finished) {
        SDL_Events(&win);
    }
    return 0;
}
