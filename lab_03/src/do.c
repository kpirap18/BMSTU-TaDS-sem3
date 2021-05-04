#include "do.h"
#include "defstrerr.h"
#include "funcwithmatrix.h"
#include "multi.h"

/*!
 * \brief do_action - Executing the selected command.
 * \param code_act - Returned value.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var do_action(func_var code_act, func_var *multi_res)
{
    func_var size_mat;
    func_var count;



    func_var size_user[2];
    FILE *f;

    matrix_r matrix_rr;
    matrix_std_r matrix_stdd;

    matrix_r vector_rr;
    vector_std_r vector_stdd;

    const func_var sizze[5] = {10, 50, 100, 150, 200};
    const char name_file[10][100] = {"C:/msys64/home/Ira/tads/lab_03/10x10.txt",
                                     "C:/msys64/home/Ira/tads/lab_03/50x50.txt",
                                     "C:/msys64/home/Ira/tads/lab_03/100x100.txt",
                                     "C:/msys64/home/Ira/tads/lab_03/150x150.txt",
                                     "C:/msys64/home/Ira/tads/lab_03/200x200.txt",
                                     "C:/msys64/home/Ira/tads/lab_03/10x1.txt",
                                     "C:/msys64/home/Ira/tads/lab_03/50x1.txt",
                                     "C:/msys64/home/Ira/tads/lab_03/100x1.txt",
                                     "C:/msys64/home/Ira/tads/lab_03/150x1.txt",
                                     "C:/msys64/home/Ira/tads/lab_03/200x1.txt"};

    switch (code_act)
    {
        case 1:

            printf(COLOR_YELLOW "%s" COLOR_RESET, "Filling a matrix from a file\n");



            printf("Select the matrix size:\n"
                   "1 - 10x10;\n2 - 50x50;\n3 - 100x100;\n4 - 150x150\n\n INPUT:");
            if (scanf("%d", &size_mat) != 1 || size_mat < 1 || size_mat > 4)
            {
                printf("ERROR!!! Invalid selection entered.\n");
                // return SIZE_ERR;
                break;
            }
            count = sizze[size_mat - 1] * sizze[size_mat - 1];

            if (matrix_rr_create(&matrix_rr, sizze[size_mat - 1], sizze[size_mat - 1]) ||
                    matrix_std_create(&matrix_stdd, sizze[size_mat - 1], sizze[size_mat - 1]))
            {
                printf("ERROR!!! Having problems creating the table.\n");
                break;
            }

            f = fopen(name_file[size_mat - 1], "r");
            if (!f)
            {
                printf("ERROR!!! File open with error!");
                break;
            }

            printf("Enter the percentage of table completion: (1%%..100%%) ");
            if (scanf("%d", &size_mat) != 1 || size_mat < 1 || size_mat > 100)
            {
                fclose(f);
                printf("ERROR!!! Invalid percentage entered.\n");
                break;
            }

            count = count * size_mat / 100;

            if (input_matrix_rr(&matrix_rr, f, count))
            {
                printf("ERROR!!! There were problems filling in the table.\n");
                break;
            }

            fclose(f);
            parsing_matrix(&matrix_rr, &matrix_stdd);
            printf(COLOR_GREEN"%s"COLOR_RESET, "\nDONE!\n");
            //print_matrix(&matrix_stdd, stdout);
            break;

        case 2:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Filling the matrix manually\n");

            printf("Enter the dimensions of the matrix\n"
                   "(separated by a space, each size from 1 to 200)\nINPUT: ");

            if (scanf("%d%d", size_user, size_user + 1) != 2 ||
                    size_user[0] <= 0 || size_user[0] > MAX_MATRIX_SIZE ||
                    size_user[1] <= 0 || size_user[1] > MAX_MATRIX_SIZE)
            {
                printf("ERROR!!! Invalid size entered.\n");
                break;
            }


            if (matrix_rr_create(&matrix_rr, size_user[0], size_user[1]))
            {
                printf("ERROR!!! Having problems creating the table.\n");
                break;
            }

            printf("Enter the number of non-zero matrix elements.\nINPUT: ");
            if (scanf("%d", &count) != 1 || count > size_user[0] * size_user[1] ||
                    count <= 0)
            {
                printf("ERROR!!! Entered the wrong number.\n");
                break;
            }

            printf(COLOR_GREEN"%s"COLOR_RESET"%s", "ATTENTION\n",
                   "Entering %d elements according to the scheme (ROW COLUMN ELEMENT)\n",
                   count);

            if (input_matrix_rr(&matrix_rr, stdin, count))
            {
                printf("ERROR!!! Problems with filling in the matrix.\n");
                break;
            }

            parsing_matrix(&matrix_rr, &matrix_stdd);
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            //print_matrix(&matrix_stdd, stdout);
            break;

        case 3:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Filling the matrix manually\n");



            printf("Select the vector size:\n"
                   "1 - 10x1;\n2 - 50x1;\n3 - 100x1;\n4 - 150x1\n\n INPUT:");
            if (scanf("%d", &size_mat) != 1 || size_mat < 1 || size_mat > 4)
            {
                printf("ERROR!!! Invalid selection entered.\n");
                // return SIZE_ERR;
                break;
            }
            count = sizze[size_mat - 1];

            if (matrix_rr_create(&vector_rr, sizze[size_mat - 1], 1) ||
                    vector_std_create(&vector_stdd, sizze[size_mat - 1], 1))
            {
                printf("ERROR!!! Having problems creating the table.\n");
                break;
            }

            f = fopen(name_file[COUNT_SIZE + size_mat - 1], "r");
            if (!f)
            {
                printf("ERROR!!! File open with error!");
                break;
            }

            printf("Enter the percentage of table completion: (1%%..100%%) ");
            if (scanf("%d", &size_mat) != 1 || size_mat < 1 || size_mat > 100)
            {
                fclose(f);
                printf("ERROR!!! Invalid percentage entered.\n");
                break;
            }

            count = count * size_mat / 100;

            if (input_matrix_rr(&vector_rr, f, count))
            {
                fclose(f);
                printf("ERROR!!! There were problems filling in the table.\n");
                break;
            }

            fclose(f);
            parsing_vector(&vector_rr, &vector_stdd);
            printf(COLOR_GREEN"%s"COLOR_RESET, "\nDONE!!!\n");
            //print_matrix(&vector_stdd, stdout);
            break;

        case 4:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "The filling of the vector manually\n");

            printf("Enter the dimensions of the vector\n"
                   "(from 1 to 200)\nINPUT: ");

            if (scanf("%d", size_user) != 1 ||
                    size_user[0] <= 0 || size_user[0] > MAX_MATRIX_SIZE)
            {
                printf("ERROE!!! Invalid size entered.\n");
                break;
            }

            count = size_user[0];
            if (matrix_rr_create(&vector_rr, size_user[0], 1))
            {
                printf("ERROR!!! Having problems creating the table.\n");
                break;
            }

            printf("Enter the number of non-zero matrix elements (from 1 to Max ocunt).\nINPUT: ");
            if (scanf("%d", &count) != 1 || count > size_user[0] * 1 ||
                    count <= 0)
            {
                printf("ERROR!!! Entered the wrong number.\n");
                break;
            }

            printf(COLOR_GREEN"%s"COLOR_RESET"%s", "\nATTENTION\n",
                   "Entering %d elements according to the scheme (ROW COLUMN ELEMENT)\n",
                   count);

            if (input_matrix_rr(&vector_rr, stdin, count))
            {
                printf("ERROR!!! Problems with filling in the matrix.\n");
                break;
            }

            parsing_vector(&vector_rr, &vector_stdd);
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            //print_matrix(&vector_stdd, stdout);
        break;

        case 5:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Product of a classical matrix by a vector\n");

            vector_std_r result_std;

            if (vector_std_create(&result_std, matrix_stdd.rows, 1))
            {
                printf("ERROR!!! Failed to create a result matrix.\n");
                break;
            }

            if (multi_std(&matrix_stdd, &vector_stdd, &result_std) != OK)
            {
                *multi_res = 0;
                printf("ERROR!!! Failed to perform a multiplicati.\n");
                break;
            }
            matrix_r result_rr;

            if (matrix_rr_create(&result_rr, matrix_rr.rows, 1))
            {
                printf("ERROR!!! Failed to create a result matrix.\n");
                break;
            }
            if (multi_rr(&matrix_rr, &vector_rr, &result_rr) != OK)
            {
                *multi_res = 0;
                printf("ERROR!!! Failed to perform a multiplicati.\n");
                break;
            }
            *multi_res = 1;
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            //print_coord(&matrix_stdd, &vector_stdd, &result_std);
            break;

        case 6:
            printf(COLOR_YELLOW"%s"COLOR_RESET, " Product of a matrix of a special storage method by a vector\n");

            if (vector_std_create(&result_std, matrix_stdd.rows, 1))
            {
                printf("ERROR!!! Failed to create a result matrix.\n");
                break;
            }

            if (multi_std(&matrix_stdd, &vector_stdd, &result_std) != OK)
            {
                *multi_res = 0;
                printf("ERROR!!! Failed to perform a multiplicati.\n");
                break;
            }
            if (matrix_rr_create(&result_rr, matrix_rr.rows, 1))
            {
                printf("ERROR!!! Failed to create a result matrix.\n");
                break;
            }
            if (multi_rr(&matrix_rr, &vector_rr, &result_rr) != OK)
            {
                *multi_res = 0;
                printf("ERROR!!! Failed to perform a multiplicati.\n");
                break;
            }
            *multi_res = 1; // *multi_res = 2;
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            //print_matrix(&result_std, stdout);
            break;

        case 7:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "The output of the comparison time works\n");

            if (matrix_rr.quan == -1 || vector_rr.quan == -1 ||
                    matrix_stdd.rows == -1 || vector_stdd.rows == -1)
            {
                printf("ERROR!!! There was no multiplication yet.\n");
                break;
            }
            if (matrix_rr_create(&result_rr, matrix_rr.rows, 1))
            {
                printf("ERROR!!! Failed to create a result matrix.\n");
                break;
            }
            if (vector_std_create(&result_std, matrix_stdd.rows, 1))
            {
                printf("ERROR!!! Failed to create a result matrix.\n");
                break;
            }
            time_count(&matrix_rr, &vector_rr, &matrix_stdd, &vector_stdd, &result_rr, &result_std);
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            break;

        case 8:
            printf(COLOR_YELLOW"%s"COLOR_RESET, "Output multiplication results\n");

            if (*multi_res == 2)
            {
                parsing_matrix(&matrix_rr, &matrix_stdd);
                parsing_vector(&vector_rr, &vector_stdd);
                parsing_vector(&result_rr, &result_std);

                if (print_std(&matrix_stdd, &vector_stdd, &result_std))
                {
                    printf("ERROR!!! The matrix is too large, select 9 or 10.");
                    break;
                }
            }
            else if (*multi_res == 1)
            {
                if (print_std(&matrix_stdd, &vector_stdd, &result_std))
                {
                    printf("ERROR!!! The matrix is too large, select 8 or 10.");
                    break;
                }
            }
            else
            {
                printf("ERROR!!! There was no multiplication yet.\n");
                break;
            }
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            break;

        case 9:
            printf("");
            if (*multi_res == 2)
            {
                parsing_matrix(&matrix_rr, &matrix_stdd);
                parsing_vector(&vector_rr, &vector_stdd);
                parsing_vector(&result_rr, &result_std);

                if (print_razr(&matrix_rr, &vector_rr, &result_rr, &result_std))
                {
                    printf("ERROR!!! Something is empty.\n");
                }
            }
            else if (*multi_res == 1)
            {
                if (print_razr(&matrix_rr, &vector_rr, &result_rr, &result_std))
                {
                    printf("ERROR!!! The matrix is too large, select 8 or 10.");
                }
            }
            else
            {
                printf("ERROR!!! There was no multiplication yet.\n");
            }
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            break;

        case 10:
            printf("");
            if (*multi_res == 2)
            {
                parsing_matrix(&matrix_rr, &matrix_stdd);
                parsing_vector(&vector_rr, &vector_stdd);
                parsing_vector(&result_rr, &result_std);

                if (print_coord(&matrix_stdd, &vector_stdd, &result_std))
                {
                    printf("ERROR!!! Something is empty.\n");
                }
            }
            else if (*multi_res == 1)
            {
                if (print_coord(&matrix_stdd, &vector_stdd, &result_std))
                {
                    printf("ERROR!!! Some error with output.\n");
                }
            }
            else
            {
                printf("ERROR!!! There was no multiplication yet.\n");
            }
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            break;

        case 11:
            printf("Output the vector in standard format.\n");
            print_vector_std(&vector_stdd, stdout);
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            break;

        case 12:
            printf("Output the vector in sparse form.\n");
            print_matrix_sparse(&vector_rr);
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            break;

        case 13:
            printf("Output the vector in coordinate format.\n");
            print_coordin_one_v(&vector_stdd);
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            break;

        case 14:
            printf("Output the matrix in standard format.\n");
            print_matrix_std(&matrix_stdd, stdout);
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            break;

        case 15:
            printf("Output the matrix in sparse form.\n");
            print_matrix_sparse(&matrix_rr);
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            break;

        case 16:
            printf("Output the matrix in coordinate format.\n");
            print_coordin_one(&matrix_stdd);
            printf(COLOR_GREEN"\nDONE!\n"COLOR_RESET);
            break;
        case 17:
            print_hello();
            break;
    }
    return OK;
}
