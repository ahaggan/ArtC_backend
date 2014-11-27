//Keep all 'display' information within the display module. Pass around a display object.
#include "display.h"

void SDL_Win_Init(SDL_Win *w, char win_name[20]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    } 
    w->finished = 0;
   
    w->win= SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (w->win == NULL) {
        fprintf(stderr, "\nUnable to initialize SDL Win:  %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    //SDL_CreateRenderer(window that the renderer will be attached to, which rendering driver to use (-1 means first we find),
    w->renderer = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED);
    if (w->renderer == NULL) {
        fprintf(stderr, "\nUnable to initialize SDL Renderer: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
  
    // Set resolution (size) of renderer to the same as window
    SDL_RenderSetLogicalSize(w->renderer, WIN_WIDTH, WIN_HEIGHT); 

    //Set screen to white
    SDL_SetRenderDrawColor(w->renderer, 255, 255, 255, 255);
    
    //call RenderClear at the beginning on every frame to clear the screen and make it ready for more stuff.
    SDL_RenderClear(w->renderer);

    //call RenderPresent to make the drawing take effect.
    SDL_RenderPresent(w->renderer);
}

void SDL_Window_Events(SDL_Win *w, SDL_Event event, Interface* interface) {
    int x, y;
    switch(event.window.event) {
        //Get new dimensions and repaint on window size change.
        case SDL_WINDOWEVENT_SIZE_CHANGED: 
            
            SDL_GetWindowSize(w->win, &x, &y);
            SDL_SetWindowSize(w->win, event.window.data1, event.window.data2);
            draw_interface(w, interface);
            // Set resolution (size) of renderer to the same as window
            SDL_RenderSetLogicalSize(w->renderer, x, y); 
            SDL_RenderPresent(w->renderer);
            break;
        //exposed means that the window was obscured in some way, and now is not obscured.
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(w->renderer);
            break;
    }    

}

// Filled Circle centred at (cx,cy) of radius r, see :
// http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r, int a) {
   for (double dy = 1; dy <= r; dy += 1.0) {
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawLine(rend, cx-dx, cy+r-dy, cx+dx, cy+r-dy);
        SDL_RenderDrawLine(rend, cx-dx, cy-r+dy, cx+dx, cy-r+dy);
   }
}

// Circle centred at (cx,cy) of radius r, see :
// http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r, int a) {
   double dx, dy;
   dx = floor(sqrt((2.0 * r ) ));
   SDL_RenderDrawLine(rend, cx-dx, cy+r, cx+dx, cy+r);
   SDL_RenderDrawLine(rend, cx-dx, cy-r, cx+dx, cy-r);
   for (dy = 1; dy <= r; dy += 1.0) {
        dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawPoint(rend, cx+dx, cy+r-dy);
        SDL_RenderDrawPoint(rend, cx+dx, cy-r+dy);
        SDL_RenderDrawPoint(rend, cx-dx, cy+r-dy);
        SDL_RenderDrawPoint(rend, cx-dx, cy-r+dy);
   }
}

void SDL_TTF_Init() {
    if (TTF_Init() != 0) {
        fprintf(stderr, "\nUnable to initialize TTF:  %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
}

TTF_Font* SDL_Load_Font(char font_path[30], int font_size) {
    TTF_Font *font = TTF_OpenFont(font_path, font_size);
    if (font == NULL) {
        fprintf(stderr, "\nTTF_OpenFont could not open the font:  %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    return font;
}

SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w) {
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(w->renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}


void SDL_TTF_Quit(TTF_Font *font) {
    TTF_CloseFont(font);
    TTF_Quit();
}


//Actually, since we only need to save text data, not game states or binary or anything
//let's keep it simple and just use <stdio.h> functions!
SDL_RWops* SDL_Open_File(char *file_name) {
    SDL_RWops* file = SDL_RWFromFile(file_name, "r+");
    //If no such file:
    if (file == NULL) {
        printf("Warning: unable to open file! SDL Error: %s\n", SDL_GetError());
        //Create one!
        file = SDL_RWFromFile(file_name, "w+");
        if (file != NULL) {
            printf("New file created!\n");
        }  
        else {
            printf("Error: unable to create file! SDL Error: %s\n", SDL_GetError());
            exit(1);
        }
    }
    return file;
}
//Note for the future: if you want to use png images (like an artc logo) look here http://headerphile.com/sdl2/sdl-2-part-7-using-png-files/
