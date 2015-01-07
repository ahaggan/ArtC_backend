#include "input.h"
#include <unistd.h>

void initialise_interface(Main_Menu* main, Interface* interface, Mode mode);
void initialise_text_editor(Interface* interface, Mode mode);

int interface(Main_Menu* main, Mode mode) {
   Interface interface;
   clock_t start_time, end_time; 
   
   initialise_interface(main, &interface, mode);
   initialise_text_editor(&interface, mode);
  render_update_clear(interface.window);

   while (interface.action != back_to_menu) {
      fix_mac_flickering(&interface, mode); 
      update_text_editor(interface.editor_columns, interface.editor_rows, &interface);
      interface.action = Interface_Events(&interface);
    
      if (interface.action == generate_clicked) {
         write_text_to_file(&interface, "user_code.artc");
         clear_area(&interface.window, interface.canvas);
        
         /* START: only here due to parser update */
            Draw fractal; 
            //Sets default values to avoid missing values if the user only inputs a few things.(Small red square)
            //parser(&fractal, "default.txt"); 
            fractal.startx = interface.canvas.rect.x + (interface.canvas.rect.w/2);
            fractal.starty = interface.canvas.rect.y + (interface.canvas.rect.h/2);
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
      render_update_clear(interface.window);
   }
   return 0;
}

void initialise_interface(Main_Menu* main_menu, Interface* interface, Mode mode) {
  interface->action = 0;
  interface->window = main_menu->window;
  interface->text_ed_font = SDL_Load_Font("font/DroidSansMono.ttf", FONT_SIZE);
  interface->button_font = main_menu->menu_font;
  display_interface(interface, mode);
}

void initialise_text_editor(Interface* interface, Mode mode) {
  SDL_GetWindowSize(interface->window.win, &interface->editor_columns, &interface->editor_rows);

  interface->editor_columns /= 27;
  interface->editor_rows /= 27;
  
  make_text_editor(interface->editor_columns, interface->editor_rows, interface);
 
  SDL_SetTextInputRect(&interface->text_editor[0][0].box.rect);
  SDL_StartTextInput();

  if (mode == challenge_mode) {
    load_text_into_text_editor("user_code.artc", interface);
  }
}
