#ifndef FUNCWITHMATRIX_H
#define FUNCWITHMATRIX_H

#include "defstrerr.h"

func_var matrix_rr_create(matrix_r *const mat, func_var r, func_var c);

func_var matrix_std_create(matrix_std_r *const mat, func_var r, func_var c);

func_var input_matrix_rr(matrix_r *const matrix, FILE *f, func_var c);

void ins_elem(matrix_r *const matrix, func_var i, func_var j, func_var val);

void ins_elem_list(matrix_r *const matrix, func_var index, func_var val, func_var r);

void parsing_matrix(matrix_r *from, matrix_std_r *to);

void print_matrix(const matrix_std_r *const matrix, FILE *const f);
#endif // FUNCWITHMATRIX_H
