#include "../artc_sdl2.h"

int BUTTON_WIDTH = 300;
int BUTTON_HEIGHT = 200;

FILE* open_file(char *file_name);

int main(void) {
	Interface interface;

	FILE* test_file = open_file("test_file2.txt");
	
	//Copy initial file contents into the text editor.

	strcpy(interface.composition, "Enter text:");

	SDL_Win w;
	SDL_Win_Init(&w, "ARTC Text Editor");

	//Initialise text things
	SDL_TTF_Init();
    TTF_Font* font = SDL_Load_Font("font/FreeSans.ttf", 50);

	SDL_Color text_colour = {0, 0, 0, 255}; // black
	
	SDL_Color button_colour = {255, 0, 0, 255};
	interface.ping.colour = button_colour; // red

	//Create text texture
	
	interface.texteditor.w = WIN_WIDTH;
	interface.texteditor.h = WIN_HEIGHT;
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, interface.composition, text_colour);
	SDL_Texture* text_editor = SurfaceToTexture(text_surface, &w);
	SDL_QueryTexture(text_editor, NULL, NULL, &interface.texteditor.w, &interface.texteditor.h);
	interface.texteditor.x = interface.texteditor.y = 0;

	//Create button texture
	
	interface.ping.rect.w = BUTTON_WIDTH;
	interface.ping.rect.y = BUTTON_HEIGHT;
	SDL_Surface* button_surface = TTF_RenderText_Shaded(font, "Ping", text_colour, interface.ping.colour);
	SDL_Texture* ping_button = SurfaceToTexture(button_surface, &w);
	SDL_QueryTexture(ping_button, NULL, NULL, &interface.ping.rect.w, &interface.ping.rect.h);
	interface.ping.rect.x = WIN_WIDTH / 2;
	interface.ping.rect.y = WIN_WIDTH / 2;

	//Sets text_rect to type text inputs.
	SDL_SetTextInputRect(&interface.texteditor);
	//Start accepting text input events
	SDL_StartTextInput();
	do {		 
		SDL_RenderClear(w.renderer);	

		SDL_Events(&w, &interface);

		SDL_DestroyTexture(text_editor);
		SDL_DestroyTexture(ping_button);

		SDL_Surface* text_surface = TTF_RenderText_Solid(font, interface.composition, text_colour);
		SDL_Texture* text_editor = SurfaceToTexture(text_surface, &w);
		SDL_QueryTexture(text_editor, NULL, NULL, &interface.texteditor.w, &interface.texteditor.h);
		
		SDL_Surface* button_surface = TTF_RenderText_Shaded(font, "Ping", text_colour, interface.ping.colour);
		SDL_Texture* ping_button = SurfaceToTexture(button_surface, &w);
		SDL_QueryTexture(ping_button, NULL, NULL, &interface.ping.rect.w, &interface.ping.rect.h);

		SDL_RenderCopy(w.renderer, text_editor, NULL, &interface.texteditor);
		SDL_RenderCopy(w.renderer, ping_button, NULL, &interface.ping.rect);
		SDL_RenderPresent(w.renderer);
	}while(!w.finished);

	//Stop accepting text input events
	SDL_StopTextInput();

	//Close font and SDL_TTF library
	SDL_TTF_Quit(font);
	
	//calls SDL_Quit when the program terminates
	atexit(SDL_Quit);
	//closes test file
	fclose(test_file);
}

FILE* open_file(char *file_name) {
	//Attempt to open file for reading and writing
	FILE *input_file = fopen(file_name, "r+");
	if (input_file == NULL) {
		printf("Warning: unable to open file.\n");
		//Attempt to create new file for writing
		input_file = fopen(file_name, "w");
		if (input_file != NULL) {
            printf("New file created!\n");
        }  
        else {
            printf("Error: unable to create file!");
            exit(1);
        }
	}
	return input_file;
} 