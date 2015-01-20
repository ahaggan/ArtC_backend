//Module begins the program and runs automated test functions

#include <math.h>
#include <stdlib.h>
#include <time.h>

#ifndef  M_PI
 #define M_PI  3.14159265358979323846
#endif 
//Return value for functions to check they worked correctly
#define TRUE 1
#define FALSE 0
//Structure that stores all values needed to draw a fractal
typedef struct draw{
    int iterations;
    char* type[10];
    char* colour[10];
    int size[10];
    int linethickness[10];
    char* shape[10];
    int height[10];
    int splits[10];
    float angle;
    float anglerange;
    int startx;
    int starty;
    int endx;
    int endy;
    char* move;
} Draw;

//Calls function in menu.c and launches the user interface
void launch_menu();
//Calls test_parser.c and runs automated black and white box testing for this module
void test_parser();
//Fuction in parser.c
//Is declared here because needs to be called by the test function
//and also needs to be accessed by interface.c
int parser(Draw *fractal, char *file_name);
