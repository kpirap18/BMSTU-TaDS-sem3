#ifndef _APP_H_
#define _APP_H_

#define OK                     0
#define INPUT_ERR             -1
#define FILE_OPEN_ERR         -2
#define FILE_READ_ERR         -3
#define DONT_INT_NUM_CHOICE   -4
#define INV_NUM_CHOICE        -5
#define GRAPH_ERR             -6

#define GHZ 1900000000

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET    "\x1b[0m"

typedef struct
{
    int count;
    double **data;
} matrix_r;


#endif // _APP_H_
