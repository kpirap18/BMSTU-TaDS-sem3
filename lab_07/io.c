#include "io.h"
#include "graph.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define INFINIT 4000

void print_hello()
{
    printf(COLOR_BLUE"%s" COLOR_RESET "%s",
           "\n\nMENU (select one item, enter a number):\n\n",
           "Operations with array:\n"
           "1  - Load graph from file\n"
           "2  - Enter the graph manually\n"
           "3  - Display road matrix\n"
           "4  - Draw a graph with GRAPHVIZ\n"
           "5  - Find ways to the capital.\n"
           "6  - Conclusion of comparative characteristics\n\n"

           "0  - Program exit.\n"
           );
}

void printf_input()
{
    printf(COLOR_BLUE"%s"COLOR_RESET"%s","\n\nFor help input 7", "\nINPUT YOUR CHOICE: ");
}

int check_number(int *const number, const int l, const int r, int flag)
{
    char num[10];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return DONT_INT_NUM_CHOICE;
    num[strlen(num) - 1] = '\0';
    *number = (int)atoi(num);

    if (flag && (*number < l || *number > r))
    {
        //clean_my();
        return INV_NUM_CHOICE;
    }

    return OK;
}

matrix_r *read_matrix(FILE *f)
{
    int count;

    if (fscanf(f, "%d", &count) != 1)
    {
        return NULL;
    }

    matrix_r *matrix = create_matrix(count);
    double num;

    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < count; ++j)
        {
            if (fscanf(f, "%lf", &num) != 1)
            {
                return NULL;
            }
            matrix->data[i][j] = num;
        }
    }

    return matrix;
}

void print_matrix(FILE *f, matrix_r *graph)
{
    if (graph == NULL)
    {
        printf("Graph is NULL\n");
        return;
    }

    for (int i = 0; i < graph->count; ++i)
    {
        for (int j = 0; j < graph->count; ++j)
        {
            fprintf(f, "%6.2lf ", graph->data[i][j]);
        }
        fprintf(f, "\n");
    }
}

void show_graph(const matrix_r *graph)
{
    FILE *f_out = fopen("out.dot", "w");

    if (graph == NULL)
    {
        printf("Graph is NULL\n");
        return;
    }

    fprintf(f_out, "digraph MY_LAB_07 {\n");

    for (int i = 0; i < graph->count; ++i)
    {
        for (int j = 0; j < graph->count; ++j)
        {
            if (graph->data[i][j] < INFINIT && graph->data[i][j] != 0)
            {
                fprintf(f_out, "%d -> %d [label=\"%.1f km\"];\n", i, j, graph->data[i][j]);
            }
        }
    }
    fprintf(f_out, "}\n");
    fclose(f_out);
}

int show_way(const matrix_r *way, int s)
{
    int n = 0;
    FILE *f_out = fopen("outway.dot", "w");
    double t;

    if (way == NULL)
    {
        printf("Graph is NULL\n");
        return GRAPH_ERR;
    }

    printf("Input the shortest distance (double): ");
    if (scanf("%lf", &t) != 0 && t < 0)
    {
        printf("Input negative number\n");
        return GRAPH_ERR;
    }

    fprintf(f_out, "digraph MY_LAB_07 {\n");
    for (int i = 0; i < way->count; ++i)
    {
        for (int j = 0; j < way->count; ++j)
        {
            if ((i == s || j == s) && way->data[i][j] > t)
            {
                n++;
                fprintf(f_out, "%d -> %d [label=\"%.1f km\"];\n", i, j, way->data[i][j]);
            }
        }
    }

    fprintf(f_out, "}\n");
    fclose(f_out);

    return n;
}
