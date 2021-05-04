#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define PLUS '+'
#define MINUS '-'

#define OK 0
#define MAX_LEN_NUMBER 39

// ОШИБКИ СЧИТЫВАНИЯ
#define ERROR 42
#define TRANS_ERROR 2

// ОШИБКИ ПРОВЕРКИ
#define CORRERCT_ERROR 3
#define INT 4
#define FLOAT 5

// ОШИБКИ ДЕЛЕНИЯ
#define DIV_ERROR 6

#define FALSE 0
#define TRUE 1

#define MAX_LEN_MANTISSA 32
#define MAX_LEN_POWER 7

typedef struct
{
    char mantissa[MAX_LEN_MANTISSA];
    char power[MAX_LEN_POWER];
    char sing_num;
    char sing_power;
    int power_int;
    short int point_pos;
    short int e_pos;
} number_r;

#endif // DEFINE_H
