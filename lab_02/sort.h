#ifndef SORT_H
#define SORT_H

#include "my_main.h"
#include "load.h"

int64_t tact(void);
func_var sort_qsort_vs_bub(table_r *const table);
int compare_key(const void *v1, const void *v2);
int compare_table(const void *v1, const void *v2);
void swap(boolean table, void *v1, void *v2);
void bubble_sort(table_r *const table, boolean tabl);

#endif // SORT_H
