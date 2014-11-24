#include "../artc_sdl2.h"

int BUTTON_WIDTH = 300;
int BUTTON_HEIGHT = 200;

int main(void) {
	char composition[1000] = "Type...";

	SDL_Win w;
	SDL_Win_Init(&w, "ARTC Text Editor");

	//Initialise text things
	SDL_TTF_Init();
    TTF_Font* font = SDL_Load_Font("font/FreeSans.ttf", 50);

	TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
	SDL_Color text_colour = {255, 255, 255, 255}; // white
	SDL_Color button_colour = {255, 0, 0, 255}; // red

	//Create text texture
	SDL_Rect text_rect;
	text_rect.w = WIN_WIDTH;
	text_rect.h = WIN_HEIGHT;
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, composition, text_colour);
	SDL_Texture* text_editor = SurfaceToTexture(text_surface, &w);
	SDL_QueryTexture(text_editor, NULL, NULL, &text_rect.w, &text_rect.h);
	text_rect.x = text_rect.y = 0;

	//Create button texture
	SDL_Rect button_rect;
	button_rect.w = BUTTON_WIDTH;
	button_rect.y = BUTTON_HEIGHT;
	SDL_Surface* button_surface = TTF_RenderText_Shaded(font, "Ping", text_colour, button_colour);
	SDL_Texture* ping_button = SurfaceToTexture(button_surface, &w);
	SDL_QueryTexture(ping_button, NULL, NULL, &button_rect.w, &button_rect.h);
	button_rect.x = WIN_WIDTH / 2;
	button_rect.y = WIN_WIDTH / 2;

	//Sets text_rect to type text inputs.
	SDL_SetTextInputRect(&text_rect);
	//Start accepting text input events
	SDL_StartTextInput();
	do {		 
		SDL_RenderClear(w.renderer);	

		SDL_Events(&w, composition, button_rect, &button_colour);

		SDL_DestroyTexture(text_editor);
		SDL_DestroyTexture(ping_button);

		SDL_Surface* text_surface = TTF_RenderText_Solid(font, composition, text_colour);
		SDL_Texture* text_editor = SurfaceToTexture(text_surface, &w);
		SDL_QueryTexture(text_editor, NULL, NULL, &text_rect.w, &text_rect.h);
		
		SDL_Surface* button_surface = TTF_RenderText_Shaded(font, "Ping", text_colour, button_colour);
		SDL_Texture* ping_button = SurfaceToTexture(button_surface, &w);
		SDL_QueryTexture(ping_button, NULL, NULL, &button_rect.w, &button_rect.h);

		SDL_RenderCopy(w.renderer, text_editor, NULL, &text_rect);
		SDL_RenderCopy(w.renderer, ping_button, NULL, &button_rect);
		SDL_RenderPresent(w.renderer);
	}while(!w.finished);

	//Stop accepting text input events
	SDL_StopTextInput();

	//Close font and SDL_TTF library
	SDL_TTF_Quit(font);
	
	//calls SDL_Quit when the program terminates
	atexit(SDL_Quit);
}