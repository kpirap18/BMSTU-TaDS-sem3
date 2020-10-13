#ifndef IO_H
#define IO_H

#include "defstrerr.h"

void print_hello();

void printf_input();

void clean_my();

func_var check_number(func_var *const number, const func_var l, const func_var r);

void print_matrix(const matrix_std_r *const matrix, FILE *const f);

func_var print_coord(const matrix_std_r *matrix, const matrix_std_r *vector,
                 const matrix_std_r *res);

func_var print_std(const matrix_std_r *matrix, const matrix_std_r *vector,
               const matrix_std_r *res);

func_var print_razr(matrix_r *const matrix, matrix_r *const vector, matrix_r *const res);

#endif // IO_H
