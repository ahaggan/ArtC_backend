#include "artc.h"

/* Main Menu */
int main(void) {
  Menu menu;  
  initialise_main_menu(&menu);
  display_main_menu(&menu); //unnecessary doing this if there have been no changes (use clear_area())
  do {  
     display_main_menu(&menu); //ONLY HERE FOR MACS - COMMENT OUT IF ON LINUX
    menu.state = SDL_Main_Menu_Events(&menu);
    main_menu_actions(&menu);
    render_update_clear(menu.window);
  } while(!menu.window.finished);
  //SDL shut_down, TTF shut down, free memory)
  
  atexit(SDL_Quit);
  return 0;
}


/* Challenges Menu */
int challenges(Menu* challenges) {
  
  initialise_challenges_menu(challenges);
   display_challenges_menu(challenges);
  while(challenges->state != main_menu) {  
      display_challenges_menu(challenges); //ONLY HERE FOR MACS - COMMENT OUT IF ON LINUX
    challenges->state = SDL_Challenges_Menu_Events(challenges);
    challenge_menu_actions(challenges);
    render_update_clear(challenges->window);
  }
  return 0;
}


/* Create main window and init TTF fonts */ 
void initialise_main_menu(Menu* menu) {
  SDL_Win_Init(&menu->window, "ART.C");
  SDL_TTF_Init();
  menu->menu_font = SDL_Load_Font("font/Edo.ttf", BUTTON_FONT_SIZE);
  menu->state = 0;
}

/* Assign properties of menu_menu to challenge menu */
void initialise_challenges_menu(Menu* menu) {
  menu->state = 0;
}

/* Act based on whether any buttons in the main menu were pressed */ 
void main_menu_actions(Menu* menu) {
  switch (menu->state) {
    case canvas: 
      SDL_RenderClear(menu->window.renderer);
      interface(menu, canvas_mode, NULL); 
    SDL_RenderClear(menu->window.renderer);
    display_main_menu(menu);
      //SDL_RenderClear(menu->window.renderer);
      //display_main_menu(menu); 
      break;
    case challenges_menu:
      SDL_RenderClear(menu->window.renderer);
      challenges(menu);
    SDL_RenderClear(menu->window.renderer);
    display_main_menu(menu);
      //SDL_RenderClear(menu->window.renderer);
      //display_main_menu(menu); 
      break;
    case options_menu:
      break;
    case quit:
      menu->window.finished = 1;
      break;
  }
 
}

void challenge_menu_actions(Menu* challenges) {
    switch (challenges->state) {
      case beginner: 
        SDL_RenderClear(challenges->window.renderer);
        interface(challenges, challenge_mode, "challenges/easydefault.txt");
      SDL_RenderClear(challenges->window.renderer);
    display_challenges_menu(challenges);
        break;
      case intermediate:
        SDL_RenderClear(challenges->window.renderer);
        interface(challenges, challenge_mode, "challenges/intermediatedefault.txt");
        SDL_RenderClear(challenges->window.renderer);
        display_challenges_menu(challenges);
        break;
      //also have an 'Read Me' button
      case expert:
        SDL_RenderClear(challenges->window.renderer);
        interface(challenges, challenge_mode, "challenges/expert1.txt");
        SDL_RenderClear(challenges->window.renderer);
        display_challenges_menu(challenges);
        break;
      case main_menu:
        challenges->state = main_menu;
        break;
    }
}
