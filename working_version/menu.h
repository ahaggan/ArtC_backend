/*
Module contains functions that control the creation of different menus throughout the program
*/
#include "display.h"
//Resets menu states, sets menu font and calls functions to display the main menu
void initialise_main_menu(Menu* main_menu);

//WHERE ARE THESE FUNCTIONS??
Menu_Choice Main_Menu_Events(Menu* main_menu);
Menu_Choice Challenges_Menu_Events(Menu* challenges);
Menu_Choice Help_Screen_Events(Menu* help);
//Controls what the program does when the user selects an option from the main menu
void main_menu_actions(Menu* main_menu);
//Controls what the program does when the user selects an option from the challenges menu
void challenges_menu(Menu* challenges);
//Resets menu states and calls functions to display the challenges menu 
void initialise_challenges_menu(Menu* challenges);
//Controls what the program does when the user selects an option from the challenges menu
void challenges_menu_actions(Menu* challenges);

//Changes the help->state to what is passed in
void help_menu_actions(Menu* help);
//Launch menu function calls the interface which handles the general user interface commands 
void interface(Menu* main_menu, Mode mode, char* file_name);
