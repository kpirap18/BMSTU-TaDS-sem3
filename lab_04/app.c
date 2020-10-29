/*! \defgroup <main> (The Main module)
  @{
  */
/**
  * \file main.c
  * \brief File with the main code
  * \version 1.0
  * \date 23.10.2020
  @}
  */

#include "defstrerr.h"
#include "io.h"
#include "array.h"
#include "list.h"
#include "time.h"

/*!
 * \brief main - Operations on a table.
 * \return error code
 */
int main()
{
    int capacity, max_capacity;
    arr_r *arr = NULL;
    liststack_r *stack_list = NULL;
    arrstack_r *stack = NULL;
    setbuf(stdout, NULL);
    print_hello();

    int num_command = -1;

    while (num_command != 0)
    {
        printf_input();
        if (check_number(&num_command, 0, 13) != OK)
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
                    printf(COLOR_GREEN
                           "Input elements of the stack.\n"
                           COLOR_RESET);
                    if (stack)
                    {
                        printf("Stack is.\n");
                        break;
                    }
                    else
                    {
                        printf("input max xapacity %d:", INT8_MAX);
                        if (check_number(&max_capacity, 1, INT8_MAX))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "Input invalid number.\n");
                            break;
                        }
                        printf("Input capacity: ");
                        if (check_number(&capacity, 1, max_capacity))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "Input invalid number.\n");
                            break;
                        }

                        stack = create_stack_arr(max_capacity);

                        printf("Input element in the string without space: ");
                        if (input_stack_arr(capacity, stack, 0, stdin))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "Input invalid element.\n");
                            break;
                        }

                        printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                    }
                    break;

                case 2:
                    printf(COLOR_GREEN
                           "Add an element to the stack.\n\n"
                           COLOR_RESET);

                    if (stack == NULL)
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack does not exist");
                        break;
                    }
                    if (is_full_arr(stack))
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack is full!\n");
                        break;
                    }
                    else
                    {
                        printf("Input element: ");

                        if (input_stack_arr(1, stack, 0, stdin))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "Input invalid element.\n\n");
                            break;
                        }

                        printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                    }
                    break;

                case 3:
                    printf(COLOR_GREEN
                           "Remove an element from the stack.\n"
                           COLOR_RESET);

                    if (stack == NULL)
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack does not exist");
                        break;
                    }
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
                    printf(COLOR_GREEN
                           "Output the current state of the stack.\n"
                           COLOR_RESET);

                    if (stack == NULL)
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack does not exist");
                        break;
                    }
                    output_stack_arr(stack);
                    printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                    break;

                case 5:
                    printf(COLOR_RED
                           "Check the correct placement of parentheses."
                           COLOR_RESET);
                    if (stack == NULL)
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack does not exist");
                        break;
                    }
                    int rc = check_brackets_arr(stack);

                    if (rc == FALSE)
                    {
                        printf(COLOR_GREEN"FALSE\n"COLOR_RESET
                               "The brackets are placed incorrectly");
                    }
                    else
                    {
                        printf(COLOR_GREEN"TRUE\n"COLOR_RESET
                               "The brackets are placed correctly");
                    }
                    break;

                case 6:
                    printf(COLOR_GREEN
                           "Input elements of the stack.\n"
                           COLOR_RESET);
                    
                    if (stack_list)
                    {
                        printf("Stack is\n\n");

                        break;
                    }
                    else
                    {
                        printf("input max xapacity %d: ", INT8_MAX);
                        if (check_number(&max_capacity, 1, INT8_MAX))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "");
                            break;
                        }
                        printf("Input capacity: ");
                        if (check_number(&capacity, 1, max_capacity))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "\n");
                            break;
                        }

                        arr = create_array(max_capacity * max_capacity);

                        printf("Input element in string without space: ");

                        if (input_stack_list(capacity, &stack_list, max_capacity, 0, stdin))
                        {
                            printf(COLOR_RED"ERROR!!!"COLOR_RESET
                                   "\n");
                            break;
                        }

                        printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                    }

                    break;

            case 7:
                printf(COLOR_GREEN
                       "Add an element to the stack.\n\n"
                       COLOR_RESET);

                if (stack_list == NULL)
                {
                    printf(COLOR_RED"ERROR!!!"COLOR_RESET
                           "Stack does not exist");
                    break;
                }
                if (is_full_list(stack_list, max_capacity))
                {
                    printf(COLOR_RED"ERROR!!!"COLOR_RESET
                           "Stack is full!\n");
                    break;
                }
                else
                {
                    printf("Input element: ");

                    if (input_stack_list(1, &stack_list, max_capacity, 0, stdin))
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Input error!\n\n");
                        break;
                    }

                    check_top_list(stack_list, arr);
                    printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                }
                break;

            case 8:
                printf(COLOR_GREEN
                       "Remove an element from the stack.\n"
                       COLOR_RESET);

                if (stack_list == NULL)
                {
                    printf(COLOR_RED"ERROR!!!"COLOR_RESET
                           "Stack does not exist");
                    break;
                }
                if (is_empty_list(stack_list))
                {
                    printf(COLOR_RED"ERROR!!!"COLOR_RESET
                           "Stack is full!\n");
                    break;
                }
                else
                {
                    char el_pop = pop_list(&stack_list, arr);

                    printf("This element '%c' remove\n\n", el_pop);
                    printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                }
                break;



                case 9:
                    printf(COLOR_RED
                           "Check the correct placement of parentheses."
                           COLOR_RESET);
                    if (stack_list == NULL)
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack does not exist");
                        break;
                    }
                    int rc1 = check_brackets_list(stack_list);

                    if (rc1 == FALSE)
                    {
                        printf(COLOR_GREEN"FALSE\n"COLOR_RESET
                               "The brackets are placed incorrectly");
                    }
                    else
                    {
                        printf(COLOR_GREEN"TRUE\n"COLOR_RESET
                               "The brackets are placed correctly");
                    }
                    break;

                case 10:
                    printf(COLOR_GREEN
                           "Output the current state of the stack.\n"
                           COLOR_RESET);

                    if (stack_list == NULL)
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack does not exist.\n");
                        break;
                    }
                    output_stack_list(stack_list);
                    printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                    break;

                case 11:
                    printf(COLOR_GREEN
                           "Output an array of freed addresses.\n"
                           COLOR_RESET);

                    if (stack_list == NULL)
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack does not exist.\n");
                        break;
                    }
                    output_array(*arr);
                    printf(COLOR_GREEN"DONE!!!\n"COLOR_RESET);
                    break;

                case 12:
                    /*if (stack == NULL || stack_list == NULL)
                    {
                        printf(COLOR_RED"ERROR!!!"COLOR_RESET
                               "Stack does not exist.\n");
                        printf("Array - %s \nList - %s\n",
                               (stack == NULL) ? "no" : "yes",
                               (stack_list == NULL) ? "no" : "yes");
                        break;
                    }*/
                    time_output(stack, stack_list, 10);

                    break;
                case 13:
                    print_hello();
                    break;
            }
        }

    }

    free(arr);
    free(stack);
    free(stack_list);
    return OK;
}
