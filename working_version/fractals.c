#include "fractals.h"

void generate_fractal(Draw *fractal, SDL_Win *window, int i) 
{
    if(strcmp(fractal->type[i], "sierpinski") == 0){
        sierpinski(fractal, window, i);
    }
    else if(strcmp(fractal->type[i], "tree") == 0){
        tree(fractal, window, i);
    }
    else if(strcmp(fractal->type[i], "star") == 0){
        star(fractal, window, i);
    }
}

/* Tree Fractal */

void tree(Draw *fractal, SDL_Win *window, int limit) {
    Shape trunk;
    make_shape(&trunk, fractal->startx, fractal->starty - (fractal->size[0]/4), 
                   fractal->size[0]/2, fractal->height[0]/2, fractal->angle);
    Shape current = trunk;

    int iterations = 1;
    for(int i=0; i<10; i++) {
        fractal->splits[i] = 2;
    }

    fractal->anglerange = 1;
  
    draw_sdl(window, fractal, current.x, current.y, 
                 current.size/fractal->splits[0], fractal->angle, iterations);

    int bx= current.x + ((current.size*sin(fractal->angle))/fractal->splits[0]);
    int by= current.y - ((current.size*cos(fractal->angle))/fractal->splits[0]);

    treeiterate(fractal, window, current, iterations, limit, 
                  fractal->angle, bx, by);
    SDL_RenderPresent(window->renderer);
    SDL_UpdateWindowSurface(window->win);
}

void treeiterate(Draw *fractal, SDL_Win *window, Shape current, 
                     int iterations, int limit, float angle, int bx, int by) {
    if(current.size < 2 || iterations == limit) {
        return;
    }

    float newangle;
    int cx, cy;
    Shape *shapes = malloc(fractal->splits[iterations]*sizeof(Shape));
    int newsize = current.size/fractal->splits[iterations];

    iterations++; 
 
    for(int i=0; i<fractal->splits[iterations]/2; i++) {
        newangle = angle - (fractal->anglerange/2.0) + 
                       i*(fractal->anglerange/fractal->splits[iterations]);
        cx = bx + ((newsize)*sin(newangle));
        cy = by - ((newsize)*cos(newangle));
        make_shape(&shapes[i], cx, cy, 
                       newsize, 
                       current.height/fractal->splits[iterations], newangle);
        draw_sdl(window, fractal, cx, cy, 
                     newsize, 
                     newangle, iterations);

        newangle = angle + (fractal->anglerange/2.0) - 
                       i*(fractal->anglerange/fractal->splits[iterations]);
        cx = bx + (sin(newangle)*(newsize));
        cy = by - (cos(newangle)*(newsize));
        make_shape(&shapes[fractal->splits[iterations]-1-i], cx, cy, 
                       newsize, 
                       current.height/fractal->splits[iterations], newangle);
        draw_sdl(window, fractal, cx, cy, 
                     newsize, 
                     newangle, iterations);
    }

    for(int i=0; i<fractal->splits[iterations]/2; i++) {
        newangle = angle - (fractal->anglerange/2.0) + 
                       i*(fractal->anglerange/fractal->splits[iterations]);
        treeiterate(fractal, window, shapes[i], 
                        iterations, limit, newangle, 
                        bx + (sin(newangle)*2*newsize), 
                        by - (cos(newangle)*2*newsize));

        newangle = angle + (fractal->anglerange/2.0) - 
                       i*(fractal->anglerange/fractal->splits[iterations]);
        treeiterate(fractal, window, shapes[fractal->splits[iterations]-1-i], 
                        iterations, limit, newangle, 
                        bx + (sin(newangle)*2*newsize), 
                        by - (cos(newangle)*2*newsize));
    }
    free(shapes);
    return;
}

/* Sierpinski Fractal */

void sierpinski(Draw *fractal, SDL_Win *window, int limit) {
    Shape shape;
    make_shape(&shape, fractal->startx, fractal->starty, fractal->size[0],
                   fractal->height[0], fractal->angle);

    int iterations = 1; //One iteration is just the shape.

    sierpinskiiterate(fractal, window, shape, iterations, limit);
    SDL_RenderPresent(window->renderer);
    SDL_UpdateWindowSurface(window->win);
}

void sierpinskiiterate(Draw *fractal, SDL_Win *window, Shape current, 
                           int iterations, int limit) {
    if (current.size < 2 || iterations == limit) {
        draw_sdl(window, fractal, current.x, current.y, 
                     current.size/2, current.rotation, iterations);
        return;
    }

    Shape top, left, right;
    float l_angle = fractal->angle - ((2*M_PI)/3.0);
    float r_angle = fractal->angle + ((2*M_PI)/3.0);

    make_shape(&top, current.x + ((current.size/4)*sin(fractal->angle)), 
                     current.y - ((current.size/4)*cos(fractal->angle)), 
                     current.size / 2, current.height/2, fractal->angle);

    make_shape(&left, current.x + ((current.size/4))*sin(l_angle),
                      current.y - ((current.size/4))*cos(l_angle), 
                      current.size/2, current.height/2, l_angle);

    make_shape(&right, current.x + ((current.size/4))*sin(r_angle),
                       current.y - ((current.size/4))*cos(r_angle),
                       current.size/2, current.height/2, r_angle);

    iterations++;

    sierpinskiiterate(fractal, window, top, iterations, limit);
    sierpinskiiterate(fractal, window, left, iterations, limit);
    sierpinskiiterate(fractal, window, right, iterations, limit);
}


/* Star Fractal */

void star(Draw *fractal, SDL_Win *window, int limit) {
    Shape centre;
    make_shape(&centre, fractal->startx, fractal->starty, 
                   fractal->size[0]/2, fractal->height[0]/2, fractal->angle);

    int iterations = 1;

    for(int i=0; i<10; i++) {
        fractal->splits[i] = 6;
    }

    stariterate(fractal, window, centre, iterations, limit, fractal->angle);
  
    SDL_RenderPresent(window->renderer);
    SDL_UpdateWindowSurface(window->win);
}

void stariterate(Draw *fractal, SDL_Win *window, Shape current, 
                     int iterations, int limit, float angle) {
    draw_sdl(window, fractal, current.x, current.y, 
                 current.size, angle, iterations);

    if(current.size < 1 || iterations == limit) {
        return;
    }

    int x, y; 
    float newangle;
    Shape *shapes = malloc(fractal->splits[iterations]*sizeof(Shape)); 

    iterations++;

    for(int i=0; i<fractal->splits[iterations]; i++) {
        newangle = ((i*2.0*M_PI)/fractal->splits[iterations]) + fractal->angle;
        x = current.x + (current.size*sin(newangle)/sqrt(2));
        y = current.y - (current.size*cos(newangle)/sqrt(2));
        make_shape(&shapes[i], x, y, current.size/fractal->splits[iterations], 
                       current.height/fractal->splits[iterations], newangle);
        stariterate(fractal, window, shapes[i], iterations, limit, newangle);
    }
    free(shapes);
}
