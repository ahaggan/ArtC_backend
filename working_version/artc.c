#include "input.h"

int challenges(Main_Menu* main);

int main() {
  Menu_Choice choice = 0;
  Main_Menu main_menu;
  SDL_Win_Init(&main_menu.window, "Art-C");
  SDL_TTF_Init();
  main_menu.font = SDL_Load_Font("font/DroidSansMono.ttf", FONT_SIZE);
  main_menu.button_font = SDL_Load_Font("font/Mastoc.ttf", BUTTON_FONT_SIZE);
  SDL_RenderPresent(main_menu.window.renderer);
  SDL_UpdateWindowSurface(main_menu.window.win);

  while(!main_menu.window.finished) {  
    draw_main_menu(&main_menu);
    choice = SDL_Main_Menu_Events(&main_menu);
    switch (choice) {
      case canvas: 
        interface(&main_menu.window, main_menu.font, main_menu.button_font); 
        break;
      case challenges_menu:
        challenges(&main_menu);
        break;
      case options_menu:
        break;
      case quit:
        main_menu.window.finished = 1;
        break;
    }
    SDL_RenderPresent(main_menu.window.renderer);
    SDL_UpdateWindowSurface(main_menu.window.win);
    SDL_RenderClear(main_menu.window.renderer);
  }
  //SDL shut_down
  return 0;
}

int challenges(Main_Menu* main) {
  Challenges_Choice choice = 0;
  main->challenges.window = main->window;
  main->challenges.font = main->font;
  main->challenges.button_font = main->button_font;
  draw_challenges_menu(main, &main->challenges);
  SDL_RenderPresent(main->challenges.window.renderer);
  SDL_UpdateWindowSurface(main->challenges.window.win);
  while(choice != main_menu) {  
    draw_challenges_menu(main, &main->challenges);
    choice = SDL_Challenges_Menu_Events(&main->challenges);
    SDL_RenderPresent(main->challenges.window.renderer);
    SDL_UpdateWindowSurface(main->challenges.window.win);
    SDL_RenderClear(main->challenges.window.renderer);
  }
  return 0;
}
