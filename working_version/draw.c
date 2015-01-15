#include "draw.h"

void draw_sdl(Interface interface, Draw *fractal, int x, int y, int size, float angle, int i) 
{
    if(strcmp(fractal->colour[i-1], "random") == 0) {
        switch(rand()%COLOUR_SIZE) {
            case 0 : strcpy(fractal->colour[i-1], "black"); break;
            case 1 : strcpy(fractal->colour[i-1], "red"); break;
            case 2 : strcpy(fractal->colour[i-1], "pink"); break;
            case 3 : strcpy(fractal->colour[i-1], "fuchsia"); break;
            case 4 : strcpy(fractal->colour[i-1], "purple"); break;
            case 5 : strcpy(fractal->colour[i-1], "blue"); break;
            case 6 : strcpy(fractal->colour[i-1], "navy"); break;
            case 7 : strcpy(fractal->colour[i-1], "turquoise"); break;
            case 8 : strcpy(fractal->colour[i-1], "green"); break;
            case 9 : strcpy(fractal->colour[i-1], "lime"); break;
            case 10: strcpy(fractal->colour[i-1], "yellow"); break;
            case 11: strcpy(fractal->colour[i-1], "olive"); break;
            case 12: strcpy(fractal->colour[i-1], "gold"); break;
            case 13: strcpy(fractal->colour[i-1], "orange"); break;
            case 14: strcpy(fractal->colour[i-1], "grey"); break;
            case 15: strcpy(fractal->colour[i-1], "brown"); break;
            case 16: strcpy(fractal->colour[i-1], "white"); break;
        }
    }

    if (strcmp(fractal->colour[i-1], "black") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 0, 0, 0, 255);
    }

    else if (strcmp(fractal->colour[i-1], "red") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 255, 0, 0, 255);
    }

    else if (strcmp(fractal->colour[i-1], "pink") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 255, 192, 203, 255);
    }
        
    else if (strcmp(fractal->colour[i-1], "fuchsia") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 255, 0, 255, 255);
    }
    
    else if (strcmp(fractal->colour[i-1], "purple") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 128, 0, 128, 255);
    }

    else if (strcmp(fractal->colour[i-1], "blue") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 0, 0, 255, 255);
    }

    else if (strcmp(fractal->colour[i-1], "navy") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 0, 0, 128, 255);
    }

    else if (strcmp(fractal->colour[i-1], "turquoise") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 64, 224, 208, 255);
    }

    else if (strcmp(fractal->colour[i-1], "green") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 0, 255, 0, 255);
    }

    else if (strcmp(fractal->colour[i-1], "lime") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 173, 255, 47, 255);
    }

    else if (strcmp(fractal->colour[i-1], "yellow") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 255, 255, 0, 255);
    }

    else if (strcmp(fractal->colour[i-1], "olive") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 128, 128, 0, 255);
    }

    else if (strcmp(fractal->colour[i-1], "gold") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 240, 205, 17, 255);
    }

    else if (strcmp(fractal->colour[i-1], "orange") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 255, 165, 0, 255);
    }

     else if (strcmp(fractal->colour[i-1], "grey") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 128, 128, 128, 255);
    }

    else if (strcmp(fractal->colour[i-1], "brown") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 120, 30, 30, 255);
    }

    else if (strcmp(fractal->colour[i-1], "white") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 240, 240, 240, 255);
    }

    else if (strcmp(fractal->colour[i-1], "random") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, rand(), rand(), rand(), 255);
    }

    if(strcmp(fractal->shape[i-1], "random") == 0) {
        switch(rand()%4) {
            case 0 : strcpy(fractal->shape[i-1], "square"); break;
            case 1 : strcpy(fractal->shape[i-1], "circle"); break;
            case 2 : strcpy(fractal->shape[i-1], "line"); break;
            case 3 : strcpy(fractal->shape[i-1], "triangle"); break;
        }
    }

    if (strcmp(fractal->shape[i-1], "square") == 0) {
        int x1 = x-(size*sin(angle)/2);
        int y1 = y+(size*cos(angle)/2);
        int x2 = x+(size*sin(angle)/2);
        int y2 = y-(size*cos(angle)/2);
        SDL_Line(interface.window.renderer, x1, y1, x2, y2, size, angle);
    }

    else if (strcmp(fractal->shape[i-1], "circle") == 0) {
        SDL_RenderFillCircle(interface.window.renderer, x, y, size/2);
    }

    else if (strcmp(fractal->shape[i-1], "line") == 0) {
        int x1 = x-(size*sin(angle));
        int y1 = y+(size*cos(angle));
        int x2 = x+(size*sin(angle));
        int y2 = y-(size*cos(angle));

        SDL_Line(interface.window.renderer, x1, y1, x2, y2, 
                          fractal->linethickness[i-1], angle);
    }

    else if(strcmp(fractal->shape[i-1], "triangle") == 0) {
        int c1x = x+((size/2.0)*sin(angle));
        int c1y = y-((size/2.0)*cos(angle));
        int c2x = x+((size/2.0)*sin(angle+(M_PI*(2.0/3.0))));
        int c2y = y-((size/2.0)*cos(angle+(M_PI*(2.0/3.0))));
        int c3x = x+((size/2.0)*sin(angle-(M_PI*(2.0/3.0))));
        int c3y = y-((size/2.0)*cos(angle-(M_PI*(2.0/3.0))));

        SDL_RenderDrawLine(interface.window.renderer, c1x, c1y, c2x, c2y);
        SDL_RenderDrawLine(interface.window.renderer, c2x, c2y, c3x, c3y);
        SDL_RenderDrawLine(interface.window.renderer, c3x, c3y, c1x, c1y);
    }

    else if(strcmp(fractal->shape[i-1], "image") == 0) {
        int image_x, image_y, image_w, image_h;
        SDL_Texture* image = load_image("ashley_head", &interface.window);
        Area img;

        image_x = x - (size/2);
        image_y = y - (size/2);
        image_w = image_h = 150;

        make_rect(&interface.window, &img, image_x, image_y, image_w, image_h, 0, 0, 0);

        SDL_RenderCopy(interface.window.renderer, image, 
                         NULL, &img.rect);
        SDL_DestroyTexture(image); 
    }
}

void SDL_Line(SDL_Renderer* renderer, int xs, int ys, int xe, int ye, int thickness, float angle)
{
    float i1=xs, i2=xe;
    float j1 = ys + (-(thickness/2.0)*sin(angle));
    float j2 = ye + (-(thickness/2.0)*sin(angle));
    for(float i=-(thickness/2.0); i<thickness/2.0; i+=1.0) {
        i1 = xs + (i*cos(angle));
        i2 = xe + (i*cos(angle));
        SDL_RenderDrawLine(renderer, (int)i1, (int)j1, (int)i2, (int)j2);
        j1 = ys + (i*sin(angle));
        j2 = ye + (i*sin(angle));
        SDL_RenderDrawLine(renderer, (int)i1, (int)j1, (int)i2, (int)j2);
    }
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
