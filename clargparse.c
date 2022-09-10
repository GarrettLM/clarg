#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "clargparse.h"

static int arg_count;
static char **arg_vect;
static int arg_index;

static inline argte *search_arg_table(argte argtable[], size_t argrows, char *flag);
static inline char* in_next_arg();

void proc_args(int argc, char *argv[], argte argtable[], size_t numrows) {
	arg_count = argc;
	arg_vect = argv;
	for (arg_index = 1; arg_index < argc;) {
		char *arg = in_next_arg(argv);
    argte *argrow = search_arg_table(argtable, numrows, arg);
    if (argrow == NULL) {
      printf("Failed to parse argument: %s\n", arg);
      continue;
    }
    if (argrow->parseFunc != NULL) {
      argrow->parseFunc(argrow->value);
    } else *((bool *) argrow->value) = true;
	}
}

static inline argte *search_arg_table(argte argtable[], size_t numrows, char *flag) {
  for (size_t i = 0; i < numrows; i++) {
    if (!strcmp(argtable[i].flag, flag)) return argtable + i;
  }
  return NULL;
}

//Implemented as inline to improve efficiency of library functions
static inline char* in_next_arg() {
	//Make sure there is a next argument
	return arg_index < arg_count ? arg_vect[arg_index++] : NULL;
}

//This is a wrapper for the in_next_arg static inline function
char* next_arg() {
	return in_next_arg();
}

void proc_int_arg(void *value) {
	char *arg = in_next_arg();
	int *int_val = (int *) value;
	*int_val = arg != NULL ? atoi(arg) : 0;
}

void proc_str_arg(void *value) {
	char *arg = in_next_arg();
	*((char **)value) = arg;
}
