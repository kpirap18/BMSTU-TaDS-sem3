#include "funcwithmatrix.h"

func_var matrix_rr_create(matrix_r *const mat, func_var r, func_var c)
{
    if (r <= 0 || r > MAX_MATRIX_SIZE || c <= 0 || c > MAX_MATRIX_SIZE)
        return MATRIX_SIZE_ERR;

    mat->rows = r;
    mat->columns = c;

    for (func_var i = 0; i < c; i++)
    {
        mat->pointer[i].next = &mat->pointer[i + 1];
        mat->pointer[i].index = 0;
    }

    mat->pointer[c].next = NULL;

    return OK;
}
func_var matrix_std_create(matrix_std_r *const mat, func_var r, func_var c)
{
    if (r <= 0 || r > MAX_MATRIX_SIZE || c <= 0 || c > MAX_MATRIX_SIZE)
        return MATRIX_SIZE_ERR;

    mat->rows = r;
    mat->columns = c;

    for (func_var i = 0; i < r; i++)
        for (func_var j = 0; i < c; i++)
            mat->data[i][j] = 0;

    return OK;
}

void ins_elem_list(matrix_r *const matrix, func_var index, func_var val, func_var r)
{
    for (func_var i = matrix->quan - 1; i >= index; i--)
    {
        matrix->value[i + 1] = matrix->value[i];
        matrix->row[i + 1] = matrix->row[i];
    }
    matrix->value[index] = val;
    matrix->row[index] = r;
}

void ins_elem(matrix_r *const matrix, func_var i, func_var j, func_var val)
{
    func_var index = matrix->pointer[j].index;

    while (index < matrix->pointer[j].next->index && matrix->row[index] < i)
        index++;

    if (matrix->row[index] == i && index < matrix->pointer[j].next->index)
    {
        matrix->value[index] = val;
        return;
    }

    for (int k = j + 1; k < matrix->columns + 1; k++)
        matrix->pointer[k].index++;

    ins_elem_list(matrix, index, val, i);

    matrix->quan++;
}

func_var input_matrix_rr(matrix_r *const matrix, FILE *f, func_var c)
{
    for (func_var i = 0; i < matrix->columns + 1; i++)
        matrix->pointer[i].index = 0;

    for (func_var i = 0; i < matrix->quan; i++)
    {
        matrix->value[i] = 0;
        matrix->row[i] = 0;
    }

    func_var three[3];
    if (c <= 0 || c >= MAX_MATRIX_ELEMS)
    {
        printf("Invalid number of non-zero elements.\n");
        return INPUT_ERR;
    }

    for (func_var i = 0; i < c; i++)
    {
        //printf(" Read %d of %d", i, c);
        if (fscanf(f, "%d%d%d", three, three + 1, three + 2) != 3 ||
                three[0] >= matrix->rows || three[1] >= matrix->columns)
        {
            printf("Invalid row or column.\n");
            return INPUT_ERR;
        }

        if (three[2] == 0)
        {
            i--;
            continue;
        }
        ins_elem(matrix, three[0], three[1], three[2]);
    }

    return OK;
}
void parsing_matrix(matrix_r *from, matrix_std_r *to)
{
    to->rows = from->rows;
    to->columns = from->columns;

    for (func_var i = 0; i < to->rows; i++)
        for (func_var j = 0; j < to->columns; j++)
            to->data[i][j] = 0;

    list_elem point = from->pointer[0];
    func_var col = 0;

    while(point.next)
    {
        for (func_var i = point.index; i < point.next->index; i++)
            to->data[from->row[i]][col] = from->value[i];
        point = *point.next;
        col++;
    }
}

void print_matrix(const matrix_std_r *const matrix, FILE *const f)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
            fprintf(f, "%10d", matrix->data[i][j]);
        fprintf(f, "\n\n");
    }
}
