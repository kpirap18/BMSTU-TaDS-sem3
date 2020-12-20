#include <stdio.h>
#include <stdlib.h>
#include "app.h"
#include "graph.h"
#include "io.h"

int main()
{
    setbuf(stdout, NULL);
    FILE *f_in = fopen("C:/msys64/home/Ira/tads/lab_07/in1.txt", "r");
    matrix_r *graph = malloc(sizeof(matrix_r*));
    graph->data = NULL;
    graph->count = 0;
    int command = -1;

    print_hello();
    while (command != 0)
    {
        printf_input();
        if (check_number(&command, 0, 8, 1) != OK)
        {
            printf(COLOR_RED"%s"COLOR_RESET"%s",
                   "ERROR!!!",
                   "Invalid command entered, please re-enter!!!\n");

            print_hello();
        }
        else
        {
            switch (command)
            {
                case 1:
                    printf(COLOR_GREEN
                           "Load graph from file\n"
                           COLOR_RESET);
                    free_matrix(graph->data, 0);
                    graph = NULL;
                    graph = read_matrix(f_in);
                    print_matrix(stdout, graph);
                    printf(COLOR_GREEN
                           "DONE\n"
                           COLOR_RESET);
                    break;

                case 2:
                    printf(COLOR_GREEN
                           "Enter the graph manually\n"
                           COLOR_RESET);
                    free_matrix(graph->data, 0);
                    graph = NULL;
                    printf("Input count of sity and matrix of road\n");
                    graph = read_matrix(stdin);
                    printf(COLOR_GREEN
                           "DONE\n"
                           COLOR_RESET);
                    break;
                case 3:
                    printf(COLOR_GREEN
                           "Display road matrix\n"
                           COLOR_RESET);
                    if (graph->data == NULL)
                    {
                        printf(COLOR_RED
                               "Graph is emtry, please put 1 at first!\n"
                               COLOR_RESET);
                        break;
                    }
                    printf("\nROAD MATRIX\n");
                    print_matrix(stdout, graph);
                    printf(COLOR_GREEN
                           "DONE\n"
                           COLOR_RESET);
                    break;
                case 4:
                    printf(COLOR_GREEN
                           "Draw a graph with GRAPHVIZ\n"
                           COLOR_RESET);
                    if (graph->data == NULL)
                    {
                        printf(COLOR_RED
                               "Graph is emtry, please put 1 at first!\n"
                               COLOR_RESET);
                        break;
                    }
                    show_graph(graph);
                    system("\"C:/Program Files/Graphviz/bin/dot.exe\" -Tpng out.dot > out.png");
                    system("out.png");
                    printf(COLOR_GREEN
                           "DONE\n"
                           COLOR_RESET);
                    break;
                case 5:
                    printf(COLOR_GREEN
                           "Find ways to the capital.\n"
                           COLOR_RESET);

                    if (graph->data == NULL)
                    {
                        printf(COLOR_RED
                               "Graph is emtry, please put 1 at first!\n"
                               COLOR_RESET);
                        break;
                    }
                    matrix_r *way = all_way(graph);
                    print_matrix(stdout, way);
                    int s;
                    printf("Input number of city: ");
                    if (scanf("%d", &s) != 1 || s < 0 || s > graph->count)
                    {
                        printf(COLOR_RED"%s"COLOR_RESET"%s",
                               "ERROR!!!",
                               "Invalid command entered, please re-enter!!!\n");
                        break;
                    }
                    int n = show_way(way, s);
                    if (n == 0 || n == GRAPH_ERR)
                    {
                        printf(COLOR_RED
                               "Graph is emtry! None road!!!\n"
                               COLOR_RESET);
                    }
                    else
                    {
                        system("\"C:/Program Files/Graphviz/bin/dot.exe\" -Tpng outway.dot > outway.png");
                        system("outway.png");
                    }
                    printf(COLOR_GREEN
                           "DONE\n"
                           COLOR_RESET);
                    break;
                case 6:
                    printf(COLOR_GREEN
                           "Conclusion of comparative characteristics\n"
                           COLOR_RESET);
                    timeget();

                    printf(COLOR_GREEN
                           "DONE\n"
                           COLOR_RESET);
                    break;
                case 7:
                    print_hello();
                    break;
            }
        }

    }

    return OK;
}
