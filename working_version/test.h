#include "parser.h"

#define PASSED 1
#define FAILED 0
 
int test_initialise_words(FILE *test_results);
int test_initialise_interpreter(FILE *test_results);
int test_validate(FILE *test_results);
int test_funclist(FILE *test_results);
int test_function(FILE *test_results);
int test_check_action(FILE *test_results);
int test_attribute(FILE *test_results);
