#include "input.h"

int main() {
  Interface interface;
  SDL_Win_Init(&interface.window, "ARTC");
  SDL_TTF_Init();
  interface.font = SDL_Load_Font("font/DroidSansMono.ttf", FONT_SIZE);
  interface.button_font = SDL_Load_Font("font/Mastoc.ttf", BUTTON_FONT_SIZE);
  clock_t start_time, end_time;
  draw_interface(&interface); 
  make_text_editor(EDITOR_COLUMNS, EDITOR_ROWS, &interface);
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
    update_text_editor(EDITOR_COLUMNS, EDITOR_ROWS, &interface);
   
    event_type = SDL_Events(&interface);
    if (event_type == generate_clicked) {

      write_text_to_file(interface.text_editor);
      clear_area(&interface.window, interface.canvas);
      parse(interface, &fractal);
    
      for (int i=1; i<=fractal.iterations; i++) {
        start_time = end_time = clock();
        generate_fractal(&fractal, interface, i);
        while((double)(end_time - start_time)/CLOCKS_PER_SEC < 0.2) {
          SDL_Events(&interface);
          update_text_editor(EDITOR_COLUMNS, EDITOR_ROWS, &interface);
          SDL_RenderPresent(interface.window.renderer);
          SDL_UpdateWindowSurface(interface.window.win);
          end_time = clock();
          if ((double)(end_time - start_time)/CLOCKS_PER_SEC < 0.2) {
            printf("%lf\n", (double)(end_time - start_time)/CLOCKS_PER_SEC);
          }
          
        } 
      }  
    }
  
  
  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);
  SDL_RenderClear(interface.window.renderer);// -stops flickering on Mac, but the fractal image disappears.m 

  }
  return 0;
}
