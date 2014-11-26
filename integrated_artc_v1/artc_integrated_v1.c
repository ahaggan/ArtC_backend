#include "artc_sdl2.h"

int main() {
    Interface artc;
    SDL_Win win;
    SDL_Win_Init(&win, "ARTC interface");
    SDL_TTF_Init();
    TTF_Font *font = SDL_Load_Font("font/FreeSans.ttf", 24);
    artc.font = font;
    draw_interface(&win, &artc);

    SDL_Color editor_text_colour = {0,0,0,255};
    //Sets text_rect to type text inputs.
    SDL_SetTextInputRect(&artc.texteditor.rect);
    //Start accepting text input events
    SDL_StartTextInput();
    strcpy(artc.composition, "Enter text:");
    SDL_RenderPresent(win.renderer);
    SDL_UpdateWindowSurface(win.win);

    while(!win.finished) {
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, artc.composition, editor_text_colour);
        SDL_Texture* text_editor = SurfaceToTexture(text_surface, &win);
        SDL_QueryTexture(text_editor, NULL, NULL, &artc.texteditor.rect.w, &artc.texteditor.rect.h);
        SDL_RenderCopy(win.renderer, text_editor, NULL, &artc.texteditor.rect);
        SDL_Events(&win, &artc);
        SDL_RenderPresent(win.renderer);
        SDL_UpdateWindowSurface(win.win);
    }
    return 0;
}

void draw_interface(SDL_Win *win, Interface *artc)
{
    int x, y;
    SDL_GetWindowSize(win->win, &x, &y);
    make_rect(win, &artc->menubar, 0, 0, x, y / 12, 255, 64, 64);
    make_rect(win, &artc->texteditor, 0, artc->menubar.rect.h, x/2, y-artc->menubar.rect.h-25, 128, 128, 128);
    make_rect(win, &artc->canvas, artc->texteditor.rect.w, artc->menubar.rect.h, x/2, y-artc->menubar.rect.h-25, 255, 255, 255);
    make_rect(win, &artc->gbutton, 0, y-25, x/10, 25, 255, 0, 0);
    make_text(win, &artc->gbutton.rect, 64, 255, 64, artc->font, "GENERATE!");
    make_rect(win, &artc->ch1button, 5, 5, 100, 40, 0, 0, 255);
    make_text(win, &artc->ch1button.rect, 192, 192, 255, artc->font, "Challenge 1");
}

void make_rect(SDL_Win *win, Area *area, int x, int y, int w, int h, int r, int g, int b)
{
  area->rect.w = w;
  area->rect.h = h;
  area->rect.x = x;
  area->rect.y = y;
  area->colour.r = r;
  area->colour.g = g;
  area->colour.b = b;
  SDL_SetRenderDrawColor(win->renderer, r, g, b, 255);
  SDL_RenderFillRect(win->renderer, &area->rect);
}

void make_text(SDL_Win *win, SDL_Rect *location, int r, int g, int b, TTF_Font *font, char* text)
{
    SDL_Color textcolour = {r,g,b,255};
    SDL_Surface* textsurface = TTF_RenderText_Solid(font, text, textcolour);
    SDL_Texture* texttexture = SurfaceToTexture(textsurface, win);
    SDL_RenderCopy(win->renderer, texttexture, NULL, location);
}
