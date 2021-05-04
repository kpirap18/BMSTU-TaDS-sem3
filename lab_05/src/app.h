#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET    "\x1b[0m"

#define MAXLENQUEUE       100000
#define EPS                 1e-9
#define MAXLEN             10000
#define GHZ                  1.9
#define ITER               10000

#define TRUE                   1
#define FALSE                  0

#define OK                     0
#define INPUT_ERR             -1
#define FILE_OPEN_ERR         -2
#define FILE_READ_ERR         -3
#define DONT_INT_NUM_CHOICE   -4
#define INV_NUM_CHOICE        -5

typedef char queuetype;
typedef struct queue
{
    char name[30];      // Имя очереди
    void* low;          // Адрес нижней границы
    void* up;           // Адрес верхней границы
    void* p_in;         // Указатель на "хвост"
    void* p_out;        // Указатель на "голову"
    int count_len;      // Число элементов
    size_t size;        // Размер типа данных
    int count_req;      // Число запросов
    int sum_len;        // Средняя длина
    int tmp_len;        // Текущая длина
    int sum_time;       // Общее время
    int out_req;        // Число запросов на выход
    int in_req;         // Число запросов на вход
} queue_r;

typedef struct node
{
    char inf;
    struct node *next;
} node_r;

typedef struct times
{
    double min;
    double max;
} times_r;


#endif // APP_H
