#include "display.h"

void initialise_main_menu(Menu* main);
int SDL_Main_Menu_Events(Menu* main_menu);
void main_menu_actions(Menu* main);

int challenge_menu(Menu* challenges);
void initialise_challenges_menu(Menu* challenges_menu);
int SDL_Challenges_Menu_Events(Menu* challenges);
void challenge_menu_actions(Menu* challenges);

void initialise_help_menu(Menu* help_menu);
int SDL_Help_Menu_Events(Menu* help);
void help_menu_actions(Menu* help);

int interface(Menu* main, Mode mode, char* file_name);
