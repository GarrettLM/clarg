#include <stdio.h>
#include "clargparse.h"

void proc_args(int argc, char *argv[], argte argtable[], size_t numrows) {
	for (int i = 0; i < argc; i++) {
		if (*(argv[i]) == '-') {
      argte *argrow = search_arg_table(argtable, numrows, *(argv[i]+1));
      if (argrow == NULL) {
        printf("Failed to parse argument: %s\n", argv[i]);
        exit(1);
      }
      if (argrow->hasarg) {
        i++;
        if (argrow->parseFunc != NULL)
          argrow->parseFunc(argrow->value, argv[i]);
      }
    }
	}
}

argte *search_arg_table(argte argtable[], size_t numrows, char flag) {
  for (size_t i = 0; i < numrows; i++) {
    if (argtable[i].flag == flag) return argtable + i;
  }
  return NULL;
}

void proc_int_arg(void *value, char *arg) {
	int *int_val = (int *) value;
	*int_val = atoi(arg);
}

void proc_str_arg(void *value, char *arg) {
	*((char **)value) = arg;
}
