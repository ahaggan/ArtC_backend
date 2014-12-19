#include "input.h"

void update_text_node(TextNode* current, Interface* interface);

void SDL_Win_Init(SDL_Win *w, char* win_name) {
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

//Filled Circle centred at (cx,cy) of radius r
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r) {
   for (double dy = 1; dy <= r; dy += 1.0) {
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawLine(rend, cx-dx, cy+r-dy, cx+dx, cy+r-dy);
        SDL_RenderDrawLine(rend, cx-dx, cy-r+dy, cx+dx, cy-r+dy);
   }
}

//Circle centred at (cx,cy) of radius r
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

TTF_Font* SDL_Load_Font(char* font_path, int font_size) {
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

/* Main Menu */
void display_main_menu(Main_Menu *main_menu) {
  int win_width, win_height;
  SDL_GetWindowSize(main_menu->window.win, &win_width, &win_height);

  display_menu_background(win_width, win_height, main_menu);
  display_logo(win_width, win_height, main_menu);
  display_canvas_button(win_width, win_height, main_menu);
  display_challenges_button(win_width, win_height, main_menu);
  display_options_button(win_width, win_height, main_menu);
  display_quit_button(win_width, win_height, main_menu);
}

void display_menu_background(int win_width, int win_height, Main_Menu* main_menu) {
  int background_x, background_y, background_w, background_h;
  background_x = background_y = 0;
  background_w = win_width;
  background_h = win_height;
  make_rect(&main_menu->window, &main_menu->background, background_x, background_y, background_w, background_h, 200, 200, 200);
}

void display_logo(int win_width, int win_height, Main_Menu* main_menu) {
  int logo_x, logo_y, logo_w, logo_h;
  logo_w = win_width / LOGO_WIDTH;
  logo_x = win_width / LEFT_MARGIN;
  logo_h = win_height / LOGO_HEIGHT;
  logo_y = win_height / TOP_MARGIN;
  make_rect(&main_menu->window, &main_menu->logo, logo_x, logo_y, logo_w, logo_h, 220, 100, 100);
  make_text(&main_menu->window, &main_menu->logo.rect, 245, 245, 245, main_menu->button_font, "Art-C");
}

void display_canvas_button(int win_width, int win_height, Main_Menu* main_menu) {
  int canvas_button_x, canvas_button_y, canvas_button_w, canvas_button_h;
  canvas_button_w = win_width / MENU_BUTTON_WIDTH;
  canvas_button_x = win_width / LEFT_MARGIN;
  canvas_button_h = win_height / MENU_BUTTON_HEIGHT;
  canvas_button_y = (main_menu->logo.rect.y + main_menu->logo.rect.h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&main_menu->window, &main_menu->canvas_button, canvas_button_x, canvas_button_y, canvas_button_w, canvas_button_h, 160, 100, 100);
  make_text(&main_menu->window, &main_menu->canvas_button.rect, 245, 245, 245, main_menu->button_font, "Canvas");
}

void display_challenges_button(int win_width, int win_height, Main_Menu* main_menu) {
  int challenges_button_x, challenges_button_y, challenges_button_w, challenges_button_h;
  challenges_button_w = win_width / MENU_BUTTON_WIDTH;
  challenges_button_x = win_width / LEFT_MARGIN;
  challenges_button_h = win_height / MENU_BUTTON_HEIGHT;
  challenges_button_y = (main_menu->canvas_button.rect.y + main_menu->canvas_button.rect.h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&main_menu->window, &main_menu->challenges_button, challenges_button_x, challenges_button_y, challenges_button_w, challenges_button_h, 160, 100, 100);
  make_text(&main_menu->window, &main_menu->challenges_button.rect, 245, 245, 245, main_menu->button_font, "Challenges");
}

void display_options_button(int win_width, int win_height, Main_Menu* main_menu) {
  int options_button_x, options_button_y, options_button_w, options_button_h;
  options_button_w = win_width / MENU_BUTTON_WIDTH;
  options_button_x = win_width / LEFT_MARGIN;
  options_button_h = win_height / MENU_BUTTON_HEIGHT;
  options_button_y = (main_menu->challenges_button.rect.y + main_menu->challenges_button.rect.h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&main_menu->window, &main_menu->options_button, options_button_x, options_button_y, options_button_w, options_button_h, 160, 100, 100);
  make_text(&main_menu->window, &main_menu->options_button.rect, 245, 245, 245, main_menu->button_font, "Options");
}

void display_quit_button(int win_width, int win_height, Main_Menu* main_menu) {
  int quit_button_x, quit_button_y, quit_button_w, quit_button_h;
  quit_button_w = win_width / MENU_BUTTON_WIDTH;
  quit_button_x = win_width / LEFT_MARGIN;
  quit_button_h = win_height / MENU_BUTTON_HEIGHT;
  quit_button_y = (main_menu->options_button.rect.y + main_menu->options_button.rect.h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&main_menu->window, &main_menu->quit_button, quit_button_x, quit_button_y, quit_button_w, quit_button_h, 100, 90, 90);
  make_text(&main_menu->window, &main_menu->quit_button.rect, 245, 245, 245, main_menu->button_font, "Quit");
}

/* Challenges Menu */
void display_challenges_menu(Main_Menu* main_menu, Challenges_Menu* challenges) {
  int win_width, win_height;
  SDL_GetWindowSize(challenges->window.win, &win_width, &win_height);

  display_challenges_background(win_width, win_height, challenges);
  display_header(win_width, win_height, challenges);
  display_beginner_button(win_width, win_height, challenges);
  display_intermediate_button(win_width, win_height, challenges);
  display_expert_button(win_width, win_height, challenges);
  display_main_menu_button(win_width, win_height, challenges);
}

void display_challenges_background(int win_width, int win_height, Challenges_Menu* challenges) {
  int background_x, background_y, background_w, background_h;
  background_x = background_y = 0;
  background_w = win_width;
  background_h = win_height;
  make_rect(&challenges->window, &challenges->background, background_x, background_y, background_w, background_h, 200, 200, 200);
}

void display_header(int win_width, int win_height, Challenges_Menu* challenges){
  int header_x, header_y, header_w, header_h;
  header_w = win_width / LOGO_WIDTH;
  header_x = win_width / LEFT_MARGIN;
  header_h = win_height / LOGO_HEIGHT;
  header_y = win_height / TOP_MARGIN;
  make_rect(&challenges->window, &challenges->header, header_x, header_y, header_w, header_h, 220, 100, 100);
  make_text(&challenges->window, &challenges->header.rect, 245, 245, 245, challenges->button_font, "Challenges");
}

void display_beginner_button(int win_width, int win_height, Challenges_Menu* challenges) {
  int beginner_x, beginner_y, beginner_w, beginner_h;
  beginner_w = win_width / MENU_BUTTON_WIDTH;
  beginner_x = win_width / LEFT_MARGIN;
  beginner_h = win_height / MENU_BUTTON_HEIGHT;
  beginner_y = (challenges->header.rect.y + challenges->header.rect.h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&challenges->window, &challenges->beginner, beginner_x, beginner_y, beginner_w, beginner_h, 160, 100, 100);
  make_text(&challenges->window, &challenges->beginner.rect, 245, 245, 245, challenges->button_font, "Beginner");
}

void display_intermediate_button(int win_width, int win_height, Challenges_Menu* challenges) {
  int intermediate_x, intermediate_y, intermediate_w, intermediate_h;
  intermediate_w = win_width / MENU_BUTTON_WIDTH;
  intermediate_x = win_width / LEFT_MARGIN;
  intermediate_h = win_height / MENU_BUTTON_HEIGHT;
  intermediate_y = (challenges->beginner.rect.y + challenges->beginner.rect.h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&challenges->window, &challenges->intermediate, intermediate_x, intermediate_y, intermediate_w, intermediate_h, 160, 100, 100);
  make_text(&challenges->window, &challenges->intermediate.rect, 245, 245, 245, challenges->button_font, "Intermediate");
}

void display_expert_button(int win_width, int win_height, Challenges_Menu* challenges) {
  int expert_x, expert_y, expert_w, expert_h;
  expert_w = win_width / MENU_BUTTON_WIDTH;
  expert_x = win_width / LEFT_MARGIN;
  expert_h = win_height / MENU_BUTTON_HEIGHT;
  expert_y = (challenges->intermediate.rect.y + challenges->intermediate.rect.h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&challenges->window, &challenges->expert, expert_x, expert_y, expert_w, expert_h, 160, 100, 100);
  make_text(&challenges->window, &challenges->expert.rect, 245, 245, 245, challenges->button_font, "Expert");
}

void display_main_menu_button(int win_width, int win_height, Challenges_Menu* challenges) {
  int main_menu_x, main_menu_y, main_menu_w, main_menu_h;
  main_menu_w = win_width / MENU_BUTTON_WIDTH;
  main_menu_x = win_width / LEFT_MARGIN;
  main_menu_h = win_height / MENU_BUTTON_HEIGHT;
  main_menu_y = (challenges->expert.rect.y + challenges->expert.rect.h) + (win_height / MENU_BUTTON_DIST);
  make_rect(&challenges->window, &challenges->main_menu, main_menu_x, main_menu_y, main_menu_w, main_menu_h, 100, 90, 90);
  make_text(&challenges->window, &challenges->main_menu.rect, 245, 245, 245, challenges->button_font, "Main Menu");
}

/* Interface */
//this needs a flag sent to it: request either canvas interface or challenge interface
void display_interface(Interface* interface) {
  int win_width, win_height;
  SDL_GetWindowSize(interface->window.win, &win_width, &win_height);
  display_toolbar(win_width, win_height, interface);
  display_menu_button(win_width, win_height, interface, 0);
  display_help_button(win_width, win_height, interface);
  display_reset_button(win_width, win_height, interface);
  display_generate_button(win_width, win_height, interface);
  display_canvas(win_width, win_height, interface);

  //if challenge mode, text editor will need different values.
  display_text_editor(win_width, win_height, interface, 0); 
  display_tutorial_button(win_width, win_height, interface);


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
}

/* void free_text_nodes(TextNode* tail) {
  TextNode* tmp = NULL;
  TextNode* current = tail;
  while (current != NULL) {
    tmp = current;
    printf("debug\n");
    current = current->previous;
    free(tmp);
  } 
}*/

void display_toolbar(int win_width, int win_height, Interface* interface) {
  int toolbar_x, toolbar_y, toolbar_w, toolbar_h;
  toolbar_x = toolbar_y = 0;
  toolbar_w = win_width;
  toolbar_h = win_height / TOOLBAR_HEIGHT; // 10%
  make_rect(&interface->window, &interface->toolbar, toolbar_x, toolbar_y, toolbar_w, toolbar_h, 240,240,240);
}

void display_help_button(int win_width, int win_height, Interface* interface) {
  int help_button_x, help_button_y, help_button_w, help_button_h;
  help_button_x = win_width / HELP_X_SPACE;
  help_button_y = interface->toolbar.rect.h / TOOLBAR_BUTTON_Y;
  help_button_w = interface->menu_button.rect.w;
  help_button_h = interface->menu_button.rect.h;
  make_rect(&interface->window, &interface->help_button, help_button_x, help_button_y, help_button_w, help_button_h, 200, 200, 100);
  make_text(&interface->window, &interface->help_button.rect, 0, 0, 0, interface->button_font, "Help");
}

void display_reset_button(int win_width, int win_height, Interface* interface) {
  int reset_button_x, reset_button_y, reset_button_w, reset_button_h;
  reset_button_x = 0;
  reset_button_w = (win_width / TEXT_ED_WIDTH) / 2;
  reset_button_h = win_height / BOTTOM_BUTTON_HEIGHT;
  reset_button_y = win_height - reset_button_h;
  make_rect(&interface->window, &interface->reset_button, reset_button_x, reset_button_y, reset_button_w, reset_button_h, 200, 100, 100);
  make_text(&interface->window, &interface->reset_button.rect, 0, 0, 0, interface->button_font, "Reset");
}

void display_generate_button(int win_width, int win_height, Interface* interface) {
  int generate_button_x, generate_button_y, generate_button_w, generate_button_h;
  generate_button_x = (win_width / TEXT_ED_WIDTH) / 2;
  generate_button_h = win_height / BOTTOM_BUTTON_HEIGHT;
  generate_button_y = win_height - generate_button_h;
  generate_button_w = (win_width / TEXT_ED_WIDTH) / 2;
  make_rect(&interface->window, &interface->generate_button, generate_button_x, generate_button_y, generate_button_w, generate_button_h, 100, 200, 100);
  make_text(&interface->window, &interface->generate_button.rect, 0, 0, 0, interface->button_font, "Generate");

} 

void display_canvas(int win_width, int win_height, Interface* interface) {
  int canvas_x, canvas_y, canvas_w, canvas_h;
  canvas_x = win_width / TEXT_ED_WIDTH;
  canvas_y = interface->toolbar.rect.h;
  canvas_w = win_width - win_width / TEXT_ED_WIDTH;
  canvas_h = win_height - interface->toolbar.rect.h;
  make_rect(&interface->window, &interface->canvas, canvas_x, canvas_y, canvas_w, canvas_h, 255, 255, 255);
}

/* dependent on challenges mode being active */

void display_menu_button(int win_width, int win_height, Interface* interface, int mode) {
  int menu_button_x, menu_button_y, menu_button_w, menu_button_h;
  
  menu_button_x = win_width / MENU_X_SPACE; // 2%
  menu_button_y = interface->toolbar.rect.h / TOOLBAR_BUTTON_Y; // 25%
  menu_button_w = win_width / TOOLBAR_BUTTON_WIDTH ; // 10%
  menu_button_h = interface->toolbar.rect.h / TOOLBAR_BUTTON_HEIGHT ; //5 %
  make_rect(&interface->window, &interface->menu_button, menu_button_x, menu_button_y, menu_button_w, menu_button_h, 100, 100, 100);

  if (mode == 0) {
    make_text(&interface->window, &interface->menu_button.rect, 0, 0, 0, interface->button_font, "Menu");
  }
  else if (mode == 1) {
    make_text(&interface->window, &interface->menu_button.rect, 0, 0, 0, interface->button_font, "Challenges");
  }
}

void display_text_editor(int win_width, int win_height, Interface* interface, int mode) {
  int texted_x, texted_y, texted_w, texted_h;
  if (mode == 0) {
    texted_x = 0;
    texted_y = interface->toolbar.rect.h;
    texted_w = win_width / TEXT_ED_WIDTH;
    texted_h = win_height - interface->toolbar.rect.h - interface->generate_button.rect.h;
    make_rect(&interface->window, &interface->text_editor_panel, texted_x, texted_y, texted_w, texted_h, 255, 255, 255);
  }
}

void display_current_challenge(){
}

void display_next_button(){
}

void display_tutorial_button(int win_width, int win_height, Interface* interface) {
  int tutorial_button_x, tutorial_button_y, tutorial_button_w, tutorial_button_h;
  tutorial_button_x = interface->menu_button.rect.x + interface->menu_button.rect.w + win_width / MENU_X_SPACE; // 2%
  tutorial_button_y = interface->toolbar.rect.h / TOOLBAR_BUTTON_Y; // 25%
  tutorial_button_w = win_width / TOOLBAR_BUTTON_WIDTH ; // 10%
  tutorial_button_h = interface->toolbar.rect.h / TOOLBAR_BUTTON_HEIGHT ; //5 %
  make_rect(&interface->window, &interface->tutorial_button, tutorial_button_x, tutorial_button_y, tutorial_button_w, tutorial_button_h, 150, 100, 150);
  make_text(&interface->window, &interface->tutorial_button.rect, 0, 0, 0, interface->button_font, "Tutorial");
}

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

void render_update_clear(SDL_Win window) {
  SDL_RenderPresent(window.renderer);
  SDL_UpdateWindowSurface(window.win);
  SDL_RenderClear(window.renderer);
}

/* TEXT EDITOR*/
//Initialises a blank text editor with the supplied dimensions
void make_text_editor(int width, int height, Interface* interface) {
   TextNode* current = NULL;
   Coordinates curr;
   for (int row = 0; row < height; row++) {
      for (int column = 0; column < width; column++) {   
         curr.row = row;
         curr.column = column;  
         current = make_cell(width, height, curr, interface, interface->text_editor, current);
      }
   }
}

//creates varying text cells based on where the cell lies on the text grid
TextNode* make_cell(int width, int height, Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current) {
  if (first_cell(curr)) {
    make_first_cell(curr, interface, text_editor, current);
  }
  else if (!last_cell(curr, *interface)) {
    make_middle_cells(curr, interface, text_editor, current);
  }
  else {
    make_last_cell(curr, interface, text_editor, current);
  }
  return &text_editor[curr.row][curr.column];
}

void make_first_cell(Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current) {
  text_editor[curr.row][curr.column] = *allocate_text_node(EMPTY_CELL, current, interface, curr.row, curr.column);
  text_editor[curr.row][curr.column].next = &interface->text_editor[0][curr.column+1];  
  set_active_text_cell(curr.row, curr.column, interface);
}

void make_middle_cells(Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current) {
  text_editor[curr.row][curr.column] = *allocate_text_node(EMPTY_CELL, current, interface, curr.row, curr.column);
  //if the text cell is in the final column, its next link is the first cell of the next row
  if (end_column(curr, *interface)) {
     text_editor[curr.row][curr.column].next = &interface->text_editor[curr.row+1][0];  
  }
  //otherwise, the next link is the next cell in the row
  else {
    text_editor[curr.row][curr.column].next = &interface->text_editor[curr.row][curr.column + 1];
  }
}

void make_last_cell(Coordinates curr, Interface* interface, TextNode text_editor[EDITOR_ROWS][EDITOR_COLUMNS], TextNode* current) {
  text_editor[curr.row][curr.column] = *allocate_text_node(EMPTY_CELL, current, interface, curr.row, curr.column);
  text_editor[curr.row][curr.column].next = NULL;
}

//Reforms the text editor based on user input
void update_text_editor(int width, int height, Interface* interface) {
  TextNode* current = &interface->text_editor[0][0];
  while (current != NULL) {
      update_text_node(current, interface);
      current = current->next;
  }
  make_rect(&interface->window, &interface->text_cursor, interface->text_editor_panel.rect.x + (interface->active_txt.column * (FONT_SIZE- 6)), interface->text_editor_panel.rect.y + (interface->active_txt.row * (FONT_SIZE + 9.1)), 3, (FONT_SIZE + 4), 240, 240, 240);
}

TextNode* allocate_text_node(char* c, TextNode* previous_node, Interface* interface, int row, int column) {
  TextNode* new_node = (TextNode *)malloc(sizeof(TextNode));
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

  new_node->location.row = y;
  new_node->location.column = x;
  new_node->w = box_w;
  new_node->h = box_h;

  new_node->previous = previous_node;

  make_rect(&interface->window, &interface->text_editor[row][column].box, x, y, box_w, box_h, 43, 43, 39);
  /* if there's no character to render, skip make_text */
  if (strcmp(new_node->character, EMPTY_CELL) != 0) {
     make_text(&interface->window, &interface->text_editor[row][column].box.rect, 240, 240, 240, interface->font, new_node->character);
  }
  return new_node;
}


void update_text_node(TextNode* current, Interface* interface) {
  make_rect(&interface->window, &current->box, current->location.column, current->location.row, current->w, current->h, 43, 43, 39);
  /* if there's no character to render, skip make_text */
  if (strcmp(current->character, EMPTY_CELL) != 0) {
    make_text(&interface->window, &current->box.rect, 240, 240, 240, interface->font, current->character);
  }
}
