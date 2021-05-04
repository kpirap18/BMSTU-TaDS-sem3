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

#include "my_main.h"
#include "io.h"
#include "read.h"
#include "load.h"
#include "find.h"
#include "sort.h"
#include "check.h"
#include "do.h"

/*!
 * \brief main - Operations on a table.
 * \return error code
 */
int main()
{
    setbuf(stdout, NULL);
    system("cls");

    print_hello();
    func_var num_command = -1;
    table_r table;

    clean_tab(&table);
    while (num_command != 0)
    {
        printf_input();
        if (check_number(&num_command, 0, 11) != OK)
        {
            printf("Invalid command entered, please re-enter!!!\n");

            print_hello();
        }
        else
        {
            func_var code_err = do_action(num_command, &table);

            if (code_err)
            {
                return code_err;
            }
        }
    }

    return OK;
}
