#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "app.h"
#include <stdio.h>

matrix_r *create_matrix(int count);

double **allocate_matrix(int count);

void free_matrix(double **data, int count);

matrix_r *all_way(const matrix_r *graph);

void timeget();

#endif // _GRAPH_H_
