#include "display.h"

void SDL_Win_Init(SDL_Win *w, char* win_name) {
   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   } 
   w->finished = 0;
   
   w->win= SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, 
                            SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, 
                            SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

   if (w->win == NULL) {
      fprintf(stderr, "\nUnable to initialize SDL Win: %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   w->renderer = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED | 
                                    SDL_RENDERER_PRESENTVSYNC | 
                                    SDL_RENDERER_TARGETTEXTURE);

   if (w->renderer == NULL) {
      fprintf(stderr, "\nUnable to initialize SDL Rend: %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }
  
   // Set resolution (size) of renderer to the window size.
   SDL_RenderSetLogicalSize(w->renderer, WIN_WIDTH, WIN_HEIGHT); 
   SDL_SetWindowMinimumSize(w->win, MIN_WIDTH, MIN_HEIGHT);

  
   //Set screen to white
   SDL_SetRenderDrawColor(w->renderer, 255, 255, 255, 255);
   render_update_clear(*w);
}

void clear_area(SDL_Win *window, Area area) {
   SDL_SetRenderDrawColor(window->renderer, 255, 255, 255,
                        255);
   SDL_RenderFillRect(window->renderer, &area.rect);  
   render_update_clear(*window);
}

void SDL_TTF_Init() {
   if (TTF_Init() != 0) {
      fprintf(stderr, "\nUnable to initialize TTF:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }
}

TTF_Font* SDL_Load_Font(char* font_path, int font_size) {
   TTF_Font *font = TTF_OpenFont(font_path, font_size);
   if (font == NULL) {
      fprintf(stderr, "\nTTF_OpenFont could not open the font: %s\n", 
              SDL_GetError());
      TTF_Quit();
      SDL_Quit();
      exit(1);
   }
   return font;
}

SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w) {
   SDL_Texture* texture = SDL_CreateTextureFromSurface(w->renderer, surface);
   SDL_FreeSurface(surface);
   return texture;
}

void SDL_TTF_Quit(TTF_Font *font) {
   TTF_CloseFont(font);
   TTF_Quit();
}


/* Create main window and init TTF fonts */ 
void initialise_main_menu(Menu* menu) {
  int win_width, win_height;

  menu->menu_font = SDL_Load_Font("font/Edo.ttf", BUTTON_FONT_SIZE);
  menu->state = 0;

   SDL_GetWindowSize(menu->window.win, &win_width, &win_height);
   display_menu_background(win_width, win_height, menu);
   display_logo(win_width, win_height, menu);
   display_canvas_button(win_width, win_height, menu);
   display_challenges_button(win_width, win_height, menu);
   display_menu_help_button(win_width, win_height, menu);
   display_quit_button(win_width, win_height, menu);

}

void display_menu_background(int win_width, int win_height, Menu* main_menu) {
   int background_x, background_y, background_w, background_h;

   background_x = background_y = 0;
   background_w = win_width;
   background_h = win_height;

   make_rect(&main_menu->window, &main_menu->background, background_x, 
            background_y, background_w, background_h, 255, 255, 255);
}

void display_logo(int win_width, int win_height, Menu* main_menu) {
  SDL_Texture* image = load_image("menu_graphics/artc_logo.bmp", &main_menu->window);
   int logo_x, logo_y, logo_w, logo_h;
   logo_w = LOGO_WIDTH / 2;
   logo_x = win_width / LEFT_MARGIN;
   logo_h = LOGO_HEIGHT / 2;
   logo_y = win_height / TOP_MARGIN; 
   make_rect(&main_menu->window, &main_menu->logo, logo_x, 
            logo_y, logo_w, logo_h, 230, 230, 230);
  SDL_RenderCopy(main_menu->window.renderer, image, NULL, &main_menu->logo.rect);
  SDL_DestroyTexture(image); 

}

void display_canvas_button(int win_width, int win_height, Menu* main_menu) {
    SDL_Texture* image = load_image("menu_graphics/canvas.bmp", &main_menu->window);
   int canvas_button_x, canvas_button_y, canvas_button_w, canvas_button_h;

   canvas_button_w = MENU_BUTTON_WIDTH;
   canvas_button_x = win_width / LEFT_MARGIN;
   canvas_button_h = MENU_BUTTON_HEIGHT;
   canvas_button_y = (main_menu->logo.rect.y + main_menu->logo.rect.h) + 
                    (win_height / TOP_MARGIN);
  
  


   make_rect(&main_menu->window, &main_menu->canvas_button, canvas_button_x, 
            canvas_button_y, canvas_button_w, canvas_button_h, 241, 14, 71);
   SDL_RenderCopy(main_menu->window.renderer, image, NULL, &main_menu->canvas_button.rect);
   SDL_DestroyTexture(image); 

}

void display_challenges_button(int win_width, int win_height, Menu* main_menu) {
   SDL_Texture* image = load_image("menu_graphics/challenges.bmp", &main_menu->window);
   int challenges_button_x, challenges_button_y, challenges_button_w, challenges_button_h;

   challenges_button_w = main_menu->canvas_button.rect.w;
   challenges_button_x = win_width / LEFT_MARGIN;
   challenges_button_h = main_menu->canvas_button.rect.h;
   challenges_button_y = (main_menu->canvas_button.rect.y + 
                         main_menu->canvas_button.rect.h) +
                         (win_height / MENU_BUTTON_DIST);

   make_rect(&main_menu->window, &main_menu->challenges_button, challenges_button_x, 
            challenges_button_y, challenges_button_w, challenges_button_h, 
            241, 14, 71);
     SDL_RenderCopy(main_menu->window.renderer, image, NULL, &main_menu->challenges_button.rect);
   SDL_DestroyTexture(image); 
}

void display_menu_help_button(int win_width, int win_height, Menu* main_menu) {
   SDL_Texture* image = load_image("menu_graphics/help.bmp", &main_menu->window);
   int menu_help_button_x, menu_help_button_y, menu_help_button_w, menu_help_button_h;

   menu_help_button_w = main_menu->canvas_button.rect.w;
   menu_help_button_x = win_width / LEFT_MARGIN;
   menu_help_button_h = main_menu->canvas_button.rect.h;
   menu_help_button_y = (main_menu->challenges_button.rect.y + 
                      main_menu->challenges_button.rect.h) +
                      (win_height / MENU_BUTTON_DIST);

   make_rect(&main_menu->window, &main_menu->menu_help_button, menu_help_button_x, 
            menu_help_button_y, menu_help_button_w, menu_help_button_h, 241, 14, 71);
       SDL_RenderCopy(main_menu->window.renderer, image, NULL, &main_menu->menu_help_button.rect);
   SDL_DestroyTexture(image); 
}

void display_quit_button(int win_width, int win_height, Menu* main_menu) {
  SDL_Texture* image = load_image("menu_graphics/quit.bmp", &main_menu->window);
   int quit_button_x, quit_button_y, quit_button_w, quit_button_h;

   quit_button_w = main_menu->canvas_button.rect.w;
   quit_button_x = win_width / LEFT_MARGIN;
   quit_button_h = main_menu->canvas_button.rect.h;
   quit_button_y = (main_menu->menu_help_button.rect.y + 
                   main_menu->menu_help_button.rect.h) +
                   win_height / MENU_BUTTON_DIST;

   make_rect(&main_menu->window, &main_menu->quit_button, quit_button_x, 
            quit_button_y, quit_button_w, quit_button_h, 100, 90, 90);
        SDL_RenderCopy(main_menu->window.renderer, image, NULL, &main_menu->quit_button.rect);
   SDL_DestroyTexture(image); 
}


/* Challenges Menu */
void initialise_challenges_menu(Menu* challenges) {
   int win_width, win_height;
   challenges->state = 0;  
   SDL_GetWindowSize(challenges->window.win, &win_width, &win_height);

   display_challenges_background(win_width, win_height, challenges);
   display_header(win_width, win_height, challenges);
   display_beginner_button(win_width, win_height, challenges);
   display_intermediate_button(win_width, win_height, challenges);
   display_expert_button(win_width, win_height, challenges);
   display_main_menu_button(win_width, win_height, challenges);
}

void display_challenges_background(int win_width, int win_height, Menu* challenges) {
   int background_x, background_y, background_w, background_h;

   background_x = background_y = 0;
   background_w = win_width;
   background_h = win_height;

   make_rect(&challenges->window, &challenges->background, background_x, 
            background_y, background_w, background_h, 255, 255, 255);
}



void display_header(int win_width, int win_height, Menu* challenges){
  SDL_Texture* image = load_image("menu_graphics/challenges_header.bmp", &challenges->window);
   int header_x, header_y, header_w, header_h;

  header_w = LOGO_WIDTH / 2;
   header_x = win_width / LEFT_MARGIN;
   header_h = LOGO_HEIGHT / 2;
   header_y = win_height / TOP_MARGIN;

   make_rect(&challenges->window, &challenges->header, header_x, header_y, 
            header_w, header_h, 220, 100, 100);
  SDL_RenderCopy(challenges->window.renderer, image, NULL, &challenges->header.rect);
   SDL_DestroyTexture(image); 
}

void display_beginner_button(int win_width, int win_height, Menu* challenges) {
  SDL_Texture* image = load_image("menu_graphics/beginner.bmp", &challenges->window);
   int beginner_x, beginner_y, beginner_w, beginner_h;

   beginner_w =  MENU_BUTTON_WIDTH;
   beginner_x = win_width / LEFT_MARGIN;
   beginner_h = MENU_BUTTON_HEIGHT;
   beginner_y = (challenges->header.rect.y + challenges->header.rect.h) + 
               (win_height / MENU_BUTTON_DIST);

   make_rect(&challenges->window, &challenges->beginner, beginner_x, beginner_y, 
            beginner_w, beginner_h, 241, 14, 71);
   SDL_RenderCopy(challenges->window.renderer, image, NULL, &challenges->beginner.rect);
   SDL_DestroyTexture(image); 
}

void display_intermediate_button(int win_width, int win_height, Menu* challenges) {

   SDL_Texture* image = load_image("menu_graphics/intermediate.bmp", &challenges->window);
   int intermediate_x, intermediate_y, intermediate_w, intermediate_h;
   intermediate_w = MENU_BUTTON_WIDTH;
   intermediate_x = win_width / LEFT_MARGIN;
   intermediate_h = MENU_BUTTON_HEIGHT;
   intermediate_y = (challenges->beginner.rect.y + challenges->beginner.rect.h) 
                   + (win_height / MENU_BUTTON_DIST);

   make_rect(&challenges->window, &challenges->intermediate, intermediate_x, 
            intermediate_y, intermediate_w, intermediate_h, 241, 14, 71);
    SDL_RenderCopy(challenges->window.renderer, image, NULL, &challenges->intermediate.rect);
   SDL_DestroyTexture(image); 
}

void display_expert_button(int win_width, int win_height, Menu* challenges) {
   SDL_Texture* image = load_image("menu_graphics/expert.bmp", &challenges->window);
  int expert_x, expert_y, expert_w, expert_h;
  expert_w = MENU_BUTTON_WIDTH;
  expert_x = win_width / LEFT_MARGIN;
  expert_h = MENU_BUTTON_HEIGHT;
  expert_y = (challenges->intermediate.rect.y + challenges->intermediate.rect.h) 
             + (win_height / MENU_BUTTON_DIST);

  make_rect(&challenges->window, &challenges->expert, expert_x, expert_y, 
            expert_w, expert_h, 241, 14, 71);
  SDL_RenderCopy(challenges->window.renderer, image, NULL, &challenges->expert.rect);
   SDL_DestroyTexture(image); 
}

void display_main_menu_button(int win_width, int win_height, Menu* challenges) {
  SDL_Texture* image = load_image("menu_graphics/main_menu.bmp", &challenges->window);
  int main_menu_x, main_menu_y, main_menu_w, main_menu_h;
  main_menu_w = MENU_BUTTON_WIDTH;
  main_menu_x = win_width / LEFT_MARGIN;
  main_menu_h = MENU_BUTTON_HEIGHT;
  main_menu_y = (challenges->expert.rect.y + challenges->expert.rect.h) 
                + (win_height / MENU_BUTTON_DIST);

  make_rect(&challenges->window, &challenges->main_menu, main_menu_x, 
            main_menu_y, main_menu_w, main_menu_h, 100, 90, 90);
  SDL_RenderCopy(challenges->window.renderer, image, NULL, &challenges->main_menu.rect);
   SDL_DestroyTexture(image); 
}

/* Interface */
//this needs a flag sent to it: request either canvas interface or challenge interface

void initialise_interface(Menu* main_menu, Interface* interface, Mode mode) {
  int win_width, win_height;
  interface->action = 0;
  interface->window = main_menu->window;
  interface->text_ed_font = SDL_Load_Font("font/DroidSansMono.ttf", FONT_SIZE);
  interface->button_font = main_menu->menu_font;
  interface->challenge_font = SDL_Load_Font("font/DroidSansMono.ttf", CHALLENGE_FONT);
  interface->mode = mode;

   SDL_GetWindowSize(interface->window.win, &win_width, &win_height);
   printf("%d %d\n", win_width, win_height);
   display_toolbar(win_width, win_height, interface, mode);
  display_menu_button(win_width, win_height, interface, mode);
  display_help_button(win_width, win_height, interface, mode);
   display_reset_button(win_width, win_height, interface, mode);
   display_generate_button(win_width, win_height, interface);
  display_canvas(win_width, win_height, interface, mode);
   display_text_editor(win_width, win_height, interface); 

   if (mode == challenge_mode) {
     display_learn_button(win_width, win_height, interface);
     display_previous_button(win_width, win_height, interface);
     display_current_challenge(win_width, win_height, interface);
     display_next_button(win_width, win_height, interface);
   }
   display_dividers(win_width, win_height, interface, mode);

   interface->click_location.row = interface->canvas.rect.x + (interface->canvas.rect.w/2);
   interface->click_location.column = interface->canvas.rect.y + (interface->canvas.rect.h/2);
}

void display_dividers(int win_width, int win_height, Interface* interface, Mode mode) {
  /* Toolbar */
  //bottom divider
   make_rect(&interface->window, &interface->toolbar_bottom_divider, 0, interface->toolbar.rect.h - 1, 
             interface->toolbar.rect.w, 1, 20, 20, 20);
   if (mode == challenge_mode) {

    //Menu/Learn divider
    make_rect(&interface->window, &interface->menu_learn_divider, interface->learn_button.rect.x - 1, 0, 
            1, interface->menu_button.rect.h, 20, 20, 20);
   
   
  }
   //Learn/Help divider OR menu/help divider
    make_rect(&interface->window, &interface->learn_help_divider, interface->help_button.rect.x - 1, 0,
            1, interface->menu_button.rect.h, 20, 20, 20);

  //Text Editor/Canvas divider
   make_rect(&interface->window, &interface->toolbar_bottom_divider, interface->text_editor_panel.rect.w,
            0, 1, win_height, 20, 20, 20);

  //Generate/Reset divider
  make_rect(&interface->window, &interface->reset_generate_divider, interface->generate_button.rect.x - 1, 
            interface->generate_button.rect.y,  1, interface->generate_button.rect.h, 0, 0, 0);

  //Generate/Reset top border
  make_rect(&interface->window, &interface->reset_generate_top_border, interface->reset_button.rect.x, 
            interface->reset_button.rect.y,  interface->reset_button.rect.w * 2, 1, 0, 0, 0);
  
  //prev divider
  make_rect(&interface->window, &interface->prev_divider, interface->previous_button.rect.x + interface->previous_button.rect.w - 1, 
            interface->previous_button.rect.y,  1, interface->previous_button.rect.h, 20, 20, 20);

   //next divider
  make_rect(&interface->window, &interface->next_divider, interface->next_button.rect.x - 1, 
            interface->next_button.rect.y,  1, interface->next_button.rect.h, 20, 20, 20);
}

void fix_mac_flickering(Interface* interface, Mode mode) {
   int win_width, win_height;
   SDL_GetWindowSize(interface->window.win, &win_width, &win_height);
    
   display_toolbar(win_width, win_height, interface, mode);
  display_menu_button(win_width, win_height, interface, mode);
  display_help_button(win_width, win_height, interface, mode);
   display_reset_button(win_width, win_height, interface, mode);
   display_generate_button(win_width, win_height, interface);
   display_text_editor(win_width, win_height, interface); 
   
   if (mode == challenge_mode) {
     display_learn_button(win_width, win_height, interface);
     display_previous_button(win_width, win_height, interface);
     display_current_challenge(win_width, win_height, interface);
     display_next_button(win_width, win_height, interface);
   }

  display_dividers(win_width, win_height, interface, mode);  
}


void display_toolbar(int win_width, int win_height, Interface* interface, Mode mode) {
   int toolbar_x, toolbar_y, toolbar_w, toolbar_h;

   toolbar_x = toolbar_y = 0;
   toolbar_h = win_height / BUTTON_HEIGHT;

   if (mode == challenge_mode) {
      toolbar_w = win_width;
   }
   else {
      toolbar_w = win_width / TEXT_ED_WIDTH;
    }

   make_rect(&interface->window, &interface->toolbar, toolbar_x, toolbar_y, 
            toolbar_w, toolbar_h, 200, 200, 200);


}


void display_reset_button(int win_width, int win_height, Interface* interface, Mode mode) {
   int reset_button_x, reset_button_y, reset_button_w, reset_button_h;

   reset_button_x = 0;
   reset_button_w = (win_width / TEXT_ED_WIDTH) / 2;
   reset_button_h = win_height / BUTTON_HEIGHT;
   reset_button_y = win_height - reset_button_h;

   make_rect(&interface->window, &interface->reset_button, reset_button_x, 
            reset_button_y, reset_button_w, reset_button_h, 241, 35, 65);

   if (mode == challenge_mode) {
     make_text(&interface->window, &interface->reset_button.rect, 255, 255, 255, 
            interface->button_font, "    Reset    ");
  }
  else {
    make_text(&interface->window, &interface->reset_button.rect, 255, 255, 255, 
            interface->button_font, "    Clear    ");
  }

  
}

   void display_generate_button(int win_width, int win_height, Interface* interface) {
   int generate_button_x, generate_button_y, generate_button_w, generate_button_h;

   generate_button_x = (win_width / TEXT_ED_WIDTH) / 2;
   generate_button_h = win_height / BUTTON_HEIGHT;
   generate_button_y = win_height - generate_button_h;
   generate_button_w = (win_width / TEXT_ED_WIDTH) / 2 + 1;

   make_rect(&interface->window, &interface->generate_button, generate_button_x, 
            generate_button_y, generate_button_w, generate_button_h, 241, 35, 65);
   make_text(&interface->window, &interface->generate_button.rect, 255, 255, 255, 
            interface->button_font, " Generate ");

} 

void display_canvas(int win_width, int win_height, Interface* interface, Mode mode) {
  int canvas_x, canvas_y, canvas_w, canvas_h;

  canvas_x = win_width / TEXT_ED_WIDTH + 1;
  canvas_w = win_width - win_width / TEXT_ED_WIDTH;

  if (mode == challenge_mode) {
    canvas_y = interface->toolbar.rect.h;
    canvas_h = win_height - interface->toolbar.rect.h;
  }
  else {
    canvas_y = 0;
    canvas_h = win_height;
  }

  make_rect(&interface->window, &interface->canvas, canvas_x, canvas_y, canvas_w,
           canvas_h, 255, 255, 255);
}


/* dependent on challenges mode being active */
void display_menu_button(int win_width, int win_height, Interface* interface, Mode mode) {
   int menu_button_x, menu_button_y, menu_button_w, menu_button_h;

   menu_button_y = 0;
   menu_button_h = interface->toolbar.rect.h - 1;
   menu_button_x = 0;
   if (mode == challenge_mode) {
      menu_button_w = interface->text_editor_panel.rect.w / 3;
    }
    else {
      menu_button_w = interface->text_editor_panel.rect.w / 2;
  }

   make_rect(&interface->window, &interface->menu_button, menu_button_x, 
            menu_button_y, menu_button_w, menu_button_h, 240, 240, 240);

   if (mode == challenge_mode) {
      make_text(&interface->window, &interface->menu_button.rect, 241, 35, 65, 
      interface->button_font, "  Levels  ");
   }
   else {
      make_text(&interface->window, &interface->menu_button.rect, 241, 35, 65, 
      interface->button_font, "      Menu      ");
      
   }
}

void display_learn_button(int win_width, int win_height, Interface* interface) {
   int learn_button_x, learn_button_y, learn_button_w, learn_button_h;

   learn_button_x = interface->menu_button.rect.x + interface->menu_button.rect.w; 
                      
   learn_button_y = 0;
   learn_button_w = interface->menu_button.rect.w;
   learn_button_h = interface->menu_button.rect.h;

   make_rect(&interface->window, &interface->learn_button, learn_button_x, 
            learn_button_y, learn_button_w, learn_button_h, 240, 240, 240);
   make_text(&interface->window, &interface->learn_button.rect, 241, 35, 65, 
            interface->button_font, " Learn ");
   }

void display_help_button(int win_width, int win_height, Interface* interface, Mode mode) {
   int help_button_x, help_button_y, help_button_w, help_button_h;

   if (mode == challenge_mode) {
    help_button_x = interface->learn_button.rect.x + 
                    interface->learn_button.rect.w; 
   }
   else {
    help_button_x = interface->menu_button.rect.x + 
                    interface->menu_button.rect.w + 1;
   }

   help_button_y = 0;
   help_button_w = interface->menu_button.rect.w;
   help_button_h = interface->menu_button.rect.h;

   make_rect(&interface->window, &interface->help_button, help_button_x, 
            help_button_y, help_button_w, help_button_h, 240, 240, 240);

   if (mode == challenge_mode) {
    make_text(&interface->window, &interface->help_button.rect, 241, 35, 65, 
            interface->button_font, "  Help  ");
   }
   else {
    make_text(&interface->window, &interface->help_button.rect, 241, 35, 65, 
            interface->button_font, "     Help     ");
   }
   
}

void display_text_editor(int win_width, int win_height, Interface* interface) {
   int texted_x, texted_y, texted_w, texted_h;

   texted_y = interface->toolbar.rect.h;

   texted_x = 0;
   texted_w = win_width / TEXT_ED_WIDTH;
   texted_h = win_height - interface->toolbar.rect.h - 
              interface->generate_button.rect.h;

   make_rect(&interface->window, &interface->text_editor_panel, texted_x, 
            texted_y, texted_w, texted_h,  43, 43, 39);
}



void display_current_challenge(int win_width, int win_height, Interface* interface) {
   int curr_chall_x, curr_chall_y, curr_chall_w, curr_chall_h;
   char centred_string[MAX_CHALLENGE_LEN];
   text_align_central(centred_string, "CHANGE THE COLOUR VARIABLES");
   //Line 1

   /*
   // not sure about the situation with the level structures
   if (level == beginner->1){
      text_align_central(centred_string, " Create a RED tree fractal! ");
   }
   if (level == beginner->2){
      text_align_central(centred_string, " Create a blue SIERPINSKI fractal that iterates 7 times! ");
   }
   if (level == beginner->3){
      text_align_central(centred_string, " Create a PURPLE SIERPINSKI fractal made of SQUARES that iterates 5 times! ");
   }
   if (level == I1){
      text_align_central(centred_string, " Create a red tree fractal made of CIRCLES, after 2 iterations change the colour to BLUE! ");
   }
   if (level == I2){
      text_align_central(centred_string, " Create a red SIERPINSKI fractal that after 2 iterations changes to GREEN, and after 7 iterations changes to TRIANGLES! ");
   }
   if (level == I3){
      text_align_central(centred_string, " Create a PURPLE tree fractal that after 4 iterations changes to RED, and after 7 iterations changes to PINK CIRCLES! ");
   }
   if (level == E1){
      text_align_central(centred_string, " Create a black Sierpinski fractal made of triangles that iterates 9 times, and turns fuchsia after 3 iterations.");
   }
   if (level == E2){
      text_align_central(centred_string, " Create a brown tree fractal made of lines that iterates 10 times, after 6 iterations change the colour to lime, make the final iteration olive.");
   }
   if (level == E3){
      text_align_central(centred_string, " Create a Sierpinski fractal made of circles that changes from navy -> blue -> turquoise -> white every 2 iterations for 8 iterations. ");
   }
   */


   curr_chall_x = interface->previous_button.rect.x + interface->previous_button.rect.w;
   curr_chall_y = 0;
   curr_chall_w = win_width - (win_width / TEXT_ED_WIDTH) - interface->previous_button.rect.w * 2;
                
   curr_chall_h = interface->menu_button.rect.h;

   make_rect(&interface->window, &interface->current_challenge, curr_chall_x, 
            curr_chall_y, curr_chall_w, curr_chall_h, 240, 240, 240);
  make_rect(&interface->window, &interface->current_challenge_text, curr_chall_x, 
            curr_chall_y + curr_chall_h / 5, curr_chall_w, CHALLENGE_FONT * 1.45, 240, 240, 240);
   make_text(&interface->window, &interface->current_challenge_text.rect, 
            0, 0, 0, interface->challenge_font, centred_string);
 
}

void text_align_central( char centred_string[MAX_CHALLENGE_LEN], char* challenge) {
  int length = strlen(challenge);
  if (length > MAX_CHALLENGE_LEN) {
    printf("Challenge name too long!\n");
    exit(1);
  }

  int difference = MAX_CHALLENGE_LEN - length;

  for (int c = 0; c <= difference / 2; c++) {
  
    centred_string[c] = ' ';
  }
  for (int c = difference / 2, i = 0; c < difference / 2 + length; c++, i++) {
  
    centred_string[c] = challenge[i];
  }
  for (int c = difference / 2 + length; c < MAX_CHALLENGE_LEN; c++) {
  
    centred_string[c] = ' ';
  }
  centred_string[MAX_CHALLENGE_LEN - 1] = '\0';
 
}

void display_next_button(int win_width, int win_height, Interface* interface) {
   int next_button_x, next_button_y, next_button_w, next_button_h;

   next_button_x = interface->current_challenge.rect.x + 
                  interface->current_challenge.rect.w;
   next_button_w = (win_width / TEXT_ED_WIDTH) / PREV_NEXT_BUTTON;
   next_button_h = interface->menu_button.rect.h;
   next_button_y = interface->current_challenge.rect.y;

   make_rect(&interface->window, &interface->next_button, next_button_x, 
            next_button_y, next_button_w, next_button_h, 241, 35, 65);
   make_text(&interface->window, &interface->next_button.rect, 255, 255, 255, 
            interface->button_font, " NEXT ");   
}

void display_previous_button(int win_width, int win_height, Interface* interface) {
   int previous_button_x, previous_button_y, previous_button_w, previous_button_h;

   previous_button_x = interface->text_editor_panel.rect.w + 1;
   previous_button_w = (win_width / TEXT_ED_WIDTH) / PREV_NEXT_BUTTON;
   previous_button_h = interface->menu_button.rect.h;
   previous_button_y = 0;

   make_rect(&interface->window, &interface->previous_button, previous_button_x, 
            previous_button_y, previous_button_w, previous_button_h, 241, 35, 65);
   make_text(&interface->window, &interface->previous_button.rect, 255, 255, 255, 
            interface->button_font, " PREV ");   
}


void make_rect(SDL_Win *win, Area *area, int x, int y, int w, int h, int r, int g, int b) {

   area->rect.w = w;
   area->rect.h = h;
   area->rect.x = x;
   area->rect.y = y;

   area->col.r = r;
   area->col.g = g;
   area->col.b = b;
  
   SDL_SetRenderDrawColor(win->renderer, r, g, b, 255);
   SDL_RenderFillRect(win->renderer, &area->rect);
}

void make_text(SDL_Win *win, SDL_Rect *location, int r, int g, int b, 
               TTF_Font *font, char* text) {
   SDL_Color textcolour = {r,g,b,255};
   SDL_Surface* textsurface = TTF_RenderText_Blended(font, text, textcolour);
   SDL_Texture* texttexture = SurfaceToTexture(textsurface, win);
   SDL_RenderCopy(win->renderer, texttexture, NULL, location);
   SDL_DestroyTexture(texttexture);
}

void make_shape(Shape *shape, int x, int y, int size, int height, float angle) {
  
   shape->x = x;
   shape->y = y;
   shape->size = size;
  
   shape->height = height;
   shape->rotation = angle;

}

/* currently isn't clearing! */
void render_update_clear(SDL_Win window) {
   SDL_RenderPresent(window.renderer);
   SDL_UpdateWindowSurface(window.win);
   //SDL_RenderClear(window.renderer);
}

//loads a bmp to a surface, then converts that surface to a texture and returns it
SDL_Texture* load_image(char* filename, SDL_Win* window) {
    SDL_Surface* image = SDL_LoadBMP(filename); 
    if (image == NULL ) {
        printf( "Unable to load image %s! SDL Error: %s\n", filename, SDL_GetError());
    } 
    return surface_to_texture(image, window) ;
}

//creates a texture from a surface and frees the surface
SDL_Texture* surface_to_texture(SDL_Surface* surface, SDL_Win* window) {
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(window->renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
