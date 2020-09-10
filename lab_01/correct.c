/*! \defgroup <correct> (The Correct module)
  @{
  */
/**
  * \file correct.c
  * \brief File with the code to check
  * \version 1.0
  * \date 09.09.2020
  @}
  */

#include "correct.h"

/*!
 * \brief correct_intfloat_number_mantissa - Checking the mantissa of a number.
 * \param number - Pointer to a structure for a number.
 * \return OK if all is well, otherwise CORRECT_ERROR.
 */
int correct_intfloat_number_mantissa(number_r *number)
{
    short int len = strlen(number->mantissa),
            pos_in_mantissa = 0;
    char simbol_correct;

    if (number->point_pos == -42)
    {
        for ( ; pos_in_mantissa < len; pos_in_mantissa++)
        {
           simbol_correct = number->mantissa[pos_in_mantissa];

           if (simbol_correct < '0' || simbol_correct > '9')
               return CORRERCT_ERROR;
        }
    }
    else
    {
        short int end_corr = number->point_pos;
        pos_in_mantissa = 0;

        for ( ; pos_in_mantissa < end_corr; pos_in_mantissa++)
        {
            simbol_correct = number->mantissa[pos_in_mantissa];

            if (simbol_correct < '0' || simbol_correct > '9')
                return CORRERCT_ERROR;
        }
    }

    return OK;
}

/*!
 * \brief correct_power - Checking the power of a number.
 * \param number - Pointer to a structure for a number.
 * \return OK if all is well, otherwise CORRECT_ERROR.
 */
int correct_power(number_r *number)
{
    if (correct_intfloat_number_mantissa(number) == OK)
    {
        if (number->power[0] != PLUS && number->power[0] != MINUS)
            return CORRERCT_ERROR;

        short int len_power = strlen(number->power);
        char simbol_correct;

        for (short int pos_in_power = 1; pos_in_power < len_power; pos_in_power++)
        {
            simbol_correct = number->power[pos_in_power];

            if (simbol_correct < '0' || simbol_correct > '9')
                return CORRERCT_ERROR;
        }
    }
    else
        return CORRERCT_ERROR;

    return OK;
}

/*!
 * \brief power - Exponentiation.
 * \param a - number.
 * \param n - power.
 * \return
 */
int power(const int a, const int n)
{
    if (n == 0)
        return 1;

    return (a * power(a, n - 1));
}

/*!
 * \brief trans_power_to_int - Transporting a power string to a number.
 * \param number - Pointer to a structure for a number.
 * \return OK if all is well, otherwise CORRECT_ERROR.
 */
int trans_power_to_int(number_r *number)
{
    if (correct_power(number) != OK)
        return CORRERCT_ERROR;

    short int power_len = strlen(number->power);
    int power_int = 0;

    for (short int pos_int = 1; pos_int < power_len; pos_int++)
    {
        power_int += (number->power[pos_int] - '0') *
                      power(10, power_len - pos_int - 1);
    }

    if (number->power[0] == '+')
        number->power_int = power_int;
    else
        number->power_int = -1 * power_int;

    return OK;
}

/*!
 * \brief type_int_or_float - Defining the number type.
 * \param number - Pointer to a structure for a number.
 * \return INT, FLOAT or CORRECT_ERROR.
 */
int type_int_or_float(number_r *number)
{
    if (trans_power_to_int(number) != OK)
        return CORRERCT_ERROR;

    if ((number->point_pos == -42 && number->e_pos == -41) ||
            (number->point_pos == -42 && number->e_pos != -41 &&
             number->power[0] == PLUS && number->power[1] >= '0'))
        return INT;
    else
        return FLOAT;
}

/*!
 * \brief if_its_null - Checking for zero.
 * \param number - Pointer to a structure for a number.
 * \return TRUE or FALSE.
 */
int if_its_null(number_r *const number)
{
    short int len_num = strlen(number->mantissa);

    for (short int pos_num = 0; pos_num < len_num; pos_num++)
    {
        if (number->mantissa[pos_num] != '0')
            return FALSE;
    }
    return TRUE;
}
