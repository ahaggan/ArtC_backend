#include "input.h"

int SDL_Main_Menu_Events(Main_Menu* main_menu) {
    SDL_Event event;
    int x, y;
    SDL_GetMouseState(&x, &y);
    while(SDL_PollEvent(&event)) { 
        //SDL_Window_Events
        switch (event.type) {
             //user requests quit
            case SDL_QUIT:
                main_menu->window.finished = 1;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (within_button(x, y, main_menu->canvas_button.rect)) {
                    printf("Canvas\n");
                    return canvas;
                }
                else if (within_button(x, y, main_menu->challenges_button.rect)) {
                    printf("Challenges\n");
                    return challenges_menu;
                }
                else if (within_button(x, y, main_menu->options_button.rect)) {
                    printf("Options\n");    
                    return options_menu;
                }
                else if (within_button(x, y, main_menu->quit_button.rect)) {
                    printf("Quit\n");
                    return quit;
                }
            break;
        }
    }
    return 0;
}

int SDL_Challenges_Menu_Events(Challenges_Menu* challenges) {
    SDL_Event event;
    int x, y;
    SDL_GetMouseState(&x, &y);
    while(SDL_PollEvent(&event)) { 
        //SDL_Window_Events
        switch (event.type) {
             //user requests quit
            case SDL_QUIT:
                challenges->window.finished = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (within_button(x, y, challenges->beginner.rect)) {
                    printf("Beginner\n");
                    return beginner;
                }
                else if (within_button(x, y, challenges->intermediate.rect)) {
                    printf("Intermediate\n");
                    return intermediate;
                }
                else if (within_button(x, y, challenges->expert.rect)) {
                    printf("Expert\n");
                    return expert;
                }
                else if (within_button(x, y, challenges->main_menu.rect)) {
                    printf("Main Menu\n");
                    return main_menu;
                }
            break;
        }
    }
    return 0;
}

int within_button(int x, int y, SDL_Rect button) {
    if (x >= button.x && x <=  button.x + button.w) {
        if (y >= button.y && y <= button.y + button.h) {
            return 1;
        }
    }
    return 0;
}

int Interface_Events(Interface* interface) {
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
                if (within_button(x, y, interface->generate_button.rect)) {
                     printf("Generate!\n");
                     return generate_clicked;
                    break;
                }

                if (within_button(x, y, interface->reset_button.rect)) {
                     printf("Reset the text!\n");
                     break;
                }
              
                if (within_button(x, y, interface->menu_button.rect)) {
                    printf("Returning to the main menu.\n");
                    return back_to_menu;
                    break;
                }
                    
                if (within_button(x, y, interface->help_button.rect)) {
                    printf("Help is on the way!\n");     
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
            display_interface(interface);
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

int SDL_Text_Editor_Events(SDL_Event event, Interface* interface) {
    Coordinates active = interface->active_txt;

    switch(event.type) {
        //textinput case MUST be before keydown; otherwise 'soh' enters the string.
        case SDL_TEXTINPUT:
           //make a check function: if text_to_be_overwritten { }
            if (!last_cell(active, *interface)) {
                if (strcmp(interface->text_editor[active.row][active.column].character, EMPTY_CELL) != 0) {
                   if (strcmp(interface->text_editor[active.row][active.column].character, " ") != 0) {
                //overwriting irrelevant if bottom_row!
                        handle_overwriting(active, interface, EMPTY_CELL);//handle overwriting
                    }
                }
            }
            strcpy(interface->text_editor[active.row][active.column].character, event.text.text);
            
            if (!last_cell(active, *interface)) {
                SDL_SetTextInputRect(&interface->text_editor[active.row][active.column].next->box.rect);
                set_active_text_cell(interface->text_editor[active.row][active.column].next->text_cell.row, interface->text_editor[active.row][active.column].next->text_cell.column, interface);
                return text_edited;
            }
            return text_edited;
        
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
                    if (last_cell(active, *interface)) {
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
                    if (bottom_row(active, *interface)) {
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
                                SDL_SetTextInputRect(&interface->text_editor[active.row - 1][interface->editor_columns - 1].box.rect);
                                set_active_text_cell(active.row - 1, interface->editor_columns - 1, interface);
                                return text_edited;
                            } 
                            break;
                        }
                        SDL_SetTextInputRect(&interface->text_editor[active.row][active.column - TAB_LENGTH].box.rect);
                        set_active_text_cell(active.row, active.column - TAB_LENGTH, interface);        
                        return text_edited;
                    }
                    
                    else {
                        if (active.column  >= interface->editor_columns - TAB_LENGTH) {
                            if (!bottom_row(active, *interface)) {
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

                    if (end_column(active, *interface)) {
                        if (!bottom_row(active, *interface)) {
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
                    if (bottom_row(active, *interface)) {
                        return text_edited;
                    }
                    SDL_SetTextInputRect(&interface->text_editor[active.row + 1][active.column].box.rect);
                    set_active_text_cell(active.row + 1, active.column, interface);
                    return text_edited;

                case SDLK_LEFT:   

                    if (start_column(active)) {
                        if (!top_row(active)) {
                            SDL_SetTextInputRect(&interface->text_editor[active.row - 1][interface->editor_columns - 1].box.rect);
                            set_active_text_cell(active.row - 1, interface->editor_columns - 1, interface);
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

int bottom_row(Coordinates active, Interface interface) {
    if (active.row == interface.editor_rows - 1) {
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

int end_column(Coordinates active, Interface interface) {
    if (active.column == interface.editor_columns - 1) {
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

int last_cell(Coordinates active, Interface interface) {
    if (bottom_row(active, interface) && end_column(active, interface)){
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

void write_text_to_file(TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS] /* perhaps allow specific file name */) {
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

void load_text_into_text_editor(char* file_name, Interface* interface) {
    FILE* challenge = fopen(file_name, "r");
    int row = 0;
    int column = 0;
    char c;
    TextNode* current = &interface->text_editor[row][column];
    
    while ((c = fgetc(challenge)) != EOF) {
        if (c == '\n') {
            column = 0;
            current = &interface->text_editor[++row][column];
        }
 
        else {
            if (column < interface->editor_columns) {
                strcpy(current->character, &c);
              //  if (current->next == NULL) {
                //    printf("Error: challenge is too big for the text editor.\n");    
                  //  exit(1);
                //}
            }
            else {
                column = 0;
                current = &interface->text_editor[++row][column];
                strcpy(current->character, &c);
            }
        } 
        current = current->next; 
    }
}

//broken when overwriting to the next line! (creates duplicate characters)
void handle_overwriting(Coordinates active, Interface* interface, char overflow[3]) {
    Coordinates over = active;
    TextNode* current = &interface->text_editor[active.row][active.column];
    int col = active.column;
    char curr[3];
    char nxt[3];
     
    if (strcmp(overflow, EMPTY_CELL) != 0) {
        printf("Flowing over to the next line.\n");
        strcpy(nxt, current->next->character);
        strcpy(current->next->character, overflow);
        strcpy(curr, current->next->character);
    }

    else {
        strcpy(curr, current->character);
        strcpy(nxt, current->next->character);
        strcpy(current->next->character, curr);
    }

    current = current->next;

    while (col < interface->editor_columns - 1) {
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
