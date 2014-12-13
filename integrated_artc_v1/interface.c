#include "input.h"

int main() {
  Interface interface;
  
  SDL_Win_Init(&interface.window, "ARTC");
  SDL_TTF_Init();
  TTF_Font *font = SDL_Load_Font("font/DroidSansMono.ttf", FONT_SIZE);
  interface.font = font;
  draw_interface(&interface); 
  make_text_editor(EDITOR_COLUMNS, EDITOR_ROWS, &interface);
  int event_type = 0;
   
  //possibly dynamically set the font size depending on the window size

  //Sets text_rect to type text inputs.
  SDL_SetTextInputRect(&interface.text_editor[0][0].box.rect);
  //Start accepting text input events
  SDL_StartTextInput();
  Draw *fractal[NO_OF_LOOPS];
  
  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);

  while(!interface.window.finished) {
   
    draw_interface(&interface); //-stops flickering on Mac, but the fractal image disappears.
     update_text_editor(EDITOR_COLUMNS, EDITOR_ROWS, &interface);
    event_type = SDL_Events(&interface);
    if (event_type == generate_clicked) {
      write_text_to_file(interface.text_editor);
      //clear_area(&interface.window, interface.canvas);
    //  parse(interface, fractal);
      //generate_fractal(fractal, interface);
    }        
    else if(event_type == text_edited) {
      ;
    }
  
  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);
  SDL_RenderClear(interface.window.renderer);// -stops flickering on Mac, but the fractal image disappears.m 

  }
  return 0;
}
