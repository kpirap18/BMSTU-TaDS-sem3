#include "io.h"

/*!
 * \brief print_hello - The output menu.
 */
void print_hello()
{
    printf(COLOR_BLUE"%s" COLOR_RESET "%s",
           "\n\nMENU (select one item, enter a number):\n\n"
           "Operations with array:\n"
           "1  - Input elements of the stack.\n"
           "2  - Add an element to the stack.\n"
           "3  - Remove an element from the stack.\n"
           "4  - Check the correct placement of parentheses.\n"
           "5  - Output the current state of the stack.\n\n"
           "Operations with list:\n"
           "6  - Input elements of the stack.\n"
           "7  - Add an element to the stack.\n"
           "8  - Remove an element from the stack.\n"
           "9  - Check the correct placement of parentheses.\n"
           "10 - Output the current state of the stack.\n"
           "11 - Output an array of freed addresses.\n\n"

           "0  - Program exit.\n"
           );
}

/*!
 * \brief printf_input - Print a command prompt.
 */
void printf_input()
{
    printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nFor help input 17", "\nINPUT YOUR CHOICE: ");
}

/*!
 * \brief clean_my - Clearing the console.
 */
void clean_my()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

/*!
 * \brief check_number - Entering a command and checking it.
 * \param *const number - Pointer to the number.
 * \param l, r - The left and right boundaries of the input.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var check_number(func_var *const number, const func_var l, const func_var r)
{
    char num[3];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return DONT_INT_NUM_CHOICE;
    num[strlen(num) - 1] = '\0';
    *number = (func_var)atoi(num);

    if (*number < l || *number > r)
    {
        clean_my();
        return INV_NUM_CHOICE;
    }

    return OK;
}
