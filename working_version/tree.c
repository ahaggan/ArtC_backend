#include "fractals.h"

int treeiterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, float angle, int branchx, int branchy);

void tree(Draw *fractal, Interface interface, int limit)
{
  Shape trunk;
  fractal->anglerange = 1;

  make_shape(&trunk, fractal->startx, fractal->starty - ((fractal->size[0]/2)/2), fractal->size[0]/2, fractal->height[0]/2, fractal->angle);

  int iterations = 1;
  for(int i=0; i<10; i++) {
    fractal->splits[i] = 2;
  }

  printf("Tree Limit: %d\n", limit);
 
  Shape current = trunk;
  
  draw_sdl(interface, fractal, current.x, current.y, current.size/fractal->splits[0], fractal->angle, iterations);

  int branchx = current.x + ((current.size*sin(fractal->angle))/fractal->splits[0]);
  int branchy = current.y - ((current.size*cos(fractal->angle))/fractal->splits[0]);

  iterations = treeiterate(fractal, interface, current, iterations, limit, fractal->angle, branchx, branchy);

  printf("Tree completed with %d iterations.\n", iterations);
  //SDL_RenderPresent(interface.window.renderer);
  //SDL_UpdateWindowSurface(interface.window.win);
}

int treeiterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, float angle, int branchx, int branchy)
{
  if(current.size < 2 || iterations == limit) {
    return iterations;
  }

  float newangle;
  int cx, cy;
  Shape *shapes = malloc(fractal->splits[iterations]*sizeof(Shape));
  iterations++; 
 
  for(int i=0; i<fractal->splits[iterations]/2; i++) {
    newangle = angle - (fractal->anglerange/2.0) + i*(fractal->anglerange/fractal->splits[iterations]);
    cx = branchx + ((current.size/fractal->splits[iterations])*sin(newangle));
    cy = branchy - ((current.size/fractal->splits[iterations])*cos(newangle));
    make_shape(&shapes[i], cx, cy, current.size/fractal->splits[iterations], current.height/fractal->splits[iterations], newangle);
    draw_sdl(interface, fractal, cx, cy, current.size/fractal->splits[iterations], newangle, iterations);

    newangle = angle + (fractal->anglerange/2.0) - i*(fractal->anglerange/fractal->splits[iterations]);
    cx = branchx + (sin(newangle)*(current.size/fractal->splits[iterations]));
    cy = branchy - (cos(newangle)*(current.size/fractal->splits[iterations]));
   
    
  
    make_shape(&shapes[fractal->splits[iterations]-1-i], cx, cy, current.size/fractal->splits[iterations], current.height/fractal->splits[iterations], newangle);
   
  draw_sdl(interface, fractal, cx, cy, current.size/fractal->splits[iterations], newangle, iterations);
  }

//  FROM ABOVE:
//  int branchx = current.x + ((current.size*sin(angle))/2.0);
//  int branchy = current.y - ((current.size*cos(angle))/2.0);

  int newits;
  for(int i=0; i<fractal->splits[iterations]/2; i++) {
    newangle = angle - (fractal->anglerange/2.0) + i*(fractal->anglerange/fractal->splits[iterations]);
    treeiterate(fractal, interface, shapes[i], iterations, limit, newangle, branchx + (sin(newangle)*current.size/(fractal->splits[iterations]/2)), branchy - (cos(newangle)*current.size/(fractal->splits[iterations]/2)));
    newangle = angle + (fractal->anglerange/2.0) - i*(fractal->anglerange/fractal->splits[iterations]);
    newits = treeiterate(fractal, interface, shapes[fractal->splits[iterations]-1-i], iterations, limit, newangle, branchx + (sin(newangle)*current.size/(fractal->splits[iterations]/2)), branchy - (cos(newangle)*current.size/(fractal->splits[iterations]/2)));
  }
  free(shapes);
  return newits;
}
