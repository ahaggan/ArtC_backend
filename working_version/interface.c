#include "interface.h"

int interface(Menu* main, Mode mode, char* file_name) {
   SDL_RenderClear(main->window.renderer);
   Interface interface;
   clock_t start_time, end_time; 
   
   initialise_interface(main, &interface, mode);
   initialise_text_editor(&interface, mode, file_name);
   render_update_clear(interface.window);

   while (interface.action != back_to_menu) {
      fix_mac_flickering(&interface, mode); 
      update_text_editor(interface.editor_columns, interface.editor_rows, &interface);
      interface.action = Interface_Events(&interface);
    
      if (interface.action == generate_clicked) {
         // COMMENT FUNCTION OUT IN ORDER TO USE FILE READY WRITTEN
         write_text_to_file(&interface, "user_code.artc");
         clear_area(&interface.window, interface.canvas);
        
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
         parser(&fractal, "user_code.artc");
        
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

      else if(interface.action == change_position) {
      }

      render_update_clear(interface.window);
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

  if (mode == challenge_mode) {
    load_text_into_text_editor(file_name, interface);
  }
  else {
    load_text_into_text_editor("user_code.artc", interface);
  }
}
