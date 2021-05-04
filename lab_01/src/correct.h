#ifndef CORRECT_H
#define CORRECT_H

#include "main.h"

int correct_intfloat_number_mantissa(number_r *number);
int correct_power(number_r *number);
int power(const int a, const int n);
int trans_power_to_int(number_r *number);
int type_int_or_float(number_r *number);
int if_its_null(number_r *const number);

#endif // CORRECT_H
