//ERWEf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FIRST_WORD { "colours", "move", "size" }
#define FIRST_WORD_SIZE 3
#define SECOND_WORD { "10", "20", "red", "green", "blue", "up", "down", "left", "right" }
#define SECOND_WORD_SIZE 9
#define YES 1
#define NO 0

typedef struct action{
	char *name;
	char **instruction;
} action;



action* create_struct_array(void);
void clear_buffer(void);
void get_input(char *first_input, char *second_input);

int main() {

	char first_input[20];
	char second_input[20];
	action *actions;

	action = create_struct_array();
	create_struct_array(&actions[0]);

	printf("\nstruct word:%s\n", actions[0].name);
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

void create_struct_array(action *actions[FIRST_WORD_SIZE])
{
	int i;
	char *first_word[FIRST_WORD_SIZE]= FIRST_WORD;
	for(i = 0; i < FIRST_WORD_SIZE; i++){
		actions[i]->name = (char*)malloc(sizeof(char[strlen(first_word[i])]));
		actions[i]->name = first_word[i];
	}
}


