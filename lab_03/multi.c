#include "multi.h"

func_var multi_std(matrix_std_r *matrix, matrix_std_r *vector, matrix_std_r *res)
{
    if (matrix->columns != vector->rows || matrix->rows != res->rows)
    {
        printf("Invalid matrix sizes.\n");
        return MULTI_ERR;
    }

    for (func_var i = 0; i < matrix->rows; i++)
        for (func_var j = 0; j < matrix->columns; j++)
            res->data[i][j] += matrix->data[j][i] * vector->data[i][0];
    return OK;
}
func_var multi_rr(matrix_r *matrix, matrix_r *vector, matrix_r *res)
{
    func_var ip_res[MAX_MATRIX_SIZE];
    func_var ip_vector[MAX_MATRIX_SIZE];

    if (matrix->columns != vector->rows)// || matrix->rows != res->rows)
    {
        printf("Invalid matrix sizes.\n");
        return MULTI_ERR;
    }

    res->quan = 0;
    for (func_var i = 0; i < matrix->rows; i++)
        ip_res[i] = -1;
    for (func_var i = 0; i < vector->rows; i++)
        ip_vector[i] = -1;

    for (func_var i = 0; i < vector->quan; i++)
        ip_vector[vector->row[i]] = i;

    func_var poss;

    list_elem point = matrix->pointer[0];

    func_var col = 0;

    while (point.next)
    {
        if (ip_vector[col] != -1)
        {
            for (func_var i = point.index; i < point.next->index; i++)
            {
                if (ip_res[matrix->row[i]] == -1)
                {
                    for (poss = res->quan; matrix->row[i] > res->row[poss - 1] && poss > 0; poss--)
                        ;

                    ip_res[matrix->row[i]] = poss;
                    for (func_var i = res->quan; i > poss; i--)
                    {
                        res->value[i] = res->value[i - 1];
                        res->row[i] = res->row[i - 1];
                    }

                    res->row[poss] = matrix->row[i];
                    res->value[poss] = vector->value[ip_vector[col]] * matrix->value[i];
                    res->quan++;
                    res->pointer->next->index++;
                }
                else
                {
                    res->value[ip_res[matrix->row[i]]] += vector->value[ip_vector[col]] * point.index;

                }
            }
        }

        col++;
        point.index = point.next->index;
        point.next = point.next->next;
    }

    return OK;

}
