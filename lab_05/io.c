/*! \defgroup <main> (The Main module)
  @{
  */
/**
  * \file io.c
  * \brief File with the input/output code
  * \version 1.0
  * \date 06.11.2020
  @}
  */

#include "io.h"

/*!
 * \brief print_hello - The output menu.
 */
void print_hello()
{
    /*printf(COLOR_YELLOW"%s" COLOR_RESET "%s",
           "\n\nMENU (select one item, enter a number):\n\n",
           "1 - Simulation and characterization for the queue as an array.\n"
           "2 - Simulation and characterization for the queue as a list.\n\n"

           "0  - Program exit.\n"
           );*/
    printf(COLOR_YELLOW"%s" COLOR_RESET "%s",
           "\n\nМЕНЮ (выбрать один пункт меню):\n\n",
           "1 - Моделирование и характеристика для очереди в виде массива.\n"
           "2 - Моделирование и характеристика для очереди в виде списка.\n"
           "3 - Изменить время обработки заявки.\n"
           "4 - Вывод сравнения времени при выполнении операций.\n\n"

           "0 - Выход из программы.\n\n"
           );
}

/*!
 * \brief printf_input - Print a command prompt.
 */
void printf_input()
{
    printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nДля помощи нажмите 5", "\nВАШ ВЫБОР: ");
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
 * \brief check_number - Entering a command and checking it.
 * \param *const number - Pointer to the number.
 * \param l, r - The left and right boundaries of the input.
 * \return OK if all is well, otherwise some ERROR_.
 */
int check_float(double *const number)
{
    char num[3];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return DONT_INT_NUM_CHOICE;
    num[strlen(num) - 1] = '\0';
    *number = (double)atof(num);

    // if (fabs(*number - 0) < EPS)
    // {
    //     //clean_my();
    //     return INV_NUM_CHOICE;
    // }

    return OK;
}

/*!
 * \brief check_number - Entering a command and checking it.
 * \param *const number - Pointer to the number.
 * \param l, r - The left and right boundaries of the input.
 * \return OK if all is well, otherwise some ERROR_.
 */
int check_number(int *const number, const int l, const int r)
{
    char num[3];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return DONT_INT_NUM_CHOICE;
    num[strlen(num) - 1] = '\0';
    *number = (int)atoi(num);

    if (*number < l || *number > r)
    {
        //clean_my();
        return INV_NUM_CHOICE;
    }

    return OK;
}

void len_swow(queue_r *queue)
{
    //printf("Current length %s: \t %d\n", queue->name, queue->tmp_len);
    printf("Текущая длина %s: \t %d\n", queue->name, queue->tmp_len);
    if (queue->count_req > 0)
    {
        /*printf("Middle length %s: \t %lf\n", queue->name, 
                (double)queue->sum_len / (double)queue->count_req);*/

        printf("Средняя длина %s: \t %lf\n", queue->name, 
                (double)queue->sum_len / (double)queue->count_req);
    }
}
