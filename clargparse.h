#ifndef __CLARG_PARSE_H__
#define __CLARG_PARSE_H__

#include <stdlib.h>
#include <stddef.h>

// clargparser: command line arugment parser
struct argtableentry {
  char *flag;
  char hasarg;
  void *value;
  void (*parseFunc)(void *value, char *arg);
};
typedef struct argtableentry argte;

void proc_args(int argc, char *argv[], argte argtable[], size_t argrows);
argte *search_arg_table(argte argtable[], size_t argrows, char *flag);

void proc_int_arg(void *value, char *arg);
void proc_str_arg(void *value, char *arg);
#endif
