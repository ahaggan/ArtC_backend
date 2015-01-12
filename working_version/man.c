#include "fractals.h"

int mandeliterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, int size);

void mandelbrot(Draw *fractal, Interface interface, int limit)
{
  Shape shape;
  make_shape(&shape, fractal->startx, fractal->starty, fractal->size[0], fractal->height[0], 0);
  int iterations = 1;
  int max = 20;


  printf("Mandelbrot Limit: %d\n", limit);

  iterations = mandeliterate(fractal, interface, shape, iterations, limit, max);
  printf("Mandelbrot completed with %d iterations.\n", iterations);
  
  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);
}

int mandeliterate(Draw *fractal, Interface interface, Shape current, int iterations, int limit, int max)
{
  if(current.size < 2 || iterations == limit) {
    return iterations;
  }
 
   int x, y;
   int height = 100;
   int size = 100;
   Shape *shapes = malloc(max*sizeof(Shape));
   int newits;
   for (int i = 0; i < height; i++)
   {
         x = 0.0;
         y = 0.0;
         current.size = (i - size/2.0)*4.0/size;
         current.height = (i - height/2.0)*4.0/size;
         float xsquared = x * x;
         float ysquared = y * y;
         while (xsquared+ysquared <= 4.0 && iterations < max){
            double xnew = xsquared - ysquared + current.size;
            y = (2 * x * y) + current.height;
            x = xnew;
            make_shape(&shapes[i], x, y, current.size, current.height, 0);
            iterations++;
               }
      newits = mandeliterate(fractal, interface, shapes[i], iterations, limit, max);
      }
  return newits;  
}

