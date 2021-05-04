#include "graph.h"
#include "io.h"
#include <stdlib.h>
#include <stdint.h>

matrix_r *create_matrix(int count)
{
    matrix_r *matrix = malloc(sizeof(matrix_r));
    if (matrix)
    {
        matrix->count = count;
        matrix->data = allocate_matrix(count);
        if (matrix->data == NULL)
        {
            free(matrix);
            matrix = NULL;
        }
    }

    return matrix;
}
double **allocate_matrix(int count)
{
    double **data = calloc(count, sizeof(double*));
    if (data)
    {
        for (int i = 0; i < count; ++i)
        {
            data[i] = calloc(count, sizeof(double));
            if (!data[i])
            {
                free_matrix(data, count);
                data = NULL;
            }
        }
    }

    return data;
}

void free_matrix(double **data, int count)
{
    for (int i = 0; i < count; ++i)
    {
        free(data[i]);
    }

    free(data);
}

matrix_r *copy_matrix(const matrix_r *from)
{
    if (from == NULL)
    {
        printf("Graph is NULL\n");
        return NULL;
    }
    matrix_r *to = create_matrix(from->count);

    to->count = from->count;

    for (int i = 0; i < from->count; ++i)
    {
        for (int j = 0; j < from->count; ++j)
        {
            to->data[i][j] =  from->data[i][j];
        }
    }

    return to;
}

matrix_r *all_way(const matrix_r *graph)
{
    matrix_r *way = copy_matrix(graph);
    if (way == NULL)
    {
        printf("Graph is NULL\n");
        return NULL;
    }

    for (int i = 0; i < graph->count; ++i)
    {
        for (int j = 0; j < graph->count; ++j)
        {
            for (int k = 0; k < graph->count; ++k)
            {
                if (j != k)
                {
                    printf("%lf %lf %lf %lf\n",way->data[j][i], way->data[i][k],way->data[j][i] + way->data[i][k],way->data[j][k]);
                    if (((way->data[j][i] + way->data[i][k]) < way->data[j][k]) && way->data[j][i] != 0)
                    {
                        way->data[j][k] = way->data[j][i] + way->data[i][k];
                    }
                    else
                    {
                        way->data[j][k] = way->data[j][k];
                    }
                }
                else
                {
                    way->data[j][k] = 0.0;
                }
                //print_matrix(stdout, way);
                //printf("\n\n");
            }
        }
    }
    // print_matrix(stdout, way);
    return way;
}

int64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void timeget()
{
    FILE *f1 = fopen("C:/msys64/home/Ira/tads/lab_07/in_5.txt", "r");
    if (f1)
    {
        FILE *f2 = fopen("C:/msys64/home/Ira/tads/lab_07/in_10.txt", "r");
        if (f2)
        {
            FILE *f3 = fopen("C:/msys64/home/Ira/tads/lab_07/in_15.txt", "r");
            if (f3)
            {
                FILE *f4 = fopen("C:/msys64/home/Ira/tads/lab_07/in_20.txt", "r");
                if (f4)
                {
                    matrix_r *g1 = read_matrix(f1);
                    matrix_r *g2 = read_matrix(f2);
                    matrix_r *g3 = read_matrix(f3);
                    matrix_r *g4 = read_matrix(f4);

                    int64_t s, e;

                    s = tick();
                    all_way(g1);
                    e = tick();

                    printf("| COUNT |   TICK   |   TIME   |  MEMORY  |\n");
                    printf("| %5d |  %6d  | %.6lf |  %7lld |\n", 5, (int)(e - s),
                           (double)(e - s)/GHZ,
                           sizeof(double)*g1->count + sizeof(matrix_r*));

                    s = tick();
                    all_way(g2);
                    e = tick();

                    printf("| %5d |  %6d  | %.6lf |  %7lld |\n", 10, (int)(e - s),
                           (double)(e - s)/GHZ,
                           sizeof(double)*g2->count + sizeof(matrix_r*));

                    s = tick();
                    all_way(g3);
                    e = tick();

                    printf("| %5d |  %6d  | %.6lf |  %7lld |\n", 15, (int)(e - s),
                           (double)(e - s)/GHZ,
                           sizeof(double)*g3->count + sizeof(matrix_r*));

                    s = tick();
                    all_way(g4);
                    e = tick();

                    printf("| %5d |  %6d  | %.6lf |  %7lld |\n", 20, (int)(e - s),
                           (double)(e - s)/GHZ,
                           sizeof(double)*g4->count + sizeof(matrix_r*));


                    fclose(f4);
                }
                fclose(f3);
            }
            fclose(f2);
        }
        fclose(f1);
    }

}

int factor(int n)
{
  return (n < 2) ? 1 : n * factor(n - 1);
}

void find(matrix_r *a)
{
    printf("Point: ");
    int p;
    scanf("%d", &p);

    printf("T: ");
    double t;
    scanf("%lf", &t);

    int c = 0;
    for (int i = 0; i < a->count; ++i)
    {
        if (i != p && a->data[p][i] == 0)
        {
            c++;
        }
    }

    if (c < 3)
    {
        printf("Ytn 3 gentq\n");
        return;
    }

    //int n = (factor(c)/(factor(3) * factor(c - 3)));


}
