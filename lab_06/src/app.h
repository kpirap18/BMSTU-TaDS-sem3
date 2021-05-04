#ifndef _APP_H_
#define _APP_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define LIMIT 10
#define SIZEST 10

#define OK 0
#define INPUTERROR -1
#define OPENERROR  -2

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET    "\x1b[0m"

typedef struct node
{
	int data;
	unsigned char height;
    struct node* left;
	struct node* right;
} node_t;

typedef struct
{
	int flag;
	int value;
} intt;

typedef struct 
{
	intt *data;
	int limit;
	int arrsize;
	int sizeall;
} inttable_t;


#endif // _APP_H_