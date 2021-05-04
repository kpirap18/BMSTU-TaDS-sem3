#ifndef ARRAY_C
#define ARRAY_C

#include "defstrerr.h"

arrstack_r *create_stack_arr(const int capacity);

func_var free_stack_arr(arrstack_r *stack);

func_var is_full_arr(arrstack_r *stack);

func_var is_empty_arr(arrstack_r *stack);

func_var push_arr(arrstack_r *stack, const char data);

func_var input_stack_arr(const int count, arrstack_r *stack, int f, FILE *ff);

func_var output_stack_arr(arrstack_r *stack);

char pop_arr(arrstack_r *stack);

arr_r *create_array(const int capacity);

void output_array(const arr_r arr);

int free_array(arr_r *arr);

int check_brackets_arr(arrstack_r *arr);
#endif // ARRAY_C

