#include "fractals.h"

void mandeliterate(Draw *fractal, Interface interface, Shape current, 
                      int iterations, int limit, int size);

void mandelbrot(Draw *fractal, Interface interface, int limit)
{
  Shape shape;
  make_shape(&shape, fractal->startx, fractal->starty, 
                 fractal->size[0], fractal->height[0], 0);
  int iterations = 1;
  int max = 20;

  mandeliterate(fractal, interface, shape, iterations, limit, max);
  
  SDL_RenderPresent(interface.window.renderer);
  SDL_UpdateWindowSurface(interface.window.win);
}

void mandeliterate(Draw *fractal, Interface interface, Shape current, 
                      int iterations, int limit, int max)
{
  if(current.size < 2 || iterations == limit) {
    return;
  }
 
   int x, y;
   int height = 100;
   int size = 100;
   Shape *shapes = malloc(max*sizeof(Shape));
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
      mandeliterate(fractal, interface, shapes[i], iterations, limit, max);
      }
}

