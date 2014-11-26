//Keep all 'display' information within the display module. Pass around a display object.
#include "artc_sdl2.h"

void SDL_Win_Init(SDL_Win *w, char win_name[20]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    } 
    w->finished = 0;
   
    w->win= SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
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


void SDL_Events(SDL_Win *w, Interface* interface) {
    SDL_Event event;
    int composition_len = SDL_strlen(interface->composition);
    int x;
    int y;
    int mouse_inside = 1;

    while(SDL_PollEvent(&event)) { 
        //Mouse events
        SDL_GetMouseState(&x, &y);
        //mouse left of button
        if (x < interface->ping.rect.x) {
            mouse_inside = 0;
        }
        //mouse right of button
        else if (x > interface->ping.rect.x + interface->ping.rect.w) {
            mouse_inside = 0;
        }
        //mouse above of button
        else if (y < interface->ping.rect.y) {
            mouse_inside = 0;
        }
        //mouse below button
        else if (y > interface->ping.rect.y + interface->ping.rect.h) {
            mouse_inside = 0;
        }
        
        
        //default button appearance
        if (mouse_inside != 1) {
            interface->ping.colour.r = 255; interface->ping.colour.g = 0; interface->ping.colour.b = 0;
        }  
        else {
            switch (event.type) {
                case SDL_MOUSEMOTION: 
                    interface->ping.colour.r = 122; interface->ping.colour.g = 0; interface->ping.colour.b = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    interface->ping.colour.r = 0; interface->ping.colour.g = 255; interface->ping.colour.b = 0;
                    printf("%c", '\a');
                    break;
                case SDL_MOUSEBUTTONUP: 
                    interface->ping.colour.r = 122; interface->ping.colour.g = 0; interface->ping.colour.b = 0;
                    break;
            }
        }

        switch (event.type) {
            //User requests quit
            case SDL_QUIT:
                w->finished = 1;
            //User presses a key
            case SDL_KEYDOWN:
                //Select actions based on key press
                switch (event.key.keysym.sym) {
                    case SDLK_BACKSPACE:
                        if (composition_len > 0) {
                            interface->composition[composition_len - 1] = '\0';
                        }
                        break;
                    case SDLK_RETURN:
                        printf("%s\n", "enter");
                        break;
                    case SDLK_c:
                        if (SDL_GetModState() & KMOD_CTRL) {
                            SDL_SetClipboardText(interface->composition);
                        }
                        break;
                    case SDLK_v:
                        if (SDL_GetModState() & KMOD_CTRL) {
                           strcat(interface->composition, SDL_GetClipboardText());
                        }
                        break;
                }
                break;
            case SDL_TEXTINPUT:
                strcat(interface->composition, event.text.text);
                break;

            //case SDL_MOUSEMOTION:
            //case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
 
                if(x >= interface->gbutton.rect.x && x <= interface->gbutton.rect.x + interface->gbutton.rect.w &&
                     y >= interface->gbutton.rect.y && y <= interface->gbutton.rect.y + interface->gbutton.rect.h) {
                     clear_canvas(w, *interface);
                     input(w, *interface);
                }
                if(x >= interface->menubar.x && x <= interface->menubar.x + interface->menubar.w &&
                   y >= interface->menubar.y && y <= interface->menubar.y + interface->menubar.h) {

                      printf("Challenge accepted.\n\n");
                    //SDL_RenderPresent(w->renderer);
                    //SDL_UpdateWindowSurface(w->win);
                }

                break;

                //if !inside
                //button_state = button_mouse_out
            
                break;
            break;
        }
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
