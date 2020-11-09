#include "list.h"

node_r* createelem(queuetype c)
{
    node_r *elem = malloc(sizeof(node_r));
    if (elem)
    {
        elem->inf = c;
        elem->next = NULL;
    }

    return elem;
}

node_r* pushfront(node_r *head, node_r *elem)
{
    elem->next = head;
    return elem;
}

node_r* popfront(node_r **head)
{
    node_r *cur = NULL;
    if (head)
    {
        cur = *head;
        *head = (*head)->next;
    }
    return cur;
}

node_r* popend(node_r **head)
{
    node_r *end = NULL;
    if (*head != NULL)
    {
        node_r *cur = *head;
        if (cur->next)
        {
            for ( ; cur->next->next; cur = cur->next)
                ;
            end = cur->next;
            cur->next = NULL;
        }
        else
        {
            end = cur;
            *head = NULL;
        }
    }

    return end;
}

void freeall(node_r *head)
{
    node_r *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}


node_r *queuelist_push(node_r *queue, queuetype c, node_r **user_memory,
                    int *user_count, node_r **free_memory,
                    int *free_count, int *second_use)
{
    node_r *item = NULL;
    item = createelem(c);
    if (item)
    {
        user_memory[*(user_count++)] = item;
        int sign = 0;
        for (int i = 0; i < *user_count; ++i)
        {
            if (item == free_memory[i])
            {
                free_memory[i] = NULL;
                sign = 1;
            }
            
            if (sign)
                free_memory[i] = free_memory[i + 1];
        }
        if (sign)
        {
            *free_count -= 1;
            *second_use += 1;
        }
        queue = pushfront(queue, item);
    }
    else
    {
        printf("Queue id full!\n");
    }

    return queue;  
}
node_r *queuelist_pop(node_r **queue)
{
    node_r *cur = NULL;
    cur = popend(queue);

    if (cur == NULL)
    {
        printf("Queue is empty!\n");
    }

    return cur;
}
void queuelist_print(node_r *queue)
{
    node_r *cur = queue;
    if (queue == NULL)
    {
        printf("Queue is emrty.\n");
    }
    else
    {
        printf("Current queue:\n");
        for ( ; cur; cur = cur->next)
            printf("%c\n", cur->inf);
        printf("\n");
    }
}

void sd_list(int n, int interval, times_r t1, 
              times_r t2, times_r t3, times_r t4, int flag)
{
    node_r *cur;
    node_r *free_memory[MAXLENQUEUE];
    node_r *used_memory[MAXLENQUEUE];
    int free_count = 0;
    int used_count = 0;
    int second_use = 0;

    node_r *queue1 = NULL;
    queue_r que1;
    strcpy(que1.name, "First Queue");
    que1.size = sizeof(node_r);
    que1.count_len= MAXLENQUEUE;
    que1.p_in = NULL;
    que1.p_out = NULL;
    que1.count_req = 0;
    que1.sum_len = 0;
    que1.tmp_len = 0;
    que1.in_req = 0;
    que1.out_req = 0;
    que1.sum_time = 0;

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

    int reqin1 = 0;
    int reqout1 = 0;
    int reqin2 = 0;
    int reqout2 = 0;
    int reqshow = 0;
    int out_queue2 = 0;

    double time = 0;
    double timereq1 = 0;
    double timereq2 = 0;
    double timereqobr = 0;
    double alltimeque1 = 0;
    double alltimeque2 = 0;

    time_t rtime1 = clock(); // можно и тактами измерить

    int type_queue = 0;

    while (reqout1 < n)
    {
        if (que1.tmp_len >= MAXLENQUEUE || que2.tmp_len >= MAXLENQUEUE)
        {
            printf("Queue is full.\n");
            break;
        }

        if (fabs(timereq1 - 0) < EPS)
            timereq1 = getime(t1);

        if (fabs(timereq2 - 0) < EPS)
            timereq2 = getime(t2);

        if (fabs(timereqobr - 0) < EPS)
        {
            if (queue1 != NULL)
            {
                timereqobr = getime(t3);
                type_queue = 1;
                cur = queuelist_pop(&queue1);
                if (cur != NULL)
                {
                    free_memory[free_count++] = cur;
                    free(cur);
                }
                que1.tmp_len--;
                que1.sum_len += que1.tmp_len;
                que1.count_req++;
                que1.out_req++;
                alltimeque1 += timereqobr;
            }
            else if (queue2 != NULL)
            {
                timereqobr = getime(t4);
                type_queue = 2;
                cur = queuelist_pop(&queue2);
                if (cur != NULL)
                {
                    free_memory[free_count++] = cur;
                    free(cur);
                }
                que2.tmp_len--;
                que2.sum_len += que2.tmp_len;
                que2.count_req++;
                que2.out_req++;
                alltimeque2 += timereqobr;
            }
        }
        else
        {
            if (type_queue == 2 && queue1 != NULL)
            {
                queue2 = queuelist_push(queue2, '2', used_memory, &used_count, free_memory,&free_count, &second_use);
                que2.tmp_len++;
                que2.sum_len += que2.tmp_len;
                que2.count_req++;
                que2.in_req++;
                alltimeque2 -= timereqobr;
                timereqobr = 0;
                out_queue2++;

                continue;
            }
        }
        
        double timemin = 0;

        if (fabs(timereqobr - 0) < EPS)
            if (timereq1 - timereq2 < EPS) // найти минимум из 2х
                timemin = timereq1;
            else
                timemin = timereq2;
        else
        {
            if (timereq2 - timereqobr < EPS) // найти минимум из 3х
                timemin = timereq2; 
            else
                timemin = timereqobr;

            if (timereq1 - timemin < EPS)
                timemin = timereq1;
        }
        
        if (fabs(timemin - timereqobr) < EPS)
        {
            timereqobr = 0;
            if (type_queue == 1)
                reqout1++;
            if (type_queue == 2)
                reqout2++;
        }

        if (reqout1 == n)
            break;
        
        if (fabs(timemin - timereq1) < EPS)
        {
            queue1 = queuelist_push(queue1, '1', used_memory, &used_count, free_memory, &free_count, &second_use);
            que1.tmp_len++;
            que1.sum_len += que1.tmp_len;
            que1.count_req++;
            que1.in_req++;
            reqin1++;
        }

        if (fabs(timemin - timereq2) < EPS)
        {
            queue2 = queuelist_push(queue2, '2', used_memory, &used_count, free_memory, &free_count, &second_use);
            que2.tmp_len++;
            que2.sum_len += que2.tmp_len;
            que2.count_req++;
            que2.in_req++;
            reqin2++;
        }

        timereq1 -= timemin;
        timereq2 -= timemin;

        if (timereqobr >= timemin)
            timereqobr -= timemin;
        time += timemin;

        if (reqout1 % interval == 0 && reqout1 != reqshow)
        {
            reqshow = reqout1;
            //printf("Applications processed of queue type 1: \t %d\n", reqout1);
            printf("Обработано заявок 1го типа: \t %d\n", reqout1);
            len_swow(&que1);
            len_swow(&que2);
            printf("\n");
        }
    }
    
    time_t rtime2 = clock();
    int timerealall = rtime2 - rtime1;

    double avetime_in1 = (t1.max + t1.min) / 2;
    double avetime_out1 = (t3.max + t3.min) / 2;
    double avetime_in2 = (t2.max + t2.min) / 2;

    double total_avetime_in1 = n * avetime_in1;
    double total_avetime_out1 = n * avetime_out1;

    double timemodel;
    if (total_avetime_in1 - total_avetime_out1 > EPS)
        timemodel = total_avetime_in1;
    else
        timemodel = total_avetime_out1;

    double wait_in1 = time / avetime_in1;
    double wait_in2 = time / avetime_in2;

    double totalwork = alltimeque1 + alltimeque2;
    double timewithoutwork = time - totalwork;

    printf("Общее время моделирования (в усл. ед. в.): \t %lf\n", time);

    if (fabs(timemodel - 0) > EPS)
    {
        double per_out = fabs(100 * (time - timemodel) / timemodel);
        printf("Погрешность времени моделирования: \t %lf%% \n\n", per_out);
    }
    else
    {
        printf("Погрешность времени моделирования: \t 0\n\n");
    }

    printf("Число вошедших в 1 очередь:  \t %d\n", reqin1);
    printf("Число вышедших из 1 очереди:  \t %d\n", reqout1);
    printf("Число вошедших во 2 очередь:  \t %d\n", reqin2);
    printf("Число вышедших из 2 очереди:  \t %d\n", reqout2);
    printf("Число выброшенных заявок из 2 очереди: %d\n", out_queue2);
    printf("Время работы (реальное)(в мкс): %d\n", timerealall);

    printf("Среднее время обработки заявки 1 очереди: \t %lf\n", avetime_in1);
    printf("Среднее время обработки заявки 2 очереди: \t %lf\n", avetime_in2);
    

    if (fabs(wait_in1 - 0) > EPS)
    {
        double per_in1 = fabs(100 * (reqin1 - wait_in1) / wait_in1);
        printf("Погрешность ввода 1 очередь^ \t %lf%%\n", per_in1);
    }
    else
    {
        printf("Погрешность ввода 1 очереди: 0\n");
    }

    if (fabs(wait_in2 - 0) > EPS)
    {
        double per_in2 = fabs(100 * (reqin2 - wait_in2) / wait_in2);
        printf("Погрешность ввода 2 очередь^ \t %lf%%\n", per_in2);
    }
    else
    {
        printf("Погрешность ввода 2 очереди: 0\n");
    }
    
    

    printf("Время не работы ОА (в усл. ед. в.): \t %lf\n\n", timewithoutwork);

    

    if (flag == 1)
    {
        //printf("Number of reused addresses after freeing memory: %d\n", second_use);
        //printf("Number of unused addresses after freeing memory: %d\n", free_count);
        printf("Количество повторно используемных адресов: %d\n", second_use);
        printf("Количество неиспользуемых адресов: %d\n", free_count);
    //printf("Unused addresses:\n");
    printf("Неиспользуемые адреса:\n");
        for (int i = 0; i < ((30 < free_count) ? 30 : free_count); i++)
            printf("%p\n", (void *)free_memory[i]);
        fflush(stdin);
    }
    free(queue1);
    free(queue2);  
    fflush(stdin);
}
