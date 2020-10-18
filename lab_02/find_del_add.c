#include "find.h"

/*!
 * \brief add_flat_end - Adding an entry to the end of the table.
 * \param *table - A pointer to a table.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var add_flat_end(table_r *const table)
{
    if (table->size + 1 == MAX_SIZE)
    {
        printf("Unable to add, table is full\n");
        return ERROR;
    }

    func_var rc = load_in_file(table, stdin, table->size, table->size + 1);

    if (rc)
        return rc;

    table->key[table->size].room = table->appar[table->size].room;
    table->key[table->size].id = table->size;

    ++(table->size);

    printf("Flat add to end table");

    return OK;
}


/*!
 * \brief delet_pos - Record deletion.
 * \param *const table - A pointer to a table.
 * \param k, del_id - delete positions.
 * \return OK if all is well, otherwise some ERROR_.
 */
void delet_pos(table_r *const table, func_var k, func_var del_id)
{
    for (func_var i = del_id; i < table->size - 1; i++)
    {
        table->appar[i] = table->appar[i + 1];
        table->key[i].id--;
    }

    for (func_var i = k; i < table->size - 1; i++)
        table->key[i] = table->key[i + 1];

    --table->size;
}

/*!
 * \brief find_to_del_room - Finding the desired record to delete.
 * \param *table - A pointer to a table.
 * \param room - count of room.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var find_to_del_room(table_r *const table, func_var room)
{
    func_var i = 0;

    for (func_var k = 0; k < table->size; k++)
    {
        if (table->key[k].room == room)
        {
            i++;
            delet_pos(table, k, table->key[k].id);
            k--;
        }
    }

    return (i) ? i : ERROR_FIND;
}

/*!
 * \brief delet_record_room - The main function of computer.
 * \param *table - A pointer to a table.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var delet_record_room(table_r *const table)
{
    func_var room;

    if (size_check(table->size))
    {
        printf("Table is empty");
        return EMPTY_TABLE;
    }

    if (input_room_delet(&room))
    {
        printf("Invalid apartment number entered.\n");
        return ERROR_INPUT;
    }

    func_var rc = find_to_del_room(table, room);
    if (rc == ERROR_FIND)
    {
        printf("There are no apartments with this number.\n");
        return ERROR_FIND;
    }

    printf("All (%d) apartments with the entered number have been deleted.\n", rc);

    return OK;
}

/*!
 * \brief find_this_app - Finding the desired entry.
 * \param *table - A pointer to a table.
 * \param min, max - search boundaries.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var find_this_app(table_r *const table, int min, int max)
{
    func_var count = 0;

    for (func_var i = 0; i < table->size; i++)
    {
        if (table->appar[i].is_prim_sec && table->appar[i].room == 2)
        {
            if (table->appar[i].square > min && table->appar[i].square < max)
            {
                if (table->appar[i].flat.second.animals == 0)
                {
                    print_pos_table(*table, i);
                    count++;
                }
            }
        }
    }

    return count;
}

/*!
 * \brief find_app_be_con - The main search function.
 * \param *table - A pointer to a table.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var find_app_be_con(table_r *const table)
{
    int min, max;
    if (read_min_max(&min, &max))
    {
        printf("\nInvalid minimum or maximum borders are entered.\n");
        return ERROR_INPUT;
    }

    if (find_this_app(table, min, max) == 0)
    {
        printf("\nNo apartments found for your search.\n");
    }

    return OK;
}
