#include "menu.h"

/* Main Menu */
void launch_menu() {
    Menu menu;

    initialise_main_menu(&menu);

    do {
        if(menu.hover_change) {
            display_popup_text(&menu);
            menu.hover_change = 0;
            render_update(menu.window);
        }

        menu.state = Main_Menu_Events(&menu);
        main_menu_actions(&menu);

        //SDL shut_down, TTF shut down, free memory)
      } while(!menu.window.finished);
  
    atexit(SDL_Quit);
}

void initialise_main_menu(Menu* main_menu) {
    main_menu->state = 0;
    main_menu->hover = 0;
    main_menu->hover_change = 1;

    initialise_SDL(main_menu);
    main_menu->menu_font = SDL_Load_Font("display/font/Edo.ttf", 
                                           BUTTON_FONT_SIZE);

    display_main_menu(main_menu);
}

/* Act based on whether any buttons in the main menu were pressed */ 
void main_menu_actions(Menu* main_menu) {
    switch (main_menu->state) {
        case canvas: 
            interface(main_menu, canvas_mode, "program_txt_files/canvas.txt"); 
            display_main_menu(main_menu); 
            render_update(main_menu->window);
            break;
        case challenges_menu_choice:
            challenges_menu(main_menu);
            display_main_menu(main_menu); 
            render_update(main_menu->window);
            break;
        case help_screen_choice:
            help_screen(main_menu);
            display_main_menu(main_menu);
            render_update(main_menu->window);
            break;
        case quit:
            main_menu->window.finished = 1;
            break;
        default: 
            return;
    }
}

void challenges_menu(Menu* challenges) {
    initialise_challenges_menu(challenges);
    while(challenges->state != main_menu) {
        if(challenges->hover_change) {
            display_popup_text(challenges);
            render_update(challenges->window);
        }
        challenges->state = Challenges_Menu_Events(challenges);
        challenges_menu_actions(challenges);
    }
}

void initialise_challenges_menu(Menu* challenges) {
    challenges->state = 0;
    challenges->hover = 0;
    challenges->hover_change = 1;
    display_challenges_menu(challenges);
}

void challenges_menu_actions(Menu* challenges) {
    switch (challenges->state) {
        case beginner: 
            interface(challenges, challenge_mode, BEGINNER);
            break;
        case intermediate:
            interface(challenges, challenge_mode, INTERMEDIATE);
            break;
        case expert:
            interface(challenges, challenge_mode, EXPERT);
            break;
        case main_menu:
            challenges->state = main_menu;
            break;
        default: 
            return;
    }
}

void help_screen(Menu* help) {
    display_help_screen(help);
    render_update(help->window);
    while(help->state != main_menu) {
        help->state = Help_Screen_Events(help);
        if(help->state == back) {
            help->state = main_menu;
        }
    }
}
