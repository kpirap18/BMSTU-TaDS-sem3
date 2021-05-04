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
#define MULTI_ERR             -4
#define DONT_INT_NUM_CHOICE   -5
#define INV_NUM_CHOICE        -6
#define MATRIX_SIZE_ERR       -7

#define COUNT_SIZE             5
#define MAX_MATRIX_SIZE      150
#define MAX_MATRIX_ELEMS   22500

#define GNZ 1990000000

typedef int func_var;
typedef struct
{
    func_var rows;
    func_var columns;
    func_var data[MAX_MATRIX_SIZE][1];
} vector_std_r;

typedef struct
{
    func_var rows;
    func_var columns;
    func_var data[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
} matrix_std_r;

typedef struct list_elem
{
    func_var index;
    struct list_elem *next;
} list_elem;

// матрица в разреженном виде
typedef struct
{
    func_var rows;
    func_var columns;
    func_var quan;
    func_var value[MAX_MATRIX_ELEMS]; // AN
    func_var row[MAX_MATRIX_ELEMS]; // JA
    list_elem pointer[MAX_MATRIX_SIZE + 1]; // IA
} matrix_r;

#endif // DEFSTRERR_H
