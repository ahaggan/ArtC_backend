//Keep all 'display' information within the display module. Pass around a display object.

#include "artc_sdl2.h"

void SDL_Win_Init(SDL_Win *w, char win_name[20]) {
 
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   } 
   w->finished = 0;
   
   w->win= SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
   if (w->win == NULL) {
      fprintf(stderr, "\nUnable to initialize SDL Win:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }
  //SDL_CreateRenderer(window that the renderer will be attached to, which rendering driver to use (-1 means first we find),
  w->renderer = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED);
  if (w->renderer == NULL) {
    fprintf(stderr, "\nUnable to initialize SDL Renderer: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  
  // Set resolution (size) of renderer to the same as window
  SDL_RenderSetLogicalSize(w->renderer, WIN_WIDTH, WIN_HEIGHT); 

  // Set screen to white
  SDL_SetRenderDrawColor(w->renderer, 0, 0, 0, 255);

  //call RenderClear at the beginning on every frame to clear the screen and make it ready for more stuff.
  SDL_RenderClear(w->renderer);

  //call RenderPresent to make the drawing take effect.
  SDL_RenderPresent(w->renderer);

}


void SDL_Events(SDL_Win *w) {
   SDL_Event event;
   while(SDL_PollEvent(&event)) {      
       switch (event.type) {
      /*
          case SDL_TEXTINPUT:
          //add new text onto the end of our text
            strcat(composition, event.text.text);
            break;

          case SDL_TEXTEDITING:
          //Update the composition text. 
          //Update the cursor pos. 
          //Update the selection length (if any).
            main_text = event.edit.text;
            cursor = event.edit.start;
            selection_len = event.edit.length;
            break;
          */
          case SDL_QUIT:
            w->finished = 1;
       }
    }
}
/*
void SDL_TTF_Init() {
    if (TTF_Init() != 0) {
        fprintf(stderr, "\nUnable to initialize TTF:  %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
}

TTF_Font* SDL_Load_Font(char font_path[30], int font_size) {
    TTF_Font *font = TTF_OpenFont(font_path, font_size);
    if (font == NULL) {
        fprintf(stderr, "\nTTF_OpenFont could not open the font:  %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    return font;
}

SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w) {
  SDL_Texture* text;
  text = SDL_CreateTextureFromSurface(w->renderer, surface);
  SDL_FreeSurface(surface);
  return text;
}
*/
// Filled Circle centred at (cx,cy) of radius r, see :
// http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r, int a)
{

   for (double dy = 1; dy <= r; dy += 1.0) {
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawLine(rend, cx-dx, cy+r-dy, cx+dx, cy+r-dy);
        SDL_RenderDrawLine(rend, cx-dx, cy-r+dy, cx+dx, cy-r+dy);
   }

}

// Circle centred at (cx,cy) of radius r, see :
// http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r, int a)
{

   double dx, dy;
   dx = floor(sqrt((2.0 * r ) ));
   SDL_RenderDrawLine(rend, cx-dx, cy+r, cx+dx, cy+r);
   SDL_RenderDrawLine(rend, cx-dx, cy-r, cx+dx, cy-r);
   for (dy = 1; dy <= r; dy += 1.0) {
        dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawPoint(rend, cx+dx, cy+r-dy);
        SDL_RenderDrawPoint(rend, cx+dx, cy-r+dy);
        SDL_RenderDrawPoint(rend, cx-dx, cy+r-dy);
        SDL_RenderDrawPoint(rend, cx-dx, cy-r+dy);
   }

}
/*
void SDL_TTF_Quit(TTF_Font *font) {
  TTF_CloseFont(font);
  TTF_Quit();
}
*/


//Note for the future: if you want to use png images (like an artc logo) look here http://headerphile.com/sdl2/sdl-2-part-7-using-png-files/

