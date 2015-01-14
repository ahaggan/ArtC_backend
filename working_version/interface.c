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
        main->state = options_menu;
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

void display_error(Interface *interface) {
  Area box;
  Area text_box_top;
  Area text_box_bottom;

  char message_top[ERROR_TEXTBOX];
  char message_bottom[ERROR_TEXTBOX];

  char aligned_message_top[ERROR_TEXTBOX];
  char aligned_message_bottom[ERROR_TEXTBOX];

  char c;

  int i=0, j=0;

  FILE *file = fopen("error_message.artc", "r");

  while((c=getc(file))!=EOF && i < (ERROR_TEXTBOX * 2) - 2) {
   printf("i is %d\n", i);
  printf("Char: %c\n", c);
  printf("Char: %d\n", c);
    if (i < ERROR_TEXTBOX - 1) {
       
       message_top[i] = c;
    }
    else {
      if (message_top[ERROR_TEXTBOX - 2] != ' ') {
        printf("Message top final cell not ' '\n Do i-- while not ' '.\n");
        do {
          i--;
          printf("%c\n", message_top[i]);
        } while (message_top[i] != ' ');
        while (i < ERROR_TEXTBOX - 1) {
          message_bottom[j++] = message_top[i+1];
          message_top[i+1] = ' ';
          i++;
        }
        i += j - 1;
      }    
      printf("Bottom: %c\n", c);
      message_bottom[i- ERROR_TEXTBOX + 1] = c;
    }
    i++;
  }    

  message_top[ERROR_TEXTBOX - 1] = '\0';
  message_bottom[ERROR_TEXTBOX - 1] = '\0';
   
//message_bottom[i] = '\0';

  printf("top: %lu bottom: %lu\n", strlen(message_top), strlen(message_bottom)); 
  text_align_central(aligned_message_top, message_top, ERROR_TEXTBOX);
 
  text_align_central(aligned_message_bottom, message_bottom, ERROR_TEXTBOX);
 
   SDL_Event event; 
  do {
    make_rect(&interface->window, &box, 0, 200, interface->text_editor_panel.rect.w, 100, 255,255,255);

    make_rect(&interface->window, &text_box_top, 0, box.rect.y + (box.rect.h / 4), interface->text_editor_panel.rect.w, CHALLENGE_FONT * 1.45, 255,255,255);
    make_text(&interface->window, &text_box_top.rect, 241, 35, 65, interface->challenge_font, aligned_message_top);

    make_rect(&interface->window, &text_box_bottom, 0, text_box_top.rect.y + text_box_top.rect.h, interface->text_editor_panel.rect.w, CHALLENGE_FONT * 1.45, 255,255,255);
    make_text(&interface->window, &text_box_bottom.rect, 241, 35, 65, interface->challenge_font, aligned_message_bottom);

    render_update_clear(interface->window);
    SDL_PollEvent(&event); 
  } while(event.type != SDL_MOUSEBUTTONDOWN);
}
