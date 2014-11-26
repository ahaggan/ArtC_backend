#include "artc_sdl2.h"

#define SMALLEST_SIZE 40
typedef struct triangle{
    double x1;
    double x2;
    double y1;
    double y2;
    int height;
    int width;
    struct triangle *one;
    struct triangle *two;
    struct triangle *three;
}tri;

void draw_iterations(SDL_Win *sw, tri *info, Interface interface, draw *object);
void draw_triangle(SDL_Win *sw, tri *info, Interface interface, draw *object);
void top(SDL_Win *sw, tri *info, Interface interface, draw *object);
void left(SDL_Win *sw, tri *info, Interface interface, draw *object);
void right(SDL_Win *sw, tri *info, Interface interface, draw *object);

int triangle(draw *object, SDL_Win *sw, Interface interface){
    
    tri info;
    
    
    info.height = WIN_HEIGHT;
    info.width = WIN_WIDTH/2;
    info.x1 = WIN_WIDTH/2;
    info.y1 = info.height;
    info.x2 = info.width + info.width/2;
    info.y2 = 0.0;
    
    draw_iterations(sw, &info, interface, object);
    
    
    
    do{
        
    }while(!sw->finished);
    return 0;
}

void draw_iterations(SDL_Win *sw, tri *info, Interface interface, draw *object){
    SDL_SetRenderDrawColor(sw->renderer, rand()%255, rand()%255, rand()%255, SDL_ALPHA_OPAQUE);
    tri one, two, three;
    info->one = &one;
    info->two = &two;
    info->three = &three;
    
    double start;
    start = info->x1;
    if(info->width < SMALLEST_SIZE || info->height < SMALLEST_SIZE){
        draw_triangle(sw, info, interface, object);
    }
    else{
        //draw_triangle(sw, info);
        top(sw, info, interface, object);
        left(sw, info, interface, object);
        right(sw, info, interface, object);
        /*
        info->height = info->height/2;
        info->width = info->width/2;
        info->x1 = info->width/2;
        info->y1 = info->height;
        info->y2 = info->height;
        info->x2 = info->x1 + info->width;
        draw_triangle(sw, info);
        */
    }
}

void top(SDL_Win *sw, tri *info, Interface interface, draw *object){
   
    info->one->height = info->height/2;
    info->one->width = info->width/2;
    info->one->x1 = info->x1 + info->one->width/2;
    info->one->y1 = info->y1 - info->one->height;
    info->one->x2 = info->x2;
    info->one->y2 = info->y2;
    draw_iterations(sw, info->one, interface, object);
    
}
void left(SDL_Win *sw, tri *info, Interface interface, draw *object){
    
    
    info->two->height = info->height/2;
    info->two->width = info->width/2;
    info->two->x1 = info->x1;
    info->two->y1 = info->y1;
    info->two->x2 = info->x1 + info->two->width/2;
    info->two->y2 = info->y1 - info->two->height;
    draw_iterations(sw, info->two, interface, object);
}
void right(SDL_Win *sw, tri *info, Interface interface, draw *object){
    
    
    info->three->height = info->height/2;
    info->three->width = info->width/2;
    info->three->x1 = info->x2;
    info->three->y1 = info->y1;
    info->three->x2 = info->three->x1 + info->three->width/2;
    info->three->y2 = info->y2 + info->three->height;
    draw_iterations(sw, info->three, interface, object);
}
void draw_triangle(SDL_Win *sw, tri *info, Interface interface, draw *object){

    
    if(sw->finished == 1){
        return;
    }
    double gradient, starty, startx;
    starty = info->y1;
    startx = info->x1;
    gradient = ((double)info->width)/((double)info->height*2);
    printf("\nStart draw.\nGradient: %lf\n", gradient);
    printf("\nx1: %lf y1: %lf  x2: %lf  y2: %lf\n", info->x1, info->y1, info->x2, info->y2);
    
 
    if (info->y1 == info->y2){
        while(info->y1 < starty + info->height && info->y2 < starty + info->height){
            SDL_Delay(1);
            object->shape = "line";
            object->startx = info->x1;
            object->starty = info->y1;
            object->endx = info->x2;
            object->endy = info->y2;
            draw_sdl(object, sw, interface);
            
            info->x1 += gradient;
            info->x2 -= gradient;
            info->y2 += 1;
            info->y1 += 1;
         }
    }
    else{
        while(info->x1 < startx + info->width + 1){
            SDL_Delay(5);
            object->shape = "line";
            object->startx = info->x1;
            object->starty = info->y1;
            object->endx = info->x2;
            object->endy = info->y2;
            draw_sdl(object, sw, interface);
            info->x1 += 2 * gradient;
            info->x2 += gradient;
            info->y2 += 1;
        }
    }
}
/*
void triangle(draw *object)
{
    object->startx = 0;
    object->starty = WIN_HEIGHT;
    object->endx = WIN_WIDTH/2;
    object->endy = 0;
    draw_sdl(object);
    object->startx = WIN_WIDTH/2;
    object->starty = 0;
    object->endx = WIN_WIDTH;
    object->endy = WIN_HEIGHT;
    draw_sdl(object);
    object->startx = WIN_WIDTH;
    object->starty = WIN_HEIGHT;
    object->endx = 0;
    object->endy = WIN_HEIGHT;
    draw_sdl(object);
}
*/
