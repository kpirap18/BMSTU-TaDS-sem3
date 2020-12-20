#ifndef _IO_H_
#define _IO_H_

#include "app.h"
#include <stdio.h>

void print_hello();

void printf_input();

int check_number(int *const number, const int l, const int r, int flag);

matrix_r *read_matrix(FILE *f);

void print_matrix(FILE *f, matrix_r *graph);

void show_graph(const matrix_r *graph);

int show_way(const matrix_r *way, int s);

#endif // _IO_H_
