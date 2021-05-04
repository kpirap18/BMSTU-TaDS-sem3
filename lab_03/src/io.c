#include "defstrerr.h"

/*!
 * \brief print_hello - The output menu.
 */
void print_hello()
{
    printf(COLOR_BLUE"%s" COLOR_RESET "%s",
           "\n\nMENU (select one item, enter a number):\n\n",
           " 1 - Filling in a matrix from a file;\n"
           " 2 - Filling in the matrix manually;\n"
           " 3 - Filling in a vector from a file;\n"
           " 4 - Filling in the vector manually;\n"
           " 5 - Multi of a classical matrix on a vector;\n"
           " 6 - Mulri of a special storage method matrix by a vector;\n"
           " 7 - The output of the comparison time works;\n"
           " 8 - Output multiplication results in standard format.\n"
           " 9 - Output multiplication results in sparse format.\n"
           "10 - Output multiplication results in coordinate format\n"
           "11 - Output the vector in standard format.\n"
           "12 - Output the vector in sparse form.\n"
           "13 - Output the vector in coordinate format.\n"
           "14 - Output the matrix in standard format.\n"
           "15 - Output the matrix in sparse form.\n"
           "16 - Output the matrix in coordinate format.\n\n"
           "0. Program exit.\n"
           );
}

/*!
 * \brief printf_input - Print a command prompt.
 */
void printf_input()
{
    printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nFor help input 17", "\nINPUT YOUR CHOICE: ");
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
func_var check_number(func_var *const number, const func_var l, const func_var r)
{
    char num[3];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return DONT_INT_NUM_CHOICE;
    num[strlen(num) - 1] = '\0';
    *number = (func_var)atoi(num);

    if (*number < l || *number > r)
    {
        clean_my();
        return INV_NUM_CHOICE;
    }

    return OK;
}

func_var print_coord(const matrix_std_r *matrix, const vector_std_r *vector,
                 const vector_std_r *res)
{
    if (matrix->rows == 0)
    {
        printf("Matrix is empty.\n");
        return 1;
    }
    if (vector->rows == 0)
    {
        printf("Vector is empty.\n");
        return 1;
    }
    if (res->rows == 0)
    {
        printf("Result is empty.\n");
        return 1;
    }

    printf("\n\nMATRIX\n");
    printf(" i   j   value\n\n");
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->columns; j++)
            if (matrix->data[i][j] != 0)
                printf("%3d %3d %5d\n", i, j, matrix->data[i][j]);

    printf("\n\nVECTOR (column)\n");
    printf(" i   j   value\n\n");
    for (int i = 0; i < vector->rows; i++)
        for (int j = 0; j < vector->columns; j++)
            if (vector->data[i][j] != 0)
                printf("%3d %3d %5d\n", i, j, vector->data[i][j]);

    func_var c = 0;
    printf("\n\nRESULT (column)\n");
    printf(" i   j   value\n\n");
    for (int i = 0; i < res->rows; i++)
        for (int j = 0; j < res->columns; j++)
            if (res->data[i][j] != 0)
            {
                printf("%3d %3d %5d\n", i, j, res->data[i][j]);
            }
            else
                c++;
    if (c + 1 == res->rows)
        printf("Result has all elements are NULL!!!\n\n");

    return OK;
}
func_var print_std(const matrix_std_r *matrix, const vector_std_r *vector,
               const vector_std_r *res)
{
    if (matrix->rows == 0)
    {
        printf("Matrix is empty.\n");
        return 1;
    }
    if (vector->rows == 0)
    {
        printf("Vector is empty.\n");
        return 1;
    }
    if (res->rows == 0)
    {
        printf("Result is empty.\n");
        return 1;
    }

    if (matrix->columns > 50 || matrix->rows > 50)
    {
        printf("The matrix is too large. It is not possible to display it in its entirety.\n");
        return 1;
    }

    printf("            MATRIX                       VECTOR   RESULT\n");
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
            printf("%3d ", matrix->data[i][j]);
        if (vector->rows > i)
            printf("   %3d    ", vector->data[i][0]);
        else
            printf("          ");
        printf("%3d\n", res->data[i][0]);
    }
    for (int i = matrix->rows; i < vector->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
            printf("    ");
        printf("   %3d    ", vector->data[i][0]);
        printf("\n");
    }
    printf("\n\n");
    return 0;
}
func_var print_razr(matrix_r *const matrix, matrix_r *const vector, matrix_r *const res, vector_std_r *true_res)
{

    if (matrix->quan == 0)
    {
        printf("Matrix is empty.\n");
        return 1;
    }
    if (vector->quan == 0)
    {
        printf("Vector is empty.\n");
        return 1;
    }
    if (res->quan == 0)
    {
        printf("Result is empty.\n");
        return 1;
    }

    printf("MATRIX\n");
    for (func_var j = 0; j < matrix->quan; j += 30)
    {
        printf("    ");
        for (func_var i = j; i < j + 30; i++)
        {
            if (matrix->value[i] != 0)
                printf("%5d ", i);
        }
        printf("\nAN: ");
        for (func_var i = j; i < j + 30; i++)
        {
            if (matrix->value[i] != 0)
                printf("%5d ", matrix->value[i]);
        }
        printf("\nJA: ");
        for (func_var i = j; i <j + 30; i++)
        {
            if (matrix->value[i] != 0)
                printf("%5d ", matrix->row[i]);
        }
        printf("\n");
    }
    printf("\nIA: ");
    for (func_var i = 0; i < matrix->rows; i++)
        printf("%5d", matrix->pointer[i].index);

    printf("\n\nVECTOR\n");
    for (func_var j = 0; j < vector->quan; j += 30)
    {
        printf("    ");
        for (func_var i = j; i < j + 30; i++)
        {
            if (vector->value[i] != 0)
                printf("%5d ", i);
        }
        printf("\nAN: ");
        for (func_var i = j; i < j + 30; i++)
        {
            if (vector->value[i] != 0)
                printf("%5d ", vector->value[i]);
        }
        printf("\nJA: ");
        for (func_var i = j; i <j + 30; i++)
        {
            if (vector->value[i] != 0)
                printf("%5d ", vector->row[i]);
        }
        printf("\n\n");
    }


    printf("\n\nRESULT\n");
    if (res->quan == 0)
        printf("Result has all elements are NULL!!!");
    else
    {
        for (func_var j = 0; j < res->quan; j += 30)
        {
            printf("    ");
            for (func_var i = j; i < j + 30; i++)
            {
                if (res->quan > 0)
                    printf("%5d ", i);
            }
            printf("\nAN: ");
            for (func_var i = j; i < j + 30; i++)
            {
                if (res->quan > 0)
                    printf("%5d ", true_res->data[res->row[i]][0]);
            }
            printf("\nJA: ");
            for (func_var i = j; i <j + 30; i++)
            {
                if (res->quan > 0)
                    printf("%5d ", res->row[i]);
            }

            printf("\n\n");
        }
    }

    return OK;
}
void print_matrix_sparse(matrix_r *matrix)
{
    if (matrix->quan == 0)
    {
        printf("Please, input matrix/vecrot before its output.\n");
        return;
    }
    printf("MATRIX\n");
    for (func_var j = 0; j < matrix->quan; j += 30)
    {
        printf("    ");
        for (func_var i = j; i < j + 30; i++)
        {
            if (matrix->value[i] != 0)
                printf("%5d ", i);
        }
        printf("\nAN: ");
        for (func_var i = j; i < j + 30; i++)
        {
            if (matrix->value[i] != 0)
                printf("%5d ", matrix->value[i]);
        }
        printf("\nJA: ");
        for (func_var i = j; i <j + 30; i++)
        {
            if (matrix->value[i] != 0)
                printf("%5d ", matrix->row[i]);
        }
        printf("\n");
    }
    printf("\nIA: ");
    for (func_var i = 0; i < matrix->rows; i++)
        printf("%5d", matrix->pointer[i].index);
}
void print_matrix_std(const matrix_std_r *const matrix, FILE *const f)
{
    if (matrix->rows == 0)
    {
        printf("Please, input matrix/vecrot before its output.\n");
        return;
    }
    if (matrix->rows > 30)
    {
        printf("This output not good, please choose other.\n");
        return;
    }
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
            fprintf(f, "%8d", matrix->data[i][j]);
        fprintf(f, "\n");
    }
}
void print_vector_std(const vector_std_r *const matrix, FILE *const f)
{
    if (matrix->rows == 0)
    {
        printf("Please, input matrix/vecrot before its output.\n");
        return;
    }
    if (matrix->rows > 30)
    {
        printf("This output not good, please choose other.\n");
        return;
    }
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
            fprintf(f, "%8d", matrix->data[i][j]);
        fprintf(f, "\n");
    }
}
void print_coordin_one(matrix_std_r *matrix)
{
    if (matrix->rows == 0)
    {
        printf("Please, input matrix/vecrot before its output.\n");
        return;
    }
    if (matrix->rows > 30)
    {
        printf("This output not good, please choose other.\n");
        return;
    }
    printf("\n\nMATRIX\n");
    printf(" i   j   value\n\n");
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->columns; j++)
            if (matrix->data[i][j] != 0)
                printf("%3d %3d %5d\n", i, j, matrix->data[i][j]);

}

void print_coordin_one_v(vector_std_r *matrix)
{
    if (matrix->rows == 0)
    {
        printf("Please, input matrix/vecrot before its output.\n");
        return;
    }
    if (matrix->rows > 30)
    {
        printf("This output not good, please choose other.\n");
        return;
    }
    printf("\n\nMATRIX\n");
    printf(" i   j   value\n\n");
    for (int i = 0; i < matrix->rows; i++)
        for (int j = 0; j < matrix->columns; j++)
            if (matrix->data[i][j] != 0)
                printf("%3d %3d %5d\n", i, j, matrix->data[i][j]);

}




// for debug
void print_matrix(const matrix_std_r *const matrix, FILE *const stream)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
            fprintf(stream, "%10d", matrix->data[i][j]);
        fprintf(stream, "\n\n");
    }
}
