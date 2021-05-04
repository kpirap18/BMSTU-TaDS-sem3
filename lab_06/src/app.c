#include "app.h"
#include "io.h"
#include "list.h"
#include "hash.h"
#include "timememory.h"

char files[3][100] = {"test1.txt", "test2.txt", "test3.txt"};
int file = 1;

int main()
{
    node_t *head = NULL;
    node_t *headbal = NULL;
    inttable_t *hashtable = NULL;
    int count;
    int rc;
    FILE *f;
    print_hello();
    

    int command = -1;

    while(command != 0)
    {
        printf_input();
        if (check_number(&command, 0, 6, 1) != OK)
        {
            printf(COLOR_RED"%s"COLOR_RESET"%s",
                   "ERROR!!!",
                   "Invalid command entered, please re-enter!!!\n");

            print_hello();
        }
        else
        {
            switch (command)
            {
            case 1:
                fflush(stdin);
                printf(COLOR_YELLOW"ЗАГРУЗКА ДАННЫХ ИЗ ФАЙЛА\n"COLOR_RESET);
                
                printf("Выберите файл для записи\n"
                "1 - test1.txt\n"
                "2 - test2.txt\n"
                "3 - test3.txt\n"
                "ВЫБОР: ");

                if (check_number(&file, 1, 3, 1)!= OK)
                {
                    printf(COLOR_RED"Неверно выбран файл\n\n"COLOR_RESET);
                    break;
                }
                freetree(head);
                freetree(headbal);
                f = fopen(files[file -1], "r");
                if (f)
                {
                    count = readtolist(f, &head, &headbal, &rc);
                    fclose(f);
                }
                else
                {
                    printf("Ошибка открытия файла\n");
                    break;
                }
                
                if (count > 0)
                {
                    f = fopen(files[file -1], "r");
                    if (f)
                    {
                        freetable(hashtable);
                        readtotable(f, &hashtable);
                        fclose(f);
                    }
                    else
                    {
                        printf("Ошибка открытия файла\n");
                        break;
                    }
                }
                printf(COLOR_YELLOW"ДАННЫЕ ЗАГРУЖЕНЫ!\n\n"COLOR_RESET);
                fflush(stdin);
                getchar();
                break;
            
            case 2:
                fflush(stdin);
                printf(COLOR_YELLOW"ПЕЧАТЬ ДЕРЕВЬЕВ И ТАБЛИЦЫ НА ЭКРАН\n"COLOR_RESET);
                
                if (head == NULL || headbal == NULL)
                {
                    printf(COLOR_RED"ОШИБКА!!!\n"COLOR_RESET"Для начала выберите пункт 1\n\n");
                    break;
                }

                f = fopen("out.gv", "w");
                exporttodot(f, head);
                fclose(f);

                f = fopen("outb.gv", "w");
                exporttodot(f, headbal);
                fclose(f);

                printf(COLOR_YELLOW"\n\nБИНАРНОЕ ДЕРЕВО\n\n"COLOR_RESET);
                printtree(head, 0, 0);

                printf(COLOR_YELLOW"\n\nСБАЛАНСИРОВАННОЕ БИНАРНОЕ ДЕРЕВО\n\n"COLOR_RESET);
                printtree(headbal, 0, 0);

                printf(COLOR_YELLOW"\n\nХЭШ-ТАБЛИЦА\n\n"COLOR_RESET);
                tableprint(stdout, hashtable);
                printf("\n");
                fflush(stdin);
                getchar();
                break;
            
            case 3:
                fflush(stdin);
                printf(COLOR_YELLOW"ДОБАВЛЕНИЕ ЧИСЛА В ДЕРЕВЬЯ, ТАБЛИЦУ И ФАЙЛ\n"COLOR_RESET);
                int rc = 0;
                int num = 0;
                fprintf(stdout, "Введите число: ");
                if (fscanf(stdin, "%d", &num) != 1)
                {
                    printf(COLOR_RED"Ошибка ввода\n\n"COLOR_RESET);
                    break;
                }

                node_t *cur = createnode(num, 1);
                node_t *curbal = createnode(num, 1);

                head = insert(head, cur, &rc);
                headbal = insertbalance(headbal, curbal, &rc);

                if (!hashtable)
                {
                    hashtable = inittable(SIZEST);
                }
                hashtable = loadhashtable(hashtable, num, &rc);

                f = fopen(files[file - 1], "r");
                int sear = searchfile(f, num);
                fclose(f);

                if (sear == 0)
                {
                   f = fopen(files[file - 1], "a");
                   fprintf(f, "%d\n", num);
                   fclose(f);
                   printf(COLOR_YELLOW"ЧИСЛО УСПЕШНО ДОБАВЛЕНО!\n"COLOR_RESET);
                }
                else
                {
                    printf(COLOR_YELLOW"ЧИСЛО УЖЕ ЕСТЬ!\n"COLOR_RESET);
                }
                fflush(stdin);
                getchar();
                break;

            case 4:
                fflush(stdin);
                if (head == NULL || headbal == NULL)
                {
                    printf(COLOR_RED"ОШИБКА!!!\n"COLOR_RESET"Для начала выберите пункт 1\n\n");
                    break;
                }
                f = fopen(files[file - 1], "r+");
                timememory(head, headbal, hashtable, f);
                fflush(stdin);
                getchar();
                break;
            case 5:
                fflush(stdin);
                int len;
                printf("Введите кол-во для рассчета средних значений: ");
                if (fscanf(stdin, "%d", &len) != 1)
                {
                    printf(COLOR_RED"Ошибка ввода\n\n"COLOR_RESET);
                    break;
                }
                
                timememory1(len);
                fflush(stdin);
                getchar();
                break;
                
            case 6:
                print_hello();
                break;

            default:
                break;
            }
        }
    }
}