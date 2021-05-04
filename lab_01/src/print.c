/*! \defgroup <print> (The Print module)
  @{
  */
/**
  * \file print.c
  * \brief File with code for print
  * \version 1.0
  * \date 09.09.2020
  @}
  */

#include "print.h"

/*!
 * \brief consol_print - Output information about this program and input rules.
 * \return
 */
void consol_print()
{
    printf("%s",
           "Dividing an integer up to 30 decimal numbers\n"
           "to a real number in the form <+-m.nE+-K>,\n"
           "where the total length of the mantissa (m+n) is up to \n"
           "30 significant numbers\n"
           "a value of the order of K up to 5 digits\n\n"
           "Rules for entering numbers:\n"
           "1 - The sign before an integer must be entered (+ or -).\n"
           "2 - The sign before a real number must be entered (+ or -)\n"
           "3 - The sign before the power must be entered (+ or -).\n"
           "4 - Enter a real number without a space.\n"
           "5 - The exponent sign must be entered in a large letter 'E'.\n"
           "6 - The maximum length of the integer - 31 \n"
           "(30 characters - number, 1 character-sign)\n"
           "7 - The maximum length of a real number is 39 characters\n"
           "(30 characters - mantissa, 1 character-number sign,\n"
           "1 character-order sign, 1 symbol - the sign of the\n"
           "exponent(if necessary), 5 characters - order\n"
           "1 character-dot(if necessary))\n\n\n");
}

/*!
 * \brief input_integer - Entering an integer.
 * \param integer_num - Pointer to an array for an integer.
 * \return
 */
void input_integer(char *integer_num)
{
    printf("%s",
           "                                             INTEGER\n"
           "                                       1       10        20        30\n"
           "                                     +-|........|.........|.........|\n"
           "Enter an integer following the rules: ");
    scanf("%s", integer_num);
}

/*!
 * \brief input_float - Entering a float.
 * \param float_num - Pointer to an array for a float.
 * \return
 */
void input_float(char *float_num)
{
    printf("%s",
           "\n                                    REAL NUMBER(THE MANTISSA)\n"
           "                                   1       10        20         31 E power\n"
           "                                 +-|........|.........|..........|..|...|\n"
           "Enter a real following the rules: ");
    scanf("%s", float_num);
}

/*!
 * \brief input_integer - The output result of the division.
 * \param result - Structure of the division result.
 * \return
 */
void print_result(number_r result)
{
    printf("Result: %c0.%sE%+d", result.sing_num, result.mantissa + 1, result.power_int);
}
