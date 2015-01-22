#include "interface.h"

void interface(Menu* main_menu, Mode mode, char* file_name) {
    Interface interface;

    strcpy(interface.default_file, file_name);
    set_code_file(&interface, mode, file_name);

    initialise_interface(main_menu, &interface, mode);
    interface.click_location.row = interface.canvas.rect.x + 
                                      (interface.canvas.rect.w/2);
    interface.click_location.column = interface.canvas.rect.y + 
                                      ((3*interface.canvas.rect.h)/4);

    initialise_text_editor(&interface, mode, file_name);
    render_update(interface.window);

    while(interface.action != back_to_menu) {
        display_interface(&interface, mode, 0); 
        update_text_editor(interface.editor_columns, interface.editor_rows, 
                               &interface);
        interface.action = Interface_Events(&interface);
    
        if(interface.action == generate_clicked) {
            write_text_to_file(&interface, interface.code_file);
            Draw fractal; 
            parser(&fractal, "program_txt_files/default.txt"); //Assign defaults
            fractal.startx = interface.click_location.row;
            fractal.starty = interface.click_location.column;

            if(parser(&fractal, interface.code_file) == TRUE) {
                generating(&fractal, &interface);
            }
            else {
                display_error_message(&interface);
            }
        }
        else if (interface.action == load_help) {
            main_menu->state = help_screen_choice;
            help_screen(main_menu);
            clear_area(&interface.window, interface.canvas);
        }

        render_update(interface.window);
    }

    if (mode == challenge_mode) { // Wipes the file.
        FILE* challenge = fopen(interface.code_file, "w");
        fclose(challenge);
    }
}

void generating(Draw *fractal, Interface *interface) {
    clock_t start_time, end_time; 

    for(int i = 1; i <= fractal->iterations; i++) {
        start_time = end_time = clock();
    
        generate_fractal(fractal, &interface->window, i);
    
        while(((double)end_time - (double)start_time)/
                 (double)CLOCKS_PER_SEC < 0.15) {
            Interface_Events(interface); 
            update_text_editor(interface->editor_columns, 
                                 interface->editor_rows, interface);
            SDL_RenderPresent(interface->window.renderer);
            end_time = clock();
        }
    } 
}

void initialise_interface(Menu* main_menu, Interface* interface, Mode mode) {

    interface->action = 0;
    interface->window = main_menu->window;
    interface->text_ed_font = SDL_Load_Font("display/font/DroidSansMono.ttf", 
                                              FONT_SIZE);
    interface->button_font = main_menu->menu_font;
    interface->challenge_font = SDL_Load_Font("display/font/DroidSansMono.ttf", 
                                              CHALLENGE_FONT_SIZE);
    interface->mode = mode;
    interface->challenge_num = 0;
    SDL_RenderClear(main_menu->window.renderer);
    display_interface(interface, mode, 1);
}

void set_code_file(Interface *interface, Mode mode, char* file_name) {
    if (mode == challenge_mode) { 
       set_challenges_based_on_level(file_name, interface); 
    }
    else {
       strcpy(interface->code_file, "program_txt_files/canvas.txt");
    }
}

void set_challenges_based_on_level(char* file_name, Interface* interface) {
    if(strcmp(file_name, BEGINNER) == 0) {
        beginner_challenges(interface);
    }
    else if(strcmp(file_name, INTERMEDIATE) == 0) {
        intermediate_challenges(interface);
    }
    else if(strcmp(file_name, EXPERT) == 0) {
        expert_challenges(interface);
    }
}

void beginner_challenges(Interface *interface) {
    strcpy(interface->code_file, 
             "program_txt_files/challenges/beginner_user_code.txt");
    strcpy(interface->challenges[0], "Change the colour variable");  
    strcpy(interface->challenges[1], "Change the shape variable to circle");
    strcpy(interface->challenges[2], "Change the type variable to star");
    strcpy(interface->challenges[3], "Level Complete!");
}

void intermediate_challenges(Interface *interface) {
    strcpy(interface->code_file, 
             "program_txt_files/challenges/intermediate_user_code.txt");
    strcpy(interface->challenges[0], 
             "Add the missing RUN statement and brackets");  
    strcpy(interface->challenges[1], 
             "Write an IF statement that changes the colour variable");
    strcpy(interface->challenges[2], 
             "Change the size variable to a number below 500");
    strcpy(interface->challenges[3], "Level Complete!");
}
void expert_challenges(Interface *interface) {
    strcpy(interface->code_file, 
             "program_txt_files/challenges/expert_user_code.txt");
    strcpy(interface->challenges[0], 
             "Create a tree fractal from scratch, and use two IF statements");  
    strcpy(interface->challenges[1], 
             "Replace one of the IF statements with a FOR loop");
    strcpy(interface->challenges[2], 
             "Alter the linethickness to 5 within the FOR loop");
    strcpy(interface->challenges[3], "Level Complete!");
}
