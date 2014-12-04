int test_parser(Interface interface){
    draw test_fractal;
    /*NEED TO TEST THESE
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
}

void make_test_default(Interface interface, draw *test_fractal){
    fractal->colour = (char*)malloc(4*sizeof(char));
	strcpy(fractal->colour, "red"); 
	fractal->move = (char*)malloc(3*sizeof(char));
	strcpy(fractal->move, "up");
	fractal->size = 10;
	fractal->shape = (char*)malloc(7*sizeof(char));
	strcpy(fractal->shape, "square");
	fractal->startx = 500;
	fractal->starty = 300;
	fractal->endx = WIN_WIDTH/2 + 10;
	fractal->endy = WIN_HEIGHT/2 + 10; 
    //strdup(fractal->type, "triangle");
	fractal->type = (char*)malloc(9*sizeof(char));
	strcpy(fractal->type, "triangle");
	//printf("\nType: %s", fractal->type);
    fractal->iterations = 1;
}

int test_colour(Interface interface, draw *test_fractal){
}

