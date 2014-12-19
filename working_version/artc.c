#include "input.h"

int challenges(Main_Menu* main);
int interface(Main_Menu* main);
void initialise_main_menu(Main_Menu* main);
void initialise_challenges_menu(Main_Menu* main);
void main_menu_actions(Main_Menu* main);

/* Main Menu */
int main() {
  Main_Menu menu;  
  initialise_main_menu(&menu);
  while(!menu.window.finished) {  
    display_main_menu(&menu); //unnecessary doing this if there have been no changes (use clear_area())
    menu.state = SDL_Main_Menu_Events(&menu);
    main_menu_actions(&menu);
    render_update_clear(menu.window);
  }
  //SDL shut_down, TTF shut down, free memory
  return 0;
}

/* Challenges Menu */
int challenges(Main_Menu* menu) {
  initialise_challenges_menu(menu);
  while(menu->challenges.state != main_menu) {  
    draw_challenges_menu(menu, &menu->challenges);
    menu->challenges.state = SDL_Challenges_Menu_Events(&menu->challenges);
    render_update_clear(menu->challenges.window);
  }
  return 0;
}

/* Create main window and init TTF fonts */ 
void initialise_main_menu(Main_Menu* menu) {
  SDL_Win_Init(&menu->window, "Art-C");
  SDL_TTF_Init();
  menu->font = SDL_Load_Font("font/DroidSansMono.ttf", FONT_SIZE);
  menu->button_font = SDL_Load_Font("font/Mastoc.ttf", BUTTON_FONT_SIZE);
  menu->state = 0;
}

/* Assign properties of menu_menu to challenge menu */
void initialise_challenges_menu(Main_Menu* menu) {
  menu->challenges.window = menu->window;
  menu->challenges.font = menu->font;
  menu->challenges.button_font = menu->button_font;
  menu->challenges.state = 0;
}

/* Act based on whether any buttons in the main menu were pressed */ 
void main_menu_actions(Main_Menu* menu) {
  switch (menu->state) {
    case canvas: 
      interface(menu); 
      break;
    case challenges_menu:
      challenges(menu);
      break;
    //also have an 'Read Me' button
    case options_menu:
      break;
    case quit:
      menu->window.finished = 1;
      break;
  }
}
