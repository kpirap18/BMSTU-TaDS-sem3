#include "check.h"
#include "io.h"

/*!
 * \brief size_check - Checking the table size.
 * \param size - Table size.
 * \return OK if all is well, otherwise EMPTY_TABLE.
 */
func_var size_check(func_var size)
{
    if (!size)
    {

        return EMPTY_TABLE;
    }

    return OK;
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
        return INV_NUMBER_CHOICE;
    }

    return OK;
}

/*!
 * \brief file_size - Find out the file size.
 * \param *table - A pointer to a table.
 * \param *f - A pointer to a file (or stdin).
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var file_size(table_r *table, FILE *f)
{
    fflush(stdin);
    if (fscanf(f, "%hd", &table->size) != 1)
        return ERROR_READ_FILE;

    if (table->size < 1 || table->size > SIZE_FILE)
        return FILE_ERROR;

    return OK;
}
