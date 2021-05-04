#ifndef ARRAY_H
#define ARRAY_H

#include"app.h"
#include "timemem.h"

void sd_array(int n, int interval, times_r t1, 
              times_r t2, times_r t3, times_r t4);//, int flag);
void queuearray_push(queue_r *queue, char c_elem);//,char *elem, )
char queuearray_pop(queue_r *gueue);//, char *elem);
void queuearray_print(queue_r *queue);//, char *elem);

#endif // ARRAY_H
