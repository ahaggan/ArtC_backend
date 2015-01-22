/*
Module contains functions that draw shapes for the fractal functions. 
It uses values contained in the user generated fractal structure. 
These functions use functions in the display module to display the shapes in SDL.
*/

#include "display.h"
#include <stdlib.h>

#define  COLOUR_SIZE  17

//Calls functions to set the shape colour and draw the shape
void draw_sdl(SDL_Win *window, Draw *fractal, int x, int y, 
                int size, float angle, int i);

//If random, calls function to set the random colour. Then sets the colour.
int draw_colour(SDL_Win *window, Draw *fractal, int i);
//Called by draw colour - checks which colour the user has chosen and assigns the value to SDL renderer
int find_and_set_colour(SDL_Win *window, Draw *fractal, int i);
//Randomly chooses one of the programs possible colours and assigns to the fractal
void write_random_colour(Draw *fractal, int i);
//If shape is random calls the function to assign a random shape. Then calls the function to draw said shape
void draw_shape(SDL_Win *window, Draw *fractal, int x, int y, 
                  int size, float angle, int i);
//Checks what shape to draw and calls the relevant function to draw it
void find_and_draw_shape(SDL_Win *window, Draw *fractal, int x, int y, 
                           int size, float angle, int i);
//Randomly selects a shape to assign to the fractal
void write_random_shape(Draw *fractal, int i);

/*
Functions below draw the respective shapes in the name of the function
*/

void Draw_Line(SDL_Renderer* renderer, int x, int y, 
                 int size, float angle, int thickness);
void Draw_Square(SDL_Renderer* renderer, int x, int y, int l, float angle);
void Draw_Circle(SDL_Renderer *renderer, int cx, int cy, int r);
void Draw_Tri(SDL_Renderer *renderer, int x, int y, 
                int size, float angle, int thickness);
void SDL_Line(SDL_Renderer* renderer, int xs, int ys, int xe, int ye, 
                 int thickness, float angle);
                 
//Draws the image created onto the canvas
void Draw_Image(SDL_Win *window, int x, int y, int size);
