
#include "parser.h"

/* parser should be passed a text file 
   also, it should treat \newlines as spaces (try ending the program with a } only one line below)*/
int parser(Draw *fractal){
    int i; //what is 'i'?
    FILE *file_pointer; // give this a proper name
    Prog program;
    
    program.interpreter_index = 0;
    program.fractal = fractal;
    
    initialise_words_array(&program);

    create_struct_array(program.actions);
    
    //make_default(&program);    
    //printf("\nCurrent word: %d\n", program.current_word);
    //interpreter(&program);
    //printf("\nParsed OK!\n");
    //test_interpreter(&program);
    //initialise_words_array(&program);

    initialise_interpreter_array(&program);
    if((file_pointer = fopen("user_code.artc", "r")) == NULL){
        fprintf(stderr, "\nCannot open file\n");
        exit(2);
    }
    
    i = 0;
    //printf("\nCurrent word: %d\n", program.current_word);
    while(fscanf(file_pointer, "%s", program.words[i]) == 1 && i < MAX_WORDS && !strings_match(program.words[i], " ")){
        //printf("\nWord read: %s\n", program.words[i]);
        i++;
    }
    validate(&program);
    printf("\nParsed OK!\n");
    interpreter(&program);
    test_interpreter(&program);
}

void initialise_words_array(Prog* program){
    int i;
    program->current_word = 0;
    for(i = 0; i < MAX_WORDS; i++){
        program->words[i][0] = '\0';
    }
}

void initialise_interpreter_array(Prog* program){
    int i;
    
    for(i = 0; i < NO_OF_INSTRUCTIONS; i++){
        program->interpreter[i][0] = '\0';
    }
}

void test_interpreter(Prog* program){
     printf("\nInside test\n");
    for(int i = 0; i < NO_OF_INSTRUCTIONS; i++){
    
        printf("\nInterpreter word: %s", program->interpreter[i]);
    
    }
    for(int i = 0; i < MAX_ITERATIONS; i++){
    
        printf("\nFractal colour %d: %s", i, program->fractal->colour[i]);
        printf("\nFractal shape %d: %s", i, program->fractal->shape[i]);
        printf("\nFractal type %d: %s", i, program->fractal->type[i]);
    }
}

void make_default(Prog* program){
    FILE *file_pointer;
    int i;
    if((file_pointer = fopen("default.txt", "r")) == NULL){
        fprintf(stderr, "\nCannot open default file\n");
        exit(2);
    }
    i = 0;
    
    while(fscanf(file_pointer, "%s", program->words[i]) == 1 && i < MAX_WORDS && !strings_match(program->words[i], " ")){
        //printf("\nWord read: %s\n", program->words[i]);
        i++;
    }
    validate(program);
    printf("\nDefault parsed OK!\n");
}
    

int validate(Prog* program){
    
    if(!strings_match(program->words[program->current_word], "run{")){
        printf("\nProgram needs to start with the word 'run{'");
        exit(1);
    }
    program->current_word += 1;
    funclist(program);
    
}

int funclist(Prog* program){
    if(strings_match(program->words[program->current_word], "}")){
        strcpy(program->interpreter[program->interpreter_index], "end" );
        program->interpreter_index += 1;
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

int function(Prog* program){
    if(strings_match(program->words[program->current_word], "if")){
        strcpy(program->interpreter[program->interpreter_index], "conditional");
            program->current_word += 1;
        if(check_if(program->words[program->current_word]) == TRUE){
            statement(program);
            program->current_word -= 1;
            program->interpreter_index += 1;
            strcpy(program->interpreter[program->interpreter_index], program->words[program->current_word]);
            program->interpreter_index += 1;
            program->current_word += 1;
            strcpy(program->interpreter[program->interpreter_index], program->words[program->current_word]);
            program->interpreter_index += 1;
            conditional(program);
        }
        
    }
    else if(strings_match(program->words[program->current_word], "for")){
        program->current_word += 1;
        loop(program);
    }
    else{
        statement(program);
    }
}

int loop(Prog* program){  
    int start_iteration, end_iteration;
    if(!strings_match(program->words[program->current_word], "iterations")){
            fprintf(stderr, "\nFor loop only works for iterations\n");
            exit(1);
    }
    statement(program);
    start_iteration = atoi(program->words[program->current_word]);
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "to")){
            fprintf(stderr, "\nFor loop needs the word 'to' between the two conditions\n");
            exit(1);
    }
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "iterations")){
            fprintf(stderr, "\nFor loop only works for iterations\n");
            exit(1);
    }
    statement(program);
    end_iteration = atoi(program->words[program->current_word]);
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "{")){
            fprintf(stderr, "\nFor loop starts with '{'\n");
            exit(1);
    }
    program->current_word += 1;
    if(start_iteration > end_iteration){
        fprintf(stderr, "\nStart iteration needs to be lower than the end iteration in your for loop.\n");
        exit(1);
    }
    
    for_loop(program, start_iteration, end_iteration);
}

void for_loop(Prog* program, int start, int end){
    int start_counter = program->current_word;
    int i;
    for(i = start; i <= end; i++){
        program->current_word = start_counter;
        strcpy(program->interpreter[program->interpreter_index], "conditional");
        program->interpreter_index += 1;
        strcpy(program->interpreter[program->interpreter_index], "iterations");
        program->interpreter_index += 1;
        sprintf(program->interpreter[program->interpreter_index], "%d", i);
        
        program->interpreter_index += 1;
        funclist(program);
    }
}
       
        
int conditional(Prog* program){  //if function
    //statement(program);
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "then{")){
        printf("\nIf condition needs to be followed with 'then{'");
        exit(1);
    }
    program->current_word += 1;
    funclist(program);
    
}

int statement(Prog* program){
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

int attribute(Prog* program){
    int i, j;
    for(i = 0; i < ACTION_SIZE; i++){
        if(strings_match(program->actions[i].name, program->words[program->current_word-1])){
            for(j = 0; !(strings_match(program->actions[i].instruction[j], "STOP")); j++){
                if (strings_match(program->words[program->current_word], program->actions[i].instruction[j])){
                    
                    if(strings_match(program->words[program->current_word-2], "if")){
                        
                    }
                    else if (strings_match(program->words[program->current_word-2], "for")){
                    }
                    else if (strings_match(program->words[program->current_word-2], "to")){
                    }
                    else{
                        strcpy(program->interpreter[program->interpreter_index], "assign");
                        program->interpreter_index += 1;
                        strcpy(program->interpreter[program->interpreter_index], program->words[program->current_word-1] );
                        program->interpreter_index += 1;
                        strcpy(program->interpreter[program->interpreter_index], program->words[program->current_word] );
                         program->interpreter_index += 1;
                        //assign_value(program, i);
                    }
                    return TRUE;
                }
                else if (atoi(program->words[program->current_word]) != 0){  //MEANS YOU CAN ENTER A NUMERIC VALUE FOR ANY ACTION!
                    if(strings_match(program->words[program->current_word-2], "if")){
                    }
                    else if (strings_match(program->words[program->current_word-2], "for")){
                    }
                    else if (strings_match(program->words[program->current_word-2], "to")){
                    }
                    else{
                        strcpy(program->interpreter[program->interpreter_index], "assign");
                        program->interpreter_index += 1;
                        strcpy(program->interpreter[program->interpreter_index], program->words[program->current_word-1] );
                        program->interpreter_index += 1;
                        strcpy(program->interpreter[program->interpreter_index], program->words[program->current_word] );
                        program->interpreter_index += 1;
                        //assign_value(program, i);
                    } 
                    return TRUE;
                }
            }
        }
        
    }
    return FALSE;
}

int check_if(char *word){
    
    if(strings_match(word, "iterations")){
        return TRUE;
    }
    else if(strings_match(word, "colour")){
        return TRUE;
    }
    fprintf(stderr, "\nThe action %s is not a valid condition for an if statement.\n", word);
    exit(1);
    return FALSE;
}

void create_struct_array(Action *actions){
    
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

/* What is this? */
/*
void assign_value(Prog* program, action_word i){

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
			program->fractal->size = atoi(program->words[program->current_word]);
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
*/

