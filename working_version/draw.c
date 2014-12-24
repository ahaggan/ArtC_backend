    #include "display.h"

void draw_sdl(Interface interface, Draw *fractal, int x, int y, int size, float angle, int i) 
{

    if (strcmp(fractal->colour[i-1], "blue") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 0, 0, 255, 50);
    }

    else if (strcmp(fractal->colour[i-1], "red") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 255, 0, 0, 50);
    }

    else if (strcmp(fractal->colour[i-1], "green") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 0, 255, 0, 50);
    }

    else if (strcmp(fractal->colour[i-1], "pink") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 180, 0, 100, 50);
    }

    else if (strcmp(fractal->colour[i-1], "purple") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 100, 0, 150, 50);
    }

    else if (strcmp(fractal->colour[i-1], "brown") == 0) {
        SDL_SetRenderDrawColor(interface.window.renderer, 88, 55, 22, 50);
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

    else if(strcmp(fractal->shape[i-1], "triangle_outline") == 0) {
    angle = 0; // THIS MAKES THE TRIANGLES ALL DRAW STRAIGHT FOR NOW.
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
    printf("Line: (%d, %d) to (%d, %d)\n", xs, ys, xe, ye);
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

