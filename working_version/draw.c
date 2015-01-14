#include "draw.h"

void draw_sdl(Interface interface, Draw *fractal, int x, int y, int size, float angle, int i) 
{

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

    if (strcmp(fractal->shape[i-1], "square") == 0) {
        SDL_Line(interface.window.renderer, x-(size*sin(angle)/2.0), y+(size*cos(angle)/2.0), x+(size*sin(angle)/2.0), y-(size*cos(angle)/2.0), size, angle);
       /* SDL_Rect rectangle;
        rectangle.w = size;
        rectangle.h = size;
        rectangle.x = x - size/2;
        rectangle.y = y - size/2;
        SDL_RenderFillRect(interface.window.renderer, &rectangle);
*/
    }

    else if (strcmp(fractal->shape[i-1], "circle") == 0) {
        SDL_RenderFillCircle(interface.window.renderer, x, y, size / 2);

    }

    else if (strcmp(fractal->shape[i-1], "line") == 0) {
        SDL_Line(interface.window.renderer, x-(size*sin(angle)), y+(size*cos(angle)), x+(size*sin(angle)), y-(size*cos(angle)), fractal->linethickness[i-1], angle);
//printf("%f|%f|%f|%f\n", (x-size/2.0)*sin(angle), (y-size/2.0)*cos(angle), (x+size/2.0)*sin(angle), (y+size/2.0)*cos(angle));
    }

    else if(strcmp(fractal->shape[i-1], "triangle") == 0) {
        int c1x = x+((size/2.0)*sin(angle)), c1y = y-((size/2.0)*cos(angle));
        int c2x = x+((size/2.0)*sin(angle+(M_PI*(2.0/3.0)))), c2y = y-((size/2.0)*cos(angle+(M_PI*(2.0/3.0))));
        int c3x = x+((size/2.0)*sin(angle-(M_PI*(2.0/3.0)))), c3y = y-((size/2.0)*cos(angle-(M_PI*(2.0/3.0))));

        SDL_RenderDrawLine(interface.window.renderer, c1x, c1y, c2x, c2y);
        SDL_RenderDrawLine(interface.window.renderer, c2x, c2y, c3x, c3y);
        SDL_RenderDrawLine(interface.window.renderer, c3x, c3y, c1x, c1y);

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
