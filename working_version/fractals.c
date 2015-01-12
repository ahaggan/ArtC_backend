#include "fractals.h"

void generate_fractal(Draw *fractal, Interface interface, int i) 
{

    if(strcmp(fractal->type[i], "sierpinski") == 0){
        sierpinski(fractal, interface, i);

    }
    else if(strcmp(fractal->type[i], "tree") == 0){
        tree(fractal, interface, i);
    }
    else if(strcmp(fractal->type[i], "sierpinski_square") == 0){
        carpet(fractal, interface, i);
    }
    else if(strcmp(fractal->type[i], "star") == 0){
        star(fractal, interface, i);
    }
}
