#include "input.h"

int SDL_Events(Interface* interface) {
    //define a tmp variable same as interface->active_txt coordinates so that you don't have to access it through interface so much
    SDL_Event event;

    //printf("%s\n", interface->composition);
    int x, y;

    SDL_GetMouseState(&x, &y);

    while(SDL_PollEvent(&event)) { 
        
        SDL_Window_Events(event, interface);
        SDL_Text_Editor_Events(event, interface);
        //SDL_Text_Editor_Events
        switch (event.type) {
            //user requests quit
            case SDL_QUIT:
                interface->window.finished = 1;
                break;

            //user changes window
            case SDL_WINDOWEVENT:
                SDL_Window_Events(event, interface);
                break;

            //user clicks somewhere
            case SDL_MOUSEBUTTONDOWN:
                printf("x:%d y:%d\n", x, y);
                printf("gbuttonx:%d gbuttony:%d gbuttonw:%d gbuttonh:%d\n", interface->gbutton.rect.x, interface->gbutton.rect.y, interface->gbutton.rect.w, interface->gbutton.rect.h);
                printf("menubarx:%d menubary:%d menubarw:%d menubarh%d\n", interface->menubar.rect.x, interface->menubar.rect.y, interface->menubar.rect.w, interface->menubar.rect.h);
                if(x >= interface->gbutton.rect.x && x <= interface->gbutton.rect.x + interface->gbutton.rect.w &&
                     y >= interface->gbutton.rect.y && y <= interface->gbutton.rect.y + interface->gbutton.rect.h) {
                     printf("Generate!\n");
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
            // Set resolution (size) of renderer to the same as window
            SDL_RenderSetLogicalSize(interface->window.renderer, x, y); 
            draw_interface(interface);
            SDL_RenderPresent(interface->window.renderer);
            break;
        //exposed means that the window was obscured in some way, and now is not obscured.
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(interface->window.renderer);
            break;
    }    
}

int SDL_Text_Editor_Events(SDL_Event event, Interface* interface) {
    Coordinates active = interface->active_txt;
    switch(event.type) {
            //textinput case MUST be before keydown; otherwise 'soh' enters the string.
        case SDL_TEXTINPUT:
            if (strcmp(interface->text_editor[active.row][active.column].character, EMPTY_CELL) != 0) {
                    printf("There's something here already\n");
                }
            strcpy(interface->text_editor[active.row][active.column].character, event.text.text);

            if (!(active.row == EDITOR_ROWS - 1 && active.column == EDITOR_COLUMNS - 1)) {
                SDL_SetTextInputRect(&interface->text_editor[active.row][active.column].next->box.rect);

                interface->active_txt.row  = interface->text_editor[active.row][active.column].next->y;
                interface->active_txt.column = interface->text_editor[active.row][active.column].next->x;
            }
        return 2;
        break;
        //user presses a key
        case SDL_KEYDOWN:
            //based on the key pressed...
            switch (event.key.keysym.sym) {
                //backspace deletes the previous character
                case SDLK_BACKSPACE:
                   
                    if (interface->text_editor[active.row][active.column].previous == NULL) {
                        break;
                    }

                    //quick and dirty fix for the final space on the grid
                    if (interface->text_editor[active.row][active.column].next == NULL) {
                        strcpy(interface->text_editor[active.row][active.column].character, EMPTY_CELL); 
                        strcpy(interface->text_editor[active.row][active.column].previous->character, EMPTY_CELL);
                    }
                    else {
                        strcpy(interface->text_editor[active.row][active.column].previous->character, EMPTY_CELL);
                    }
                    
                    SDL_SetTextInputRect(&interface->text_editor[active.row][active.column].previous->box.rect);
                     
                    interface->active_txt.row  = interface->text_editor[active.row][active.column].previous->y;
                
                    interface->active_txt.column = interface->text_editor[active.row][active.column].previous->x;
                   
                    return 2;
                    break;
                
                //enter will move the cursor to the next line
                case SDLK_RETURN:          
                    if (active.row  == EDITOR_ROWS - 1) {
                        break;
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row + 1][0].box.rect);
                    interface->active_txt.row  = active.row + 1;
                    interface->active_txt.column = 0;
                    return 2;
                    break;

                /*okay, instead of ALL of these for loops, why not just havea value in text_editor which holds the currently selected cell?*/
                case SDLK_TAB:
                    if (SDL_GetModState() & KMOD_SHIFT) {
                        printf("hello!\n");
                        if (active.column <= 2) {
                            if (active.row != 0) {
                                SDL_SetTextInputRect(&interface->text_editor[active.row - 1][EDITOR_COLUMNS - 1].box.rect);

                                interface->active_txt.row  = active.row - 1;
                                interface->active_txt.column = EDITOR_COLUMNS - 1;
                                return 2;
                                break;
                            }
                            return 2;
                            break;
                        }
               
                        SDL_SetTextInputRect(&interface->text_editor[active.row][active.column - 3].box.rect);
                        interface->active_txt.row  = active.row - 1;
                        interface->active_txt.column = active.column -3;
        
                        return 2;
                        break;
                    }
                    
                  else {
                    if (active.column  >= EDITOR_COLUMNS - 3) {
                        if (active.row != EDITOR_ROWS - 1) {
                            SDL_SetTextInputRect(&interface->text_editor[active.row + 1][0].box.rect);
                            interface->active_txt.row  = active.row + 1;
                            interface->active_txt.column = 0;
                            return 2;
                            break;
                        }
                        return 2;
                        break;
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row][active.column + 3].box.rect);


                    interface->active_txt.column = active.column + 3;

                    return 2;
                    break;
                }

                case SDLK_UP:   
                  
                    if (active.row == 0) {
                        return 2;
                        break;
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row - 1][active.column].box.rect);
                    interface->active_txt.row = active.row - 1;
                    return 2;
                    break;

                case SDLK_RIGHT:   

                    if (active.column == EDITOR_COLUMNS - 1) {
                        if (active.row != EDITOR_ROWS - 1) {
                            SDL_SetTextInputRect(&interface->text_editor[active.row + 1][0].box.rect);
                            interface->active_txt.row = active.row + 1;
                            interface->active_txt.column = 0;
                            return 2;
                            break;
                        }
                        break;     
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row][active.column + 1].box.rect);      
                    interface->active_txt.column = active.column + 1;
                    return 2;
                    break;

                case SDLK_DOWN:   
                    if (active.row == EDITOR_ROWS - 1) {
                        return 2;
                        break;
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row + 1][active.column].box.rect);
                  
                    interface->active_txt.row = active.row + 1;
                    return 2;
                    break;

                case SDLK_LEFT:   

                    if (active.column == 0) {
                     if (active.row  != 0) {
                        SDL_SetTextInputRect(&interface->text_editor[active.row - 1][EDITOR_COLUMNS - 1].box.rect);
                        
                        interface->active_txt.row = active.row - 1;
                        interface->active_txt.column = EDITOR_COLUMNS - 1;
                        return 2;
                        }
                        break;
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row ][active.column - 1].box.rect);
                        
                    interface->active_txt.column = active.column - 1;
                    return 2;
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
    }
}
//functions to handle the key presses
