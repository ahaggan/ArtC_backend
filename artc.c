/* Checks two word user input. Also creates an array of action structures,
*  as many as there are words in the FIRST_WORD array. 
*  It then assigns each structure's name element with a word from said array
*  It also assigns, for each action in turn, the corresponding attributes.
*  When the NEXT word is found, the assignment is moved to the next action.
*  Uses the structures to validate user inputs, making sure action linked to
*  attribute.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FIRST_WORD { "colours", "move", "size" }
#define FIRST_WORD_SIZE 3
#define SECOND_WORD { "red", "green", "blue", "STOP", "NEXT", "up", "down", "left", "right", "STOP", "NEXT", "10", "20", "STOP", "NEXT"}
#define SECOND_WORD_SIZE 15
#define YES 1
#define NO 0

typedef struct action{
	char *name;
	char **instruction;
} action;



void create_struct_array(action *actions);
void clear_buffer(void);
void get_input(action *actions, char *first_input, char *second_input);

int main() {

	char first_input[20];
	char second_input[20];
	action actions[FIRST_WORD_SIZE];
	
	create_struct_array(actions);
	//create_struct_array(&actions[0]);
	
	get_input(actions,first_input,second_input);
	printf("From main: %s %s\n", first_input, second_input);

	return 0;
}

void get_input(action * actions, char *first_input, char *second_input) {
	
	//char *first_word[] = FIRST_WORD;
	//char *second_word[] = SECOND_WORD;
	int found_first;
	int found_second;
	int which_action;
	int i;
	do {

		if (scanf("%s %s", first_input, second_input) != 2 ) {

			printf("You have entered the wrong number of instructions");
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
			}
			if(found_first == YES && found_second == NO){
				printf("Your second word is not valid with your chosen action\n");
			}
			printf("\n\n%s %s\n\n\n", first_input,second_input);
		}
		clear_buffer();
	} while (found_first == NO || found_second == NO);
}

void clear_buffer(void){

	while (getchar() != '\n'){
	}
	
}

void create_struct_array(action *actions)
{
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
			printf("\nFirst word: %s\n", actions[i].name);
			printf("\nSecond word: %s\n", actions[i].instruction[l]);
		}
		cnt = 0;
		array_cnt += 1;
	}	
}


