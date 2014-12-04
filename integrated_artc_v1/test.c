#include "parser.h"
#include "test.h"

int test_parser(Interface interface){
    Draw test_fractal;
    int test_count= 0;
    printf("\nPARSER TEST\n");
    if (make_test_default(interface, &test_fractal) == NO){
        printf("\nError in the make default function.");
        exit(1);
    }
    else{
        test_count += 1;
    } 
    printf("\nTest function:\nfractal->colour = %s\n", test_fractal.colour);
    
    /*NEED TO TEST THESE
    If everything works, just a message saying all tests work.
    int get_input(action *actions, char *first_input, char *second_input, Draw *fractal);
    int read_file_line(FILE *fp, action *actions, char* first_input, char* second_input);
    test_fractal.colour;
    test_fractal.move;
    test_fractal.size;
    test_fractal.shape;
    test_fractal.startx;
    test_fractal.starty;
    test_fractal.endx;
    test_fractal.endy;
    test_fractal.type;
    test_fractal.iterations;
    */

    /* DONT NEED TO TEST, either manually assigning values or only called if previous tested functions work correctly!
    void create_struct_array(action *actions);
    void clear_buffer(void);
    void update_values(Draw *fractal, char *first_input, char *second_input);
    void assign_value(Draw *fractal, action_word i, char *input);
    void make_default(Interface interface, Draw *fractal);
    */
    printf("\nParser passed %d tests!\n", test_count);
    SDL_Delay(10000);
    return 0;
}

int make_test_default(Interface interface, Draw *fractal){
    make_default(interface, fractal);
    if(strcmp(fractal->colour,"red") != 0){
        return NO;
    } 
    if(strcmp(fractal->move, "up") != 0){
        return NO;
    }
	if(fractal->size != 10){
	    return NO;
	}
	if(strcmp(fractal->shape, "square") != 0){
	    return NO;
	}
	if(fractal->startx != interface.canvas.rect.x + (interface.canvas.rect.w/2) - size){
	    return NO;
	}
	if(fractal->starty != interface.canvas.rect.y + (interface.canvas.rect.h/2) - size){
	    return NO;
	}
	if(fractal->endx != WIN_WIDTH/2 + 10){
	    return NO;
	}
	if(fractal->endy != WIN_HEIGHT/2 + 10){
	    return NO;
	}
	if(strcmp(fractal->type, "tree") != 0){
	    return NO;
	}
    //strdup(fractal->type, "triangle");
	if(fractal->iterations != 1){
	    return NO;
	}
	return YES;   
}

int test_colour(Interface interface, Draw *test_fractal){
    return 0;
}

