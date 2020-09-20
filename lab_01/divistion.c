/*! \defgroup <divistion> (The Division module)
  @{
  */
/**
  * \file divistion.c
  * \brief File with the division code
  * \version 1.0
  * \date 09.09.2020
  @}
  */

#include "divistion.h"

/*!
 * \brief int_bigger_float - Determining which number is greater.
 * \param int_float - Pointer to a structure for an integer.
 * \param float_num - Pointer to a structure for a float.
 * \return TRUE if all is well, otherwise FALSE.
 */
int int_bigger_float(number_r *const int_num, number_r *const float_num)
{
    short int len_mantissa = strlen(int_num->mantissa);

    for (short int pos_num = 0; pos_num < len_mantissa; pos_num++)
    {
        if ((int)(int_num->mantissa[pos_num] - float_num->mantissa[pos_num] > 0))
            return TRUE;
        else if ((int)(int_num->mantissa[pos_num] -
                       float_num->mantissa[pos_num] < 0))
            return FALSE;
    }

    return TRUE;
}

/*!
 * \brief new_mantissa - The correction of the mantissa.
 * \param number - Pointer to a structure for a number.
 * \param len - The number by which to move the mantissa.
 * \return
 */
void new_mantissa(number_r *const number, short int len)
{
    for (short int pos_num = 0;
         pos_num < MAX_LEN_MANTISSA - len - 1; pos_num++)
        number->mantissa[pos_num] = number->mantissa[pos_num + len];

    for (short int pos_num = MAX_LEN_MANTISSA - len - 1;
         pos_num < MAX_LEN_MANTISSA - 1; pos_num++)
        number->mantissa[pos_num] = '0';
}

/*!
 * \brief result_mantissa - The calculation of the result mantissa.
 * \param int_float - Pointer to a structure for an integer.
 * \param float_num - Pointer to a structure for a float.
 * \return OK if all is well, otherwise DIV_ERROR.
 */
int result_mantissa(number_r *const int_num, number_r *const float_num)
{
    if (int_bigger_float(int_num, float_num) == TRUE)
    {
        short int pos_num = strlen(float_num->mantissa) - 1;
        for ( ; pos_num >= 0; pos_num--)
        {
            if (int_num->mantissa[pos_num] - float_num->mantissa[pos_num] >= 0)
                int_num->mantissa[pos_num] -= float_num->mantissa[pos_num] - '0';
            else
            {
                short int pos_num_1 = pos_num - 1;
                while (int_num->mantissa[pos_num_1] - '0' == 0)
                    --pos_num_1;
                int_num->mantissa[pos_num_1]--;
                pos_num_1++;
                for ( ;pos_num_1 < pos_num; pos_num_1++)
                    int_num->mantissa[pos_num_1] += 9;

                int_num->mantissa[pos_num] += 10 -
                        (float_num->mantissa[pos_num] - '0');
            }
        }

        return OK;
    }

        return DIV_ERROR;
}

/*!
 * \brief division_algorithm - The division algorithm.
 * \param int_float - Pointer to a structure for an integer.
 * \param float_num - Pointer to a structure for a float.
 * \param result_num - Pointer to a structure for a result number.
 * \return OK if all is well, otherwise DIV_ERROR.
 */
int division_algorithm(number_r *const int_num, number_r *const float_num,
                       number_r *const result_num)
{
    if (if_its_null(float_num))
    {
        printf("YOU CAN'T DIVIDE BY ZERO");
        return DIV_ERROR;
    }
    if (if_its_null(int_num))
    {
        result_num->sing_num = PLUS;
        result_num->mantissa[0] = '0';
        result_num->mantissa[1] = '0';
        result_num->power_int = 0;
        result_num->mantissa[2] = '\0';
        return OK;
    }

    if (abs(int_num->power_int - float_num->power_int) > 99999)//oiuygtfrdesrdtfyghujioi
    {
        printf("OVERFLOW OF ORDER!!!");
        return DIV_ERROR;
    }

    if (int_bigger_float(int_num, float_num) == FALSE)
    {
        new_mantissa(int_num, 1);
        int_num->power_int--;
    }

    result_num->mantissa[0] = '0';
    short int count = 0;

    while(result_mantissa(int_num, float_num) == OK)
        count++;
    new_mantissa(int_num, 1);

    result_num->mantissa[1] = '0' + count;

    short int id;

    for (id = 2; id < MAX_LEN_MANTISSA - 1; id++)
    {
        if (if_its_null(int_num))
        {
            result_num->mantissa[id] = '\0';
            count = 0;
            break;
        }
        if (int_bigger_float(int_num, float_num) == FALSE)
        {
            new_mantissa(int_num, 1);
            result_num->mantissa[id] = '0';
        }
        else
        {
            count = 0;
            while(result_mantissa(int_num, float_num) == OK)
                count++;
            new_mantissa(int_num, 1);

            result_num->mantissa[id] = '0' + count;
        }
    }
    result_num->mantissa[MAX_LEN_MANTISSA - 1] = '\0';
    short int count_1 = 0;
    while(result_mantissa(int_num, float_num) == OK)
        count_1++;
    new_mantissa(int_num, 1);
    if (id == MAX_LEN_MANTISSA - 1 && count_1 >= 5)
        result_num->mantissa[MAX_LEN_MANTISSA - 2] += 1;

    for ( ; id < MAX_LEN_MANTISSA - 1; id++)
        result_num->mantissa[id] = '0';

    result_num->mantissa[MAX_LEN_MANTISSA - 1] = '\0';

    short int con = 0;
    for (id = MAX_LEN_MANTISSA - 2; id >= 0; id--)
    {
        result_num->mantissa[id] += con;
        if (result_num->mantissa[id] == '.')
        {
            result_num->mantissa[id] = '0';
            con = 1;
        }
        else
            break;
    }

    if (result_num->mantissa[0] == '1')
    {
        for (id = MAX_LEN_MANTISSA - 2; id > 0; id--)
            result_num->mantissa[id] = result_num->mantissa[id - 1];

        result_num->mantissa[0] = '0';
    }
    else
        con = 0;
    result_num->mantissa[MAX_LEN_MANTISSA - 1] = '\0';
    if (int_num->sing_num != float_num->sing_num)
        result_num->sing_num = MINUS;
    else
        result_num->sing_num = PLUS;

    result_num->power_int = int_num->power_int - float_num->power_int +con + 1;

    return OK;
}
