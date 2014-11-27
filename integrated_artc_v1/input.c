#include "display.h"

void SDL_Events(SDL_Win *w, Interface* interface) {
    SDL_Event event;
    int composition_len = SDL_strlen(interface->composition);
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    while(SDL_PollEvent(&event)) { 
        SDL_Window_Events(w, event, interface);
        switch (event.type) {
            //User requests quit
            case SDL_QUIT:
                w->finished = 1;
            //window is altered
            case SDL_WINDOWEVENT:
                SDL_Window_Events(w, event, interface);
                break;
            //User presses a key
            case SDL_KEYDOWN:
                //Select actions based on key press
                switch (event.key.keysym.sym) {
                    case SDLK_BACKSPACE:
                       clear_area(w, interface->texteditor);
                        if (composition_len > 0) {
                            interface->composition[composition_len - 1] = '\0';
                            //
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
                     clear_area(w, interface->canvas);
                     input(w, *interface);
                }
                if(x >= interface->menubar.rect.x && x <= interface->menubar.rect.x + interface->menubar.rect.w &&
                   y >= interface->menubar.rect.y && y <= interface->menubar.rect.y + interface->menubar.rect.h) {

                      printf("Challenge accepted.\n\n");
                    //SDL_RenderPresent(w->renderer);
                    //SDL_UpdateWindowSurface(w->win);
                }
                break;

                //if !inside
                //button_state = button_mouse_out
        }
    }
}
