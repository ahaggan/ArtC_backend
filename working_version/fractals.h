#include "draw.h"

void sierpinski(Draw *fractal, Interface interface, int limit);
void tree(Draw *fractal, Interface interface, int limit);
void carpet(Draw *fractal, Interface interface, int limit);
void star(Draw *fractal, Interface interface, int limit);

void make_shape(Shape *shape, int x, int y, int size, int height, float angle);
