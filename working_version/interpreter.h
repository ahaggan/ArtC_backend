#include "parser.h"

int check_condition(Prog* program, int iteration);
void search_for_end(Prog* program);
void assign_value(Prog* program, int iteration);

void interpret_size_word(Prog *program, int iteration);
void interpret_thick_word(Prog *program, int iteration);
