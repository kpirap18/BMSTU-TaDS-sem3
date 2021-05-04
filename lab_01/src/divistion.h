#ifndef DIVISTION_H
#define DIVISTION_H

#include "main.h"
#include "correct.h"

int int_bigger_float(number_r *const int_num, number_r *const float_num);
void new_mantissa(number_r *const number, short int len);
int result_mantissa(number_r *const int_num, number_r *const float_num);
int division_algorithm(number_r *const int_num, number_r *const float_num,
                       number_r *const result_num);

#endif // DIVISTION_H
