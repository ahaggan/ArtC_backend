#include "input.h"

int main() {
    Interface interface;
    
    SDL_Win_Init(&interface.window, "ARTC interface");
    SDL_TTF_Init();
    TTF_Font *font = SDL_Load_Font("font/FreeSans.ttf", 24);

    interface.font = font;
    draw_interface(&interface);
    Draw fractal;


    SDL_Color editor_text_colour = {0,0,0,255};
    //Sets text_rect to type text inputs.
    SDL_SetTextInputRect(&interface.texteditor.rect);
    //Start accepting text input events
    SDL_StartTextInput();
    strcpy(interface.composition, "Enter text:");
    SDL_RenderPresent(interface.window.renderer);
    SDL_UpdateWindowSurface(interface.window.win);

    while(!interface.window.finished) {
      SDL_Surface* text_surface = TTF_RenderText_Solid(font, interface.composition, editor_text_colour);
      SDL_Texture* text_editor = SurfaceToTexture(text_surface, &interface.window);
      SDL_QueryTexture(text_editor, NULL, NULL, &interface.texteditor.rect.w, &interface.texteditor.rect.h);
      SDL_RenderCopy(interface.window.renderer, text_editor, NULL, &interface.texteditor.rect);

      if (SDL_Events(&interface) == 1) {
        clear_area(&interface.window, interface.canvas);
        input(interface, &fractal);
        printf("\nafter input");
        generate_fractal(&fractal, interface);
      }        
      else if(SDL_Events(&interface) == 2) {
        clear_area(&interface.window, interface.texteditor);
      }
      SDL_RenderPresent(interface.window.renderer);
      SDL_UpdateWindowSurface(interface.window.win);

      SDL_DestroyTexture(text_editor);
    }
    return 0;
}

void draw_interface(Interface *interface) {
    int x, y;
    SDL_GetWindowSize(interface->window.win, &x, &y);
    make_rect(&interface->window, &interface->menubar, 0, 0, x, y / 12, 255, 64, 64);
    make_rect(&interface->window, &interface->texteditor, 0, interface->menubar.rect.h, x/2, y-interface->menubar.rect.h-25, 128, 128, 128);
    make_rect(&interface->window, &interface->canvas, interface->texteditor.rect.w, interface->menubar.rect.h, x/2, y- interface->menubar.rect.h-25, 255, 255, 255);
    make_rect(&interface->window, &interface->gbutton, 0, y-25, x/10, 25, 255, 0, 0);
    make_text(&interface->window, &interface->gbutton.rect, 64, 255, 64, interface->font, "GENERATE!");
    make_rect(&interface->window, &interface->ch1button, 5, 5, 100, 40, 0, 0, 255);
    make_text(&interface->window, &interface->ch1button.rect, 192, 192, 255, interface->font, "Challenge 1");
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
