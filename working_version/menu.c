#include "input.h"

int main() {
  int menu_choice;
  Main_Menu main_menu;
  SDL_Win_Init(&main_menu.window, "Art-C");
  SDL_TTF_Init();
  main_menu.font = SDL_Load_Font("font/DroidSansMono.ttf", FONT_SIZE);
  main_menu.button_font = SDL_Load_Font("font/Mastoc.ttf", BUTTON_FONT_SIZE);
  

  SDL_RenderPresent(main_menu.window.renderer);
  SDL_UpdateWindowSurface(main_menu.window.win);

  while(!main_menu.window.finished) {  
    draw_main_menu(&main_menu);
    menu_choice = SDL_Menu_Events(&main_menu);
    if (menu_choice) {
      interface(&main_menu.window, main_menu.font, main_menu.button_font); 
    }
    SDL_RenderPresent(main_menu.window.renderer);
    SDL_UpdateWindowSurface(main_menu.window.win);
    SDL_RenderClear(main_menu.window.renderer);// -stops flickering on Mac, but the fractal image disappears.m 
  }
  return 0;
}
