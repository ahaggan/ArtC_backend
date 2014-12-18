#include "input.h"

void initialise_main_menu(Main_Menu* main);
void menu_actions(Main_Menu* main);
void render_update_clear(Main_Menu main);
int challenges(Main_Menu* main);

/* Main Menu */
int main() {
  Main_Menu main;  
  initialise_main_menu(&main);
  while(!main.window.finished) {  
    display_main_menu(&main);
    main.state = SDL_Main_Menu_Events(&main);
    menu_actions(&main);
    render_update_clear(main);
  }
  //SDL shut_down
  //TTF shut down
  //free everything that has been allocated space
  return 0;
}

void initialise_main_menu(Main_Menu* main) {
  SDL_Win_Init(&main->window, "Art-C");
  SDL_TTF_Init();
  main->font = SDL_Load_Font("font/DroidSansMono.ttf", FONT_SIZE);
  main->button_font = SDL_Load_Font("font/Mastoc.ttf", BUTTON_FONT_SIZE);
  main->state = 0;
  SDL_RenderPresent(main->window.renderer);
  SDL_UpdateWindowSurface(main->window.win);
}

void menu_actions(Main_Menu* main) {
  switch (main->state) {
    case canvas: 
      interface(&main->window, main->font, main->button_font); 
      break;
    case challenges_menu:
      challenges(main);
      break;
    //also have a How-To-'Play' (play isn't really the right word)
    case options_menu:
      break;
    case quit:
      main->window.finished = 1;
      break;
  }
}

void render_update_clear(Main_Menu main) {
  SDL_RenderPresent(main.window.renderer);
  SDL_UpdateWindowSurface(main.window.win);
  SDL_RenderClear(main.window.renderer);
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

