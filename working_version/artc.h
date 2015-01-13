#include <math.h>

#ifndef  M_PI
 #define M_PI  3.14159265358979323846
#endif 

#define TRUE 1
#define FALSE 0

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

void launch_menu();
void test_parser();
