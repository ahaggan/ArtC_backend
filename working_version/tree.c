#include "fractals.h"

void treeiterate(Draw *fractal, Interface interface, Shape current,
                     int iterations, int limit, float angle, int bx, int by);

void tree(Draw *fractal, Interface interface, int limit) {
    Shape trunk;
    make_shape(&trunk, fractal->startx, fractal->starty - (fractal->size[0]/4), 
                   fractal->size[0]/2, fractal->height[0]/2, fractal->angle);
    Shape current = trunk;

    int iterations = 1;
    for(int i=0; i<10; i++) {
        fractal->splits[i] = 2;
    }

    fractal->anglerange = 1;
  
    draw_sdl(interface, fractal, current.x, current.y, 
                 current.size/fractal->splits[0], fractal->angle, iterations);

    int bx= current.x + ((current.size*sin(fractal->angle))/fractal->splits[0]);
    int by= current.y - ((current.size*cos(fractal->angle))/fractal->splits[0]);

    treeiterate(fractal, interface, current, iterations, limit, 
                  fractal->angle, bx, by);
}

void treeiterate(Draw *fractal, Interface interface, Shape current, 
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
        draw_sdl(interface, fractal, cx, cy, 
                     newsize, 
                     newangle, iterations);

        newangle = angle + (fractal->anglerange/2.0) - 
                       i*(fractal->anglerange/fractal->splits[iterations]);
        cx = bx + (sin(newangle)*(newsize));
        cy = by - (cos(newangle)*(newsize));
        make_shape(&shapes[fractal->splits[iterations]-1-i], cx, cy, 
                       newsize, 
                       current.height/fractal->splits[iterations], newangle);
        draw_sdl(interface, fractal, cx, cy, 
                     newsize, 
                     newangle, iterations);
    }

    for(int i=0; i<fractal->splits[iterations]/2; i++) {
        newangle = angle - (fractal->anglerange/2.0) + 
                       i*(fractal->anglerange/fractal->splits[iterations]);
        treeiterate(fractal, interface, shapes[i], 
                        iterations, limit, newangle, 
                        bx + (sin(newangle)*2*newsize), 
                        by - (cos(newangle)*2*newsize));

        newangle = angle + (fractal->anglerange/2.0) - 
                       i*(fractal->anglerange/fractal->splits[iterations]);
        treeiterate(fractal, interface, shapes[fractal->splits[iterations]-1-i], 
                        iterations, limit, newangle, 
                        bx + (sin(newangle)*2*newsize), 
                        by - (cos(newangle)*2*newsize));
    }
    free(shapes);
    return;
}
