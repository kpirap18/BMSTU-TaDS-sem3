/*! \defgroup <main> (The Main module)
  @{
  */
/**
  * \file array.c
  * \brief File with func about array
  * \version 1.0
  * \date 23.10.2020
  @}
  */

#include "array.h"

// Функция создания стека в виде массива
arrstack_r *create_stack_arr(const int capacity)
{
    arrstack_r *stack = (arrstack_r *)malloc(sizeof(arrstack_r));
    if (!stack)
        return NULL;

    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (char *)malloc(stack->capacity * sizeof(char));

    if (!stack->arr)
    {
        free(stack);
        return NULL;
    }

    return stack;
}

// Функция проверки стека в виде массива на полноту
int is_full_arr(arrstack_r *stack)
{
    return stack->top == stack->capacity - 1;
}

// Функция проверки стека в виде массива на пустоту
int is_empty_arr(arrstack_r *stack)
{
    return stack->top == -1;
}

// Функция добавления элемента в стек
int push_arr(arrstack_r *stack, const char data)
{
    if (is_full_arr(stack))
        return STACK_PUSH_ERR;

    stack->arr[++stack->top] = data;

    return OK;
}

// Функция ввода элементов в стек
int input_stack_arr(const int count, arrstack_r *stack, int f, FILE *ff)
{
    char c;

    for (int i = 0; i < count; i++)
    {
        if (f == 0)
            if (fscanf(ff, "%c", &c) != 1)
                return INPUT_ERR;

        if (f == 0)
        {
            if (push_arr(stack, c))
                return STACK_FULL_ERR;
        }
        else
        {
            if (push_arr(stack, 'w'))
                return STACK_FULL_ERR;
        }
    }

    if (f == 0 && ff == stdin)
        getchar();
    return OK;
}

// Функция вывода стека
int output_stack_arr(arrstack_r *stack)
{
    if (is_empty_arr(stack))
        return STACK_OUT_ERR;

    func_var s = stack->top;

    while (s >= 0)
    {
        printf("%c\n", stack->arr[s--]);
    }

    return OK;
}

// Функция удаления элемента из стек
char pop_arr(arrstack_r *stack)
{
    if (is_empty_arr(stack))
        return STACK_POP_ERR;

    return stack->arr[stack->top--];
}

// Функция освобождения стека
func_var free_stack_arr(arrstack_r *stack)
{
    if (stack)
    {
        if (stack->arr)
        {
            free(stack->arr);
            free(stack);

            return OK;
        }

        free(stack);

        return OK;
    }

    return STACK_MEMORY_ERR;
}

// Функция создания массива пустых адресов
arr_r *create_array(const int capacity)
{
    arr_r *array = (arr_r *)malloc(sizeof(arr_r));
    if (!array)
        return NULL;

    array->capacity = capacity;
    array->ind = -1;
    array->arr = (size_t *)malloc(sizeof(size_t));

    return array;
}

// Функция вывода массива пустых адресов
void output_array(const arr_r arr)
{
    if (arr.ind == -1)
    {
        printf("Array is empty.\n");
    }
    else
    {
        for (int i = 0; i < arr.ind + 1; i++)
            printf("%zx\n", arr.arr[i]);

        printf("\n");
    }
}

// Функция освобождения массива пустых адресов
int free_array(arr_r *arr)
{
    if (arr)
    {
        if (arr->arr)
        {
            free(arr->arr);
            free(arr);

            return OK;
        }
    free(arr);

    return OK;
    }

    return STACK_ERR;
}

// Функция проверки скобок в стеке
int check_brackets_arr(arrstack_r *arr)
{
    char one[1000];
    func_var k = 0;
    int flag = 0;
    for (func_var i = 0; i < arr->top + 1; i++)
    {
        if (arr->arr[i] == '(')
        {
            one[k] = 1;
            k++;
        }
        if (arr->arr[i] == '{')
        {
            one[k] = 2;
            k++;
        }
        if (arr->arr[i] == '[')
        {
            one[k] = 3;
            k++;
        }
        flag = 0;
        if (arr->arr[i] == ')')
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
        if (arr->arr[i] == '}')
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
        if (arr->arr[i] == ']')
        {
            if (k == 0)
                return FALSE;
            for (func_var j = k - 1; j >= 0; j--)
            {
                if (one[j] == 3 && flag == 0)
                {
                    flag = 1;
                    for (int l = j; l <= k - 1; l++)
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
