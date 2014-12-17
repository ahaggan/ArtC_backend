#include "input.h"

///


int SDL_Events(Interface* interface) {
    SDL_Event event;
    
    int x, y;

    SDL_GetMouseState(&x, &y);
  
    
    while(SDL_PollEvent(&event)) { 
          
        //need a way of breaking out of these so that not all events are checked
        SDL_Window_Events(event, interface);
   
        SDL_Text_Editor_Events(event, interface);   
        
 
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
                if(x >= interface->generate_button.rect.x && x <= interface->generate_button.rect.x + interface->generate_button.rect.w &&
                     y >= interface->generate_button.rect.y && y <= interface->generate_button.rect.y + interface->generate_button.rect.h) {
                     printf("Generate!\n");
                     return generate_clicked;
                    break;
                }

                if(x >= interface->reset_button.rect.x && x <= interface->reset_button.rect.x + interface->reset_button.rect.w &&
                     y >= interface->reset_button.rect.y && y <= interface->reset_button.rect.y + interface->reset_button.rect.h) {
                     printf("Reset the text!\n");
                     break;
                }

                //user clicks on menubar (should be specific challenge button)                
                if (x >= interface->menu_button.rect.x && x <= interface->menu_button.rect.x + interface->menu_button.rect.w &&
                   y >= interface->menu_button.rect.y && y <= interface->menu_button.rect.y + interface->menu_button.rect.h) {
                    printf("Returning to the main menu.\n\n");
                    break;
                }
               
                
                  //user clicks on menubar (should be specific challenge button)      
                printf("%d-%d %d-%d\n", interface->help_button.rect.x, interface->help_button.rect.w,  interface->help_button.rect.y, interface->help_button.rect.h);         
                if (x >= interface->help_button.rect.x && x <= interface->help_button.rect.x + interface->help_button.rect.w &&
                   y >= interface->help_button.rect.y && y <= interface->help_button.rect.y + interface->help_button.rect.h) {
                    printf("Help is on the way!   \n\n");     
                    break;
                }
              
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
            SDL_GetWindowSize(interface->window.win, &interface->editor_columns , &interface->editor_rows);
            interface->editor_columns /= 24;
            interface->editor_rows /= 29.5;
            
             make_text_editor(interface->editor_columns, interface->editor_rows, interface);
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

//also make functions for each  key: otherwise the switch looks ridiculously messy
int SDL_Text_Editor_Events(SDL_Event event, Interface* interface) {
    Coordinates active = interface->active_txt;

    switch(event.type) {
        //textinput case MUST be before keydown; otherwise 'soh' enters the string.
        case SDL_TEXTINPUT:
           //make a check function: if text_to_be_overwritten { }
            if (strcmp(interface->text_editor[active.row][active.column].character, EMPTY_CELL) != 0) {
               if (strcmp(interface->text_editor[active.row][active.column].character, " ") != 0) {
            //overwriting irrelevant if bottom_row!
                    handle_overwriting(active, interface, EMPTY_CELL);//handle overwriting
                }
            }
            
            strcpy(interface->text_editor[active.row][active.column].character, event.text.text);
            
            if (!last_cell(active)) {
                SDL_SetTextInputRect(&interface->text_editor[active.row][active.column].next->box.rect);
                set_active_text_cell(interface->text_editor[active.row][active.column].next->text_cell.row, interface->text_editor[active.row][active.column].next->text_cell.column, interface);
                return text_edited;
            }
        
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
                        strcpy(interface->text_editor[active.row][active.column].character, " "); 
                        strcpy(interface->text_editor[active.row][active.column].previous->character, " ");
                    }
                    else {
                        strcpy(interface->text_editor[active.row][active.column].previous->character, " ");
                    }
                    
                    SDL_SetTextInputRect(&interface->text_editor[active.row][active.column].previous->box.rect);
                    set_active_text_cell(interface->text_editor[active.row][active.column].previous->text_cell.row, interface->text_editor[active.row][active.column].previous->text_cell.column, interface);
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
                        set_active_text_cell(active.row, active.column - TAB_LENGTH, interface);        
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
                    return text_edited;

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
    if (active.column == EDITOR_COLUMNS - 1) {
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

FILE* open_file(char *file_name) {
    FILE *input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        printf("File does not exist.\n");
        make_file(file_name);
    }
    return input_file;
} 

FILE* make_file(char *file_name) {
    FILE* new_file = fopen(file_name, "w");
    if (new_file != NULL) {
        printf("New file created!\n");
    }  
    else {
        printf("Error: unable to create file!");
        exit(1);
    }
    return new_file;
}

void write_text_to_file(TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS]) {
    FILE* user_code = fopen("user_code.artc", "w");
    TextNode* current = &text_editor[0][0];
    while (current->next != NULL) {
        if (strcmp(current->character, EMPTY_CELL) != 0) {
            fputs(current->character, user_code);
        }
        current = current->next;
    }
    fclose(user_code);
}

//broken when overwriting over a new line!
void handle_overwriting(Coordinates active, Interface* interface, char overflow[3]) {
    Coordinates over = active;
    TextNode* current = &interface->text_editor[active.row][active.column];
    int col = active.column;
    char curr[3];
    char nxt[3];
     
    if (strcmp(overflow, EMPTY_CELL) != 0) {
        strcpy(nxt, current->next->character);
        strcpy(current->next->character, overflow);
        strcpy(curr, overflow);
    
    }
    else {
        strcpy(curr, current->character);
        strcpy(nxt, current->next->character);
        strcpy(current->next->character, curr);
    }
    current = current->next;
    while (col < EDITOR_COLUMNS - 1) {
        col++; 
        current = current->next;
        strcpy(curr, nxt);
        strcpy(nxt, current->character);
        strcpy(current->character, curr);
    }
    
    over.row = active.row + 1;
    over.column = 0;

    printf("%s\n", interface->text_editor[over.row][0].character);
    
    if (strcmp(interface->text_editor[over.row][0].character, EMPTY_CELL) != 0) {
        handle_overwriting(over, interface, nxt);
    }
}
