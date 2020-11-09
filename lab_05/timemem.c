#include "timemem.h"

double getime(times_r t)
{
    return (t.max - t.min) * (double)(rand()) / (double)RAND_MAX + t.min;
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

void memory_io()
{
    node_r *free_memory[MAXLENQUEUE];
    node_r *used_memory[MAXLENQUEUE];
    int free_count = 0;
    int used_count = 0;
    int second_use = 0;

    queue_r queue1;
    strcpy(queue1.name, "First Queue");
    queue1.count_len = MAXLENQUEUE;
    queue1.size = sizeof(queuetype);
    char *quearr1;
    quearr1 = (queuetype *)malloc(queue1.count_len * sizeof(queuetype));
    queue1.low = quearr1;
    queue1.up = quearr1 + queue1.count_len;
    queue1.p_in = quearr1;
    queue1.p_out = quearr1;
    for (int i = 0; i < queue1.count_len; i++)
        quearr1[i] = '\0';
    queue1.out_req = 0;
    queue1.in_req = 0;
    queue1.count_req = 0;
    queue1.sum_len = 0;
    queue1.sum_time = 0;
    queue1.tmp_len = 0;

    node_r *queue2 = NULL;
    queue_r que2;
    strcpy(que2.name, "Second Queue");
    que2.size = sizeof(node_r);
    que2.count_len= MAXLENQUEUE;
    que2.p_in = NULL;
    que2.p_out = NULL;
    que2.count_req = 0;
    que2.sum_len = 0;
    que2.tmp_len = 0;
    que2.in_req = 0;
    que2.out_req = 0;
    que2.sum_time = 0;

    int64_t t1b = tick();
    queuearray_push(&queue1, '1');
    int64_t t1e = tick();
    int64_t t2b = tick();
    queue2 = queuelist_push(queue2, '2', used_memory, &used_count, free_memory, &free_count, &second_use);
    int64_t t2e = tick();
    printf(COLOR_YELLOW"ДОБАВЛЕНИЕ\n"COLOR_RESET);
    printf("Очередь-массив \t %d\n", (int)(t1e - t1b));
    printf("Очередь-список \t %d\n\n", (int)(t2e - t2b));

    t1b = tick();
    queuearray_pop(&queue1);
    t1e = tick();
    t2b = tick();
    queuelist_pop(&queue2);
    t2e = tick();

    printf(COLOR_YELLOW"УДАЛЕНИЕ\n"COLOR_RESET);
    printf("Очередь-массив \t %d\n", (int)(t1e - t1b));
    printf("Очередь-список \t %d\n\n", (int)(t2e - t2b));

    int n = 10;
    printf(COLOR_YELLOW"ПАМЯТЬ\n"COLOR_RESET);
    for (int i = 0; i < 4; i++)
    {
        printf("Колчество элементов = %d\n", n);
        printf("Очередь-массив \t %d\n", (int)(sizeof(char) * n));
        printf("Очередь-список \t %d\n\n", (int)((sizeof(node_r*) + sizeof(char)) * n));
        n *= 10;
    }
}
