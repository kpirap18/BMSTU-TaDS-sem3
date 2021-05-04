/*! \defgroup <trans> (The Trans module)
  @{
  */
/**
  * \file trans.c
  * \brief File with the transport code
  * \version 1.0
  * \date 09.09.2020
  @}
  */

#include "trans.h"

/*!
 * \brief trans_sign - Transportation of the number sign.
 * \param number - Pointer to the number being processed.
 * \param trans_num - Pointer to a structure for a number.
 * \return OK if all is well, otherwise TRANS_ERROR.
 */
int trans_sign(const char *number, number_r *const trans_num)
{
    if (number[0] == '+')
    {
        trans_num->sing_num = PLUS;
        return OK;
    }
    else if (number[0] == '-')
    {
        trans_num->sing_num = MINUS;
        return OK;
    }

    return TRANS_ERROR;
}

/*!
 * \brief trans_point - Transportation of a point sign number.
 * \param number - Pointer to the number being processed.
 * \param trans_num - Pointer to a structure for a number.
 * \return OK if all is well, otherwise TRANS_ERROR.
 */
int trans_point(const char *number, number_r *const trans_num)
{
    if (trans_sign(number, trans_num) != OK)
        return TRANS_ERROR;

    short int pos_in_num = 0;
    short int point_pos = -41, flag = FALSE;

    short int len_number = strlen(number);

    for ( ; pos_in_num < len_number; pos_in_num++)
    {
        if (number[pos_in_num] == '.')
        {
            if (flag == FALSE)
            {
                point_pos = pos_in_num;
                flag = TRUE;
            }
            else
                return TRANS_ERROR;
        }
    }

    trans_num->point_pos = point_pos - 1;
    return OK;
}

/*!
 * \brief trans_e_sign - Transporting the sign of the exponent of a number.
 * \param number - Pointer to the number being processed.
 * \param trans_num - Pointer to a structure for a number.
 * \return OK if all is well, otherwise TRANS_ERROR.
 */
int trans_e_sign(const char *number, number_r *const trans_num)
{
    if (trans_point(number, trans_num) != OK)
        return TRANS_ERROR;

    short int pos_in_num = 0;
    short int e_pos;

    short int len_number = strlen(number);

    for ( ; pos_in_num < len_number; pos_in_num++)
    {
        if (number[pos_in_num] == 'E')
        {
            e_pos = pos_in_num;
            break;
        }

    }

    if (pos_in_num == len_number)
        e_pos = -41;

    trans_num->e_pos = e_pos;
    return OK;
}

/*!
 * \brief trans_mantissa - Transporting the mantissa of a number.
 * \param number - Pointer to the number being processed.
 * \param trans_num - Pointer to a structure for a number.
 * \return OK if all is well, otherwise TRANS_ERROR.
 */
int trans_mantissa(const char *number, number_r *const trans_num)
{
    if (trans_e_sign(number, trans_num) != OK)
        return TRANS_ERROR;

    short int start = 1, end;

    if (trans_num->e_pos == -41)
        end = strlen(number);
    else
        end = trans_num->e_pos;

    if ((trans_num->point_pos == -42 && \
            end - start > 30) ||
            (end - start > 31 && \
            trans_num->point_pos != -42))
        return TRANS_ERROR;

    for ( ; start < end; start++)
        trans_num->mantissa[start - 1] = number[start];

    trans_num->mantissa[start - 1] = '\0';

    return OK;
}

/*!
 * \brief trans_power - Transporting a power of number.
 * \param number - Pointer to the number being processed.
 * \param trans_num - Pointer to a structure for a number.
 * \return OK if all is well, otherwise TRANS_ERROR.
 */
int trans_power(const char *number, number_r *const trans_num)
{
    if (trans_mantissa(number,trans_num) != OK)
        return TRANS_ERROR;

    short int len = strlen(number);

    if (trans_num->e_pos == -41)
    {
        trans_num->power[0] = '+';
        trans_num->power[1] = '0';
        trans_num->power[2] = '\0';

        return OK;
    }
    else
    {
        short int start = trans_num->e_pos + 1, end = len;

        if ((end - start) > 7 - 1)
            return ERROR;

        short int pos_in_num = 0;

        for ( ; start < end; start++, pos_in_num++)
            trans_num->power[pos_in_num] = number[start];

        trans_num->power[pos_in_num] = '\0';

        return OK;
    }
}
