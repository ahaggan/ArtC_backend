#include "input.h"

int SDL_Events(Interface* interface) {
    SDL_Event event;

    int x, y;

    SDL_GetMouseState(&x, &y);

    while(SDL_PollEvent(&event)) { 
        
        //need a way of breaking out of these so that not all events are checked
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
    int win_width, win_height;
    switch(event.window.event) {
        //Get new dimensions and repaint on window size change.
        case SDL_WINDOWEVENT_SIZE_CHANGED: 
            SDL_GetWindowSize(interface->window.win, &win_width, &win_height);
            // Set resolution (size) of renderer to the same as window
            SDL_RenderSetLogicalSize(interface->window.renderer, win_width, win_height); 
            draw_interface(interface);
            SDL_RenderPresent(interface->window.renderer);
            break;
        //exposed means that the window was obscured in some way, and now is not obscured.
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(interface->window.renderer);
            break;
    }    
}


//return text_edited isn't doing anything at the moment because this is nested
//set a flag or something!!!

//perhaps pass smarter arguments to this: having to interface-> all the time wastes space 
//and isn't readable
int SDL_Text_Editor_Events(SDL_Event event, Interface* interface) {
    Coordinates active = interface->active_txt;
    Coordinates active_next = interface->text_editor[active.row][active.column].next->text_cell;
    Coordinates active_prev = interface->text_editor[active.row][active.column].previous->text_cell;

    switch(event.type) {
        //textinput case MUST be before keydown; otherwise 'soh' enters the string.
        case SDL_TEXTINPUT:
            //condition too long--make a function
            if (strcmp(interface->text_editor[active.row][active.column].character, EMPTY_CELL) != 0) {
                //then move all the text on the row along one!
            }

            strcpy(interface->text_editor[active.row][active.column].character, event.text.text);

            if (!last_cell(active)) {
                SDL_SetTextInputRect(&interface->text_editor[active.row][active.column].next->box.rect);
                set_active_text_cell(active_next.row, active_next.column, interface);
                return text_edited;
            }
        break;

        //user presses a key
        case SDL_KEYDOWN:
            //based on the key pressed...
            switch (event.key.keysym.sym) {

                //backspace deletes the previous character
                case SDLK_BACKSPACE:
                    if (first_cell(active)) {
                        break;
                    }

                    //quick and dirty fix for the final space on the grid
                    if (last_cell(active)) {
                        strcpy(interface->text_editor[active.row][active.column].character, EMPTY_CELL); 
                        strcpy(interface->text_editor[active.row][active.column].previous->character, EMPTY_CELL);
                    }
                    else {
                        strcpy(interface->text_editor[active.row][active.column].previous->character, EMPTY_CELL);
                    }
                    
                    SDL_SetTextInputRect(&interface->text_editor[active.row][active.column].previous->box.rect);
                    set_active_text_cell(active_prev.row, active_prev.column, interface);
                    return text_edited;
                
                //return takes you to the next line
                case SDLK_RETURN:          
                    if (bottom_row(active)) {
                        break;
                    }
                    //move the cursor to the next line
                    SDL_SetTextInputRect(&interface->text_editor[active.row + 1][0].box.rect);
                    set_active_text_cell(active.row + 1, 0, interface);
                    return text_edited;

                //tab moves you forward a number of spaces
                case SDLK_TAB:
                    if (SDL_GetModState() & KMOD_SHIFT) {
                        if (active.column <= 2) {
                            if (!top_row(active)) {
                                SDL_SetTextInputRect(&interface->text_editor[active.row - 1][EDITOR_COLUMNS - 1].box.rect);
                                set_active_text_cell(active.row - 1, EDITOR_COLUMNS - 1, interface);
                                return text_edited;
                            } 
                            break;
                        }
                        SDL_SetTextInputRect(&interface->text_editor[active.row][active.column - TAB_LENGTH].box.rect);
                        set_active_text_cell(active.row - 1, active.column - TAB_LENGTH, interface);        
                        return text_edited;
                    }
                    
                    else {
                        if (active.column  >= EDITOR_COLUMNS - TAB_LENGTH) {
                            if (!bottom_row(active)) {
                                SDL_SetTextInputRect(&interface->text_editor[active.row + 1][0].box.rect);
                                set_active_text_cell(active.row + 1, 0, interface);
                                return text_edited;
                            }
                            break;
                        }
                        SDL_SetTextInputRect(&interface->text_editor[active.row][active.column + TAB_LENGTH].box.rect);
                        set_active_text_cell(active.row, active.column + TAB_LENGTH, interface);
                        return text_edited;
                    }

                case SDLK_UP:   
                    if (top_row(active)) {
                        break;
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row - 1][active.column].box.rect);
                    set_active_text_cell(active.row - 1, active.column, interface);
                    return text_edited;

                case SDLK_RIGHT:   

                    if (end_column(active)) {
                        if (!bottom_row(active)) {
                            SDL_SetTextInputRect(&interface->text_editor[active.row + 1][0].box.rect);
                            set_active_text_cell(active.row + 1, 0, interface);
                            return text_edited;
                        }
                        break;     
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row][active.column + 1].box.rect); 
                    set_active_text_cell(active.row, active.column + 1, interface);

                case SDLK_DOWN:   
                    if (bottom_row(active)) {
                        return text_edited;
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row + 1][active.column].box.rect);
                    set_active_text_cell(active.row + 1, active.column, interface);
                    return text_edited;

                case SDLK_LEFT:   

                    if (start_column(active)) {
                        if (!top_row(active)) {
                            SDL_SetTextInputRect(&interface->text_editor[active.row - 1][EDITOR_COLUMNS - 1].box.rect);
                            set_active_text_cell(active.row - 1, EDITOR_COLUMNS - 1, interface);
                            return text_edited;
                        }
                        break;
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row ][active.column - 1].box.rect);
                    set_active_text_cell(active.row, active.column - 1, interface);
                    return text_edited;

                //ctrl + c copies text to the clipboard
                case SDLK_c:
                    if (SDL_GetModState() & KMOD_CTRL) {
                        //this will only work if you have highlight functionality
                    }
                break;

                //ctrl + v copies text to the clipboard
                case SDLK_v:
                    if (SDL_GetModState() & KMOD_CTRL) {
                       //this will only work if you have highlight functionality
                    }
                break;
            }   
    }
    return 0;
}

int top_row(Coordinates active) {
    if (active.row == 0) {
        return 1;
    }
    return 0;
}

int bottom_row(Coordinates active) {
    if (active.row == EDITOR_ROWS - 1) {
        return 1;
    }
    return 0;
}

int start_column(Coordinates active) {
    if (active.column == 0) {
        return 1;
    }
    return 0;
}

int end_column(Coordinates active) {
    if (active.column == EDITOR_ROWS - 1) {
        return 1;
    }
    return 0;
}

int first_cell(Coordinates active) {
    if (top_row(active) && start_column(active)) {
        return 1;
    }
    return 0;
}

int last_cell(Coordinates active) {
    if (bottom_row(active) && end_column(active)){
        return 1;
    }
    return 0;
}


void set_active_text_cell(int row, int column, Interface* interface) {
    interface->active_txt.row = row;
    interface->active_txt.column = column;
}
