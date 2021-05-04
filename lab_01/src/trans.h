#ifndef TRANS_H
#define TRANS_H
#include "main.h"

int trans_sign(const char *number, number_r *const trans_num);
int trans_point(const char *number, number_r *const trans_num);
int trans_e_sign(const char *number, number_r *const trans_num);
int trans_mantissa(const char *number, number_r *const trans_num);
int trans_power(const char *number, number_r *const trans_num);

#endif // TRANS_H
