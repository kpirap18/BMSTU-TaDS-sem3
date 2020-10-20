#ifndef ARRAY_C
#define ARRAY_C

#include "defstrerr.h"

arrstack_r *create_stack_arr(const int capacity);

func_var free_stack_arr(arrstack_r *stack);

func_var is_full_arr(arrstack_r *stack);

func_var is_empty_arr(arrstack_r *stack);

func_var push_arr(arrstack_r *stack, const char data);

func_var input_stack_arr(const int count, arrstack_r *stack);

func_var output_stack_arr(arrstack_r *stack);

char pop_arr(arrstack_r *stack);
#endif // ARRAY_C
