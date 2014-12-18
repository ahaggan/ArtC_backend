#include "input.h"

int challenges(Main_Menu* main);
int interface(Main_Menu* main);
void initialise_main_menu(Main_Menu* main);
void initialise_challenges_menu(Main_Menu* main);
void main_menu_actions(Main_Menu* main);

/* Main Menu */
int main() {
  Main_Menu main;  
  initialise_main_menu(&main);
  while(!main.window.finished) {  
    display_main_menu(&main); //unnecessary doing this if there have been no changes (use clear_area())
    main.state = SDL_Main_Menu_Events(&main);
    main_menu_actions(&main);
    render_update_clear(main.window);
  }
  //SDL shut_down, TTF shut down, free memory
  return 0;
}

/* Challenges Menu */
int challenges(Main_Menu* main) {
  initialise_challenges_menu(main);
  while(main->challenges.state != main_menu) {  
    draw_challenges_menu(main, &main->challenges);
    main->challenges.state = SDL_Challenges_Menu_Events(&main->challenges);
    render_update_clear(main->challenges.window);
  }
  return 0;
}

/* Create main window and init TTF fonts */ 
void initialise_main_menu(Main_Menu* main) {
  SDL_Win_Init(&main->window, "Art-C");
  SDL_TTF_Init();
  main->font = SDL_Load_Font("font/DroidSansMono.ttf", FONT_SIZE);
  main->button_font = SDL_Load_Font("font/Mastoc.ttf", BUTTON_FONT_SIZE);
  main->state = 0;
}

/* Assign properties of main_menu to challenge menu */
void initialise_challenges_menu(Main_Menu* main) {
  main->challenges.window = main->window;
  main->challenges.font = main->font;
  main->challenges.button_font = main->button_font;
  main->challenges.state = 0;
}

/* Act based on whether any buttons in the main menu were pressed */ 
void main_menu_actions(Main_Menu* main) {
  switch (main->state) {
    case canvas: 
      interface(main); 
      break;
    case challenges_menu:
      challenges(main);
      break;
    //also have an 'Read Me' button
    case options_menu:
      break;
    case quit:
      main->window.finished = 1;
      break;
  }
}
