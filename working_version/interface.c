#include "interface.h"

int interface(Menu* main, Mode mode, char* file_name) {
   SDL_RenderClear(main->window.renderer);
   Interface interface;
   clock_t start_time, end_time; 

  strcpy(interface.default_file, file_name);
  if (mode == challenge_mode) { 
      set_challenges_based_on_level(file_name, &interface); 
  }
  else {
    strcpy(interface.code_file, "canvas.txt");
  }

   initialise_interface(main, &interface, mode);
  
   initialise_text_editor(&interface, mode, file_name);
    
    

   render_update_clear(interface.window);

   while (interface.action != back_to_menu) {
      fix_mac_flickering(&interface, mode); 
      update_text_editor(interface.editor_columns, interface.editor_rows, &interface);
      interface.action = Interface_Events(&interface);
    
      if (interface.action == generate_clicked) {
         // COMMENT FUNCTION OUT IN ORDER TO USE FILE READY WRITTEN
         write_text_to_file(&interface, interface.code_file);
        
         /* START: only here due to parser update */
            Draw fractal; 
            //Sets default values to avoid missing values if the user only inputs a few things.(Small red square)
            parser(&fractal, "default.txt"); 
            fractal.startx = interface.click_location.row;
            fractal.starty = interface.click_location.column;

            fractal.endx = WIN_WIDTH/2 + 10; //How could we put this into the parser? Could we limit the values the user can enter(Make 0,0 the coordinates of the top left of the canvas?
            fractal.endy = WIN_HEIGHT/2 + 10; 
            
         /* END */
        // This needs to be an if statement? Parser will return True or False.
         if (parser(&fractal, interface.code_file) == TRUE){
        
             for (int i = 1; i <= fractal.iterations; i++) {
                start_time = end_time = clock();
                
                generate_fractal(&fractal, interface, i);
                
                while(((double)end_time - (double)start_time)/(double)CLOCKS_PER_SEC < 0.15) {
                   Interface_Events(&interface); 
                   update_text_editor(interface.editor_columns, interface.editor_rows, &interface);
                   SDL_RenderPresent(interface.window.renderer);
                   end_time = clock();
              
                } 
             } 
         }
         else {
            display_error(&interface);
         }
      }
      else if (interface.action == load_help) {
        printf("Load help menu\n");
        help_menu(main);
      }



      render_update_clear(interface.window);
   }
   if (mode == challenge_mode) { 
       FILE* challenge = fopen(interface.code_file, "w");
       fclose(challenge);
    }
   return 0;
}

void initialise_text_editor(Interface* interface, Mode mode, char* file_name) {
  SDL_GetWindowSize(interface->window.win, &interface->editor_columns, &interface->editor_rows);

  interface->editor_columns /= 27;
  interface->editor_rows /= 27;

  make_text_editor(interface->editor_columns, interface->editor_rows, interface);
  
  SDL_SetTextInputRect(&interface->text_editor[0][0].box.rect);
  SDL_StartTextInput();
  
  printf("%s\n", interface->default_file);
  load_text_into_text_editor(interface->default_file, interface);    
  
}

void set_challenges_based_on_level(char* file_name, Interface* interface) {
  if (strcmp(file_name, BEGINNER) == 0) {
    printf("Beginner\n");
  strcpy(interface->code_file, "challenges/beginner_user_code.txt");
    strcpy(interface->challenges[0], "Change the colour variable value");  
    strcpy(interface->challenges[1], "Change the shape variable value to circle");
    strcpy(interface->challenges[2], "Change the type variable value to star");
    strcpy(interface->challenges[3], "Level Complete!");
    
  }

  else if (strcmp(file_name, INTERMEDIATE) == 0) {
     printf("Intermediate\n");
  strcpy(interface->code_file, "challenges/intermediate_user_code.txt");
    strcpy(interface->challenges[0], "Add the missing RUN statement and brackets");  
    strcpy(interface->challenges[1], "Write an IF statement that changes the colour variable value");
    strcpy(interface->challenges[2], "Change the size variable value to a number below 500");
     strcpy(interface->challenges[3], "Level Complete!");

  }
       
  else if (strcmp(file_name, EXPERT) == 0) {
  printf("Expert\n");
    strcpy(interface->code_file, "challenges/expert_user_code.txt");
    strcpy(interface->challenges[0], "Create a tree fractal from scratch, and use two IF statements");  
    strcpy(interface->challenges[1], "Replace one of the IF statements with a FOR loop");
    strcpy(interface->challenges[2], "Alter the linethickness to 5 within the FOR loop");
     strcpy(interface->challenges[3], "Level Complete!");

   
  }
}

void display_error(Interface *interface) 
{
  Area box;
  char message[ERROR_MAX];
  char c;
  int i=0;
  FILE *file = fopen("error_message.artc", "r");

  while((c=getc(file))!=EOF && i<ERROR_MAX-1) {
    message[i] = c;
    i++;
  }    
  message[i] = '\0';

  SDL_Event event; 
  do {

    make_rect(&interface->window, &box, 0, 200, interface->text_editor_panel.rect.w, 100, 255,255,255);
    make_text(&interface->window, &box.rect, 255,0,0, interface->challenge_font, message);
    render_update_clear(interface->window);

    SDL_PollEvent(&event); 
  }
  while(event.type != SDL_MOUSEBUTTONDOWN);
}
