#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#define  WIN_WIDTH  1366
#define  WIN_HEIGHT  715
#define  MIN_WIDTH  800
#define  MIN_HEIGHT  600

//Structure containing information about the SDL window
typedef struct SDL_Win {
    SDL_bool finished;
    SDL_Window *win;
    SDL_Renderer *renderer;
} SDL_Win;

//General area structure, used to display rectangular blocks of colour
typedef struct area {
    SDL_Rect rect;
    SDL_Color col;
} Area;

void SDL_Win_Init(SDL_Win *w, char* win_name);

//Quits the program and is called if there is an error within the SDL functions
void SDL_Handle_Error(char* error);

//Clears a chosen area of the SDL window
void clear_area(SDL_Win *window, Area area);

//Updates the renderer with any changes to the display since it was last called
void render_update(SDL_Win window);

//If SDL_TTF doesn't initialise function calls SDL_handle_error
void SDL_TTF_Init();

//Closes SDL TTF library
void SDL_TTF_Quit(TTF_Font *font);

//Loads the chosen font and size to TTF and returns this font, 
// calls error if font in NULL
TTF_Font* SDL_Load_Font(char* font_path, int font_size);

//creates a texture from a surface and frees the surface
SDL_Texture* surface_to_texture(SDL_Surface* surface, SDL_Win* window);

//loads a bmp to a surface, converts that surface to a texture and returns it
SDL_Texture* load_image(char* filename, SDL_Win* window);



