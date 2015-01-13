#include "fractals.h"

int stariterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, float angle);

void star(Draw *fractal, Interface interface, int limit)
{
  Shape centre;
  make_shape(&centre, fractal->startx, fractal->starty, fractal->size[0]/2, fractal->height[0]/2, fractal->angle);
  int iterations = 1;
  for(int i=0; i<10; i++) {
    fractal->splits[i] = 6;
  }

  printf("Star Limit: %d\n", limit);

  iterations = stariterate(fractal, interface, centre, iterations, limit, 0);
  printf("Star completed with %d iterations.\n", iterations);
  
  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);
}

int stariterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, float angle)
{
    draw_sdl(interface, fractal, current.x, current.y, current.size, angle, iterations);
  if(current.size < 1 || iterations == limit) {
    return iterations;
  }

  int x, y; 
  float newangle;
  Shape *shapes = malloc(fractal->splits[iterations]*sizeof(Shape)); 

  iterations++;
  int newits;
  for(int i=0; i<fractal->splits[iterations]; i++) {
    newangle = ((i*2.0*M_PI)/fractal->splits[iterations]) + fractal->angle;
    x = current.x + (current.size*sin(newangle)/sqrt(2));
    y = current.y - (current.size*cos(newangle)/sqrt(2));
    make_shape(&shapes[i], x, y, current.size/fractal->splits[iterations], current.height/fractal->splits[iterations], newangle);
    newits = stariterate(fractal, interface, shapes[i], iterations, limit, newangle);
  }
  return newits;
}
