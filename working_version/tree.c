#include "display.h"

int treeiterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, float angle, int branchx, int branchy);

void tree(Draw *fractal, Interface interface, int limit)
{
  Shape trunk;
  float angle = 0;
  fractal->anglerange = 1;
    
  make_shape(&trunk, fractal->startx, interface.canvas.rect.h, fractal->size[0]/2, fractal->height[0]/2, 0);

  int iterations = 1;
  fractal->divisions = 2;

  printf("Tree Limit: %d\n", limit);
 
  Shape current = trunk;
  
  draw_sdl(interface, fractal, current.x, current.y, current.size/fractal->divisions, angle, iterations);

  int branchx = current.x + ((current.size*sin(angle))/fractal->divisions);
  int branchy = current.y - ((current.size*cos(angle))/fractal->divisions);

  iterations = treeiterate(fractal, interface, current, iterations, limit, angle, branchx, branchy);

  printf("Tree completed with %d iterations.\n", iterations);
  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);
}

int treeiterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, float angle, int branchx, int branchy)
{
  if(current.size < 2 || iterations == limit) {
    return iterations;
  }

  printf("passed %.2f pi, (%d, %d)\n", angle/M_PI, branchx, branchy);
  float newangle;
  int cx, cy;
  Shape *shapes = malloc(fractal->divisions*sizeof(Shape));
  iterations++; 
 
  for(int i=0; i<fractal->divisions/2; i++) {
    newangle = angle - (fractal->anglerange/2.0) + i*(fractal->anglerange/fractal->divisions);
    cx = branchx + ((current.size/fractal->divisions)*sin(newangle));
    cy = branchy - ((current.size/fractal->divisions)*cos(newangle));
    printf("newangle: %.2f pi, centre: (%d %d)\n", newangle/M_PI, cx, cy);
    make_shape(&shapes[i], cx, cy, current.size/fractal->divisions, current.height/fractal->divisions, newangle);
    draw_sdl(interface, fractal, cx, cy, current.size/fractal->divisions, newangle, iterations);

    newangle = angle + (fractal->anglerange/2.0) - i*(fractal->anglerange/fractal->divisions);
    cx = branchx + (sin(newangle)*(current.size/fractal->divisions));
    cy = branchy - (cos(newangle)*(current.size/fractal->divisions));
    printf("newangle: %.2f pi, centre: (%d %d)\n", newangle/M_PI, cx, cy);
   
    
  
    make_shape(&shapes[fractal->divisions-1-i], cx, cy, current.size/fractal->divisions, current.height/fractal->divisions, newangle);
   
  draw_sdl(interface, fractal, cx, cy, current.size/fractal->divisions, newangle, iterations);
  }

//  FROM ABOVE:
//  int branchx = current.x + ((current.size*sin(angle))/2.0);
//  int branchy = current.y - ((current.size*cos(angle))/2.0);

  int newits;
  for(int i=0; i<fractal->divisions/2; i++) {
    newangle = angle - (fractal->anglerange/2.0) + i*(fractal->anglerange/fractal->divisions);
    treeiterate(fractal, interface, shapes[i], iterations, limit, newangle, branchx + (sin(newangle)*current.size/(fractal->divisions/2)), branchy - (cos(newangle)*current.size/(fractal->divisions/2)));
    newangle = angle + (fractal->anglerange/2.0) - i*(fractal->anglerange/fractal->divisions);
    newits = treeiterate(fractal, interface, shapes[fractal->divisions-1-i], iterations, limit, newangle, branchx + (sin(newangle)*current.size/(fractal->divisions/2)), branchy - (cos(newangle)*current.size/(fractal->divisions/2)));
  }
  free(shapes);
  return newits;
}
