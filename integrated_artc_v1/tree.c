#include "display.h"

int treeiterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, int branches, float angle);
void make_shape(Shape *shape, int x, int y, int size);

void tree(Draw *fractal, Interface interface, int limit)
{
  Shape trunk;
  make_shape(&trunk, fractal->startx, interface.canvas.rect.y+interface.canvas.rect.h-(fractal->size/4), fractal->size/2);

  int iterations = 1;
  int branches = 2;

  printf("Tree Limit: %d\n", limit);

  Shape current = trunk;
  float angle = 0;
  draw_sdl(interface, fractal, current.x, current.y, current.size, angle);

  iterations = treeiterate(fractal, interface, current, iterations, limit, branches, 0);

  printf("Tree completed with %d iterations.\n", iterations);
  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);
  SDL_Delay(SDL_DELAY);

}

int treeiterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, int branches, float angle)
{
  if(current.size < 2 || iterations == limit) {
    return iterations;
  }

  int x, y;
  Shape *shapes = malloc(branches*sizeof(Shape));

  for(int i=0; i<branches; i++) {
    x = current.x - (current.size/2) + (current.size/(2*branches)) + (i*(current.size/branches));
    y = current.y - (current.size/2) - (current.size/(2*branches));
    make_shape(&shapes[i], x, y, current.size/branches);
printf("shape: %d %d %d\n", x, y, current.size/branches);
  draw_sdl(interface, fractal, x, y, current.size/branches, angle-(M_PI/4.0)+(i*(M_PI/2.0)));
  }

  iterations++;
  for(int i=0; i<branches/2; i++) {
    treeiterate(fractal, interface, shapes[i], iterations, limit, branches,  angle);
    iterations = treeiterate(fractal, interface, shapes[branches-i-1], iterations, limit, branches, angle);
  }
  return iterations;
}
