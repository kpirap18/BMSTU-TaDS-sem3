#include "defstrerr.h"
#include "io.h"
#include "do.h"

int main()
{
    setbuf(stdout, NULL);
    print_hello();

    int num_command = -1;

    while (num_command != 0)
    {
        printf_input();
        if (check_number(&num_command, 0, 12) != OK)
        {
            printf(COLOR_RED"%s"COLOR_RESET"%s",
                   "ERROR!!!",
                   "Invalid command entered, please re-enter!!!\n");

            print_hello();
        }
        else
        {
            func_var code_err;
            code_err = do_action(num_command);

            if (code_err)
            {
                return code_err;
            }
        }
    }

    return OK;
}
