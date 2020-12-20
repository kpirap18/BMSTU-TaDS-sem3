#ifndef _TIMEMEMORY_H_
#define _TIMEMEMORY_H_

#include "app.h"
#include "list.h"
#include "hash.h"

int searchfile(FILE *f, int num);

void timememory1(int len);

void timememory(node_t *head, node_t *headbal, inttable_t *table, FILE *f);

#endif // _TIMEMEMORY_H_