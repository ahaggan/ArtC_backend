#include "input.h"

int SDL_Events(Interface* interface) {

    SDL_Event event;
    
    int composition_len = SDL_strlen(interface->composition);

    //printf("%s\n", interface->composition);
    int x, y;

    SDL_GetMouseState(&x, &y);

    while(SDL_PollEvent(&event)) { 
        SDL_Window_Events(event, interface);
        switch (event.type) {
            //user requests quit
            case SDL_QUIT:
                interface->window.finished = 1;
                break;

            //user changes window
            case SDL_WINDOWEVENT:
                SDL_Window_Events(event, interface);
                break;

            //textinput case MUST be before keydown; otherwise a weird soh enters the string.
            case SDL_TEXTINPUT:
                strcat(interface->composition, event.text.text);
                break;
            //user presses a key
            case SDL_KEYDOWN:

                //based on the key pressed...
                switch (event.key.keysym.sym) {

                    //backspace deletes the previous character
                    case SDLK_BACKSPACE:
                        if (composition_len > 0) {
                            interface->composition[composition_len - 1] = '\0';
                        }
                        return 2;
                        break;

                    //enter will move the cursor to the next line
                    case SDLK_RETURN:
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
                }
            break;
            
            //any other keyboard input? add it on to the current text.


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
    return 0;
}

void SDL_Window_Events(SDL_Event event, Interface* interface) {
    int x, y;
    switch(event.window.event) {
        //Get new dimensions and repaint on window size change.
        case SDL_WINDOWEVENT_SIZE_CHANGED: 
            
            SDL_GetWindowSize(interface->window.win, &x, &y);
            SDL_SetWindowSize(interface->window.win, event.window.data1, event.window.data2);
            draw_interface(interface);
            // Set resolution (size) of renderer to the same as window
            SDL_RenderSetLogicalSize(interface->window.renderer, x, y); 
            SDL_RenderPresent(interface->window.renderer);
            break;
        //exposed means that the window was obscured in some way, and now is not obscured.
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(interface->window.renderer);
            break;
    }    

}