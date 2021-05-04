#ifndef IO_H
#define IO_H

#include "my_main.h"

void print_hello();
void printf_input();
void clean_my();
void print_pos_table(const table_r table, func_var k);
void print_table(const table_r table, boolean keys);
void print_keys(const table_r table);
func_var input_room_delet(func_var *room);
func_var input_ch_sort();
void print_res(table_r *const table, int64_t tact, int64_t tact_qsort,
               func_var type_sort, func_var type_table);
void clean_tab(table_r *const table);
#endif // IO_H
