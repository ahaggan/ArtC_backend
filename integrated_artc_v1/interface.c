#include "input.h"

#define MENU_OFFSET 12

int main() {
  Interface interface;
  int event_type = 0;

  SDL_Win_Init(&interface.window, "ARTC");
  SDL_TTF_Init();
  TTF_Font *font = SDL_Load_Font("font/FreeSans.ttf", 24);
  interface.font = font;
  strcpy(interface.composition, "Enter text:");
  SDL_Color editor_text_colour = {0,0,0,255};
  //Sets text_rect to type text inputs.
  SDL_SetTextInputRect(&interface.texteditor.rect);
  //Start accepting text input events
  SDL_StartTextInput();
  
  Draw fractal;

  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);

  while(!interface.window.finished) {

    draw_interface(&interface); //-stops flickering on Mac, but the fractal image disappears.

    SDL_Surface* text_surface = TTF_RenderText_Solid(font, interface.composition, editor_text_colour);
    SDL_Texture* text_editor = SurfaceToTexture(text_surface, &interface.window);
    SDL_QueryTexture(text_editor, NULL, NULL, &interface.texteditor.rect.w, &interface.texteditor.rect.h);
    SDL_RenderCopy(interface.window.renderer, text_editor, NULL, &interface.texteditor.rect);

    event_type = SDL_Events(&interface);

    if (event_type == generate_clicked) {
      //clear_area(&interface.window, interface.canvas);
      parse(interface, &fractal);
      printf("\nafter input");
      generate_fractal(&fractal, interface);
    }        
    else if(event_type == text_edited) {
      ;//clear_area(&interface.window, interface.texteditor);
    }

    SDL_RenderPresent(interface.window.renderer);
    SDL_UpdateWindowSurface(interface.window.win);

    SDL_RenderClear(interface.window.renderer);// -stops flickering on Mac, but the fractal image disappears.  
    SDL_DestroyTexture(text_editor);
  }
  return 0;
}

void draw_interface(Interface *interface) {
  int x, y;
  int menu_x, menu_y, menu_w, menu_h;
  int texted_x, texted_y, texted_w, texted_h;
  int canvas_x, canvas_y, canvas_w, canvas_h;
  int gbutton_x, gbutton_y, gbutton_w, gbutton_h;
  int ch1button_x, ch1button_y, ch1button_w, ch1button_h;
  SDL_GetWindowSize(interface->window.win, &x, &y);

  menu_x = menu_y = texted_x = gbutton_x = 0;
  menu_w = x;
  menu_h = y / MENU_OFFSET;

  texted_y = canvas_y = menu_h;
  texted_w = canvas_x = canvas_w = x / 2;
  texted_h = canvas_h = y - menu_h - 25;

  gbutton_y = y - 25;
  gbutton_w = x / 10;
  gbutton_h = 25;

  ch1button_x = 5;
  ch1button_y = 5;
  ch1button_w = 100;
  ch1button_h = 40;

  //Panels
  make_rect(&interface->window, &interface->menubar, menu_x, menu_y, menu_w, menu_h, 255, 64, 64);
  make_rect(&interface->window, &interface->texteditor, texted_x, texted_y, texted_w, texted_h, 128, 128, 128);
  make_rect(&interface->window, &interface->canvas, canvas_x, canvas_y, canvas_w, canvas_h, 255, 255, 255);

  //Buttons
  make_rect(&interface->window, &interface->gbutton, gbutton_x, gbutton_y, gbutton_w, gbutton_h, 255, 0, 0);
  make_text(&interface->window, &interface->gbutton.rect, 64, 255, 64, interface->font, "GENERATE!");

  make_rect(&interface->window, &interface->ch1button, ch1button_x, ch1button_y, ch1button_w, ch1button_h, 0, 0, 255);
  make_text(&interface->window, &interface->ch1button.rect, 192, 192, 255, interface->font, "Challenge 1");
}

