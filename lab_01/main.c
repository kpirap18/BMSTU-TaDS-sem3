/*! \defgroup <main> (The Main module)
  @{
  */
/**
  * \file main.c
  * \brief File with the main code
  * \version 1.0
  * \date 09.09.2020
  @}
  */

#include "main.h"
#include "print.h"
#include "trans.h"
#include "correct.h"
#include "divistion.h"
#include "normalization.h"

/*!
 * \brief main - The division of long numbers.
 * \return error code
 */
int main()
{
    char int_num[MAX_LEN_NUMBER],
            float_num[MAX_LEN_NUMBER];
    consol_print();
    input_integer(int_num);
    if (strlen(int_num) <= 1)
    {
        printf("CHECK THE INPUT!!!\nSEE THE RULES!");
        return CORRERCT_ERROR;
    }
    number_r int_number, float_number, result_number;

    if (trans_power(int_num, &int_number) == OK)
    {
        short int type_int_num = type_int_or_float(&int_number);

        if (type_int_num == INT)
            normalization_mantissa(&int_number);
        else if (type_int_num == FLOAT)
        {
            printf("CHECK THE INPUT!!!\nREAL NUMBER ENTERED!!!");
            return ERROR;
        }
        else if (type_int_num == CORRERCT_ERROR)
        {
            printf("CHECK THE INPUT!!!\nSEE THE RULES!");
            return CORRERCT_ERROR;
        }
    }
    else
    {
        printf("CHECK THE INPUT!!!\nSEE THE RULES!");
        return CORRERCT_ERROR;
    }

    input_float(float_num);
    if (strlen(float_num) <= 1)
    {
        printf("CHECK THE INPUT!!!\nSEE THE RULES!");
        return CORRERCT_ERROR;
    }
    if (trans_power(float_num, &float_number) == OK)
    {
        short int type_float_num = type_int_or_float(&float_number);

        if (type_float_num == FLOAT || type_float_num == INT)
            normalization_mantissa(&float_number);
        else if (type_float_num == INT)
        {
            printf("CHECK THE INPUT!!!\nINTEGER NUMBER ENTERED!!!");
            return ERROR;
        }
        else if (type_float_num == CORRERCT_ERROR)
        {
            printf("CHECK THE INPUT!!!\nSEE THE RULES!");
            return CORRERCT_ERROR;
        }

        rewrite_lead_null(&int_number);
        rewrite_lead_null(&float_number);

        if (division_algorithm(&int_number, &float_number, &result_number) != OK)
            return DIV_ERROR;

        /* Для вывода только значащих цифр
        short int pos_num, len_num = strlen(result_number.mantissa);
        pos_num = len_num - 1;

        while (result_number.mantissa[pos_num] == '0' && pos_num > 1)
            pos_num--;
        result_number.mantissa[pos_num + 1] = '\0';
        */

        print_result(result_number);

        return OK;
    }
    else
    {
        printf("CHECK THE INPUT!!!\nSEE THE RULES!");
        return CORRERCT_ERROR;
    }

    return 0;
}
