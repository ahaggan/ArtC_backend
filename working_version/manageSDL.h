#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#define  WIN_WIDTH  1366
#define  WIN_HEIGHT  715
#define  MIN_WIDTH  800
#define  MIN_HEIGHT  600

typedef struct SDL_Win {
    SDL_bool finished;
    SDL_Window *win;
    SDL_Renderer *renderer;
} SDL_Win;

typedef struct area {
    SDL_Rect rect;
    SDL_Color col;
} Area;

void SDL_Win_Init(SDL_Win *w, char* win_name);
void SDL_Handle_Error(char* error);

void clear_area(SDL_Win *window, Area area);
void render_update_clear(SDL_Win window);

void SDL_TTF_Init();
void SDL_TTF_Quit(TTF_Font *font);
TTF_Font* SDL_Load_Font(char* font_path, int font_size);

SDL_Texture* surface_to_texture(SDL_Surface* surface, SDL_Win* window);
SDL_Texture* load_image(char* filename, SDL_Win* window);



