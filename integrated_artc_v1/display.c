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
void SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r, int a) {
   for (double dy = 1; dy <= r; dy += 1.0) {
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawLine(rend, cx-dx, cy+r-dy, cx+dx, cy+r-dy);
        SDL_RenderDrawLine(rend, cx-dx, cy-r+dy, cx+dx, cy-r+dy);
   }
}

// Circle centred at (cx,cy) of radius r, see :
// http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles
void SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r, int a) {
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
    SDL_Surface* textsurface = TTF_RenderText_Solid(font, text, textcolour);
    SDL_Texture* texttexture = SurfaceToTexture(textsurface, win);
    SDL_RenderCopy(win->renderer, texttexture, NULL, location);
}

//arguably should be in the draw module (then interface would be able to call the draw module, which wasn't planned
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

  //Text Editor --will become way more complex..
  make_rect(&interface->window, &interface->texteditor, texted_x, texted_y, texted_w, texted_h, 128, 128, 128);
  make_rect(&interface->window, &interface->text_cursor, textcurs_x, textcurs_y, textcurs_w, textcurs_h, 255, 0, 0);

  //Buttons
  make_rect(&interface->window, &interface->gbutton, gbutton_x, gbutton_y, gbutton_w, gbutton_h, 255, 0, 0);
  make_text(&interface->window, &interface->gbutton.rect, 64, 255, 64, interface->font, "GENERATE!");

  make_rect(&interface->window, &interface->ch1button, ch1button_x, ch1button_y, ch1button_w, ch1button_h, 0, 0, 255);
  make_text(&interface->window, &interface->ch1button.rect, 192, 192, 255, interface->font, "Challenge 1");

  //Cursor
}

//Note for the future: if you want to use png images (like an artc logo) look here http://headerphile.com/sdl2/sdl-2-part-7-using-png-files/
