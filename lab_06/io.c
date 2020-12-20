#include "io.h"
#include "list.h"
#include "hash.h"

void print_hello()
{
    printf(COLOR_GREEN"%s"COLOR_RESET,
    "УСЛОВИЕ!!!\n"
    "В текстовом файле содержатся целые числа. Построить ДДП из чисел файла.\n"
    "Вывести его на экран в виде дерева. Сбалансировать полученное дерево \n"
    "и вывести его на экран. Построить хеш-таблицу из чисел файла.\n"
    "Использовать закрытое  хеширование для  устранения  коллизий.\n"
    "Осуществить добавление введенного целого числа,если его там нет,\n"
    "в ДДП, в сбалансированноедерево, в хеш-таблицу и в файл.Сравнить\n"
    "время добавления, объем памяти и количество сравнений при использовании\n"
    "различных(4-х)структур данных. Если количество сравнений  в  хеш-таблице  \n"
    "больше  указанного(вводить),то  произвести реструктуризацию таблицы, выбрав другую функцию.");

    printf(COLOR_YELLOW"\n\nMENU\n"COLOR_BLUE"%s"COLOR_RESET,
    "1 - Загрузить данные их файла\n"
    "2 - Вывести деревья и хеш-таблицу\n"
    "3 - Добавить элемент\n"
    "4 - Вывести сравнение\n"
    "5 - Рассчитать средние величины\n"
    "\n"
    "0 - Выход\n\n");
}

void printf_input()
{
    printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nFor help input 6", "\nINPUT YOUR CHOICE: ");
}

int check_number(int *const number, const int l, const int r, int flag)
{
    char num[3];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return INPUTERROR;
    num[strlen(num) - 1] = '\0';
    *number = (int)atoi(num);

    if (flag && (*number < l || *number > r))
    {
        //clean_my();
        return INPUTERROR;
    }

    return OK;
}
int readtolist(FILE *f, node_t **head, node_t **headbal, int *rc)
{
    node_t *cur = NULL;
    node_t *curbal = NULL;

    int numread;
    int count = 0;
    int max = 0;
    
    while (TRUE)
    {
        if (feof(f))
        {
            break;
        }

        fscanf(f, "%d", &numread);
        count++;

        if (abs(numread) > max)
        {
            max = abs(numread);
        }

        cur = createnode(numread, 1);
        curbal = createnode(numread, 1);

        *head = insert(*head, cur, rc);
        *headbal = insertbalance(*headbal, curbal, rc);
    }

    return count;
}

void readtotable(FILE *f, inttable_t **table)
{
    inttable_t *tab = inittable(SIZEST);
    int rc = 0;
    int numread;
    while (TRUE)
    {
        if (feof(f))
        {
            break;
        }
        fscanf(f, "%d", &numread);
       tab = loadhashtable(tab, numread, &rc);
    }
    *table = tab;
}