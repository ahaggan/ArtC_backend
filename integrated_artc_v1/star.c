#include "display.h"

int stariterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, int points, float angle);

void star(Draw *fractal, Interface interface, int limit)
{
  Shape centre;
  int points = 5;
  make_shape(&centre, fractal->startx, fractal->starty, 2*fractal->size/points, 2*fractal->height);
  int iterations = 1;

  printf("Star Limit: %d\n", limit);

  iterations = stariterate(fractal, interface, centre, iterations, limit, points, 0);
  printf("Star completed with %d iterations.\n", iterations);
  
  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);
  SDL_Delay(SDL_DELAY);
}

int stariterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, int points, float angle)
{
    draw_sdl(interface, fractal, current.x, current.y, current.size, angle);
  if(current.size < 2 || iterations == limit) {
    return iterations;
  }

  int x, y; 
  float newangle;
  Shape *shapes = malloc(points*sizeof(Shape)); 

  iterations++;
  int newits;
  for(int i=0; i<points; i++) {
    newangle = (i*2.0*M_PI)/points;
    x = current.x + current.size*sin(newangle);
    y = current.y - current.size*cos(newangle);
    make_shape(&shapes[i], x, y, current.size/(2.0*sqrt(points)), current.height/(2.0*sqrt(points)));
    newits = stariterate(fractal, interface, shapes[i], iterations, limit, points, newangle);
  }
  return newits;
}
