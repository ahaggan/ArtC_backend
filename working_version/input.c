#include "input.h"

int SDL_Main_Menu_Events(Menu* main_menu) {
    SDL_Event event;
    int x, y;

    SDL_GetMouseState(&x, &y);

    main_menu->hover = 0;
    main_menu_hover(x, y, main_menu);

    while(SDL_PollEvent(&event)) { 
        switch(event.type) {

            case SDL_QUIT:
                main_menu->window.finished = 1;
                return quit;

            // Click; find where clicked and act accordingly
            case SDL_MOUSEBUTTONDOWN:
                return main_menu_click(x, y, main_menu);

        }
    }
    return 0;
}

void main_menu_hover(int x, int y, Menu *main_menu) {
    if(within_button(x, y, main_menu->canvas_button.rect)) {
        main_menu->hover = canvas;
    }
    else if(within_button(x, y, main_menu->challenges_button.rect)) {
        main_menu->hover = challenges_menu;
    }
    else {
        main_menu->hover = 0;
    }
}

int main_menu_click(int x, int y, Menu *main_menu) {
    if(within_button(x, y, main_menu->canvas_button.rect)) {
        return canvas;
    }
    else if(within_button(x,y, main_menu->challenges_button.rect)) {
        return challenges_menu;
    }
    else if(within_button(x, y, main_menu->menu_help_button.rect)) {
        return options_menu;
    }
    else if(within_button(x, y, main_menu->quit_button.rect)) {
        return quit;
    }
    return 0;
}

int SDL_Challenges_Menu_Events(Menu* challenges) {
    SDL_Event event;
    int x, y;

    SDL_GetMouseState(&x, &y);

    challenges->hover = 0;
    challenges_menu_hover(x, y, challenges);

    while(SDL_PollEvent(&event)) { 
        switch(event.type) {

            case SDL_QUIT:
                challenges->window.finished = 1;
                return quit;

            // Click; find where clicked and act accordingly
            case SDL_MOUSEBUTTONDOWN:
                return challenges_menu_click(x, y, challenges);

        }
    }
    return 0;
}

void challenges_menu_hover(int x, int y, Menu *challenges) {
    if(within_button(x, y, challenges->beginner.rect)) {
        challenges->hover = beginner;
    }
    else if(within_button(x, y, challenges->intermediate.rect)) {
        challenges->hover = intermediate;
    }
    else if(within_button(x, y, challenges->expert.rect)) {
        challenges->hover = expert;
    }
    else {
        challenges->hover = 0;
    }
}

int challenges_menu_click(int x, int y, Menu *challenges) {
    if(within_button(x, y, challenges->beginner.rect)) {
        return beginner;
    }
    else if(within_button(x, y, challenges->intermediate.rect)) {
        return intermediate;
    }
    else if(within_button(x, y, challenges->expert.rect)) {
        return expert;
    }
    else if(within_button(x, y, challenges->main_menu.rect)) {
        return main_menu;
    }
    return 0;
}

int SDL_Help_Menu_Events(Menu* help) {
    SDL_Event event;
    int x, y;

    SDL_GetMouseState(&x, &y);

    while(SDL_PollEvent(&event)) { 
        switch(event.type) {

            case SDL_QUIT:
                help->window.finished = 1;
                return quit;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(within_button(x, y, help->back_button.rect)) {
                    return back;
                }
                break;

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
        switch(event.type) {

            case SDL_QUIT:
                SDL_Quit();
                exit(1);
                break;

            case SDL_MOUSEBUTTONDOWN: 
                return interface_click(x, y, interface); 

        }
    }
    return 0;
}

int interface_click(int x, int y, Interface *interface) {              
    if (within_button(x, y, interface->generate_button.rect)) {
        if (interface->mode  == challenge_mode) {
            clear_area(&interface->window, interface->canvas);
        }
        return generate_clicked;
    }

    else if (within_button(x, y, interface->reset_button.rect)) {
        if (interface->mode == challenge_mode) { 
            if (interface->challenge_num == 0) {
                load_text_into_text_editor(interface->default_file, interface);
            }
            else {
                load_text_into_text_editor(interface->code_file, interface);
            }
        }
        clear_area(&interface->window, interface->canvas);
        return 0;
    }

    else if (within_button(x, y, interface->menu_button.rect)) {
        return back_to_menu;
    }

    else if (within_button(x, y, interface->help_button.rect)) {
        return load_help;
    }

    else if (within_button(x, y, interface->next_button.rect)) {
        if (interface->challenge_num < LEVEL_NUM - 1) {
            interface->challenge_num++;
           
            return load_challenge;
        }
    }

    else if (within_button(x, y, interface->previous_button.rect)) {
        if (interface->challenge_num > 0) {
            interface->challenge_num--;
            
            return load_challenge;
        }
    }

    else if (within_button(x, y, interface->canvas.rect)) {
        interface->click_location.row = x;
        interface->click_location.column = y;
        return change_position;
    }

    return 0;
}

int SDL_Text_Editor_Events(SDL_Event event, Interface* interface) {
    Coordinates active = interface->active_txt;
    int x, y;

    SDL_GetMouseState(&x, &y); 
 
    switch(event.type) {

        case SDL_MOUSEMOTION:     
            Text_Editor_mouse_motion(interface, x, y);       
            break;

        case SDL_MOUSEBUTTONDOWN:  
            mouse_move_to_cell(interface, x, y);
            return text_edited;

        //textinput case MUST be before keydown; otherwise 'soh' enters the string.
        case SDL_TEXTINPUT:
            Text_Editor_text_input(interface, event.text.text, x, y, active);
            return text_edited;

        //user presses a key
        case SDL_KEYDOWN:
            Text_Editor_keydown(interface, event.key.keysym.sym, 
                                    x, y, active);
            return text_edited;

    }
    return 0;
}

void Text_Editor_mouse_motion(Interface *interface, int x, int y) {
    SDL_Cursor *cursor;
    if(inside_text_editor(interface, x, y)) {
        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
    }
    else {
        cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    }
    SDL_SetCursor(cursor);
}

int within_button(int x, int y, SDL_Rect button) {
    if(x>=button.x && x<=button.x+button.w
      && y>=button.y && y<=button.y+button.h) {
        return 1;
    }
    return 0;
}

int inside_cell(TextNode current, int mouse_x, int mouse_y) {
    if(mouse_x >= current.box.rect.x && 
         mouse_x <= current.box.rect.x + current.box.rect.w &&
           mouse_y >= current.box.rect.y && 
             mouse_y <= current.box.rect.y + current.box.rect.h) {
        return 1;
    }
    return 0;
}

int inside_text_editor(Interface* interface, int mouse_x, int mouse_y) {
    if(mouse_x >= interface->text_editor_panel.rect.x && 
         mouse_x <= interface->text_editor_panel.rect.x + 
                      interface->text_editor_panel.rect.w && 
           mouse_y >= interface->text_editor_panel.rect.y && 
             mouse_y <= interface->text_editor_panel.rect.y + 
                          interface->text_editor_panel.rect.h) {
        return 1;
    }
    return 0;
}
