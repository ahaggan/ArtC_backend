//Keep all 'display' information within the display module. Pass around a display object.
#include "input.h"

void SDL_Win_Init(SDL_Win *w, char win_name[20]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    } 
    w->finished = 0;
   
    w->win= SDL_CreateWindow(win_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (w->win == NULL) {
        fprintf(stderr, "\nUnable to initialize SDL Win:  %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    //SDL_CreateRenderer(window that the renderer will be attached to, which rendering driver to use (-1 means first we find),
    w->renderer = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if (w->renderer == NULL) {
        fprintf(stderr, "\nUnable to initialize SDL Renderer: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
  
    // Set resolution (size) of renderer to the same as window
    SDL_RenderSetLogicalSize(w->renderer, WIN_WIDTH, WIN_HEIGHT); 
    SDL_SetWindowMinimumSize(w->win, MIN_WIDTH, MIN_HEIGHT);

    //Set screen to white
    SDL_SetRenderDrawColor(w->renderer, 255, 255, 255, 255);
    
    //call RenderClear at the beginning on every frame to clear the screen and make it ready for more stuff.
    SDL_RenderClear(w->renderer);

    //call RenderPresent to make the drawing take effect.
    SDL_RenderPresent(w->renderer);

}

void clear_area(SDL_Win *window, Area area) {
    SDL_SetRenderDrawColor(window->renderer, area.colour.r, area.colour.g, area.colour.b, 255);
    SDL_RenderFillRect(window->renderer, &area.rect);
}

// Filled Circle centred at (cx,cy) of radius r, see :
// http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r) {
   for (double dy = 1; dy <= r; dy += 1.0) {
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawLine(rend, cx-dx, cy+r-dy, cx+dx, cy+r-dy);
        SDL_RenderDrawLine(rend, cx-dx, cy-r+dy, cx+dx, cy-r+dy);
   }
}

// Circle centred at (cx,cy) of radius r, see :
// http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r) {
   double dx, dy;
   dx = floor(sqrt((2.0 * r ) ));
   SDL_RenderDrawLine(rend, cx-dx, cy+r, cx+dx, cy+r);
   SDL_RenderDrawLine(rend, cx-dx, cy-r, cx+dx, cy-r);
   for (dy = 1; dy <= r; dy += 1.0) {
        dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawPoint(rend, cx+dx, cy+r-dy);
        SDL_RenderDrawPoint(rend, cx+dx, cy-r+dy);
        SDL_RenderDrawPoint(rend, cx-dx, cy+r-dy);
        SDL_RenderDrawPoint(rend, cx-dx, cy-r+dy);
   }
}

void SDL_TTF_Init() {
    if (TTF_Init() != 0) {
        fprintf(stderr, "\nUnable to initialize TTF:  %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
}

TTF_Font* SDL_Load_Font(char font_path[30], int font_size) {
    TTF_Font *font = TTF_OpenFont(font_path, font_size);
    if (font == NULL) {
        fprintf(stderr, "\nTTF_OpenFont could not open the font:  %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    return font;
}

SDL_Texture* SurfaceToTexture(SDL_Surface* surface, SDL_Win* w) {
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(w->renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}


void SDL_TTF_Quit(TTF_Font *font) {
    TTF_CloseFont(font);
    TTF_Quit();
}

void make_text_editor(int width, int height, Interface* interface) {
  TextNode* current = NULL;
  for (int row = 0; row < height; row++) {
    for (int column = 0; column < width; column++) {
      //cell 0 = start
      if (row == 0 && column == 0) {
        interface->text_editor[row][column] = *allocate_text_node(EMPTY_CELL, current, interface, row, column); //1 = current text input
        interface->text_editor[row][column].next = &interface->text_editor[0][column+1];  
      }
      else if (!(row == (height - 1) && column == (width -1))) {
        interface->text_editor[row][column] = *allocate_text_node(EMPTY_CELL, current, interface, row, column);

        if (column == width - 1) {
      
          interface->text_editor[row][column].next = &interface->text_editor[row+1][0];  
        }
        else {
          interface->text_editor[row][column].next = &interface->text_editor[row][column + 1];
        }
 
      }
      else {
        interface->text_editor[row][column] = *allocate_text_node(EMPTY_CELL, current, interface, row, column);
        interface->text_editor[row][column].next = NULL;
      }
      current = &interface->text_editor[row][column];
        
    }
  
  }
  interface->active_txt.row = 0;
  interface->active_txt.column = 0;
   
}

void update_text_editor(int width, int height, Interface* interface) {
  TextNode* current = NULL;
  
 for (int row = 0; row < height; row++) {
    for (int column = 0; column < width; column++) {
      //final cell

      if (!(row == (height - 1) && column == (width -1))) {
        interface->text_editor[row][column] = *allocate_text_node(interface->text_editor[row][column].character, current, interface, row, column);
        if (column == width - 1) {
          interface->text_editor[row][column].next = &interface->text_editor[row+1][0];  
        }
        else {
          interface->text_editor[row][column].next = &interface->text_editor[row][column + 1];
        }
      }
      else {
        interface->text_editor[row][column] = *allocate_text_node(interface->text_editor[row][column].character, current, interface, row, column);
        interface->text_editor[row][column].next = NULL;
      }
      current = &interface->text_editor[row][column];
    }
  }

   make_rect(&interface->window, &interface->text_cursor, interface->text_editor_panel.rect.x + (interface->active_txt.column * (FONT_SIZE- 6)), interface->text_editor_panel.rect.y + (interface->active_txt.row * (FONT_SIZE + 9.1)), 3, (FONT_SIZE + 4), 240, 240, 240);
 

}

void draw_interface(Interface *interface) {
  int win_width, win_height;
  int menu_x, menu_y, menu_w, menu_h;
  int menu_bottom_x, menu_bottom_y, menu_bottom_w, menu_bottom_h;
  int texted_x, texted_y, texted_w, texted_h;
  int canvas_x, canvas_y, canvas_w, canvas_h;
  int generate_button_x, generate_button_y, generate_button_w, generate_button_h;
  int menu_button_x, menu_button_y, menu_button_w, menu_button_h;
  int reset_button_x, reset_button_y, reset_button_w, reset_button_h;
  
  int help_button_x, help_button_y, help_button_w, help_button_h;

  SDL_GetWindowSize(interface->window.win, &win_width, &win_height);

  /* Top toolbar/ menu */
  menu_x = menu_y = 0;
  menu_w = win_width;
  menu_w = win_width;
  menu_h = win_height / TOOLBAR_HEIGHT; // 10%

  /* Home button */
  menu_button_x = win_width / HOME_X_SPACE; // 2%
  menu_button_y = menu_h / TOOLBAR_BUTTON_Y; // 25%
  menu_button_w = win_width / TOOLBAR_BUTTON_WIDTH ; // 10%
  menu_button_h = menu_h / TOOLBAR_BUTTON_HEIGHT ; //5 %

  help_button_x = win_width / HELP_X_SPACE;
  help_button_y = menu_h / TOOLBAR_BUTTON_Y;
  help_button_w = menu_button_w;
  help_button_h = menu_button_h;

  /* Bottom reset/generate toolbar */
  menu_bottom_x = 0;
  menu_bottom_w = win_width / TEXT_ED_WIDTH;
  menu_bottom_h = win_height / BOTTOM_TOOLBAR_HEIGHT; // 10%
  menu_bottom_y = win_height - menu_bottom_h;

  generate_button_x = menu_bottom_w / 2;
  generate_button_y = menu_bottom_y;
  generate_button_w = menu_bottom_w / 2;
  generate_button_h = menu_button_h;
  
  reset_button_x = 0;
  reset_button_y = menu_bottom_y;
  reset_button_w = menu_bottom_w / 2;
  reset_button_h = menu_button_h;

  canvas_x = menu_bottom_w;
  canvas_y = menu_h;
  canvas_w = win_width - menu_bottom_w;
  canvas_h = win_height - menu_h;
  /* Interface components exclusive to challenge mode: */

  /* Challenges button 
  _button_x = win_width / _X_SPACE; // 2%
  _button_y = menu_h / _Y_SPACE; // 25%
  _button_w = win_width / _WIDTH ; // 10%
  _button_h = win_height / _HEIGHT ; //5 %  

  Tutorial button 
  _button_x = win_width / _X_SPACE; // 2%
  _button_y = menu_h / _Y_SPACE; // 25%
  _button_w = win_width / _WIDTH ; // 10%
  _button_h = win_height / _HEIGHT ; //5 %  

  Current Challenge Description

  Next Challenge button
  */

  texted_x = 0;

  texted_y = menu_h;
  texted_w = win_width / 2;
  texted_h = win_height - menu_h - 25;


  //Text Editor
  make_rect(&interface->window, &interface->text_editor_panel, texted_x, texted_y, texted_w, texted_h, 255, 255, 255);

  //Panels
  make_rect(&interface->window, &interface->canvas, canvas_x, canvas_y, canvas_w, canvas_h, 255, 255, 255);
  make_rect(&interface->window, &interface->menubar, menu_x, menu_y, menu_w, menu_h, 240,240,240);
  make_rect(&interface->window, &interface->menu_bottom, menu_bottom_x, menu_bottom_y, menu_bottom_w, menu_bottom_h, 240,240,240);

 
  //load a different font for the buttons.

  //Buttons
  make_rect(&interface->window, &interface->generate_button, generate_button_x, generate_button_y, generate_button_w, generate_button_h, 100, 200, 100);
  make_text(&interface->window, &interface->generate_button.rect, 0, 0, 0, interface->button_font, "Generate");

  make_rect(&interface->window, &interface->reset_button, reset_button_x, reset_button_y, reset_button_w, reset_button_h, 200, 100, 100);
  make_text(&interface->window, &interface->reset_button.rect, 0, 0, 0, interface->button_font, "Reset");

  make_rect(&interface->window, &interface->menu_button, menu_button_x, menu_button_y, menu_button_w, menu_button_h, 100, 100, 100);
  make_text(&interface->window, &interface->menu_button.rect, 0, 0, 0, interface->button_font, "Menu");

  make_rect(&interface->window, &interface->help_button, help_button_x, help_button_y, help_button_w, help_button_h, 200, 200, 100);
  make_text(&interface->window, &interface->help_button.rect, 0, 0, 0, interface->button_font, "Help");
}

 
TextNode* allocate_text_node(char* c, TextNode* previous_node, Interface* interface, int row, int column) {
  TextNode* new_node = (TextNode *)malloc(sizeof(TextNode));
  TextNode* tmp = new_node;
  int box_w = (FONT_SIZE- 6);
  int box_h =  (FONT_SIZE + 9);
 
  int x = (interface->text_editor_panel.rect.x + (column * box_w));
  int y = (interface->text_editor_panel.rect.y + (row * box_h));

  if (new_node == NULL) {
    printf("Cannot Allocate Node\n");
    exit(2);
  }

  new_node->text_cell.row = row;
  new_node->text_cell.column = column;
  strcpy(new_node->character, c);

  new_node->previous = previous_node;

  make_rect(&interface->window, &interface->text_editor[row][column].box, x, y, box_w, box_h, 43, 43, 39);
  if (strcmp(new_node->character, EMPTY_CELL) == 0) {
    free(tmp);
    return new_node;
  }
  else {
    make_text(&interface->window, &interface->text_editor[row][column].box.rect, 240, 240, 240, interface->font, new_node->character);
  }
  free(tmp);
  return new_node;
}

/*
void free_text_nodes(TextNode* tail) {
  TextNode* tmp = NULL;
  TextNode* current = tail;
  while (current != NULL) {
    tmp = current;
    printf("debug\n");
    current = current->previous;
    free(tmp);
  } 
}
*/


void make_rect(SDL_Win *win, Area *area, int x, int y, int w, int h, int r, int g, int b) {
  area->rect.w = w;
  area->rect.h = h;
  area->rect.x = x;
  area->rect.y = y;
  area->colour.r = r;
  area->colour.g = g;
  area->colour.b = b;
  SDL_SetRenderDrawColor(win->renderer, r, g, b, 255);
  SDL_RenderFillRect(win->renderer, &area->rect);
}

void make_text(SDL_Win *win, SDL_Rect *location, int r, int g, int b, TTF_Font *font, char* text) {
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

void print_composition(TextNode* start) {
  TextNode* current = start;
  char str[2000];
  while (current != NULL) {
    strcat(str, current->character);
    current = current->next;
  }
  printf("%s\n", str);
}

void draw_main_menu(Main_Menu *main_menu) {
  int win_width, win_height;
  int background_x, background_y, background_w, background_h;
  int logo_x, logo_y, logo_w, logo_h;
  int canvas_button_x, canvas_button_y, canvas_button_w, canvas_button_h;
  int challenges_button_x, challenges_button_y, challenges_button_w, challenges_button_h;
  int options_button_x, options_button_y, options_button_w, options_button_h;
  int quit_button_x, quit_button_y, quit_button_w, quit_button_h;

  SDL_GetWindowSize(main_menu->window.win, &win_width, &win_height);

  background_x = background_y = 0;
  background_w = win_width;
  background_h = win_height;
  make_rect(&main_menu->window, &main_menu->background, background_x, background_y, background_w, background_h, 200, 200, 200);

  
  logo_w = win_width / LOGO_WIDTH;
  logo_x = win_width / LEFT_MARGIN;
  logo_h = win_height / LOGO_HEIGHT;
  logo_y = win_height / TOP_MARGIN;
  make_rect(&main_menu->window, &main_menu->logo, logo_x, logo_y, logo_w, logo_h, 220, 100, 100);
  make_text(&main_menu->window, &main_menu->logo.rect, 245, 245, 245, main_menu->button_font, "Art-C");

  canvas_button_w = win_width / MENU_BUTTON_WIDTH;
  canvas_button_x = win_width / LEFT_MARGIN;
  canvas_button_h = win_height / MENU_BUTTON_HEIGHT;
  canvas_button_y = (logo_y + logo_h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&main_menu->window, &main_menu->canvas_button, canvas_button_x, canvas_button_y, canvas_button_w, canvas_button_h, 160, 100, 100);
  make_text(&main_menu->window, &main_menu->canvas_button.rect, 245, 245, 245, main_menu->button_font, "Canvas");

  challenges_button_w = win_width / MENU_BUTTON_WIDTH;
  challenges_button_x = win_width / LEFT_MARGIN;
  challenges_button_h = win_height / MENU_BUTTON_HEIGHT;
  challenges_button_y = (canvas_button_y + canvas_button_h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&main_menu->window, &main_menu->challenges_button, challenges_button_x, challenges_button_y, challenges_button_w, challenges_button_h, 160, 100, 100);
  make_text(&main_menu->window, &main_menu->challenges_button.rect, 245, 245, 245, main_menu->button_font, "Challenges");

  options_button_w = win_width / MENU_BUTTON_WIDTH;
  options_button_x = win_width / LEFT_MARGIN;
  options_button_h = win_height / MENU_BUTTON_HEIGHT;
  options_button_y = (challenges_button_y + challenges_button_h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&main_menu->window, &main_menu->options_button, options_button_x, options_button_y, options_button_w, options_button_h, 160, 100, 100);
  make_text(&main_menu->window, &main_menu->options_button.rect, 245, 245, 245, main_menu->button_font, "Options");

  quit_button_w = win_width / MENU_BUTTON_WIDTH;
  quit_button_x = win_width / LEFT_MARGIN;
  quit_button_h = win_height / MENU_BUTTON_HEIGHT;
  quit_button_y = (options_button_y + options_button_h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&main_menu->window, &main_menu->quit_button, quit_button_x, quit_button_y, quit_button_w, quit_button_h, 100, 90, 90);
  make_text(&main_menu->window, &main_menu->quit_button.rect, 245, 245, 245, main_menu->button_font, "Quit");
}


void draw_challenges_menu(Main_Menu* main_menu, Challenges_Menu* challenges) {
  int win_width, win_height;
  int background_x, background_y, background_w, background_h;
  int header_x, header_y, header_w, header_h;
  int beginner_x, beginner_y, beginner_w, beginner_h;
  int intermediate_x, intermediate_y, intermediate_w, intermediate_h;
  int expert_x, expert_y, expert_w, expert_h;
  int main_menu_x, main_menu_y, main_menu_w, main_menu_h;

  SDL_GetWindowSize(challenges->window.win, &win_width, &win_height);

  background_x = background_y = 0;
  background_w = win_width;
  background_h = win_height;
  make_rect(&challenges->window, &challenges->background, background_x, background_y, background_w, background_h, 200, 200, 200);

  
  header_w = win_width / LOGO_WIDTH;
  header_x = win_width / LEFT_MARGIN;
  header_h = win_height / LOGO_HEIGHT;
  header_y = win_height / TOP_MARGIN;
  make_rect(&challenges->window, &challenges->header, header_x, header_y, header_w, header_h, 220, 100, 100);
  make_text(&challenges->window, &challenges->header.rect, 245, 245, 245, challenges->button_font, "Challenges");

  beginner_w = win_width / MENU_BUTTON_WIDTH;
  beginner_x = win_width / LEFT_MARGIN;
  beginner_h = win_height / MENU_BUTTON_HEIGHT;
  beginner_y = (header_y + header_h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&challenges->window, &challenges->beginner, beginner_x, beginner_y, beginner_w, beginner_h, 160, 100, 100);
  make_text(&challenges->window, &challenges->beginner.rect, 245, 245, 245, challenges->button_font, "Beginner");

  intermediate_w = win_width / MENU_BUTTON_WIDTH;
  intermediate_x = win_width / LEFT_MARGIN;
  intermediate_h = win_height / MENU_BUTTON_HEIGHT;
  intermediate_y = (beginner_y + beginner_h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&challenges->window, &challenges->intermediate, intermediate_x, intermediate_y, intermediate_w, intermediate_h, 160, 100, 100);
  make_text(&challenges->window, &challenges->intermediate.rect, 245, 245, 245, challenges->button_font, "Intermediate");

  expert_w = win_width / MENU_BUTTON_WIDTH;
  expert_x = win_width / LEFT_MARGIN;
  expert_h = win_height / MENU_BUTTON_HEIGHT;
  expert_y = (intermediate_y + intermediate_h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&challenges->window, &challenges->expert, expert_x, expert_y, expert_w, expert_h, 160, 100, 100);
  make_text(&challenges->window, &challenges->expert.rect, 245, 245, 245, challenges->button_font, "Expert");

  main_menu_w = win_width / MENU_BUTTON_WIDTH;
  main_menu_x = win_width / LEFT_MARGIN;
  main_menu_h = win_height / MENU_BUTTON_HEIGHT;
  main_menu_y = (expert_y + expert_h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&challenges->window, &challenges->main_menu, main_menu_x, main_menu_y, main_menu_w, main_menu_h, 100, 90, 90);
  make_text(&challenges->window, &challenges->main_menu.rect, 245, 245, 245, challenges->button_font, "Main Menu");
}






