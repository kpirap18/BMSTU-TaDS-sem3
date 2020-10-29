#ifndef DEFSTRERR_H
#define DEFSTRERR_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <locale.h>
#include <string.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET    "\x1b[0m"

#define TRUE                   1
#define FALSE                  0

#define OK                     0
#define INPUT_ERR             -1
#define FILE_OPEN_ERR         -2
#define FILE_READ_ERR         -3
#define STACK_ERR             -4
#define DONT_INT_NUM_CHOICE   -5
#define INV_NUM_CHOICE        -6
#define MATRIX_SIZE_ERR       -7
#define STACK_MEMORY_ERR      -8
#define STACK_PUSH_ERR        -9
#define STACK_POP_ERR        -10
#define STACK_OUT_ERR        -11
#define STACK_FULL_ERR       -12

#define OPEN "{[("
#define CLOSE "}])"
typedef int func_var;

typedef struct liststack
{
    char data;
    func_var ind;
    struct liststack *next;
} liststack_r;

typedef struct
{
    size_t *arr;
    func_var capacity;
    func_var ind;
} arr_r;

typedef struct
{
    func_var top;
    func_var capacity;
    char *arr;
} arrstack_r;

#endif // DEFSTRERR_H
