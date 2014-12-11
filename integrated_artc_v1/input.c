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
                for (int row = 0; row < EDITOR_ROWS; row++) {
                    for (int column = 0; column < EDITOR_COLUMNS; column++) {
                        if (interface->text_editor[row][column].selected == 1) {
                            if (strcmp(interface->text_editor[row][column].character, EMPTY_CELL) != 0) {
                                printf("There's something here already\n");
                            }
                            strcpy(interface->text_editor[row][column].character, event.text.text);
                            if (!(row == EDITOR_ROWS - 1 && column == EDITOR_COLUMNS - 1)) {
                                SDL_SetTextInputRect(&interface->text_editor[row][column].next->box.rect);
                                interface->text_editor[row][column].selected = 0;
                                interface->text_editor[row][column].next->selected = 1;
                            }
                            return 2;
                            break;
                        }
                    }
                }
                
            break;
            //user presses a key
            case SDL_KEYDOWN:
                //based on the key pressed...
                switch (event.key.keysym.sym) {
                    //backspace deletes the previous character
                    case SDLK_BACKSPACE:
                        for (int row = 0; row < EDITOR_ROWS; row++) {
                            for (int column = 0; column < EDITOR_COLUMNS; column++) {
                                if (interface->text_editor[row][column].selected == 1) {
                                
                                    if (interface->text_editor[row][column].previous == NULL) {
                                        break;
                                    }
                                    //quick and dirty fix for the final space on the grid
                                    if (interface->text_editor[row][column].next == NULL) {
                                        strcpy(interface->text_editor[row][column].character, EMPTY_CELL); 
                                        strcpy(interface->text_editor[row][column].previous->character, EMPTY_CELL);
                                    }
                                    else {
                                        strcpy(interface->text_editor[row][column].previous->character, EMPTY_CELL);
                                    }
                                    SDL_SetTextInputRect(&interface->text_editor[row][column].previous->box.rect);
                                    interface->text_editor[row][column].selected = 0;
                                    interface->text_editor[row][column].previous->selected = 1;
                                }
                            }
                        }
                        return 2;
                        break;

                    //enter will move the cursor to the next line
                    case SDLK_RETURN:
                        for (int row = 0; row < EDITOR_ROWS; row++) {
                            for (int column = 0; column < EDITOR_COLUMNS; column++) {
                                if (interface->text_editor[row][column].selected == 1) {
                                  
                                    if (row == EDITOR_ROWS - 1) {
                                        break;
                                    }
                                    SDL_SetTextInputRect(&interface->text_editor[row + 1][0].box.rect);
                                    interface->text_editor[row][column].selected = 0;
                                    interface->text_editor[row + 1][0].selected = 1;
                                    return 2;
                                    break;

                                }
                            }
                        }
                    /*okay, instead of ALL of these for loops, why not just havea value in text_editor which holds the currently selected cell?*/
                    case SDLK_TAB:
                        for (int row = 0; row < EDITOR_ROWS; row++) {
                            for (int column = 0; column < EDITOR_COLUMNS; column++) {
                                if (interface->text_editor[row][column].selected == 1) {
                                  if (SDL_GetModState() & KMOD_SHIFT) {
                                    printf("hello!\n");
                                    if (column <= 2) {
                                        if (row != 0) {
                                            SDL_SetTextInputRect(&interface->text_editor[row - 1][EDITOR_COLUMNS - 1].box.rect);
                                            interface->text_editor[row][column].selected = 0;
                                            interface->text_editor[row - 1][EDITOR_COLUMNS - 1].selected = 1;  
                                            return 2;
                                            break;
                                        }
                                        return 2;
                                        break;
                                    }
                                    SDL_SetTextInputRect(&interface->text_editor[row][column - 3].box.rect);
                                    interface->text_editor[row][column].selected = 0;
                                    interface->text_editor[row][column - 3].selected = 1;
                                    return 2;
                                    break;
                                  }
                                
                                  else {
                                    if (column >= EDITOR_COLUMNS - 3) {
                                        if (row != EDITOR_ROWS - 1) {
                                            SDL_SetTextInputRect(&interface->text_editor[row + 1][0].box.rect);
                                            interface->text_editor[row][column].selected = 0;
                                            interface->text_editor[row + 1][0].selected = 1;  
                                            return 2;
                                            break;
                                        }
                                        return 2;
                                        break;
                                    }
                                    SDL_SetTextInputRect(&interface->text_editor[row][column + 3].box.rect);
                                    interface->text_editor[row][column].selected = 0;
                                    interface->text_editor[row][column + 3].selected = 1;
                                    return 2;
                                    break;
                                  }
                                }
                            }
                        }

                    case SDLK_UP:   
                        for (int row = 0; row < EDITOR_ROWS; row++) {
                            for (int column = 0; column < EDITOR_COLUMNS; column++) {
                                if (interface->text_editor[row][column].selected == 1) {
                                   
                                    if (row == 0) {
                                        return 2;
                                        break;
                                    }
                                    SDL_SetTextInputRect(&interface->text_editor[row - 1][column].box.rect);
                                    interface->text_editor[row][column].selected = 0;
                                    interface->text_editor[row - 1][column].selected = 1;
                                    return 2;
                                    break;

                                }
                            }
                        }
                    case SDLK_RIGHT:   
                            for (int row = 0; row < EDITOR_ROWS; row++) {
                            for (int column = 0; column < EDITOR_COLUMNS; column++) {
                                if (interface->text_editor[row][column].selected == 1) {
                                    
                                    if (column == EDITOR_COLUMNS - 1) {
                                        if (row != EDITOR_ROWS - 1) {
                                            SDL_SetTextInputRect(&interface->text_editor[row + 1][0].box.rect);
                                            interface->text_editor[row][column].selected = 0;
                                            interface->text_editor[row + 1][0].selected = 1;
                                            printf("Next row! %d %d\n", row + 1, 0);
                                            return 2;
                                        }
                                        break;     
                                    }
                                    SDL_SetTextInputRect(&interface->text_editor[row][column + 1].box.rect);
                                    interface->text_editor[row][column].selected = 0;
                                    interface->text_editor[row][column + 1].selected = 1;
                                    printf("Next column! %d %d\n", row, column + 1);
                                    return 2;
                                    break;

                                }
                            }
                        }
                    case SDLK_DOWN:   
                            for (int row = 0; row < EDITOR_ROWS; row++) {
                            for (int column = 0; column < EDITOR_COLUMNS; column++) {
                                if (interface->text_editor[row][column].selected == 1) {
                                    
                                    if (row == EDITOR_ROWS - 1) {
                                        return 2;
                                        break;
                                    }
                                    SDL_SetTextInputRect(&interface->text_editor[row + 1][column].box.rect);
                                    interface->text_editor[row][column].selected = 0;
                                    interface->text_editor[row + 1][column].selected = 1;
                                    return 2;
                                    break;

                                }
                            }
                        }
                    case SDLK_LEFT:   
                            for (int row = 0; row < EDITOR_ROWS; row++) {
                            for (int column = 0; column < EDITOR_COLUMNS; column++) {
                                if (interface->text_editor[row][column].selected == 1) {
                                    
                                    if (column == 0) {
                                     if (row  != 0) {
                                        SDL_SetTextInputRect(&interface->text_editor[row - 1][EDITOR_COLUMNS - 1].box.rect);
                                        interface->text_editor[row][column].selected = 0;
                                        interface->text_editor[row - 1][EDITOR_COLUMNS - 1].selected = 1;
                                        return 2;
                                        }
                                        break;
                                    }
                                    SDL_SetTextInputRect(&interface->text_editor[row][column - 1].box.rect);
                                    interface->text_editor[row][column].selected = 0;
                                    interface->text_editor[row][column - 1].selected = 1;
                                    return 2;
                                    break;

                                }
                            }
                        }
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

//functions to handle the key presses
