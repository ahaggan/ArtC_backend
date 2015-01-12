#include "input.h"

int SDL_Main_Menu_Events(Menu* main_menu) {
    SDL_Event event;
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    while(SDL_PollEvent(&event)) { 
        
        switch (event.type) {
             //user requests quit
            case SDL_QUIT:
                main_menu->window.finished = 1;
                return quit;
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
                else if (within_button(x, y, main_menu->menu_help_button.rect)) {
                    printf("Help\n");    
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

int SDL_Challenges_Menu_Events(Menu* challenges) {
    SDL_Event event;
    int x, y;
    SDL_GetMouseState(&x, &y);
    while(SDL_PollEvent(&event)) { 
        switch (event.type) {
             //user requests quit
            case SDL_QUIT:
                challenges->window.finished = 1;
                return quit;
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
          
        SDL_Text_Editor_Events(event, interface);   
       
 
        switch (event.type) {
            case SDL_QUIT:
                SDL_Quit();
                exit(1);
                break;

            //user clicks somewhere
            case SDL_MOUSEBUTTONDOWN:                
                if (within_button(x, y, interface->generate_button.rect)) {
                     printf("Generate!\n");
                     return generate_clicked;
                    break;
                }

                if (within_button(x, y, interface->reset_button.rect)) {
                     if (interface->mode == challenge_mode) {
                        load_text_into_text_editor(interface->challenge, interface);
                     }
                     else {
                        ;
                    }
                    
                     
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

                if (within_button(x, y, interface->canvas.rect)) {
                    printf("New fractal position.\n");
                    interface->click_location.row = x;
                    interface->click_location.column = y;
                    return change_position;
                }
        }
    }
    return 0;
}

int SDL_Text_Editor_Events(SDL_Event event, Interface* interface) {
    Coordinates active = interface->active_txt;
    int x, y;
    SDL_GetMouseState(&x, &y);  
    SDL_Cursor* cursor;
    switch(event.type) {
        case SDL_MOUSEMOTION:
            

            if (inside_text_editor(interface, x, y)) {
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
                SDL_SetCursor(cursor);
               
            }
            else {
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                SDL_SetCursor(cursor);
            }
            
        break;

         case SDL_MOUSEBUTTONDOWN:  
            mouse_move_to_cell(interface, x, y);
            console_text_editor(*interface);
            return text_edited;
        break;

        //textinput case MUST be before keydown; otherwise 'soh' enters the string.
        case SDL_TEXTINPUT:
          
            if (!last_cell(active, *interface)) {
                if (strcmp(interface->text_editor[active.row][active.column].character, EMPTY_CELL) != 0) {
                    handle_overwriting(active, interface, EMPTY_CELL);//handle overwriting
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

                case SDLK_BACKSPACE:
                    /* Broken if backspacing on the 'first' cell when the text editor is empty */
                    if (first_cell(active)) {
                      
                        break;
                    }
                    else if (last_cell(active, *interface)) {
                      
                        strcpy(interface->text_editor[active.row][active.column].character, EMPTY_CELL); 
                        strcpy(interface->text_editor[active.row][active.column].previous->character, EMPTY_CELL);
                    }
                    else if (strcmp(interface->text_editor[active.row][active.column].previous->character, EMPTY_CELL) != 0) {
                        //If there's something in the previous cell          
                        strcpy(interface->text_editor[active.row][active.column].previous->character, EMPTY_CELL);
                        SDL_SetTextInputRect(&interface->text_editor[active.row][active.column].previous->box.rect);
                        set_active_text_cell(interface->text_editor[active.row][active.column].previous->text_cell.row, interface->text_editor[active.row][active.column].previous->text_cell.column, interface);
                        handle_backwriting(active, interface);
                    } 
                    else {
                        //If there's nothing in the previous cell
                        handle_backwriting(active, interface);   
                       
                    }
                    console_text_editor(*interface);
                    return text_edited;
                    break;
                
                //return takes you to the next line
                case SDLK_RETURN:          
                    if (bottom_row(active, *interface)) {
                        break;
                    }
                    handle_enter_shuffling(active, interface);
                    //move the cursor to the next line
                    SDL_SetTextInputRect(&interface->text_editor[active.row + 1][0].box.rect);
                    set_active_text_cell(active.row + 1, 0, interface);
                                        console_text_editor(*interface);

                    return text_edited;

                //tab moves you forward a number of spaces
                case SDLK_TAB:
                    if (SDL_GetModState() & KMOD_SHIFT) {
                        
                        if (active.column <= 2) {
                            ;
                            console_text_editor(*interface);
                            break;
                        }
                        else {
                            tab(active, interface, 0);
                            SDL_SetTextInputRect(&interface->text_editor[active.row][active.column - TAB_LENGTH].box.rect);
                            set_active_text_cell(active.row, active.column - TAB_LENGTH, interface);   
                        }     
                        console_text_editor(*interface);
                        return text_edited;
                    }
                    
                    else {
                        if (active.column  >= interface->editor_columns - TAB_LENGTH) {
                            if (!bottom_row(active, *interface)) {
                                ;   
                            }
                            console_text_editor(*interface);
                            break;
                        }
                        else {
                            tab(active, interface, 1);
                            SDL_SetTextInputRect(&interface->text_editor[active.row][active.column + TAB_LENGTH].box.rect);
                            set_active_text_cell(active.row, active.column + TAB_LENGTH, interface);
                        }
                        console_text_editor(*interface);
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
                    if (last_cell(active, *interface) || bottom_row(active, *interface)) {
                        break;
                    }       
                    else if (strcmp(interface->text_editor[active.row][active.column].character, EMPTY_CELL) != 0) {
                        if (end_column(active, *interface)) {
                            SDL_SetTextInputRect(&interface->text_editor[active.row + 1][0].box.rect); 
                            set_active_text_cell(active.row + 1, 0, interface);
                        }
                        else {
                            SDL_SetTextInputRect(&interface->text_editor[active.row][active.column + 1].box.rect); 
                            set_active_text_cell(active.row, active.column + 1, interface);
                        }
                    }
                    else {
                        find_next_active_node(&active, interface);
                        SDL_SetTextInputRect(&interface->text_editor[active.row][active.column].box.rect);
                        set_active_text_cell(active.row, active.column, interface);
                    }
                    return text_edited;
                    break;
        
                case SDLK_DOWN:   
                    if (bottom_row(active, *interface)) {
                        break;
                    }  
                    else if (final_active_node(active, *interface)) {
                        break;
                    }   
                    else {
                        SDL_SetTextInputRect(&interface->text_editor[active.row + 1][active.column].box.rect);
                        set_active_text_cell(active.row + 1, active.column, interface);
                        return text_edited;
                    }
                    break;

                case SDLK_LEFT:   
                    if (first_cell(active)) {
                        break;
                    }
                                        
                    if (strcmp(interface->text_editor[active.row][active.column].previous->character, EMPTY_CELL) != 0) {
     
                        if (start_column(active)) {
                            SDL_SetTextInputRect(&interface->text_editor[active.row - 1][interface->editor_columns-1].box.rect); 
                            set_active_text_cell(active.row - 1, interface->editor_columns-1, interface);
                        }
                        else {
                            SDL_SetTextInputRect(&interface->text_editor[active.row][active.column - 1].box.rect); 
                            set_active_text_cell(active.row, active.column - 1, interface);
                        }
                    }
                    else {
                        find_previous_active_node(&active, interface);
                        SDL_SetTextInputRect(&interface->text_editor[active.row][active.column].box.rect);
                        set_active_text_cell(active.row, active.column, interface);
                    }
                    return text_edited;
                    break;

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

void mouse_move_to_cell(Interface* interface, int mouse_x, int mouse_y) {
    for (int row = 0; row < interface->editor_rows; row++) {
        for (int column = 0; column < interface->editor_columns; column++) {
            if (inside_cell(interface->text_editor[row][column], mouse_x, mouse_y)) {
                 //click on a cell with text within? take you directly to that cell
                if (strcmp(interface->text_editor[row][column].character, EMPTY_CELL) != 0) {
                
                    SDL_SetTextInputRect(&interface->text_editor[row][column - TAB_LENGTH].box.rect);
                    set_active_text_cell(row, column, interface);  
                }
                //click on a line? take to prev live cell on that row
                else {
                    find_previous_cell_on_row(&interface->text_editor[row][column], interface);
                }
            }
           
        }
    }
}

void find_previous_cell_on_row(TextNode* current, Interface* interface) {
   
   while (current->text_cell.column != 0 && strcmp(current->previous->character, EMPTY_CELL) == 0) {
        current = current->previous;  
    }

    SDL_SetTextInputRect(&interface->text_editor[current->text_cell.row][current->text_cell.column].box.rect);
    set_active_text_cell(current->text_cell.row, current->text_cell.column, interface);  
}

int inside_cell(TextNode current, int mouse_x, int mouse_y) {
    if (mouse_x >= current.box.rect.x && mouse_x <= current.box.rect.x + current.box.rect.w) {
        if (mouse_y >= current.box.rect.y && mouse_y <= current.box.rect.y + current.box.rect.h) {
            return 1;
        }
    }
    return 0;
}

int inside_text_editor(Interface* interface, int mouse_x, int mouse_y) {
    if (mouse_x >= interface->text_editor_panel.rect.x && mouse_x <= interface->text_editor_panel.rect.x + interface->text_editor_panel.rect.w) {
        if (mouse_y >= interface->text_editor_panel.rect.y && mouse_y <= interface->text_editor_panel.rect.y + interface->text_editor_panel.rect.h) {
            return 1;
        }
    }
    return 0;
}

void console_text_editor(Interface interface) {
  printf("Text Editor\n");
  int row, col;
  row = col = 0;
  for (row = 0; row <= interface.editor_rows; row++) {
        printf("%d: ", row);
        for (col = 0; col < interface.editor_columns; col++) {
            
            printf("%s", interface.text_editor[row][col].character);
        }
        printf("\n");
    }
    printf("\n");
}
