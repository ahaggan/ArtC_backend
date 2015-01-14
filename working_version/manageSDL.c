#include "manageSDL.h"

void SDL_Win_Init(SDL_Win *w, char* win_name) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Handle_Error("Unable to initialize SDL");
    } 

    w->finished = 0;
    w->win= SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, 
                              SDL_WINDOW_SHOWN);
    if (w->win == NULL) {
        SDL_Handle_Error("Unable to initialize SDL Win");
    }

    w->renderer = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED | 
                                      SDL_RENDERER_PRESENTVSYNC | 
                                      SDL_RENDERER_TARGETTEXTURE);
    if (w->renderer == NULL) {
        SDL_Handle_Error("Unable to initialize SDL Rend");
    }

    // Set resolution (size) of renderer to the window size.
    SDL_RenderSetLogicalSize(w->renderer, WIN_WIDTH, WIN_HEIGHT); 
    SDL_SetWindowMinimumSize(w->win, MIN_WIDTH, MIN_HEIGHT);
    // Set screen to white.
    SDL_SetRenderDrawColor(w->renderer, 255, 255, 255, 255);
    render_update_clear(*w);
}

void SDL_Handle_Error(char* error) {
    fprintf(stderr, "%s: %s\n\n", error, SDL_GetError());
    SDL_Quit();
    exit(1);
}

void clear_area(SDL_Win *window, Area area) {
   SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
   SDL_RenderFillRect(window->renderer, &area.rect);  
   render_update_clear(*window);
}

void render_update_clear(SDL_Win window) {
   SDL_RenderPresent(window.renderer);
   SDL_UpdateWindowSurface(window.win);
   //SDL_RenderClear(window.renderer);
}

void SDL_TTF_Init() {
    if (TTF_Init() != 0) {
        SDL_Handle_Error("Unable to initialize TTF");
    }
}

void SDL_TTF_Quit(TTF_Font *font) {
   TTF_CloseFont(font);
   TTF_Quit();
}

TTF_Font* SDL_Load_Font(char* font_path, int font_size) {
   TTF_Font *font = TTF_OpenFont(font_path, font_size);
   if (font == NULL) {
      fprintf(stderr, "\nTTF_OpenFont could not open the font: %s\n", 
              SDL_GetError());
      TTF_Quit();
      SDL_Quit();
      exit(1);
   }
   return font;
}

//creates a texture from a surface and frees the surface
SDL_Texture* surface_to_texture(SDL_Surface* surface, SDL_Win* window) {
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(window->renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

//loads a bmp to a surface, then converts that surface to a texture and returns it
SDL_Texture* load_image(char* filename, SDL_Win* window) {
    SDL_Surface* image = SDL_LoadBMP(filename); 
    if (image == NULL ) {
        printf( "Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
    } 
    return surface_to_texture(image, window) ;
}

