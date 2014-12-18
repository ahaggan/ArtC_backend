#include "parser.h"
#include <math.h>

int parse(Interface interface, Draw *fractal) {
   //test_parser(interface); //Test will create its own fractals and test the functions in this module
	char input[NO_WORDS][MAX_LENGTH];
	action actions[FIRST_WORD_SIZE];
	printf("\nstart");
	create_struct_array(actions);	//Creates an array of structures containing the actions and relevant attributes of #defined arrays above 
	make_default(interface, fractal);
	get_input(actions, input, fractal);  //Takes values from file and puts them in the fractal structure	
/*    if(strcmp(fractal.type, "triangle") == 0){
        triangle(&fractal, sw, interface);
    }
    else{
        Draw_sdl(&fractal, sw, interface);
	}*/

    for(int i=1; i<10; i++) {
        fractal->height[i] = fractal->size[i];
        if(strcmp(fractal->shape[i], "triangle") == 0) {
            fractal->height[i] = fractal->size[i]*(sin(M_PI/3));
        }
    }

	printf("\nIn main:");
    printf("\nTypes: ");
    for(int i=0; i<10; i++) {
        printf("%s, ", fractal->type[i]);
    }
    printf("\nColours: ");
    for(int i=0; i<10; i++) {
        printf("%s, ", fractal->colour[i]);
    }
	printf("\nShapes: ");
    for(int i=0; i<10; i++) {
        printf("%s, ", fractal->shape[i]);
    }	
	return 0;
}



void make_default(Interface interface, Draw *fractal){
    //Call function and check it changes what it should
  printf("\ndefault");
    fractal->iterations = 1;
    for(int i=0; i<10; i++) {
        fractal->colour[i] = (char*)malloc(4*sizeof(char));
        strcpy(fractal->colour[i], "red"); 
	    fractal->size[i] = 100;
    	fractal->shape[i] = (char*)malloc(7*sizeof(char));
    	strcpy(fractal->shape[i], "square");
    	fractal->type[i] = (char*)malloc(9*sizeof(char));
    	strcpy(fractal->type[i], "tree");
        fractal->linethickness[i] = 1;
    }
	fractal->startx = interface.canvas.rect.x + (interface.canvas.rect.w/2);
	fractal->starty = interface.canvas.rect.y + (interface.canvas.rect.h/2);
	fractal->endx = WIN_WIDTH/2 + 10;
	fractal->endy = WIN_HEIGHT/2 + 10; 
	fractal->move = (char*)malloc(3*sizeof(char));
	strcpy(fractal->move, "up");
}

int get_input(action *actions, char input[NO_WORDS][MAX_LENGTH], Draw *fractal) {
	
	//char *first_word[] = FIRST_WORD;
	//char *second_word[] = SECOND_WORD;
	printf("\ninput");
	char c = 'f';
    int actit;
	FILE *fp;
	if((fp = fopen("instruction.txt", "r")) == NULL)
	{
		fprintf(stderr, "\nCouldn't open file!\n");
		return NO;
	}
	while(c != EOF){
		actit = -1;
		if(read_file_line(fp, actions, input, &actit) == YES){
			update_values(fractal, input, actit);
	
		}
		c = getc(fp);
		
			//clear_buffer();
	} 
	fclose(fp);
	return YES;
}

int read_file_line(FILE *fp, action *actions, char input[NO_WORDS][MAX_LENGTH], int *actit){
	int found_first = NO;
	int found_second = NO;
	int which_action = 0;
	int counter = 0;
	int i = 0, j = 0;
	char tmp_char;
	printf("\nfile line");
	memset(input[0], '\0', MAX_LENGTH);
	memset(input[1], '\0', MAX_LENGTH);
	while ((tmp_char = getc(fp)) != ';') {
printf("|%c|", tmp_char);
	    if(tmp_char == EOF){
	        printf("\nEnd of file reached");
	        return NO;
	    }
	    
	    if(tmp_char == ' ') {
	        i++;
	        j = 0;
	        counter++;
	        printf("\nFirst word: '%s'", input[0]);
	    }
			else if(tmp_char == '\n') {}
        else if((strcmp(input[0], "colour")==0 ||
                strcmp(input[0], "type")==0 ||
                strcmp(input[0], "shape")==0 ||
                strcmp(input[0], "size")==0 ||
                strcmp(input[0], "height")==0) &&
                tmp_char - '0' <= 9 && tmp_char - '0' >= 0) {
            *actit = tmp_char - '0';
            printf("actit: %d\n", *actit);
        }
	    else {
	       input[i][j] = tmp_char;
	       j++;
	    }
	}
	printf("\nSecond word: '%s'", input[1]);
	counter++;
	/*	if(j != -1){
			printf("\nYou have entered %d instructions, you need 2.\n", j);
			return NO;
		}
		printf("\nReached end of file.\n");
	    return YES;*/
    if(counter == 2){
		for(i = 0, found_first = NO; i<FIRST_WORD_SIZE && found_first == NO; i++){
			if (strcmp(input[0], actions[i].name) == 0 ) {
				found_first = YES;
				which_action = i;
			}
		}
	
		if(found_first == NO){
			printf("Your first word is not a valid function\n");
			return NO;
		}
	    for(i = 0, found_second = NO; strcmp(actions[which_action].instruction[i], "STOP") != 0 && found_second == NO && found_first == YES; i++){
		    if (strcmp(input[1], actions[which_action].instruction[i]) == 0 ) {
				found_second = YES;
			}
		    else if (atoi(input[1]) != 0){       //Will allow user to enter any integer, for any attribute that would be an integer
		        found_second = YES;
		    }
			
		}
		if(found_first == YES && found_second == NO){
			printf("Your second word is not valid with your chosen action\n");
			return NO;
		}
		return YES;
    }	
    return NO;
}

void update_values(Draw *fractal, char input[NO_WORDS][MAX_LENGTH], int actit){
	int i;
	char *first_word[FIRST_WORD_SIZE]= FIRST_WORD;
	printf("\nupdate");
	for(i = 0; i < FIRST_WORD_SIZE; i++){
		if(strcmp(first_word[i], input[0]) == 0){
			printf("\nStrings match.\n");
			assign_value(fractal, i, input[1], actit);
		}	
	}
}

void assign_value(Draw *fractal, action_word i, char *input, int actit){
	printf("\nIn assign\n");
	switch(i) {
        case iterations:
            fractal->iterations = atoi(input);
            break;
		case colour:
            if(actit==-1) {
    			for(int j=0; j<10; j++) {
                    fractal->colour[j] = (char*)malloc(strlen(input)*sizeof(char));
	    		    strcpy(fractal->colour[j], input);
                }
            }
            else {
                fractal->colour[actit-1] = (char*)malloc(strlen(input)*sizeof(char));
	    		strcpy(fractal->colour[actit-1], input);
            }
			break;
		case size:
            if(actit==-1) {
    			for(int j=0; j<10; j++) {
			        fractal->size[j] = atoi(input);
                }
                fractal->startx -= (fractal->size[0]/2);
    	        fractal->starty -= (fractal->size[0]/2);
            // In order to centre the image properly.
            }
            else {
                fractal->size[actit-1] = atoi(input);
            }
			break;
		case linethickness:
            if(actit==-1) {
    			for(int j=0; j<10; j++) {
			        fractal->linethickness[j] = atoi(input);
                }
            }
            else {
                fractal->linethickness[actit-1] = atoi(input);
            }
			break;  
		case shape:
            if(actit==-1) {
    			for(int j=0; j<10; j++) {
			        fractal->shape[j] = (char*)malloc(strlen(input)*sizeof(char));
			strcpy(fractal->shape[j], input);
                }
            }
            else {
                fractal->shape[actit-1] = (char*)malloc(strlen(input)*sizeof(char));
			strcpy(fractal->shape[actit-1], input);
            }
			break;  
		case type:
            if(actit==-1) {
    			for(int j=0; j<10; j++) {
        		    fractal->type[j] = (char*)malloc(strlen(input)*sizeof(char));
			        strcpy(fractal->type[j], input);
                }
            }
            else {
                fractal->type[actit-1] = (char*)malloc(strlen(input)*sizeof(char));
			        strcpy(fractal->type[actit-1], input);
            }
			break;
		case startx:
		    fractal->startx = atoi(input);
		    break;
		case starty:
		    fractal->starty = atoi(input);
		    break; 
		case endx:
		    fractal->endx = atoi(input);
		    break; 
		case endy:
		    fractal->endy = atoi(input);
		    break;
		case move:
			fractal->move = (char*)malloc(strlen(input)*sizeof(char));
			strcpy(fractal->move, input);
			break;
	}
	printf("\nEnd assign\n");
}

void clear_buffer(void){

	while (getchar() != '\n'){
	}
	
}

void create_struct_array(action *actions)
{
    printf("\ncreate");
	int i, j, k, l, cnt = 0, array_cnt = 0;
	char *first_word[FIRST_WORD_SIZE]= FIRST_WORD;
	char *second_word[SECOND_WORD_SIZE]= SECOND_WORD;
	
	for(i = 0; i < FIRST_WORD_SIZE && array_cnt < SECOND_WORD_SIZE; i++){
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
			/*for(l = 0; l < strlen(second_word[k]); l++){
				actions[i].instruction[k][l] = second_word[k][l];
			}*/
			//printf("\nFirst word: %s\n", actions[i].name);
			//printf("\nSecond word: %s\n", actions[i].instruction[l]);
		}
		cnt = 0;
		array_cnt += 1;
	}	
	printf("\nend ");
}

