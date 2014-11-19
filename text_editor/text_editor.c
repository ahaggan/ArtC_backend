#include "artc_sdl2.h"

int main(void) {
	char composition[1000];

	SDL_Win w;
	SDL_Win_Init(&w, "ArtC Text Editor");
	SDL_Rect text_editor;
	text_editor.w = WIN_WIDTH;
    text_editor.h = WIN_HEIGHT;
	SDL_SetTextInputRect(&text_editor);
	SDL_StartTextInput();

	do { 
		SDL_SetDrawColour(&w, 255, 255, 255);
    	text_editor.x = (0);
    	text_editor.y = (0);
		SDL_RenderFillRect(w.renderer, &text_editor); 
	    SDL_RenderPresent(w.renderer);
	    SDL_UpdateWindowSurface(w.win); 
		SDL_Events(&w, composition);	
	}while(!w.finished);
	
	SDL_StopTextInput();
	atexit(SDL_Quit);
}