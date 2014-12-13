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
   make_rect(&interface->window, &interface->text_cursor, (interface->text_editor_panel.rect.x + (interface->active_txt.column * (FONT_SIZE - FONT_SIZE / 2.5))), (interface->text_editor_panel.rect.y + (  interface->active_txt.row * (FONT_SIZE * 1.6))) + 3, (FONT_SIZE - FONT_SIZE / 2.8) /5, (FONT_SIZE * 1.6) - 8, 240, 240, 240);
 

}

void draw_interface(Interface *interface) {
  int x, y;
  int menu_x, menu_y, menu_w, menu_h;
  int texted_x, texted_y, texted_w, texted_h;
  int canvas_x, canvas_y, canvas_w, canvas_h;
  int gbutton_x, gbutton_y, gbutton_w, gbutton_h;
  int ch1button_x, ch1button_y, ch1button_w, ch1button_h;
  int textcurs_x, textcurs_y, textcurs_w, textcurs_h;

  SDL_GetWindowSize(interface->window.win, &x, &y);

  menu_x = menu_y = texted_x = gbutton_x = 0;
  menu_w = x;
  menu_h = y / MENU_OFFSET;

  texted_y = canvas_y = menu_h;
  texted_w = canvas_x = canvas_w = x / 2;
  texted_h = canvas_h = y - menu_h - 25;

  gbutton_y = y - 25;
  gbutton_w = x / 10;
  gbutton_h = 25;

  ch1button_x = 5;
  ch1button_y = 5;
  ch1button_w = 100;
  ch1button_h = 40;

  textcurs_x = texted_x;
  textcurs_y = texted_y + FONT_SIZE / 10;
  textcurs_w = FONT_SIZE / 10;
  textcurs_h = FONT_SIZE;

  //Panels
  make_rect(&interface->window, &interface->menubar, menu_x, menu_y, menu_w, menu_h, 255, 64, 64);
  make_rect(&interface->window, &interface->canvas, canvas_x, canvas_y, canvas_w, canvas_h, 255, 255, 255);

  //Text Editor
  make_rect(&interface->window, &interface->text_editor_panel, texted_x, texted_y, texted_w, texted_h, 255, 255, 255);
 
  //Buttons
  make_rect(&interface->window, &interface->gbutton, gbutton_x, gbutton_y, gbutton_w, gbutton_h, 255, 0, 0);
  make_text(&interface->window, &interface->gbutton.rect, 64, 255, 64, interface->font, "GENERATE!");

  make_rect(&interface->window, &interface->ch1button, ch1button_x, ch1button_y, ch1button_w, ch1button_h, 0, 0, 255);
  make_text(&interface->window, &interface->ch1button.rect, 192, 192, 255, interface->font, "Challenge 1");
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


void make_shape(Shape *shape, int x, int y, int size, int height) {
    shape->x = x;
    shape->y = y;
    shape->size = size;
    shape->height = height;
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
//Note for the future: if you want to use png images (like an artc logo) look here http://headerphile.com/sdl2/sdl-2-part-7-using-png-files/
