#ifndef _IO_H_
#define _IO_H_

#include "app.h"

void print_hello();

void printf_input();

int check_number(int *const number, const int l, const int r, int flag);

int readtolist(FILE *f, node_t **head, node_t **headbal, int *rc);

void readtotable(FILE *f, inttable_t **table);

#endif // _IO_H_