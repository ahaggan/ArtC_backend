#include "input.h"


//rename to interface(int interface_type (challenge, canvas))
int main() {
  clock_t start_time, end_time;
  Interface interface;
  SDL_Win_Init(&interface.window, "ARTC");
  SDL_TTF_Init();
  interface.font = SDL_Load_Font("font/DroidSansMono.ttf", FONT_SIZE);
  interface.button_font = SDL_Load_Font("font/Mastoc.ttf", BUTTON_FONT_SIZE);
  SDL_GetWindowSize(interface.window.win, &interface.editor_columns , &interface.editor_rows);
  interface.editor_columns /= 24;
  interface.editor_rows /= 29.5;
  printf("%d %d\n", interface.editor_columns, interface.editor_rows);
  draw_interface(&interface); 


  make_text_editor(interface.editor_columns, interface.editor_rows, &interface);
  int event_type = 0;
   
  //possibly dynamically set the font size depending on the window size

  //Sets text_rect to type text inputs.
  SDL_SetTextInputRect(&interface.text_editor[0][0].box.rect);
  //Start accepting text input events
  SDL_StartTextInput();
  Draw fractal;

  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);

  while(!interface.window.finished) {
   
    draw_interface(&interface); //-stops flickering on Mac, but the fractal image disappears.
    update_text_editor(interface.editor_columns, interface.editor_rows, &interface);
   
    event_type = SDL_Events(&interface);
    if (event_type == generate_clicked) {

      write_text_to_file(interface.text_editor);
      clear_area(&interface.window, interface.canvas);
      parse(interface, &fractal);
    
      for (int i=1; i<=fractal.iterations; i++) {
        start_time = end_time = clock();
        
        generate_fractal(&fractal, interface, i);
        
        while((double)(end_time - start_time)/CLOCKS_PER_SEC < 0.4 && !interface.window.finished) {
          SDL_Events(&interface);
          update_text_editor(interface.editor_columns, interface.editor_rows, &interface);
          SDL_RenderPresent(interface.window.renderer);
          SDL_UpdateWindowSurface(interface.window.win);
         
          end_time = clock();
        } 
      }  
    }
  
  
  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);
  SDL_RenderClear(interface.window.renderer);// -stops flickering on Mac, but the fractal image disappears.m 

  }
  return 0;
}
