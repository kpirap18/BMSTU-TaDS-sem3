#include "load.h"

/*!
 * \brief load_in_file - Loading data from a file.
 * \param *table - A pointer to a table.
 * \param *f - A pointer to a file.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var load_in_file(table_r *table, FILE *f, func_var s, func_var e)
{
    func_var rc;

    for (func_var i = s; i < e; i++)
    {
        rc = read_address(table, f, i);

        if (rc)
            return rc;

        rc = read_other(table, f, i);

        if (rc)
            return rc;

        if (table->appar[i].is_prim_sec)
            rc = read_primary(table, f, i);
        else
            rc = read_secondary(table, f, i);

        table->key[i].id = i;
        table->key[i].room = table->appar[i].room;
    }

    return OK;

}
/*!
 * \brief parsing_from_file - Loading data from a file and
 * checking, the main function.
 * \param *table - A pointer to a table.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var parsing_from_file(table_r *table)
{
    FILE *f = NULL;

    clean_tab(table);

    f = fopen(NAME_FILE, "r");

    if (f == NULL)
    {
        printf("Some file error!!!");
        return FILE_ERROR;
    }

    if (file_size(table, f) != OK)
    {
        printf("File empry, please check your file!!!");
        return FILE_ERROR;
    }

    func_var rc = load_in_file(table, f, 0, table->size);

    if (rc)
        return rc;

    fclose(f);

    return OK;
}
