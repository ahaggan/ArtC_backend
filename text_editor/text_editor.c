#include "../artc_sdl2.h"

int main(void) {
	SDL_Win w;
	SDL_Surface display;
	SDL_Win_Init(&w, &display, "ARTC Text Editor");

	SDL_TTF_Init();
  	TTF_Font *font;
    font = TTF_OpenFont("FreeSans.ttf", 24);	

	SDL_Rect tux_pos;
	tux_pos.x = 0;
	tux_pos.y = 0;
	tux_pos.w = WIN_WIDTH;
	tux_pos.h = WIN_HEIGHT;

	SDL_Surface* tux_surface = SDL_LoadBMP("sam.bmp");
	SDL_Texture* tux_texture = SDL_CreateTextureFromSurface(w.renderer, tux_surface);

	SDL_FreeSurface(tux_surface);

	do {		 
		//Blank screen
		SDL_RenderClear(w.renderer);
		SDL_RenderCopy(w.renderer, tux_texture, NULL, &tux_pos);
		SDL_RenderPresent(w.renderer);
		SDL_Events(&w);

	}while(!w.finished);

	TTF_CloseFont(font);
	atexit(SDL_Quit);
}