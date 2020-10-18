#include "do.h"

/*!
 * \brief do_action - Executing the selected command.
 * \param *table - A pointer to a table.
 * \param code_act - Returned value.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var do_action(func_var code_act, table_r *table)
{
    func_var rc;

    //system("cls");

    switch (code_act)
    {
        case 1:
            printf(COLOR_YELLOW "%s" COLOR_RESET, "Entering data from a file (40 record)\n");
            rc = parsing_from_file(table);
            if (rc)
            {
                //return rc;
                break;
            }
            printf("Data is loaded into the table");
            break;

        case 2:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Adding an entry to the end of the file\n");
            if (table->size + 1 > MAX_ARRAY)
            {
                printf("The table is completely filled in.\n");
                //return ERROR_MAX_ARRAY;
                break;
            }
            else
            {
                code_act = add_flat_end(table);
            }
            break;

        case 3:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Deleting an entry from a file by the specified field\n");
            if (size_check(table->size))
            {
                printf("The table is empty.\n");
                //return EMPTY_TABLE;
                break;
            }
            else
            {
                code_act = delet_record_room(table);
            }
            break;

        case 4:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Sorting keys\n");
            if (size_check(table->size))
            {
                printf("The table is empty.\n");
                //return EMPTY_TABLE;
                break;
            }
            else
            {
                func_var p = input_ch_sort();
                if (p == 1)
                {

                    qsort(table->key, table->size, sizeof(table->key[0]), compare_key);
                    print_keys(*table);
                }
                else if (p == 2)
                {
                    bubble_sort(table, false);
                    print_keys(*table);
                }
                else
                {
                    printf("Error choice sort.\n");
                    break;
                }
            }
            break;

        case 5:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Sorting table\n");
            if (size_check(table->size))
            {
                printf("The table is empty.\n");
                //return EMPTY_TABLE;
                break;
            }
            else
            {
                func_var p = input_ch_sort();
                if (p == 1)
                {

                    qsort(table->appar, table->size, sizeof(table->appar[0]), compare_table);
                    print_table(*table, false);
                }
                else if (p == 2)
                {
                    bubble_sort(table, true);
                    print_table(*table, false);
                }
                else
                {
                    printf("Error choice sort.\n");
                    break;
                }
            }
            break;

        case 6:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Output a table by sorted keys\n");
            if (size_check(table->size))
            {
                printf("The table is empty.\n");
                //return EMPTY_TABLE;
                break;
            }
            else
            {
                qsort(table->key, table->size, sizeof(table->key[0]), compare_key);
                print_table(*table, true);
            }
            break;

        case 7:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Comparison of sorts\n");
            if (size_check(table->size))
            {
                printf("The table is empty.\n");
                //return EMPTY_TABLE;
                break;
            }
            else
            {
                table->size = 500;
                sort_qsort_vs_bub(table);
                printf("qsort_bubble");
            }
            break;

        case 8:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Search for records by the specified fields\n");
            if (size_check(table->size))
            {
                printf("The table is empty.\n");
                //return EMPTY_TABLE;
                break;
            }
            else
            {
                code_act = find_app_be_con(table);
            }
            break;

        case 9:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Output the table\n");
            if (size_check(table->size))
            {
                printf("The table is empty.\n");
                //return EMPTY_TABLE;
                break;
            }
            else
            {

                print_table(*table, false);
            }
            break;
        case 10:
            printf("Clean table.\n");
            clean_tab(table);
            break;
        case 11:
            print_hello();
            break;
    }
    return OK;
}
