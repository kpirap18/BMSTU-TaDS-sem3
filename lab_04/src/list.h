#ifndef LIST_H
#define LIST_H

#include "defstrerr.h"

liststack_r *create_stack_list(const char data);

func_var is_full_list(liststack_r *stack_list, const func_var lim);

func_var is_empty_list(liststack_r *stack_list);

func_var push_list(liststack_r **stack_list, const char data, const func_var lim);

func_var input_stack_list(const func_var c, liststack_r **stack_list,
                          const func_var lim, int f, FILE *ff);

func_var output_stack_list(liststack_r *stack_list);

void check_top_list(liststack_r *stack_list, arr_r *arr);

char pop_list(liststack_r **stack_list, arr_r *arr);

func_var free_stack_list(liststack_r **stack_list, arr_r *arr);

int check_brackets_list(liststack_r *arr);
#endif // LIST_H
