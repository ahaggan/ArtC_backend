#include "parser.h"

int parser(Draw *fractal){
    int i;
    FILE *file_pointer;
    prog program;
    //Draw fractal;
    program.fractal = fractal;
    
    initialise_words_array(&program);
    
    create_struct_array(program.actions);
    
   // make_default(&program);
    
     //printf("\nCurrent word: %d\n", program.current_word);
   // test_interpreter(&program);
   // initialise_words_array(&program);
    if((file_pointer = fopen("parser.txt", "r")) == NULL){
        fprintf(stderr, "\nCannot open file\n");
        exit(2);
    }
    
    i = 0;
    printf("\nCurrent word: %d\n", program.current_word);
    while(fscanf(file_pointer, "%s", program.words[i]) == 1 && i < MAX_WORDS && !strings_match(program.words[i], " ")){
        printf("\nWord read: %s\n", program.words[i]);
        i++;
    }
    validate(&program);
    printf("\nParsed OK!\n");
    test_interpreter(&program);
}

void initialise_words_array(prog *program){
    int i;
    program->current_word = 0;
    for(i = 0; i < MAX_WORDS; i++){
        program->words[i][0] = '\0';
    }
}
void test_interpreter(prog *program){
    printf("\nFractal colour: %s", program->fractal->colour[0]);
    printf("\nFractal colour: %s", program->fractal->colour[7]);
    printf("\nFractal size: %d", program->fractal->size[0]);
    printf("\nFractal shape: %s", program->fractal->shape[0]);
    printf("\nFractal shape: %s", program->fractal->shape[5]);
    printf("\nFractal type: %s", program->fractal->type[0]);
    printf("\nFractal type: %s", program->fractal->type[4]);
    printf("\nFractal iterations: %d", program->fractal->iterations);
}

void make_default(prog *program){
    FILE *file_pointer;
    int i;
    if((file_pointer = fopen("default.txt", "r")) == NULL){
        fprintf(stderr, "\nCannot open default file\n");
        exit(2);
    }
    i = 0;
    
    while(fscanf(file_pointer, "%s", program->words[i]) == 1 && i < MAX_WORDS && !strings_match(program->words[i], " ")){
        printf("\nWord read: %s\n", program->words[i]);
        i++;
    }
    validate(program);
    printf("\nDefault parsed OK!\n");
}
    

int validate(prog *program){
    
    if(!strings_match(program->words[program->current_word], "run{")){
        printf("\nProgram needs to start with the word 'run{'");
        exit(1);
    }
    program->current_word += 1;
    funclist(program);
    
}

int funclist(prog *program){
    if(strings_match(program->words[program->current_word], "}")){
        return TRUE;
    }
    else if(strings_match(program->words[program->current_word], "")){
        fprintf(stderr, "\nProgram needs to end with '}'.\n");
        exit(2);
    }
    function(program);
    program->current_word += 1;
    funclist(program);
}

int function(prog *program){
    if(strings_match(program->words[program->current_word], "if")){
        program->current_word += 1;
        conditional(program);
    }
    else if(strings_match(program->words[program->current_word], "for")){
        loop(program);
    }
    else{
        statement(program);
    }

}

int loop(prog *program){     //for function
}

int conditional(prog *program){  //if function
    statement(program);
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "then{")){
        printf("\nIf condition needs to be followed with 'then{'");
        exit(1);
    }
    program->current_word += 1;
    funclist(program);
    
}

int statement(prog *program){
    if (check_action(program->words[program->current_word]) == TRUE){
        program->current_word += 1;
        if(attribute(program)){
            //assign_to_fractal(
        }
        else{
            fprintf(stderr, "\n Attribute word %s is not valid with action %s", program->words[program->current_word], program->words[program->current_word-1] );
            exit(2);
        }
    }
    else{
        fprintf(stderr, "\n Action word %s is not valid.", program->words[program->current_word]);
        exit(2);
    }
}

int check_action(char *word){
    char *actions[ACTION_SIZE] = ACTION;
    int i;
    for(i = 0; i < ACTION_SIZE; i++){
        if(strings_match(actions[i], word)){
            return TRUE;
        }
    } 
    return FALSE; 
}

int attribute(prog *program){
    int i, j;
    for(i = 0; i < ACTION_SIZE; i++){
        if(strings_match(program->actions[i].name, program->words[program->current_word-1])){
            for(j = 0; !(strings_match(program->actions[i].instruction[j], "STOP")); j++){
                if (strings_match(program->words[program->current_word], program->actions[i].instruction[j])){
                    if(strings_match(program->words[program->current_word-2], "if")){
                        //check_if(program);
                    }
                    else if (strings_match(program->words[program->current_word-2], "for")){
                    }
                    else{
                        assign_value(program, i);
                    }
                    return TRUE;
                }
                else if (atoi(program->words[program->current_word]) != 0){  //MEANS YOU CAN ENTER A NUMERIC VALUE FOR ANY ACTION!
                    if(strings_match(program->words[program->current_word-2], "if")){
                    }
                    else if (strings_match(program->words[program->current_word-2], "for")){
                    }
                    else{
                        assign_value(program, i);
                    } 
                    return TRUE;
                }
            }
        }
        
    }
    return FALSE;
}
/*
void check_if(prog *program){
    if(strings_match(program->words[program->current_word-1], "iterations")){
        iteration_if(program);
    }
    else{
        fprintf("Action %s, cannot be used in an if statement.", program->words[program->current_word-1])
    }
    /*else if(strings_match(program->words[program->current_word-1], "colour")){
    }
    else if(strings_match(program->words[program->current_word-1], "shape")){
    }
    else if(strings_match(program->words[program->current_word-1], "type")){
    }
   

}*/
/*
void iteration_if(prog *program){
*/
void create_struct_array(action *actions){
    
	int i, j, k, l, cnt = 0, array_cnt = 0;
	char *first_word[ACTION_SIZE]= ACTION;
	char *second_word[ATTRIBUTE_SIZE]= ATTRIBUTE;
	
	for(i = 0; i < ACTION_SIZE && array_cnt < ATTRIBUTE_SIZE; i++){
		actions[i].name = (char*)malloc(1 * sizeof(char[strlen(first_word[i])]));
		actions[i].name = first_word[i];
	
		for(j = array_cnt; strcmp(second_word[j], "NEXT") != 0; j++){
				
				cnt += 1;
		}
		array_cnt += cnt;
		
		actions[i].instruction = (char**)malloc(cnt * sizeof(char*));
		
		for(k = array_cnt - cnt, l = 0; k < array_cnt; k++, l++){
			
			actions[i].instruction[l] = (char*)malloc(strlen(second_word[k]) * sizeof(char));
			strcpy(actions[i].instruction[l], second_word[k]);
		}
		cnt = 0;
		array_cnt += 1;
	}
}

void assign_value(prog *program, action_word i){

	switch(i){
		case colour:
           for(int j=0; j<MAX_ITERATIONS; j++) {
                    program->fractal->colour[j] = (char*)malloc(strlen(program->words[program->current_word])*sizeof(char));
	    		    strcpy(program->fractal->colour[j], program->words[program->current_word]);
            }
			break;
		case move:
			program->fractal->move = (char*)malloc(strlen(program->words[program->current_word])*sizeof(char));
			strcpy(program->fractal->move, program->words[program->current_word]);
			break;
		case size:
		    for(int j=0; j<MAX_ITERATIONS; j++) {
			    program->fractal->size[j] = atoi(program->words[program->current_word]);
			}
        	program->fractal->startx -= (size/2);
	        program->fractal->starty -= (size/2);
            // In order to centre the image properly.
//   HAVE NOT GOT TIME TO MAKE WORK PROPERLY RIGHT NOW WILL FIX LATER PROBABLY.
			break;
		case shape:
		    for(int j=0; j<MAX_ITERATIONS; j++) {
			    program->fractal->shape[j] = (char*)malloc(strlen(program->words[program->current_word])*sizeof(char));
			    strcpy(program->fractal->shape[j], program->words[program->current_word]);
			}
			break;
			
		case startx:
		    program->fractal->startx = atoi(program->words[program->current_word]);
		    break;
		case starty:
		    program->fractal->starty = atoi(program->words[program->current_word]);
		    break; 
		case endx:
		    program->fractal->endx = atoi(program->words[program->current_word]);
		    break; 
		case endy:
		    program->fractal->endy = atoi(program->words[program->current_word]);
		    break;  
		case type:
		    for(int j=0; j<MAX_ITERATIONS; j++) {
		        program->fractal->type[j] = (char*)malloc(strlen(program->words[program->current_word])*sizeof(char));
			    strcpy(program->fractal->type[j], program->words[program->current_word]);
			}
			break;		
        case iterations:
            program->fractal->iterations = atoi(program->words[program->current_word]);
            break;
	}
	
}

