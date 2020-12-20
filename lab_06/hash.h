#ifndef _HASH_H_
#define _HASH_H_

#include "app.h"

int hashh(int key, int len);

intt *newtabledata(int n);

inttable_t *rewritehash(inttable_t *table);

int keyintable(inttable_t *table, int key);

inttable_t *inittable(int n);

inttable_t *rerwritefunchash(inttable_t *table);

inttable_t* loadhashtable(inttable_t *table, int key, int *rc);

void tableprint(FILE *f, inttable_t *hash_table);

void freetable(inttable_t *table);

#endif // _HASH_H_