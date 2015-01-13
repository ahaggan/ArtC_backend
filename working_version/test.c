
#include "test.h"

void test_parser(void){
    FILE *test_results;
    //int test_count= 0;
    printf("\nTEST FUNCTION!!!!\n");
    test_results = fopen("test_results.txt", "w");
    fprintf(test_results, "\nPARSER TEST\nBelow are the test results for this module\n");
    if (test_initialise_words(test_results) == PASSED){
        fprintf(test_results, "\nInitialise words array test PASSED.\n");
    }
    else{
        fprintf(test_results, "\nInitialise words array test FAILED.\n");
    } 
    
    if (test_initialise_interpreter(test_results) == PASSED){
        fprintf(test_results, "\nInitialise interpreter array test PASSED.\n");
    }
    else{
        fprintf(test_results, "\nInitialise interpreter array test FAILED.\n");
    } 
    
    if (test_validate(test_results) == PASSED){
        fprintf(test_results, "\nValidate test PASSED.\n");
    }
    else{
        fprintf(test_results, "\nValidate test FAILED.\n");
    } 
    fclose(test_results);
    
}

int test_initialise_words(FILE *test_results){
    Prog test_program;
    int i;
    initialise_words_array(&test_program);
    for(i = 0; i < MAX_WORDS; i++){
        if(test_program.words[i][0] != '\0'){
            return FAILED;
        }
    }
    return PASSED;
}

int test_initialise_interpreter(FILE *test_results){
    Prog test_program;
    int i;
    initialise_interpreter_array(&test_program);
    for(i = 0; i < NO_OF_INSTRUCTIONS; i++){
        if(test_program.interpreter[i][0] != '\0'){
            return FAILED;
        }
    }
    return PASSED;
}

int test_validate(FILE *test_results){
    Prog test_program;
    int pass_count = 0, no_of_tests = 0;
    initialise_words_array(&test_program);
    
    //passes an incorrect word to instrctlst, this should be passes along and eventually return FALSE.
    
    no_of_tests += 1;
    test_program.current_word = 0;
    strcpy(test_program.words[0], "Hello");
   
    if (validate(&test_program) == FALSE){        
        fprintf(test_results, "\nValidate test 1: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nValidate test 1: Failed");
    }
    
    //passes an incorrect program end so should return FALSE
    no_of_tests += 1;
    strcpy(test_program.words[0], "run");
    strcpy(test_program.words[1], "program");
    if (validate(&test_program) == FALSE){
        fprintf(test_results, "\nValidate test 2: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nValidate test 2: Failed");
    }
   
    if(pass_count == no_of_tests){
        return PASSED;
    }
    return FAILED;
}
    /*NEED TO TEST THESE
    If everything works, just a message saying all tests work.
    test_validate
    test_funclist
    test_function
    test_loop
    test_for_loop
    test_conditional
    test_statement
    test_attribute
    test_check_action
    test_check_if
    test_create_struct_array
    
    

    DONT NEED TO TEST, either manually assigning values or only called if previous tested functions work correctly!
    void create_struct_array(action *actions);
    void clear_buffer(void);
    void update_values(Draw *fractal, char *first_input, char *second_input);
    void assign_value(Draw *fractal, action_word i, char *input);
    
    
    printf("\nParser passed %d tests!\n", test_count);
 */
