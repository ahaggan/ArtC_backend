
#include "test_parser.h"

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
        fprintf(test_results, "\nValidate tests PASSED.\n");
    }
    else{
        fprintf(test_results, "\nValidate tests FAILED.\n");
    } 
    
    if (test_funclist(test_results) == PASSED){
        fprintf(test_results, "\nFunclist tests PASSED.\n");
    }
    else{
        fprintf(test_results, "\nFunclist tests FAILED.\n");
    } 
    
    if (test_check_action(test_results) == PASSED){
        fprintf(test_results, "\nCheck action tests PASSED.\n");
    }
    else{
        fprintf(test_results, "\nCheck action tests FAILED.\n");
    } 
    
    if (test_attribute(test_results) == PASSED){
        fprintf(test_results, "\nAttribute tests PASSED.\n");
    }
    else{
        fprintf(test_results, "\nAttribute tests FAILED.\n");
    } 
    
    if (test_check_if(test_results) == PASSED){
        fprintf(test_results, "\nCheck if tests PASSED.\n");
    }
    else{
        fprintf(test_results, "\nCheck if tests FAILED.\n");
    }
    
    if (test_statement(test_results) == PASSED){
        fprintf(test_results, "\nStatement tests PASSED.\n");
    }
    else{
        fprintf(test_results, "\nStatement tests FAILED.\n");
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

int test_funclist(FILE *test_results){
    Prog test_program;
    int pass_count = 0, no_of_tests = 0;
    initialise_words_array(&test_program);
    
    no_of_tests += 1;
    test_program.current_word = 0;
    strcpy(test_program.words[0], "}");
   
    if (funclist(&test_program) == TRUE){        
        fprintf(test_results, "\nFunclist test 1: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nFunclist test 1: Failed");
    }
    
    no_of_tests += 1;
    test_program.current_word = 0;
    test_program.words[0][0] = '\0';
   
    if (funclist(&test_program) == FALSE){        
        fprintf(test_results, "\nFunclist test 2: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nFunclist test 2: Failed");
    }
    
    if(pass_count == no_of_tests){
        return PASSED;
    }
    return FAILED;
    
}

int test_function(FILE *test_results){
    Prog test_program;
    int pass_count = 0, no_of_tests = 0;
    initialise_words_array(&test_program);
    
    no_of_tests += 1;
    test_program.current_word = 0;
    strcpy(test_program.words[0], "}");
   
    if (function(&test_program) == TRUE){        
        fprintf(test_results, "\nFunction test 1: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nFunction test 1: Failed");
    }
    
     if(pass_count == no_of_tests){
        return PASSED;
    }
    return FAILED;
}

int test_check_action(FILE *test_results){
    char test_word[WORD_LENGTH];
    
    int pass_count = 0, no_of_tests = 0;
    no_of_tests += 1;
    strcpy(test_word, "Hello");
    //Function should return FALSE
    if (check_action(test_word) == FALSE){        
        fprintf(test_results, "\nCheck action test 1: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nCheck action test 1: Failed");
    }
    
    no_of_tests += 1;
    strcpy(test_word, "colour");
    //Function should return TRUE
    if (check_action(test_word) == TRUE){        
        fprintf(test_results, "\nCheck action test 2: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nCheck action test 2: Failed");
    }
    
    no_of_tests += 1;
    strcpy(test_word, "Colour");
    //Function should return FALSE
    if (check_action(test_word) == FALSE){        
        fprintf(test_results, "\nCheck action test 3: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nCheck action test 3: Failed");
    }
    
    
    if(pass_count == no_of_tests){
        return PASSED;
    }
    return FAILED;
}

int test_statement(FILE *test_results){
    Prog test_program;
    int pass_count = 0, no_of_tests = 0;
    initialise_words_array(&test_program);
    create_struct_array(test_program.actions);
    initialise_interpreter_array(&test_program);
    
    no_of_tests += 1;
    test_program.current_word = 1;
    strcpy(test_program.words[0], "Hello"); //Arbitrary, needs to be there for function test.
    strcpy(test_program.words[1], "colour");
    strcpy(test_program.words[2], "blue");
    //Correct statement, should return TRUE
    if (statement(&test_program) == TRUE){        
        fprintf(test_results, "\nStatement test 1: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nStatement test 1: Failed");
    }
    
    no_of_tests += 1;
    test_program.current_word = 1;
    strcpy(test_program.words[0], "Hello"); //Arbitrary, needs to be there for function test.
    strcpy(test_program.words[1], "colour");
    strcpy(test_program.words[2], "Hello");
    //Incorrect statement, should return FALSE
    if (statement(&test_program) == FALSE){        
        fprintf(test_results, "\nStatement test 2: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nStatement test 2: Failed");
    }
    
    no_of_tests += 1;
    test_program.current_word = 1;
    strcpy(test_program.words[0], "Hello"); //Arbitrary, needs to be there for function test.
    strcpy(test_program.words[1], "colou");
    strcpy(test_program.words[2], "blue");
    //Incorrect statement, should return FALSE
    if (statement(&test_program) == FALSE){        
        fprintf(test_results, "\nStatement test 3: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nStatement test 3: Failed");
    }
    
    
    if(pass_count == no_of_tests){
        return PASSED;
    }
    return FAILED;
}

int test_attribute(FILE *test_results){
    
    Prog test_program;
    
    int pass_count = 0, no_of_tests = 0;
    initialise_words_array(&test_program);
    create_struct_array(test_program.actions);
    
    initialise_interpreter_array(&test_program);
    test_program.current_word = 2;
    no_of_tests += 1;
    strcpy(test_program.words[0], "arbitrary"); //Just needs to be a word other than if, for or to.
    
    strcpy(test_program.words[1], "colour");
    strcpy(test_program.words[2], "blue");
    //correct input, should return TRUE
    if (attribute(&test_program) == TRUE){        
        fprintf(test_results, "\nAttribute test 1: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nAttribute test 1: Failed");
    }
    
    test_program.current_word = 2;
    no_of_tests += 1;
    strcpy(test_program.words[0], "arbitrary");
    strcpy(test_program.words[1], "colour");
    strcpy(test_program.words[2], "Hello");
    //correct input, should return FALSE
    if (attribute(&test_program) == FALSE){        
        fprintf(test_results, "\nAttribute test 2: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nAttribute test 2: Failed");
    }
    
    test_program.current_word = 2;
    no_of_tests += 1;
    strcpy(test_program.words[0], "arbitrary");
    strcpy(test_program.words[1], "colour");
    strcpy(test_program.words[2], "");
    //correct input, should return FALSE
    if (attribute(&test_program) == FALSE){        
        fprintf(test_results, "\nAttribute test 3: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nAttribute test 3: Failed");
    }
    
    test_program.current_word = 2;
    no_of_tests += 1;
    strcpy(test_program.words[0], "arbitrary");
    strcpy(test_program.words[1], "size");
    strcpy(test_program.words[2], "10");
    //correct input, should return TRUE
    if (attribute(&test_program) == TRUE){        
        fprintf(test_results, "\nAttribute test 4: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nAttribute test 4: Failed");
    }
    
    if(pass_count == no_of_tests){
        return PASSED;
    }
    return FAILED;
}

int test_check_if(FILE *test_results){
    char test_word[WORD_LENGTH];
    
    int pass_count = 0, no_of_tests = 0;
    no_of_tests += 1;
    strcpy(test_word, "Hello");
    //Function should return FALSE
    if (check_if(test_word) == FALSE){        
        fprintf(test_results, "\nCheck if test 1: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nCheck if test 1: Failed");
    }
    
    no_of_tests += 1;
    strcpy(test_word, "iterations");
    //Function should return TRUE
    if (check_if(test_word) == TRUE){        
        fprintf(test_results, "\nCheck if test 2: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nCheck if test 2: Failed");
    }
    
    no_of_tests += 1;
    strcpy(test_word, "colour");
    //Function should return TRUE
    if (check_if(test_word) == TRUE){        
        fprintf(test_results, "\nCheck if test 3: Passed");
        pass_count += 1;
    }
    else{
        fprintf(test_results, "\nCheck if test 3: Failed");
    }
    
    if(pass_count == no_of_tests){
        return PASSED;
    }
    return FAILED;
}



    /*NEED TO TEST THESE
    If everything works, just a message saying all tests work.
    
    
    test_function - done but very basic, relys on other tests not done yet.
    test_loop
    test_for_loop
    test_conditional

    
    test_create_struct_array
    
    

    DONT NEED TO TEST, either manually assigning values or only called if previous tested functions work correctly!
    void create_struct_array(action *actions);
    void clear_buffer(void);
    void update_values(Draw *fractal, char *first_input, char *second_input);
    void assign_value(Draw *fractal, action_word i, char *input);
    
    
    printf("\nParser passed %d tests!\n", test_count);
 */
