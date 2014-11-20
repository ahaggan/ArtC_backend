#include "../artc_sdl2.h"

SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w);
void CreateTextTextures();

int main(void) {
	SDL_Win w;
	SDL_Win_Init(&w, "ARTC Text Editor");

	//Initialise text things
	SDL_TTF_Init();
    TTF_Font* font = SDL_Load_Font("font/FreeSans.ttf", 90);

	SDL_Color text_colour = {255, 255, 255, 255}; // white

	//Create rect
	SDL_Rect solid_rect;
	solid_rect.h = 20;
	solid_rect.w = 20;
	
	//Create text texture
	SDL_Surface* solid_text = TTF_RenderText_Solid(font, "Welcome", text_colour);
	SDL_Texture *solid_texture = SurfaceToTexture(solid_text, &w);
	SDL_QueryTexture(solid_texture, NULL, NULL, &solid_rect.w, &solid_rect.h);
	solid_rect.x = 0;
	solid_rect.y = 0;

	do {		 
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