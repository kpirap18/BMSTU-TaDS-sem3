#include "array.h"
#include "time.h"
#include "io.h"

void queuearray_push(queue_r *queue, char c_elem)//,char *elem, )
{
    char *p_in = queue->p_in;
    
    if (queue->p_in == queue->p_out &&
        *((char*)queue->p_in) != '\0')
    {
        printf(COLOR_RED"ATTENTION!\n"COLOR_RESET"Queue is full!\n");
    }
    else
    {
        *((char*)queue->p_in) = c_elem;
        //elem[strlen(elem)] = c_elem;
        if (queue->p_in != queue->up)
        {
            queue->p_in = p_in + 1;
        }
        else
        {
            queue->p_in = queue->low;
        }
    }
}

char queuearray_pop(queue_r *queue)//, char *elem)
{
    char *p_out = queue->p_out;
    char ps;

    if (queue->p_in == queue->p_out &&
        *((char*)queue->p_in) == '\0')
    {
        printf(COLOR_RED"ATTENTION!\n"COLOR_RESET"Queue is empty!\n");
    }
    else
    {
        ps = *((char*)queue->p_out);
        //elem[strlen(elem)] = '\0'; /////////
        *((char*)queue->p_out) = '\0';
        if (queue->p_out != queue->up)
        {
            queue->p_out = p_out + 1;
        }
        else
        {
            queue->p_out = queue->low;
        }
    }
    return ps;
}
void queuearray_print(queue_r *queue)//, char *elem)
{
    if (queue->p_out == queue->p_in &&
        *((char*)queue->p_in) == '\0')
    {
        printf(COLOR_RED"ATTENTION!\n"COLOR_RESET"Queue is empty!\n");
    }
    else
    {
        //printf("Current queue %s: \n", elem);/////////
        char *begin = queue->p_out;
        char *end = queue->p_in;
        while (begin != end) // возможно надо будет записать do while
        {
            printf("%c\n", *begin);
            if (begin != queue->up)
            {
                begin++;
            }
            else
            {
                begin = queue->low;
            }
        }
    }   
}

void sd_array(int n, int interval, times_r t1, 
              times_r t2, times_r t3, times_r t4)//, int flag)
{
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

    queue_r queue2;
    strcpy(queue2.name, "Second Queue");
    queue2.count_len = MAXLENQUEUE;
    queue2.size = sizeof(queuetype);
    char *quearr2;
    quearr2 = (queuetype *)malloc(queue2.count_len * sizeof(queuetype));
    queue2.low = quearr2;
    queue2.up = quearr2 + queue2.count_len;
    queue2.p_in = quearr2;
    queue2.p_out = quearr2;
    for (int i = 0; i < queue2.count_len; i++)
        quearr2[i] = '\0';
    queue2.out_req = 0;
    queue2.in_req = 0;
    queue2.count_req = 0;
    queue2.sum_len = 0;
    queue2.sum_time = 0;
    queue2.tmp_len = 0;
    int out_queue2 = 0;

    int reqin1 = 0;
    int reqout1 = 0;
    int reqin2 = 0;
    int reqout2 = 0;
    int reqshow = 0;

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
        if ((queue1.p_in == queue1.p_out && *((char*)queue1.p_in) != '\0') ||
            (queue2.p_in == queue2.p_out && *((char*)queue2.p_in) != '\0'))
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
            if (!(queue1.p_in == queue1.p_out && *((char*)queue1.p_in) == '\0'))
            {
                timereqobr = getime(t3);
                type_queue = 1;
                queuearray_pop(&queue1);//, quearr1);
                queue1.tmp_len--;
                queue1.sum_len += queue1.tmp_len;
                queue1.count_req++;
                queue1.out_req++;
                alltimeque1 += timereqobr;
            }
            else if (!(queue2.p_in == queue2.p_out && *((char*)queue2.p_in) == '\0'))
            {
                timereqobr = getime(t4);
                type_queue = 2;
                queuearray_pop(&queue2);//, quearr2);
                queue2.tmp_len--;
                queue2.sum_len += queue2.tmp_len;
                queue2.count_req++;
                queue2.out_req++;
                alltimeque2 += timereqobr;
            }
        }
        else if (type_queue == 2 && !(queue2.p_in == queue2.p_out && *((char*)queue2.p_in) == '\0'))
        {
            queuearray_push(&queue2, '2');//quearr2, '2');
            queue2.tmp_len++;
            queue2.sum_len += queue2.tmp_len;
            queue2.count_req++;
            queue2.in_req++;
            alltimeque2 -= timereqobr;
            timereqobr = 0;
            out_queue2++;
            continue;
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
            queuearray_push(&queue1, '1');//quearr1, '1');
            queue1.tmp_len++;
            queue1.sum_len += queue1.tmp_len;
            queue1.count_req++;
            queue1.in_req++;
            reqin1++;
        }

        if (fabs(timemin - timereq2) < EPS)
        {
            queuearray_push(&queue2, '2');//quearr2, '2');
            queue2.tmp_len++;
            queue2.sum_len += queue2.tmp_len;
            queue2.count_req++;
            queue2.in_req++;
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
            len_swow(&queue1);
            len_swow(&queue2);
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

    double totalwork = alltimeque1 + alltimeque2;
    double timewithoutwork = time - totalwork;

    double timemodel;
    if (total_avetime_in1 - total_avetime_out1 > EPS)
        timemodel = total_avetime_in1;
    else
        timemodel = total_avetime_out1;

    double wait_in1 = time / avetime_in1;
    double wait_in2 = time / avetime_in2;

    printf("Общее время моделирования (в усл. ед. в.): \t %lf\n", time);

    if (fabs(timemodel - 0) > EPS)
    {
        double per_out = fabs(100 * (time - timemodel) / timemodel);
        printf("Погрешность работы ОА: \t %lf%% \n\n", per_out);
    }
    else
    {
        printf("Погрешность моелирования: \t 0\n\n");
    }
    printf("Среднее время обработки заявки 1 очереди: \t %lf\n", avetime_in1);
    printf("Среднее время обработки заявки 2 очереди: \t %lf\n", avetime_in2);
    printf("Число вошедших в 1 очередь:  \t %d\n", reqin1);
    printf("Число вышедших из 1 очереди:  \t %d\n", reqout1);
    printf("Число вошедших во 2 очередь:  \t %d\n", reqin2);
    printf("Число вышедших из 2 очереди:  \t %d\n", reqout2);
    printf("Число выброшенных заявок из 2 очереди: %d\n", out_queue2);
    printf("Время работы (реальное)(в мкс): %d\n\n", timerealall);


    if (fabs(wait_in1 - 0) > EPS)
    {
        double per_in1 = fabs(100 * (reqin1 - wait_in1) / wait_in1);
        printf("Погрешность ввода 1 очередь: \t %lf%%\n", per_in1);
    }
    else
    {
        printf("Погрешность ввода 1 очереди: 0\n");
    }

    if (fabs(wait_in2 - 0) > EPS)
    {
        double per_in2 = fabs(100 * (reqin2 - wait_in2) / wait_in2);
        printf("Погрешность ввода 2 очередь: \t %lf%%\n", per_in2);
    }
    else
    {
        printf("Погрешность ввода 2 очереди: 0\n");
    }
    
   

    printf("Время не работы ОА (в усл. ед. в.): \t %lf\n\n", timewithoutwork);

    

    free(quearr1);
    free(quearr2);    
}
