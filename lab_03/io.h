#ifndef IO_H
#define IO_H

#include "defstrerr.h"

void print_hello();

void printf_input();

void clean_my();

func_var check_number(func_var *const number, const func_var l, const func_var r);

void print_matrix_std(const matrix_std_r *const matrix, FILE *const f);

void print_vector_std(const vector_std_r *const matrix, FILE *const f);

func_var print_coord(const matrix_std_r *matrix, const vector_std_r *vector,
                 const vector_std_r *res);

func_var print_std(const matrix_std_r *matrix, const vector_std_r *vector,
               const vector_std_r *res);

func_var print_razr(matrix_r *const matrix, matrix_r *const vector, matrix_r *const res, vector_std_r *true_res);

void print_matrix_sparse(matrix_r *matrix);

void print_coordin_one(matrix_std_r *matrix);

void print_coordin_one_v(vector_std_r *matrix);

void print_matrix(const matrix_std_r *const matrix, FILE *const stream);

#endif // IO_H
