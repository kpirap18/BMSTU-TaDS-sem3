#include "hash.h"

int hashh(int key, int len)
{
    return (int)abs(key) % len;
}

intt *newtabledata(int n)
{
    intt *r = malloc(sizeof(intt) * n);
    if (r)
    {
        for (int i = 0; i < n; ++i)
        {
            r[i].flag = r[i].value = 0;
        }
    }

    return r;
}
inttable_t *rewritehash(inttable_t *table)
{
    if (table == NULL)
    {
        return NULL;
    }

    int size = table->sizeall;
    table->sizeall += (table->sizeall / 5);
    printf("%d ", table->sizeall);
    intt *newdata = newtabledata(table->sizeall);

    for (int i = 0; i < size; ++i)
    {
        newdata[i].flag = table->data[i].flag;
        newdata[i].value = table->data[i].value;
    }
    free(table->data);
    table->data = newdata;

    return table;
}

int keyintable(inttable_t *table, int key)
{
    if (table == NULL)
    {
        return 0;
    }

    int h = hashh(key, table->sizeall);
    int i = h;
    int limit = 0;

    while (limit < table->sizeall)
    {
        limit++;
        if (table->data[i % table->sizeall].value == key &&
            table->data[i % table->sizeall].flag == 1)
            {
                return 1;
            }
        i++;
    }
    return 0;    
}

inttable_t *inittable(int n)
{
    inttable_t *table = malloc(sizeof(inttable_t));
    table->sizeall = n;
    table->data = newtabledata(n);
    table->limit = table->arrsize = 0;

    return table;
}

inttable_t *rerwritefunchash(inttable_t *table)
{
    int rc = 0;
    printf("Реструктурирование таблицы\n\n");
    inttable_t *newtable = inittable(table->sizeall + table->sizeall / 5);

    for (int i = 0; i < table->sizeall; ++i)
    {
        if (table->data[i].flag == 1)
        {
            loadhashtable(newtable, table->data[i].value, &rc);
        }
    }
    printf("%d\n", newtable->sizeall);

    if (table)
    {
        free(table->data);
        free(table);
    }

    return newtable;
}
inttable_t* loadhashtable(inttable_t *table, int key, int *rc)
{
    *rc = 1;
    if (table == NULL)
    {
        return NULL;
    }
    if (table->sizeall == table->arrsize)
    {
        table = rewritehash(table);
    }

    while (table->limit >= LIMIT)
    {
        table = rerwritefunchash(table);
    }
    if (keyintable(table, key))
    {
        return table;
    }

    int h = hashh(key, table->sizeall);
    int limit = 0;
    while (table->data[h % table->sizeall].flag == 1)
    {
        (*rc)++;
        h++;
        limit++;

        if (limit >= table->sizeall)
        {
            printf("Таблица переполнена\n");
            break;
        }
    }
    if (h >= table->sizeall)
    {
        h = h % table->sizeall;
    }
    table->limit += (limit == 0) ? 0: 1;
    table->data[h].value = key;
    table->data[h].flag = 1;
    (table->arrsize)++;

    return table;
    
}


void tableprint(FILE *f, inttable_t *hash_table)
{
    printf("Коллизий: %d\n", hash_table->limit);
 
    fprintf(f, "|   i   |   Хэш   |   Значения   |\n");

    for (int i = 0; i < hash_table->sizeall; i++)
    {
        fprintf(f, "| %3d   |   %3d   |   %8d   |\n", i, abs(hash_table->data[i].value) % hash_table->sizeall, 
                              hash_table->data[i].value);
    }
}
void freetable(inttable_t *table)
{
    if (table)
    {
        free(table->data);
        free(table);
    }
}