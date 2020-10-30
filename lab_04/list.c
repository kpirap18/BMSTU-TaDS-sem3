/*! \defgroup <main> (The Main module)
  @{
  */
/**
  * \file list.c
  * \brief File with func about list
  * \version 1.0
  * \date 23.10.2020
  @}
  */

#include "list.h"

// Функция создания стека в виде списка
liststack_r *create_stack_list(const char data)
{
    liststack_r *stack = (liststack_r *)malloc(sizeof(liststack_r));

    if (!stack)
        return NULL;

    stack->data = data;
    stack->ind = 0;
    stack->next = NULL;

    return stack;
}

// Функция проверки стека в виде списка на полноту
func_var is_full_list(liststack_r *stack_list, const func_var lim)
{
    return stack_list->ind == lim;
}

// Функция проверки стека в виде стека на пустоту
func_var is_empty_list(liststack_r *stack_list)
{
    return !stack_list;
}

// Функция добавления элемента в стек
func_var push_list(liststack_r **stack_list, const char data, const func_var lim)
{
    if (is_full_list(*stack_list, lim))
        return STACK_PUSH_ERR;

    liststack_r *stack = create_stack_list(data);
    if (!stack)
        return STACK_PUSH_ERR;

    stack->ind = (*stack_list)->ind + 1;
    stack->next = *stack_list;
    *stack_list = stack;

    return OK;
}

// Функция ввода элементов в стек
func_var input_stack_list(const func_var c, liststack_r **stack_list,
                          const func_var lim, int f, FILE *ff)
{
    char elem;
    func_var i = 0;

    while (i < c)
    {
        //printf("%d\n", i);
        if (f == 0)
            if (fscanf(ff, "%c", &elem) != 1)
                return INPUT_ERR;

        if (!(*stack_list))
            *stack_list = create_stack_list(elem);
        else
        {
            if (f == 0)
            {
                if (push_list(stack_list, elem, lim))
                    return STACK_PUSH_ERR;
            }
            else
            {
                if (push_list(stack_list, 'w', lim))
                    return STACK_PUSH_ERR;
            }

        }
        i++;
    }

    return OK;
}

// Функция вывода элементов из стека
func_var output_stack_list(liststack_r *stack_list)
{
    if (is_empty_list(stack_list))
        return STACK_OUT_ERR;

    int sixe = stack_list->ind;
    liststack_r *o = stack_list;

    while (sixe >= 0)
    {
        printf("%c -- %zx\n", o->data, (size_t)(o));
        o = o->next;
        sixe--;
    }

    return OK;
}

// Функция проверки вершины стека
void check_top_list(liststack_r *stack_list, arr_r *arr)
{
    size_t t = (size_t)stack_list;

    for (func_var i = 0; i < arr->ind; i++)
    {
        if (t == arr->arr[i])
            for (func_var j = i; j < arr->ind - 1; j++)
            {
                size_t buf = arr->arr[j];
                arr->arr[j] = arr->arr[j + 1];
                arr->arr[j + 1] = buf;
            }
    }

    arr->ind--;
}

// Функция удаления элемета из стека
char pop_list(liststack_r **stack_list, arr_r *arr)
{
    if (is_empty_list(*stack_list))
        return STACK_POP_ERR;

    liststack_r *t = *stack_list;
    *stack_list = (*stack_list)->next;

    char p = t->data;

    arr->arr[++arr->ind] = (size_t)t;
    free(t);

    return p;
}

// Функция освобождения списка
func_var free_stack_list(liststack_r **stack_list, arr_r *arr)
{
    while (!is_empty_list(*stack_list))
    {
        pop_list(stack_list, arr);
    }

    return OK;
}

// Функия проверки скоок в стеке
int check_brackets_list(liststack_r *stack)
{
    char s[1000], s1[1000];
    int p = 0;
    while (stack->next != NULL)
    {
        s[p] = stack->data;
        p++;
        //printf("%c %d\n", s[p - 1], p);
        stack = stack->next;
    }
    s[p] = stack->data;
    p++;

    //printf("%s  %d", s, p);
    for (int i = 0; i < p; i++)
    {
        s1[i] = s[p - i - 1];
    }
    char one[150];
    func_var k = 0;
    int flag = 0;
    for (func_var i = 0; i < p; i++)
    {
        if (s1[i] == '(')
        {
            one[k] = 1;
            k++;
        }
        if (s1[i] == '{')
        {
            one[k] = 2;
            k++;
        }
        if (s1[i] == '[')
        {
            one[k] = 3;
            k++;
        }
        flag = 0;
        if (s1[i] == ')')
        {
            if (k == 0)
                return FALSE;
            for (func_var j = k - 1; j >= 0; j--)
            {
                if (one[j] == 1 && flag == 0)
                {
                    flag = 1;
                    for (int l = j; l < k - 1; l++)
                        one[l] = one[l + 1];
                    k--;
                    break;
                }
                else
                {
                    if (j == k - 1)
                        return FALSE;
                }
            }
        }
        flag = 0;
        if (s1[i] == '}')
        {
            if (k == 0)
                return FALSE;
            for (func_var j = k - 1; j >= 0; j--)
            {
                if (one[j] == 2 && flag == 0)
                {
                    flag = 1;
                    for (int l = j; l < k - 1; l++)
                        one[l] = one[l + 1];
                    k--;
                    break;
                }
                else
                {
                    if (j == k - 1)
                        return FALSE;
                }
            }
        }
        flag = 0;
        if (s1[i] == ']')
        {
            if (k == 0)
                return FALSE;
            for (func_var j = k - 1; j >= 0; j--)
            {
                if (one[j] == 3 && flag == 0)
                {
                    flag = 1;
                    for (int l = j; l < k - 1; l++)
                        one[l] = one[l + 1];
                    k--;
                    break;
                }
                else
                {
                    if (j == k - 1)
                        return FALSE;
                }
            }
        }
    }

    return TRUE;
}
