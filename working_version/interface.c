#include "input.h"

void initialise_interface(Main_Menu* main, Interface* interface);
void initialise_text_editor(Interface* interface);

int interface(Main_Menu* main) {
   Interface interface;
   clock_t start_time, end_time; //hideous
   Draw fractal; //shouldn't be in here
   initialise_interface(main, &interface); 
   initialise_text_editor(&interface);

   while (interface.action != back_to_menu) {
      display_interface(&interface);
      update_text_editor(interface.editor_columns, interface.editor_rows, &interface);
      interface.action = Interface_Events(&interface);

      if (interface.action == generate_clicked) {
         write_text_to_file(&interface, "user_code.artc");
         clear_area(&interface.window, interface.canvas);

         /* START: only here due to parser udpate */
            fractal.startx = interface.canvas.rect.x + (interface.canvas.rect.w/2);
            fractal.starty = interface.canvas.rect.y + (interface.canvas.rect.h/2);
            fractal.endx = WIN_WIDTH/2 + 10;
            fractal.endy = WIN_HEIGHT/2 + 10; 
            for (int q = 0; q < 10; q++){
               fractal.linethickness[q] = 1;
            }
         /* END */

         parser(&fractal);
         
         for (int i = 1; i <= fractal.iterations; i++) {
            start_time = end_time = clock();
            generate_fractal(&fractal, interface, i);
            while(((double)end_time - (double)start_time)/(double)CLOCKS_PER_SEC < 0.1) {
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

void initialise_interface(Main_Menu* main_menu, Interface* interface) {
  interface->action = 0;
  interface->window = main_menu->window;
  interface->font = main_menu->font;
  interface->button_font = main_menu->button_font;
  display_interface(interface);
}

void initialise_text_editor(Interface* interface) {
  SDL_GetWindowSize(interface->window.win, &interface->editor_columns, &interface->editor_rows);

  //Canvas Mode:
  interface->editor_columns /= 24;
  interface->editor_rows /= 29.5;
  
  make_text_editor(interface->editor_columns, interface->editor_rows, interface);
 
  SDL_SetTextInputRect(&interface->text_editor[0][0].box.rect);
  SDL_StartTextInput();
  load_text_into_text_editor("user_code.artc", interface);
}
