#include "display.h"

/* Main Menu */
void launch_menu() {
  Menu menu;
  SDL_Win_Init(&menu.window, "Art.C");
  SDL_TTF_Init();

  do {
    initialise_main_menu(&menu);
    render_update_clear(menu.window);
 
    menu.state = SDL_Main_Menu_Events(&menu);
    main_menu_actions(&menu);
  //SDL shut_down, TTF shut down, free memory)

  } while(!menu.window.finished);
  
  atexit(SDL_Quit);
}

/* Challenges Menu */
int challenge_menu(Menu* challenges) {


  while(challenges->state != main_menu) {
    initialise_challenges_menu(challenges);
    render_update_clear(challenges->window);
    challenges->state = SDL_Challenges_Menu_Events(challenges);
    challenge_menu_actions(challenges);
  }
  return 0;
}

/* Act based on whether any buttons in the main menu were pressed */ 
void main_menu_actions(Menu* menu) {
  switch (menu->state) {
    case canvas: 
      interface(menu, canvas_mode, "user_code.artc"); 
      //SDL_RenderClear(menu->window.renderer);
      //display_main_menu(menu); 
      break;
    case challenges_menu:
      challenge_menu(menu);
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
       // { "challenges/easydefault.txt", "easy1.txt", "easy2.txt", "easy3.txt" }

        interface(challenges, challenge_mode, "challenges/easydefault.txt");
        break;
      case intermediate:
        //{ "challenges/intermediatedefault.txt", "intermediate1.txt", "intermediate2.txt", "intermediate3.txt" }
        interface(challenges, challenge_mode, "challenges/intermediatedefault.txt");
        break;
      //also have an 'Read Me' button
      case expert:
        //{ "challenges/expertdefault.txt", "expert1.txt", "expert2.txt", "expert3.txt" }
        interface(challenges, challenge_mode, "challenges/expertdefault.txt");
        break;
      case main_menu:
        challenges->state = main_menu;
        break;
    }
}
