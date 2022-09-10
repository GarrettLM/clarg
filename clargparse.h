#ifndef __CLARG_PARSE_H__
#define __CLARG_PARSE_H__

#include <stdlib.h>
#include <stddef.h>

// clargparser: command line arugment parser
struct argtableentry {
  char *flag;
  void *value;
  void (*parseFunc)(void *value);
};
typedef struct argtableentry argte;

void proc_args(int argc, char *argv[], argte argtable[], size_t argrows);

//Returns NULL if there isn't a next arg
char* next_arg();
void proc_int_arg(void *value);
void proc_str_arg(void *value);
#endif //__CLARG_PARSE_H__
