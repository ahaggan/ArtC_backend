//  This module tests the users program for gramatical accuracy. It will return an error if the input is incorrect. 
//
//  As the program is tested, the correct attributes are assigned to an interpreter array. If the program is written correctly
//  this array is passed to the intereter module which will assign values from the user to the given fractal

#include "parser.h"
//int main(Draw *fractal, char *file_name){     //Use this to pass a file name to the parser function.
int parser(Draw *fractal, char *file_name){
    printf("\nParsing begin.\n");
    //test_parser();
    int i;//Used to count through number of words in a program
    FILE *file_pointer;
    Prog program;
       
    
    program.interpreter_index = 0;
    program.fractal = fractal;
    
    
    initialise_words_array(&program);
    
    create_struct_array(program.actions);
    
    initialise_interpreter_array(&program);
    if((file_pointer = fopen(file_name, "r")) == NULL){
        fprintf(stderr, "\nCannot open file\n");
        fclose(program.error);
        return FALSE;
    }
    
    i = 0;
    printf("\nCurrent word: %d\n", program.current_word);
    while(fscanf(file_pointer, "%s", program.words[i]) == 1 && i < MAX_WORDS && program.words[i] != NULL){
        printf("\nWord read: %s\n", program.words[i]);
        i++;
    }
    
    if (validate(&program) == FALSE){
        fclose(program.error);
        return FALSE;
    }
    
    printf("\nParsed OK!\n");
    interpreter(&program);
    test_interpreter(&program);
    fclose(program.error);
    return TRUE;
}

void initialise_words_array(Prog *program){
    int i;
    program->error = fopen("error_message.artc", "w");
    program->current_word = 0;
    for(i = 0; i < MAX_WORDS; i++){
        program->words[i][0] = '\0';
    }
}

void initialise_interpreter_array(Prog *program){
    int i;
    
    for(i = 0; i < NO_OF_INSTRUCTIONS; i++){
        program->interpreter[i][0] = '\0';
    }
}

void test_interpreter(Prog *program){
     //printf("\nInside test\n");
    for(int i = 0; i < NO_OF_INSTRUCTIONS; i++){
    
        printf("\nInterpreter word: %s", program->interpreter[i]);
    
    }
    for(int i = 0; i < MAX_ITERATIONS; i++){
    
        printf("\nFactal colour %d: %s", i, program->fractal->colour[i]);
        printf("\nFactal shape %d: %s", i, program->fractal->shape[i]);
        printf("\nFactal type %d: %s", i, program->fractal->type[i]);
    }
}

    

int validate(Prog *program){
    
    if(!strings_match(program->words[program->current_word], "run") || program->words[program->current_word][0] == '\0'){
        printf("\nInside validate if\n");
        printf("\nWord: %s\n", program->words[program->current_word]);
        fprintf(program->error, "\nProgram needs to start with 'run {'");
        return FALSE;
    }
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "{") || program->words[program->current_word] == NULL){
        fprintf(program->error, "\nProgram needs to start with 'run {'");
        return FALSE;
    }
    program->current_word += 1;
    if(funclist(program) == TRUE){
        return TRUE;
    }
    return FALSE;
    
}

int funclist(Prog *program){
    if(strings_match(program->words[program->current_word], "}")){
        strcpy(program->interpreter[program->interpreter_index], "end" );
        program->interpreter_index += 1;
        return TRUE;
    }
    else if(strings_match(program->words[program->current_word], "")){      //Should this be something else, EOF?
        fprintf(program->error, "\nProgram needs to end with '}'.\n");
        return FALSE;
    }
    if(function(program)){
        program->current_word += 1;
        return funclist(program);
    }
    return FALSE;
}

int function(Prog *program){
    if(strings_match(program->words[program->current_word], "if")){
        strcpy(program->interpreter[program->interpreter_index], "conditional");
            program->current_word += 1;
        if(check_if(program->words[program->current_word]) == TRUE){
            if (!statement(program)){
                return FALSE;
            } 
            program->current_word -= 1;
            program->interpreter_index += 1;
            strcpy(program->interpreter[program->interpreter_index], program->words[program->current_word]);
            program->interpreter_index += 1;
            program->current_word += 1;
            strcpy(program->interpreter[program->interpreter_index], program->words[program->current_word]);
            program->interpreter_index += 1;
            return conditional(program);
        }
        else {
            fprintf(program->error, "\nThe action %s is not a valid condition for an if statement.\n", program->words[program->current_word]);
        return FALSE;
        }
        
    }
    else if(strings_match(program->words[program->current_word], "for")){
        program->current_word += 1;
        return loop(program);
    }
    else{
        return statement(program);
    }
}

int loop(Prog *program){  
    int start_iteration, end_iteration;
    if(!strings_match(program->words[program->current_word], "iterations")){
            fprintf(program->error, "\nFor loop only works with iterations\n");
            return FALSE;
    }
    statement(program);
    start_iteration = atoi(program->words[program->current_word]);
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "to")){
            fprintf(program->error, "\nFor loop needs the word 'to' between the two conditions\n");
            return FALSE;
    }
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "iterations")){
            fprintf(program->error, "\nFor loop only works with iterations\n");
            return FALSE;
    }
    statement(program);
    end_iteration = atoi(program->words[program->current_word]);
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "{")){
            fprintf(program->error, "\nFor loop needs to start with '{'\n");
            return FALSE;
    }
    program->current_word += 1;
    if(start_iteration > end_iteration){
        fprintf(program->error, "\nStart iteration needs to be lower than the end iteration in your for loop.\n");
        return FALSE;
    }
    
    for_loop(program, start_iteration, end_iteration);
    return TRUE;
}

void for_loop(Prog *program, int start, int end){
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
       
        
int conditional(Prog *program){  //if function
    //statement(program);
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "then")){
        fprintf(program->error, "\nIf condition needs to be followed with 'then {'");
        return FALSE;
    }
    program->current_word += 1;
    if(!strings_match(program->words[program->current_word], "{")){
        fprintf(program->error, "\nIf condition needs to be followed with 'then {'");
        return FALSE;
    }
    program->current_word += 1;
    return funclist(program);
    
}

int statement(Prog *program){
    if (check_action(program->words[program->current_word]) == TRUE){
        program->current_word += 1;
        if(attribute(program)){
            return TRUE;
        }
        else{
            fprintf(program->error, "\n Attribute word %s is not valid with action %s", program->words[program->current_word], program->words[program->current_word-1] );
            return FALSE;
        }
    }
    else{
        fprintf(program->error, "\n Action word %s is not valid.", program->words[program->current_word]);
        return FALSE;
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

int attribute(Prog *program){
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
