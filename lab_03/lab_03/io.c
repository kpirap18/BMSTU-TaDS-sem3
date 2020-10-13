#include "defstrerr.h"

/*!
 * \brief print_hello - The output menu.
 */
void print_hello()
{
    printf(COLOR_BLUE"%s" COLOR_RESET "%s",
           "\n\nMENU (select one item, enter a number):\n\n",
           "1. Filling in a matrix from a file;\n"
           "2. Filling in the matrix manually;\n"
           "3. Filling in a vector from a file;\n"
           "4. Filling in the vector manually;\n"
           "5. Multi of a classical matrix on a vector;\n"
           "6. Mulri of a special storage method matrix by a vector;\n"
           "7. The output of the comparison time works;\n"
           "8. Output multiplication results.\n\n"
           "0. Program exit.\n"
           );
}

/*!
 * \brief printf_input - Print a command prompt.
 */
void printf_input()
{
    printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nFor help input 9", "\nINPUT YOUR CHOICE: ");
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
