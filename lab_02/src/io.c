#include "io.h"

/*!
 * \brief print_hello - The output menu.
 */
void print_hello()
{
    printf(COLOR_GREEN "%s" COLOR_RESET "%s",
           "\nThis program allows you to: \n",
           " - compare the time taken to sort the table by sorts;\n"
           " - with asymptotic complexities O(n^2) and O(nlogn);\n"
           " - add the entry entered by the user to the end of the"
           "   table;\n"
           " - delete an entry from the table by the value of the"
           "   specified field;\n"
           " - view the sorted key table when the source table "
           "   is unsorted;\n"
           " - output an ordered source table;\n"
           " - output the source table in an ordered form using "
           "   an ordered key table;\n"
           " - display the results of using different sorting "
           "   algorithms;\n\n\n");

    printf("%s",
           "1 -  Load the table from the file.\n"
           "2 -  Add an entry to the end of the table.\n"
           "3 -  Delete an entry from the table for the number of rooms.\n"
           "4 -  Sort the key table (select sort to choose from) and display it on the screen.\n"
           "5 -  Sort the table (select the sort option) and display the table on the screen.\n"
           "6 -  Sort the key table and output the source table by the sorted key table.\n"
           "7 -  Compare the time of sorting the table by sorting with\n"
           "     complexities O(n^2) and O(n*log(n)) and compare\n"
           "     the time of normal sorting and sorting the key table.\n"
           "8 -  Display all secondary 2-room housing in the specified price range without animals.\n"
           "9 -  Display the table on screen.\n"
           "10 - Clean table.\n"
           "11 - Calling help (menu).\n"
           "0 -  Program exit.\n");
}

/*!
 * \brief printf_input - Print a command prompt.
 */
void printf_input()
{
    printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nFor help input 11", "\nINPUT YOUR CHOICE: ");
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
 * \brief print_pos_table - Output a record from a table.
 * \param *table - A pointer to a table.
 */
void print_pos_table(const table_r table, func_var k)
{
    printf("%30s %8s %7s %7s %10s\n", "Address", "Square", "Rooms",
           "Price", "Primacy");
    printf("%66s %4s\n", "Yes", "Decor");
    printf("%66s %9s %5s %7s %6s\n", "No", "time", "Owner", "Tenants", "Animal");

    printf("%30s %8hd %7hd %10d %7s", table.appar[k].address,
           table.appar[k].arrr, table.appar[k].room,
           table.appar[k].square, (table.appar[k].is_prim_sec) ? "Yes" : "No");

    if (table.appar[k].is_prim_sec)
        printf(" %4s\n", (table.appar[k].flat.primary.decoration) ? "Yes" : "No");
    else
        printf(" %9hd %5hd %7hd %6s\n", table.appar[k].flat.second.build_time,
               table.appar[k].flat.second.previous_own_count,
               table.appar[k].flat.second.last_tenants_count,
               (table.appar[k].flat.second.animals) ? "Yes" : "No");
}

/*!
 * \brief print_table - The output table.
 * \param *table - A pointer to a table.
 */
void print_table(const table_r table, boolean keys)
{
    printf("\n");
;
    func_var k;
    printf("%30s %8s %7s %7s %10s\n", "Address", "Square", "Rooms",
           "Price", "Primacy");
    printf("%66s %4s\n", "Yes", "Decor");
    printf("%66s %9s %5s %7s %6s\n", "No", "time", "Owner", "Tenants", "Animal");
    for (func_var i = 0; i < table.size; i++)
    {
        if (keys == false)
        {
            k = i;

            printf("%30s %8hd %7hd %10d %7s", table.appar[k].address,
                   table.appar[k].arrr, table.appar[k].room,
                   table.appar[k].square, (table.appar[k].is_prim_sec) ? "Yes" : "No");

            if (table.appar[k].is_prim_sec)
                printf(" %4s\n", (table.appar[k].flat.primary.decoration) ? "Yes" : "No");
            else
                printf(" %9hd %5hd %7hd %6s\n", table.appar[k].flat.second.build_time,
                       table.appar[k].flat.second.previous_own_count,
                       table.appar[k].flat.second.last_tenants_count,
                       (table.appar[k].flat.second.animals) ? "Yes" : "No");
        }
        else
        {
            k = table.key[i].id;

            printf("%30s %8hd %7hd %10d %10s", table.appar[k].address,
                   table.appar[k].arrr, table.appar[k].room,
                   table.appar[k].square, (table.appar[k].is_prim_sec) ? "Yes" : "No");

            if (table.appar[k].is_prim_sec)
                printf(" %4s\n", (table.appar[k].flat.primary.decoration) ? "Yes" : "No");
            else
                printf(" %4hd %10hd %10hd %7s\n", table.appar[k].flat.second.build_time,
                       table.appar[k].flat.second.previous_own_count,
                       table.appar[k].flat.second.last_tenants_count,
                       (table.appar[k].flat.second.animals) ? "Yes" : "No");
        }

    }
}

/*!
 * \brief print_keys - Key table output.
 * \param *table - A pointer to a table.
 */
void print_keys(const table_r table)
{
    printf("%4s %7s", "Key", "Rooms\n");
    for (func_var i = 0; i < table.size; i++)
    {
        printf("%4hd %7hd\n", table.key[i].id, table.key[i].room);
    }
}

/*!
 * \brief input_room_delet - Enter the number of the command to remove.
 */
func_var input_room_delet(func_var *room)
{
    printf("Enter the number of apartments that you want to remove from the list (from 1 to 20): ");
    if (scanf("%hd", room) != 1)
    {
        printf("Invalid apartment number entered.\n");
        return ERROR_INPUT;
    }

    if (*room < MIN_ROOM || *room > MAX_ROOM)
    {
        printf("Invalid apartment number entered.\n");
        return ERROR_INPUT;
    }

    return OK;
}

/*!
 * \brief input_ch_sort - Entering a sort selection.
 */
func_var input_ch_sort()
{
    func_var k;
    printf("Choose which sorting, bubble or qsort\n"
           "1 - qsort (O(n*log(n)))\n"
           "2 - bubble (O(n^2))\n"
           "Your choice: ");
    int rc = scanf("%hd", &k);
    if (rc)
    {
        if (k == 1 || k == 2)
        return k;
    }
    else
    {
        return rc;
    }

    return OK;
}

/*!
 * \brief print_res - print the results of time measurements.
 * \param *table - A pointer to a table.
 */
void print_res(table_r *const table, int64_t tact, int64_t tact_qsort,
               func_var type_sort, func_var type_table)
{
    double prob_t, prob_tac;

    if (!type_table)
    {
        prob_t = 100 * ((double)tact / GNZ) / ((double)tact_qsort / GNZ);
        prob_tac = 100 * (double)(tact) / tact_qsort;
        printf("%8s %11lld %14lld (%.2lf%%) %18.10lf (%.2lf%%)\n",
               (type_sort) ? "bubble" : "qsort",
               sizeof(table->key[0]) * table->size, tact, prob_tac,
                (double)tact / GNZ, prob_t);
    }
    else
    {
        prob_t = 100 * ((double)tact / GNZ) / ((double)tact_qsort / GNZ);
        prob_tac = 100 * (double)(tact) / tact_qsort;
        printf("%8s %11lld %14lld (%.2lf%%) %18.10lf (%.2lf%%)\n",
               (type_sort) ? "bubble" : "qsort",
               sizeof(table->appar[0]) * table->size, tact, prob_tac,
                (double)tact / GNZ, prob_t);
    }
}

/*!
 * \brief clean_tab - Clearing the table.
 * \param *table - A pointer to a table.
 */
void clean_tab(table_r *const table)
{
    for (func_var i = 0; i < table->size; i++)
    {
        table->key[i].id = 0;
        table->appar[i].address[0] = '\0';
    }
    table->size = 0;
}
