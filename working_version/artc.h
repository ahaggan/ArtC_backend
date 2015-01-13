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
  int divisions;
  float anglerange;
  int startx;
  int starty;
  int endx;
  int endy;
  char* move;
} Draw;

void launch_menu();
