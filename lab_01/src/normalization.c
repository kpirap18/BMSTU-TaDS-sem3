/*! \defgroup <normalization> (The Normalization module)
  @{
  */
/**
  * \file normalization.c
  * \brief File with code for normalization
  * \version 1.0
  * \date 09.09.2020
  @}
  */

#include "normalization.h"

/*!
 * \brief normalization_mantissa - The normalization of the representation of the mantissa.
 * \param number - Pointer to a structure for a number.
 * \return OK if all is well.
 */
int normalization_mantissa(number_r *const number)
{
    short int len_mantissa = strlen(number->mantissa);

    if (number->point_pos != -42)
    {
        for (short int pos_num = number->point_pos; pos_num < len_mantissa;
             pos_num++)
        {
            number->mantissa[pos_num] = number->mantissa[pos_num + 1];
        }

        number->mantissa[len_mantissa] = '\0';
        number->power_int += -1 * (len_mantissa - 1 - number->point_pos);

        for (short int pos_num = len_mantissa - 1;
             pos_num < MAX_LEN_MANTISSA; pos_num++)
        {
            number->mantissa[pos_num] = '0';
            number->power_int--;
        }
    }
    else
    {
        for (short int pos_num = len_mantissa;
             pos_num < MAX_LEN_MANTISSA; pos_num++)
        {
            number->mantissa[pos_num] = '0';
            number->power_int--;
        }
    }
    number->mantissa[MAX_LEN_MANTISSA - 1] = '\0';

    return OK;
}

/*!
 * \brief rewrite_lead_null - Structuring zeros in a number.
 * \param number - Pointer to a structure for a number.
 * \return
 */
void rewrite_lead_null(number_r *const number)
{
    short int len_mantissa = strlen(number->mantissa);
    short int count = 0;

    while (number->mantissa[0] == '0' && count != len_mantissa - 1)
    {
        //printf("%d ", count);
        for (short int pos_num = 0; pos_num < len_mantissa - 1; pos_num++)
        {
            char change = number->mantissa[pos_num];
            number->mantissa[pos_num] = number->mantissa[pos_num + 1];
            number->mantissa[pos_num + 1] = change;
        }

        count++;
    }

    number->mantissa[len_mantissa - count] = '\0';

    len_mantissa = strlen(number->mantissa);

    for (short int pos_num = len_mantissa; pos_num > 0; pos_num--)
        number->mantissa[pos_num] = number->mantissa[pos_num - 1];

    number->mantissa[0] = '0';
    number->mantissa[len_mantissa] = '\0';
}
