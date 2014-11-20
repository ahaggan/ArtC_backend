#include "../artc_sdl2.h"

int main(void) {
	SDL_Win w;
	SDL_Surface display;
	SDL_Win_Init(&w, &display, "ARTC Text Editor");

	SDL_TTF_Init();
  	TTF_Font *font;
    font = TTF_OpenFont("FreeSans.ttf", 24);	

	int block_X = WIN_WIDTH/2;
	int block_Y = IN_HEIGHT/2;

	SDL_Rect block;
	
	do {		 
		//Blank screen
		SDL_SetRenderDrawColor(w.renderer, 255, 255, 255, 255);
		SDL_RenderClear(w.renderer);

		//Draw blue rectangle outline
		SDL_SetRenderDrawColor(w.renderer, 0, 0, 255, 255);
		block.x = block_X
		block.y = block_Y
		block.w = 200;
		block.h = 200;

		SDL_RenderDrawRect(w.renderer, &block);


		//Fill blue rectangle
		SDL_RenderFillRect(w.renderer, &block);
		SDL_RenderPresent(w.renderer);
		SDL_Events(&w);
	}while(!w.finished);

	TTF_CloseFont(font);
	atexit(SDL_Quit);
}