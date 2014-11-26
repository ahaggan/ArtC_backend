#include "artc_sdl2.h"

int input(SDL_Win *sw, Interface interface) {

	char first_input[MAX_LENGTH];
	char second_input[MAX_LENGTH];
	action actions[FIRST_WORD_SIZE];
	draw object;
	printf("\nstart");
	create_struct_array(actions);	//Creates an array of structures containing the actions and relevant attributes of #defined arrays above 
	make_default(&object);
	get_input(actions,first_input,second_input, &object);  //Takes values from file and puts them in the object structure

	
    if(strcmp(object.fractal, "triangle") == 0){
        triangle(&object, sw, interface);
    }
    else{
        draw_sdl(&object, sw, interface);
	}
    
	

	return 0;
}

void make_default(draw *object){
    printf("\ndefault");
    object->colour = (char*)malloc(4*sizeof(char));
	strcpy(object->colour, "red"); 
	object->move = (char*)malloc(3*sizeof(char));
	strcpy(object->move, "up");
	object->size = 10;
	object->shape = (char*)malloc(7*sizeof(char));
	strcpy(object->shape, "square");
	object->startx = WIN_WIDTH/2 - 10;
	object->starty = WIN_HEIGHT/2 - 10;
	object->endx = WIN_WIDTH/2 + 10;
	object->endy = WIN_HEIGHT/2 + 10; 

	object->fractal = (char*)malloc(9*sizeof(char));
	strcpy(object->fractal, "triangle");

}

void get_input(action *actions, char *first_input, char *second_input, draw *object) {
	
	//char *first_word[] = FIRST_WORD;
	//char *second_word[] = SECOND_WORD;
	printf("\ninput");
	char c = 'f';
	FILE *fp;
	if((fp = fopen("instruction.txt", "r")) == NULL)
	{
		fprintf(stderr, "\nCouldn't open file!\n");
		return;
	}
	while(c != EOF){
		if(read_file_line(fp, actions, first_input, second_input) ==YES)
		{
			update_values(object, first_input, second_input);
	
		}
		c = getc(fp);
		
			//clear_buffer();
	} 
	fclose(fp);
}

int read_file_line(FILE *fp, action *actions, char* first_input, char* second_input){
	int found_first = NO;
	int found_second = NO;
	int which_action = 0;
	int i, j;
	printf("\nfile line");
	if ((j = fscanf(fp, "%s%s", first_input, second_input)) != 2 ) {
		if(j != -1){
			printf("\nYou have entered %d instructions, you need 2.\n", j);
			return NO;
		}
		printf("\nReached end of file.\n");
	    return NO;
	}
	else {
		for(i = 0, found_first = NO; i<FIRST_WORD_SIZE && found_first == NO; i++){
			if (strcmp(first_input, actions[i].name) == 0 ) {
				found_first = YES;
				which_action = i;
			}
		}
		
		if(found_first == NO){
			printf("Your first word is not a valid function\n");
		}
			for(i = 0, found_second = NO; strcmp(actions[which_action].instruction[i], "STOP") != 0 && found_second == NO && found_first == YES; i++){
			    if (strcmp(second_input, actions[which_action].instruction[i]) == 0 ) {
					found_second = YES;
				}
			    else if (atoi(second_input) != 0){       //Will allow user to enter any integer, for any attribute that would be an integer
			        found_second = YES;
			    }
				
			}
		if(found_first == YES && found_second == NO){
			printf("Your second word is not valid with your chosen action\n");
			return NO;
		}
		return YES;
		printf("\n\n%s %s\n\n\n", first_input,second_input);
	}
}

void update_values(draw *object, char *first_input, char *second_input){
	int i;
	char *first_word[FIRST_WORD_SIZE]= FIRST_WORD;
	printf("\nupdate");
	for(i = 0; i < FIRST_WORD_SIZE; i++){
		if(strcmp(first_word[i], first_input) == 0){
			printf("\nStrings match.\n");
			assign_value(object, i, second_input);
		}	
	}
}

void assign_value(draw *object, action_word i, char* input){
	printf("\nIn assign\n");
	switch(i){
		case colour:
			printf("\nFound colour: %s\n", input);
			object->colour = (char*)malloc(strlen(input)*sizeof(char));
			strcpy(object->colour, input);
			break;
		case move:
			object->move = (char*)malloc(strlen(input)*sizeof(char));
			strcpy(object->move, input);
			break;
		case size:
			object->size = atoi(input);
			break;
		case shape:
			object->shape = (char*)malloc(strlen(input)*sizeof(char));
			strcpy(object->shape, input);
			break;
		case startx:
		    object->startx = atoi(input);
		    break;
		case starty:
		    object->starty = atoi(input);
		    break; 
		case endx:
		    object->endx = atoi(input);
		    break; 
		case endy:
		    object->endy = atoi(input);
		    break;  

		case fractal:
		    object->fractal = (char*)malloc(strlen(input)*sizeof(char));
			strcpy(object->shape, input);
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

