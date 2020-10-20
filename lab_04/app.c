#include "defstrerr.h"
#include "io.h"
#include "do.h"
#include "array.h"

int main()
{
    int capacity, max_capacity;
    //arr_r *fmem = NULL;
    //liststack_r *root = NULL;
    arrstack_r *stack = NULL;
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


            switch (num_command)
            {
                case 1:
                    printf("Input elements of the stack.\n");
                    if (stack)
                    {
                        printf("Stack is.\n");
                        break;
                    }
                    else
                    {
                        printf("input max xapacity %d", INT8_MAX);
                        if (check_number(&max_capacity, 1, INT8_MAX))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "");
                            break;
                        }
                        printf("Input capacity ");
                        if (check_number(&capacity, 0, max_capacity))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "\n");
                            break;
                        }

                        stack = create_stack_arr(max_capacity);

                        if (input_stack_arr(capacity, stack))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "\n");
                            break;
                        }

                        printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                    }
                    break;

                case 2:
                    printf(COLOR_GREEN"Add an element to the stack.\n\n"COLOR_RESET);

                    if (is_full_arr(stack))
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack is full!\n");
                        break;
                    }
                    else
                    {
                        printf("Input element: ");

                        if (input_stack_arr(1, stack))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "Input error!\n\n");
                            break;
                        }

                        printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                    }
                    break;

                case 3:
                    printf(COLOR_GREEN"Remove an element from the stack.\n"COLOR_RESET);

                    if (is_empty_arr(stack))
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack is empty.\n\n");
                        break;
                    }
                    else
                    {
                        char el_pop = pop_arr(stack);

                        printf("This element '%c' remove\n\n", el_pop);
                        printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                    }

                    break;

                case 4:
                    printf(" Output the current state of the stack.");

                    output_stack_arr(stack);
                    printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                    break;

                case 5:

                    break;

                case 6:

                    break;

                case 7:

                    break;

                case 8:

                    break;

                case 9:

                    break;

                case 10:

                    break;

                case 11:

                    break;

                case 12:

                    break;

                case 13:

                    break;

                case 14:

                    break;

                case 15:

                    break;

                case 16:

                    break;
                case 17:
                    print_hello();
                    break;
            }
        }
    }

    return OK;
}
