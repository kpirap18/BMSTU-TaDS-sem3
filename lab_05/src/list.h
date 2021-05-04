#ifndef LIST_H
#define LIST_H

#include "app.h"
#include "timemem.h"
#include "io.h"

node_r* createelem(queuetype c);
node_r* pushfront(node_r *head, node_r *elem);
node_r* popfront(node_r **head);
node_r* popend(node_r **head);
void freeall(node_r *head);

void sd_list(int n, int interval, times_r t1, 
              times_r t2, times_r t3, times_r t4, int flag);
node_r *queuelist_push(node_r *queue, queuetype c, node_r **user_memory,
                    int *user_count, node_r **free_memory,
                    int *free_count, int *second_use);
node_r *queuelist_pop(node_r **queue);
void queuelist_print(node_r *queue);

#endif // LIST_H
