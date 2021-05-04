#ifndef READ_H
#define READ_H

#include "my_main.h"

void gluing_address(table_r *table, char *city, char *street,
                     func_var num_home, func_var app, func_var i);
func_var read_address(table_r *table, FILE *f, func_var i);
func_var read_other(table_r *table, FILE *f, func_var i);
func_var read_primary(table_r *table, FILE *f, func_var i);
func_var read_secondary(table_r *const table, FILE *f, func_var i);
func_var read_min_max(int *min, int *max);

#endif // READ_H
