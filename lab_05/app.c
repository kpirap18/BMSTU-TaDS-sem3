#include "app.h"
#include "io.h"
#include "array.h"
#include "timemem.h"
#include "list.h"

int main()
{
    printf("%d", (int)(sizeof(int*)));
    setbuf(stdout, NULL);
    srand(time(NULL));
    int n = 1000;
    int interval = 100;
    int flag = 0;
    times_r t1 = { 1, 5 };
    times_r t2 = { 0, 3 };
    times_r t3 = { 0, 4 };
    times_r t4 = { 0, 1 };
    print_hello();
    
    int num_command = -1;

    while (num_command != 0)
    {
        printf_input();
        if (check_number(&num_command, 0, 5) != OK)
        {
            fflush(stdin);
            printf(COLOR_RED"%s"COLOR_RESET"%s",
                   "ERROR!!!",
                   "Invalid command entered, please re-enter!!!\n");

            print_hello();
        }
        else
        {
            fflush (stdin);
            switch (num_command)
            {
                case 1:
                    printf(COLOR_GREEN
                           "Simulation and characterization for the queue as an array.\n"
                           COLOR_RESET);
                    sd_array(n, interval, t1, t2, t3, t4);//, flag);

                    break;
                case 2:
                    printf(COLOR_GREEN
                           "Simulation and characterization for the queue as an array.\n"
                           COLOR_RESET);
                    printf("Display info about memory? \n1 - yes, 0 - no\nSelection: ");
                    int rc = scanf("%d", &flag);
                    if (rc != 1 || !(flag == 1 || flag == 0))
                    {
                        printf(COLOR_RED"%s"COLOR_RESET"%s",
                               "ERROR!!!",
                               "Invalid number input!\nPlease choose some command\n");
                        break;
                    }
                    fflush(stdin);
                    sd_list(n, interval, t1, t2, t3, t4, flag);
                    fflush(stdin);
                    break;
                case 3:
                    printf(COLOR_GREEN
                           "Change the processing time.\n"
                           COLOR_RESET);
                    double l, r;
                    int c;
                    printf("1: min = %lf; max = %lf\n", t1.min, t1.max);
                    printf("2: min = %lf; max = %lf\n", t2.min, t2.max);
                    printf("3: min = %lf; max = %lf\n", t3.min, t3.max);
                    printf("4: min = %lf; max = %lf\n", t4.min, t4.max);
                    printf("What interval to change?\n");
                    if (check_number(&c, 1, 4) != OK)
                    {
                        fflush(stdin);
                        printf(COLOR_RED"%s"COLOR_RESET"%s",
                               "ERROR!!!",
                               "Invalid number input!\nPlease choose some command\n");
                        break;
                    }
                    else
                    {
                        printf("Input left and right borders: ");
                        int rc = check_float(&l);
                        if (rc != 0)
                        {
                            printf(COLOR_RED"%s"COLOR_RESET"%s",
                               "ERROR!!!",
                               "Invalid number input!\nPlease choose some command\n");
                            break;
                        }
                        rc += check_float(&r);
                        if (rc != 0)
                        {
                            printf(COLOR_RED"%s"COLOR_RESET"%s",
                               "ERROR!!!",
                               "Invalid number input!\nPlease choose some command\n");
                            break;
                        }
                        if (c == 1)
                        {
                            t1.min = l;
                            t1.max = r;
                        }
                        if (c == 2)
                        {
                            t2.min = l;
                            t2.max = r;
                        }
                        if (c == 3)
                        {
                            t3.min = l;
                            t3.max = r;
                        }
                        if (c == 4)
                        {
                            t4.min = l;
                            t4.max = r;
                        }
                        printf("AFTER\n");
                        printf("1: min = %lf; max = %lf\n", t1.min, t1.max);
                        printf("2: min = %lf; max = %lf\n", t2.min, t2.max);
                        printf("3: min = %lf; max = %lf\n", t3.min, t3.max);
                        printf("4: min = %lf; max = %lf\n", t4.min, t4.max);
                    }
                    break;  
                case 4:
                    printf(COLOR_GREEN
                           "Вывод сравнений по времени\n"
                           COLOR_RESET);
                    memory_io();
                    break;    
                case 5:
                    print_hello();
                    break;            
            }
        }
    }
    return OK;
}
