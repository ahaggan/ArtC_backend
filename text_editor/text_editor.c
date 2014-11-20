#include "../artc_sdl2.h"

SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w);

int main(void) {
	SDL_Win w;
	SDL_Surface display;
	SDL_Win_Init(&w, "ARTC Text Editor");
	
	SDL_TTF_Init();
  	TTF_Font *font;
	
    font = TTF_OpenFont("font/FreeSans.ttf", 200);	
	SDL_Color text_colour = { 255, 255, 0, 255 }; // white

	SDL_Rect solid_rect;
	solid_rect.h = 500;
	solid_rect.w = 500;
	
	SDL_Surface* solid_text = TTF_RenderText_Solid(font, "Welcome", text_colour);
	SDL_Texture *solid_texture = SurfaceToTexture(solid_text, &w);
	
	SDL_QueryTexture(solid_texture, NULL, NULL, &solid_rect.w, &solid_rect.h);
	solid_rect.x = 0;
	solid_rect.y = 0;
 	
	do {		 
		//Blank screen
		SDL_RenderClear(w.renderer);	
		SDL_RenderCopy(w.renderer, solid_texture, NULL, &solid_rect);
		SDL_RenderPresent(w.renderer);
		SDL_Events(&w);
	}while(!w.finished);

	TTF_CloseFont(font);
	atexit(SDL_Quit);
}

// Convert an SDL_Surface to SDL_Texture. We've done this before, so I'll keep it short
SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w) {
	SDL_Texture* text;
	text = SDL_CreateTextureFromSurface(w->renderer, surface);
	SDL_FreeSurface(surface);
	return text;
} 