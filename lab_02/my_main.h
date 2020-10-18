#ifndef MY_MAIN_H
#define MY_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

#define NAME_FILE "flat.txt"

#define OK 0
#define ERROR 1
#define INV_NUMBER_CHOICE 2
#define DONT_INT_NUM_CHOICE 3
#define FILE_ERROR 4
#define ERROR_READ_FILE 5
#define EMPTY_TABLE 6
#define ERROR_INPUT 7
#define ERROR_FIND 8
#define ERROR_MAX_ARRAY 9

#define MAX_LEN_STRING 100
#define SIZE_FILE 500
#define MAX_SIZE 100

#define MIN_NUM_HOME 1
#define MAX_NUM_HOME 999

#define MIN_ARRR 1
#define MAX_ARRR 999

#define MIN_YEAR 1930
#define MAX_YEAR 2020

#define MIN_OWNER 1
#define MAX_OWNER 15

#define MIN_TEN 1
#define MAX_TEN 15

#define MAX_ROOM 20
#define MIN_ROOM 1

#define MAX_PRICE 1000000
#define MIN_PRICE 1

#define MAX_ARRAY 100
#define GNZ 1990000000

typedef short int func_var;

typedef enum BOOLEAN{false = 0, true = 1} boolean;

typedef struct primary
{
    boolean decoration;
}primary_r;

typedef struct secondary
{
       func_var build_time;
       func_var previous_own_count;
       func_var last_tenants_count;
       boolean animals;
} secondary_r;

typedef union prim_sec
{
    primary_r primary;
    secondary_r second;
} prim_sec_r;

typedef struct keys
{
    func_var room;
    func_var id;
} key_r;

typedef struct appartment
{
    char address[110];
    func_var arrr;
    func_var room;
    int square;
    boolean is_prim_sec;
    prim_sec_r flat;
} appartment_r;

typedef struct table
{
    appartment_r appar[500];
    key_r key[500];
    func_var size;
    func_var size_max;
} table_r;

#endif // MY_MAIN_H
