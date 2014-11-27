#include "input.h"
#include "artc.h"
#include "display.h"

int SDL_Events(SDL_Win *w, Interface* interface) {

    SDL_Event event;
    
    int composition_len = SDL_strlen(interface->composition);
    
    int x, y;
    SDL_GetMouseState(&x, &y);

    while(SDL_PollEvent(&event)) { 
        SDL_Window_Events(w, event, interface);
        switch (event.type) {

            //user requests quit
            case SDL_QUIT:
                w->finished = 1;
                break;

            //user changes window
            case SDL_WINDOWEVENT:
                SDL_Window_Events(w, event, interface);
                break;

            //user presses a key
            case SDL_TEXTINPUT:

                //based on the key pressed...
                switch (event.key.keysym.sym) {

                    //backspace deletes the previous character
                    case SDLK_BACKSPACE:
                       //!!CALL TO DISPLAY.C!!//
                       clear_area(w, interface->texteditor);
                        if (composition_len > 0) {
                            interface->composition[composition_len - 1] = '\0';
                        }
                        break;

                    //enter will move the cursor to the next line
                    case SDLK_RETURN:
                        printf("%s\n", "enter");
                        break;

                    //ctrl + c copies text to the clipboard
                    case SDLK_c:
                        if (SDL_GetModState() & KMOD_CTRL) {
                            SDL_SetClipboardText(interface->composition);
                        }
                        break;
    
                    //ctrl + v copies text to the clipboard
                    case SDLK_v:
                        if (SDL_GetModState() & KMOD_CTRL) {
                           strcat(interface->composition, SDL_GetClipboardText());
                        }
                        break;

                    //any other keyboard input? add it on to the current text.
                    case SDL_TEXTINPUT:
                        strcat(interface->composition, event.text.text);
                        break;
                }
                
            //user clicks somewhere
            case SDL_MOUSEBUTTONDOWN:
 

                if(x >= interface->gbutton.rect.x && x <= interface->gbutton.rect.x + interface->gbutton.rect.w &&
                     y >= interface->gbutton.rect.y && y <= interface->gbutton.rect.y + interface->gbutton.rect.h) {
                     return 1;
                }

                //user clicks on menubar (should be specific challenge button)                
                if (x >= interface->menubar.rect.x && x <= interface->menubar.rect.x + interface->menubar.rect.w &&
                   y >= interface->menubar.rect.y && y <= interface->menubar.rect.y + interface->menubar.rect.h) {
                      printf("Challenge accepted.\n\n");
                }
                break;
        }
    }
}
