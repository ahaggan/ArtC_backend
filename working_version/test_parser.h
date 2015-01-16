#include "parser.h"

#define PASSED 1
#define FAILED 0

//WHITE BOX TESTS - Each function below tests a single function in the Parser
int test_initialise_words(FILE *test_results);
int test_initialise_interpreter(FILE *test_results);
int test_validate(FILE *test_results);
int test_funclist(FILE *test_results);
int test_function(FILE *test_results);
int test_check_action(FILE *test_results);
int test_attribute(FILE *test_results);
int test_check_if(FILE *test_results);
int test_statement(FILE *test_results);
int test_conditional(FILE *test_results);
int test_loop(FILE *test_results);
int test_for_loop(FILE *test_results);

//BLACK BOX TESTS - This function tests the whole Parser module
int test_whole(FILE *test_results);
