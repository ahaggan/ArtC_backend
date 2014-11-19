/* Checks two word user input. Also creates an array of action structures,
*  as many as there are words in the FIRST_WORD array. 
*  It then assigns each structure's name element with a word from said array
*  It also assigns, for each action in turn, the corresponding attributes.
*  When the NEXT word is found, the assignment is moved to the next action.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FIRST_WORD { "colours", "move", "size" }
#define FIRST_WORD_SIZE 3
#define SECOND_WORD { "red", "green", "blue", "NEXT", "up", "down", "left", "right", "NEXT", "10", "20", "NEXT"}
#define SECOND_WORD_SIZE 12
#define YES 1
#define NO 0

typedef struct action{
	char *name;
	char **instruction;
} action;



void create_struct_array(action *actions);
void clear_buffer(void);
void get_input(char *first_input, char *second_input);

int main() {

	char first_input[20];
	char second_input[20];
	action actions[FIRST_WORD_SIZE];

	create_struct_array(actions);
	//create_struct_array(&actions[0]);

	printf("\nstruct word: %s\n", actions[0].name);
	printf("\nFirst instruction: %s\n", actions[0].instruction[0]);
	get_input(first_input,second_input);
	printf("From main: %s %s\n", first_input, second_input);

	return 0;
}

void get_input(char *first_input, char *second_input) {
	
	char *first_word[] = FIRST_WORD;
	char *second_word[] = SECOND_WORD;
	int found_first;
	int found_second;
	int i;
	do {

		if (scanf("%s %s", first_input, second_input) != 2 ) {

			printf("You have entered the wrong number of instructions");
		}
		
		else {
			for(i = 0, found_first = NO; i<FIRST_WORD_SIZE && found_first == NO; i++){
				if (strcmp(first_input, first_word[i]) == 0 ) {
					found_first = YES;
				}
			}
			if(found_first == NO){
				printf("Your first word is not a valid function\n");
			}

			for(i=0, found_second = NO; i<SECOND_WORD_SIZE && found_second == NO && found_first == YES; i++){
				if (strcmp(second_input, second_word[i]) == 0 ) {
					found_second = YES;
				}
			}
			if(found_first == YES && found_second == NO){
				printf("Your second word is not a valid function\n");
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
				printf("\nSecond word: %s\n", second_word[j]);
				cnt += 1;
		}
		array_cnt += cnt;
		
		actions[i].instruction = (char**)malloc(cnt * sizeof(char*));
		
		for(k = array_cnt - cnt; k < array_cnt; k++){
		
			actions[i].instruction[k] = (char*)malloc(strlen(second_word[k]) * sizeof(char));
			
			for(l = 0; l < strlen(second_word[k]); l++){
				actions[i].instruction[k][l] = second_word[k][l];
			}
		}
		cnt = 0;
		array_cnt += 1;
	}	
}


