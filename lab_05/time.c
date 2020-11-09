#include "time.h"

double getime(times_r t)
{
    return (t.max - t.min) * (double)(rand()) / (double)RAND_MAX + t.min;
}
