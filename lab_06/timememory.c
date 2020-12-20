#include "timememory.h"
#include <stdint.h>

int64_t getFileSize(const char* file_name){
	int64_t _file_size = 0;
	FILE* fd = fopen(file_name, "rb");
	if(fd == NULL){
		_file_size = -1;
	}
	else{
		while(getc(fd) != EOF)
			_file_size++;
		fclose(fd);
	}
	return _file_size;
}

int searchfile(FILE *f, int num)
{
    int numfile;
    int count = 0, flag = 0;
    while (fscanf(f, "%d", &numfile) > 0)
    {
        count++;

        if (num == numfile)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        return count;
    }
    else
    {
        return 0;
    }
    fseek(f, 0L, SEEK_SET);
}

int64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void timememory(node_t *head, node_t *headbal, inttable_t *table, FILE *f)
{
    printf("Введите кол-во сравнений для хэш-таблицы\n");
    int limit;
    if (fscanf(stdin, "%d", &limit) != 1)
    {
        printf(COLOR_RED"Ошибка ввода\n\n"COLOR_RESET);
        return;
    }
    int num;
    int s1, e1;
    int count = 0 , countb = 0, counth = 0, countf = 0;
    int flag = 0;

    while(TRUE)
    {
        printf("Введите число, которое надо добавить\n");

        if (fscanf(stdin, "%d", &num) != 1)
        {
            printf(COLOR_RED"Ошибка ввода\n\n"COLOR_RESET);
            flag = 1;
            break;
        }
        countf = searchfile(f, num);
        if (countf == 0)
        {
            break;
        }
        else
        {
            printf("Такое число уже есть\n\n");
        }
        
    }
    if (flag == 1)
    {
        return;
    }

    s1 = tick();
    node_t *cur = createnode(num, 1);
    //node_t *curbal = createnode(num, 1);

    head = insert(head, cur, &count);
    //headbal = insertbalance(headbal, curbal, &countb)
    e1 = tick();
    printf("КОЛИЧЕСТВО %d\n", table->arrsize);
    printf("|  Структура  |   Время  | Сравнений | Память |\n");
    printf("|     ДДП     |  %6d  | %9d | %6ld |\n", e1-s1, count, sizeof(node_t) * table->arrsize);

    s1 = tick();
    node_t *curbal = createnode(num, 1);

    headbal = insertbalance(headbal, curbal, &countb);
    e1 = tick();

    printf("|    CДДП     |  %6d  | %9d | %6ld |\n", e1-s1, countb, sizeof(node_t) * table->arrsize);

    s1 = tick();
    loadhashtable(table, num, &counth);
    e1 = tick();

    printf("| ХЭШ ТАБЛИЦА |  %6d  | %9d | %6ld |\n", e1-s1, counth, sizeof(intt) * table->arrsize + sizeof(inttable_t));

    s1 = tick();
    rewind(f);
    fseek(f, 0, SEEK_END);
    int s = ftell(f);
    
    fprintf(f, "%d\n", num);
    fseek(f, 0L, SEEK_SET);
    e1 = tick();

    printf("|     ФАЙЛ    |  %5d  | %9d | %6ld |\n\n\n", e1-s1, table->arrsize, sizeof(char) * s);

    while (limit <= counth)
    {
        table  = rerwritefunchash(table);
        counth = 0;
        s1 = tick();
        loadhashtable(table, num, &counth);
        e1 = tick();

        printf("| ХЭШ ТАБЛИЦА |  %5d  | %9d | %6ld |\n", e1-s1, counth, sizeof(intt) * table->arrsize + sizeof(inttable_t));
    }
}

void timememory1(int len)
{
    printf("Введите кол-во сравнений для хэш-таблицы\n");
    int limit;
    if (fscanf(stdin, "%d", &limit) != 1)
    {
        printf(COLOR_RED"Ошибка ввода\n\n"COLOR_RESET);
        return;
    }

    node_t *head = NULL;
    node_t *headbal = NULL;
    inttable_t *hashtable = inittable(len);
    srand(time(NULL));
    FILE *f = fopen("a.txt", "a");
    int count = 0;
    int rc = 0;
    int c = 0;
    int s1, e1;
    int x = 0;

    int tall = 0;
    while (c < len)
    {
        x = abs(rand()%200 - 50);
        s1 = tick();
        for (int i = 0; i < 100; ++i);
        fprintf(f, "%d\n", x);
        e1 = tick();
        tall += (e1 - s1);
        count += c;
        c++;
    }
    fclose(f);
    int size = getFileSize("a.txt");
    printf("|  Структура  |  Кол-во  |   Ср.время   | Ср.сравнений |  Память |\n");
    printf("|     ФАЙЛ    |  %6d  | %12.6lf |   %.6lf   | %6d  |\n", len, (double)tall / len, (double)count / len, size);


    f = fopen("a.txt", "r");
    count = 0;
    x = 0;
    tall = 0;
    c = 0;
    while (c < len)
    {
        fscanf(f, "%d", &x);
        s1 = tick();
        node_t *cur = createnode(x, 1);

        head = insert(head, cur, &count);
        e1 = tick();
        tall += (e1 - s1);
        c++;
    }
    printf("|     ДДП     |  %6d  | %12.6lf |   %.6lf   | %6d  |\n", len, (double)tall / len, (double)count / len, (int)(sizeof(node_t) * len));

    fclose(f);
    f = fopen("a.txt", "r");
    tall = 0;
    c = 0;
    count = 0;
    x = 0;
    while (c < len)
    {
        fscanf(f, "%d", &x);
        s1 = tick();
        node_t *curb = createnode(x, 1);

        headbal = insertbalance(headbal, curb, &count);
        e1 = tick();
        tall += (e1 - s1);
        c++;
    }
    printf("|    CДДП     |  %6d  | %12.6lf |   %.6lf   | %6d  |\n", len, (double)tall / len, (double)count / len, (int)(sizeof(node_t) * len));

    fclose(f);
    f = fopen("a.txt", "r");
    tall = 0;
    c = 0;
    count = 0;
    while (c < len)
    {
        fscanf(f, "%d", &x);
        s1 = tick();
        int r = 0;
        hashtable = loadhashtable(hashtable, x, &r);
        e1 = tick();
        count += r;
        tall += (e1 - s1);
        c++;
    }
    printf("| ХЭШ ТАБЛИЦА |  %6d  | %12.6lf |   %.6lf   | %6d  |\n", len, (double)tall /8/ len, (double)count / len, (int)(sizeof(intt) * len + sizeof(inttable_t)));
    fclose(f);

    while (limit <= (count / len))
    {
        hashtable  = rerwritefunchash(hashtable);
        f = fopen("a.txt", "r");
        tall = 0;
        c = 0;
        count = 0;
        while (c < len)
        {
            fscanf(f, "%d", &x);
            s1 = tick();
            int r = 0;
            hashtable = loadhashtable(hashtable, x, &r);
            e1 = tick();
            count += r;
            tall += (e1 - s1);
            c++;
        }
        printf("| ХЭШ ТАБЛИЦА |  %6d  | %12.6lf |   %.6lf   | %6d  |\n", len, (double)tall / len, (double)count / len, (int)(sizeof(intt) * len + sizeof(inttable_t)));
        fclose(f);
    }
}