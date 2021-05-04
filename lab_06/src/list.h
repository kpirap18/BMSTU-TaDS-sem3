#ifndef _LIST_H_
#define _LIST_H_

#include "app.h"

node_t *createnode(int data, int height);

node_t *find(node_t *head, int key);

node_t *insert(node_t *head, node_t *node, int *rc);

int whatheight(node_t *head);

void newheight(node_t *head);

int factorlr(node_t *head);

node_t *returnright(node_t *head);

node_t *returnleft(node_t *head);

node_t *balancenode(node_t *head);

node_t *insertbalance(node_t *head, node_t *node, int *rc);

void printtree(node_t *head, int down, int lr);

void freetree(node_t *head);

void exporttodot(FILE *f, node_t *head);

void todot(node_t *head, void *p);

void apply_pre(node_t *head, void (*f)(node_t *, void *), void *arg);

void apply_po(node_t *head, void (*f)(node_t *, void *), void *arg);

#endif // _LIST_H_