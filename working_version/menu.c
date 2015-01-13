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
      interface(menu, canvas_mode, "canvas.txt"); 
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
       // { "Change the colour variable value", "Change the shape variable value to circle", "Change the type variable value to star.txt" }

        interface(challenges, challenge_mode, "challenges/easydefault.txt");
        break;
      case intermediate:
        //{ "Add the missing RUN statement and brackets", "Write an IF statement that changes the colour variable valuet", "Change the size variable value to a number below 500.txt" }
        interface(challenges, challenge_mode, "challenges/intermediatedefault.txt");
        break;
      case expert:
        //{ "Create a tree fractal from scratch, and use two IF statements", "Replace one of the IF statements with a FOR loop", "Alter the linethickness to 5 within the FOR loop" }
        interface(challenges, challenge_mode, "challenges/expertdefault.txt");
        break;
      case main_menu:
        challenges->state = main_menu;
        break;
    }
}
