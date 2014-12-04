#include "input.h"

#define FONT_SIZE 20

int main() {
  Interface interface;
  int event_type = 0;

  SDL_Win_Init(&interface.window, "ARTC");
  SDL_TTF_Init();
  //possibly dynamically set the font size depending on the window size
  TTF_Font *font = SDL_Load_Font("font/FreeMonoBold.ttf", FONT_SIZE);
  interface.font = font;
  strcpy(interface.composition, "Enter text:");
  SDL_Color editor_text_colour = {0,0,0,255};
  //Sets text_rect to type text inputs.
  
  //Start accepting text input events
  SDL_StartTextInput();
  
  Draw fractal;

  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);

  while(!interface.window.finished) {
    SDL_SetTextInputRect(&interface.text_editor[0][0].box.rect);
    draw_interface(&interface); //-stops flickering on Mac, but the fractal image disappears.


    /* going to have to do this in a for loop for all of the cells in the text editor */
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, interface.composition, editor_text_colour);
    SDL_Texture* text_editor = SurfaceToTexture(text_surface, &interface.window);
    SDL_QueryTexture(text_editor, NULL, NULL, &interface.text_editor[0][0].box.rect.w, &interface.text_editor[0][0].box.rect.h);
    SDL_RenderCopy(interface.window.renderer, text_editor, NULL, &interface.text_editor[0][0].box.rect);
    

    event_type = SDL_Events(&interface);

    if (event_type == generate_clicked) {
      //clear_area(&interface.window, interface.canvas);
      parse(interface, &fractal);
      printf("\nafter input");
      generate_fractal(&fractal, interface);
    }        
    else if(event_type == text_edited) {
      ;//clear_area(&interface.window, interface.text_editor);
    }

    SDL_RenderPresent(interface.window.renderer);
    SDL_UpdateWindowSurface(interface.window.win);

    SDL_RenderClear(interface.window.renderer);// -stops flickering on Mac, but the fractal image disappears.m  
    //SDL_DestroyTexture(text_editor);
  }
  return 0;
}

