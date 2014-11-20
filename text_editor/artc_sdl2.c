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

   w->renderer = SDL_CreateRenderer(w->win, -1, 0);
   if(w->renderer == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Renderer:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   // Set screen to black
   SDL_SetDrawColour(w, 0, 0, 0);
   SDL_RenderClear(w->renderer);
   SDL_RenderPresent(w->renderer);
}

void SDL_Events(SDL_Win *w, char *composition) {
   SDL_Event event;
   
   while(SDL_PollEvent(&event)) {      
       switch (event.type) {
          case SDL_TEXTINPUT:
          //add new text onto the end of our text
            strcat(composition, event.text.text);
            break;
          /*
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

void SDL_TTF_Init() {
  if (TTF_Init() != 0) {
      fprintf(stderr, "\nUnable to initialize TTF:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }
}


void SDL_Load_Font() {
   TTF_Font *font;
   font = TTF_OpenFont("font/FreeSans.ttf", 24);
   if (font == NULL)
   {
      fprintf(stderr, "\nTTF_OpenFont could not open the font:  %s\n", SDL_GetError());
      TTF_Quit();
      SDL_Quit();
      exit(1);
   }
}

// Wrapper to avoid complexities of renderer & alpha channels
void SDL_SetDrawColour(SDL_Win *w, Uint8 r, Uint8 g, Uint8 b) {
   SDL_SetRenderDrawColor(w->renderer, r, g, b, SDL_ALPHA_OPAQUE);
}