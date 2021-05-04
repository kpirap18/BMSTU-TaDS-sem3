#include "sort.h"

int64_t tact(void)
{
    int32_t h, l;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (h), "=r" (l)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    int64_t tacks = ((int64_t)h << 32) | l;

    return tacks;
}

/*!
 * \brief sort_qsort_vs_bub - Comparison of sorts.
 * \param *table - A pointer to a table.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var sort_qsort_vs_bub(table_r *const table)
{
    int64_t s, e, s1, e1, s2, e2, s3, e3;

    printf(COLOR_GREEN"           %s\n"COLOR_RESET, "TABLE");
    printf("%8s %17s %15s %20s\n", "What", "Memory (bytes)", "Tacts", "Time");
    parsing_from_file(table);
    s = tact();
    qsort(table->appar, table->size, sizeof(table->appar[0]), compare_table);
    e = tact();
    print_res(table, e - s, e - s, 0, 1);

    parsing_from_file(table);
    s1 = tact();
    bubble_sort(table, true);
    e1 = tact();
    print_res(table, e1 - s1, e - s, 1, 1);

    printf("\n\n");
    printf(COLOR_GREEN"           %s\n"COLOR_RESET, "KEYS");
    printf("%8s %17s %15s %20s\n", "What", "Memory (bytes)", "Tacts", "Time");
    parsing_from_file(table);
    s2 = tact();
    qsort(table->key, table->size, sizeof(table->key[0]), compare_key);
    e2 = tact();
    print_res(table, e2 - s2, e2 - s2, 0, 0);

    parsing_from_file(table);
    s3 = tact();
    bubble_sort(table, false);
    e3 = tact();
    print_res(table, e3 - s3, e2 - s2, 1, 0);

    return OK;
}
int compare_key(const void *v1, const void *v2)
{
    return ((key_r*)(v1))->room - ((key_r*)(v2))->room;
}
int compare_table(const void *v1, const void *v2)
{
    return ((appartment_r*)(v1))->room - ((appartment_r*)(v2))->room;
}
void swap(boolean table, void *v1, void *v2)
{
    if (!table)
    {
        appartment_r buf = *(appartment_r*)v1;
        *(appartment_r*)v1 = *(appartment_r*)v2;
        *(appartment_r*)v2 = buf;

    }
    else
    {
        key_r buf = *(key_r*)v1;
        *(key_r*)v1 = *(key_r*)v2;
        *(key_r*)v2 = buf;
    }
}

/*!
 * \brief bubble_sort - Bubble sorting (universal).
 * \param *table - A pointer to a table.
 * \return OK if all is well, otherwise some ERROR_.
 */
void bubble_sort(table_r *const table, boolean tabl)
{
    if (tabl)
    {
        for (func_var i = 0; i < table->size; i++)
        {
            for (func_var j = 0; j < table->size - 1; j++)
            {
                if (table->appar[j].room > table->appar[j + 1].room)
                {
                    appartment_r buf = table->appar[j];
                    table->appar[j] = table->appar[j + 1];
                    table->appar[j + 1] = buf;
                }
            }
        }
    }
    else
    {
        for (func_var i = 0; i < table->size; i++)
        {
            for (func_var j = 0; j < table->size - 1; j++)
            {
                if (table->key[j].room > table->key[j + 1].room)
                {
                    key_r buf = table->key[j];
                    table->key[j] = table->key[j + 1];
                    table->key[j + 1] = buf;
                }
            }
        }
    }
}
