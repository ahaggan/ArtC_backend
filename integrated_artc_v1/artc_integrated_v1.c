#include "artc_sdl2.h"

int main() {
    Interface artc;
    //&window = (int *)malloc(sizeof(interface));
    /*&window.menubar = malloc(sizeof(SDL_Rect));
    &window.texteditor = malloc(sizeof(SDL_Rect));
    &window.canvas = malloc(sizeof(SDL_Rect));
    &window.gbutton = malloc(sizeof(SDL_Rect));*/
    SDL_Win win;
    SDL_Win_Init(&win, "ARTC interface");
    SDL_TTF_Init();
    TTF_Font *font = SDL_Load_Font("font/FreeSans.ttf", 24);
    
    strcpy(artc.composition, "Enter text:");

    Button ch1button;

    make_rect(&win, &artc.menubar, 0, 0, WIN_WIDTH, 50, 255, 64, 64);
    // Height of 50, coloured red.
    make_rect(&win, &artc.texteditor, 0, artc.menubar.h, WIN_WIDTH/2, WIN_HEIGHT-artc.menubar.h-30, 128, 128, 128);
    // border of 5, button 25, coloured grey.
    make_rect(&win, &artc.canvas, artc.texteditor.w, artc.menubar.h, WIN_WIDTH/2, WIN_HEIGHT-artc.menubar.h-30, 255, 255, 255);
    // coloured white.
    make_rect(&win, &artc.gbutton.rect, artc.texteditor.w-100-5, WIN_HEIGHT-25-5, 100, 25, 255, 0, 0);
    // width 100, height 25, positioned underneath text editor.
    make_rect(&win, &ch1button.rect, 5, 5, 100, 40, 0, 0, 255);
    // challenge 1 button, blue.

    SDL_Color textcolour = {64,255,64,255};
    SDL_Surface* textsurface = TTF_RenderText_Solid(font, "GENERATE!", textcolour);
    SDL_Texture* texttexture = SurfaceToTexture(textsurface, &win);
    SDL_RenderCopy(win.renderer, texttexture, NULL, &artc.gbutton.rect);

    SDL_Color chcolour = {192,192,255,255};
    textsurface = TTF_RenderText_Solid(font, "Challenge 1", chcolour);
    texttexture = SurfaceToTexture(textsurface, &win);
    SDL_RenderCopy(win.renderer, texttexture, NULL, &ch1button.rect);

    SDL_Color editor_text_colour = {0,0,0,255};
    textsurface = TTF_RenderText_Solid(font, artc.composition, editor_text_colour);
    texttexture = SurfaceToTexture(textsurface, &win);
    SDL_RenderCopy(win.renderer, texttexture, NULL, &artc.texteditor);

    //Sets text_rect to type text inputs.
    SDL_SetTextInputRect(&artc.texteditor);
    //Start accepting text input events
    SDL_StartTextInput();

    SDL_RenderPresent(win.renderer);
    SDL_UpdateWindowSurface(win.win);

    // Pass rects around so respective modules know where they are.
    while(!win.finished) {
        /* Composition stuff bugs - lots of flickering, no backspace*/    
        SDL_DestroyTexture(texttexture);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, artc.composition, editor_text_colour);
        SDL_Texture* text_editor = SurfaceToTexture(text_surface, &win);
        SDL_QueryTexture(text_editor, NULL, NULL, &artc.texteditor.w, &artc.texteditor.h);
        SDL_RenderCopy(win.renderer, text_editor, NULL, &artc.texteditor);
        SDL_RenderPresent(win.renderer);
        SDL_Events(&win, &artc);
    }
    return 0;
}

void make_rect(SDL_Win *win, SDL_Rect *rect, 
                int x, int y, int w, int h, int r, int g, int b)
{
  rect->w = w;
  rect->h = h;
  rect->x = x;
  rect->y = y;
  SDL_SetRenderDrawColor(win->renderer, r, g, b, 255);
  SDL_RenderFillRect(win->renderer, rect);
}
