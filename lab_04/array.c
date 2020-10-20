#include "array.h"

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

int is_full_arr(arrstack_r *stack)
{
    return stack->top == stack->capacity - 1;
}

int is_empty_arr(arrstack_r *stack)
{
    return stack->top == -1;
}

int push_arr(arrstack_r *stack, const char data)
{
    if (is_full_arr(stack))
        return STACK_PUSH_ERR;

    stack->arr[++stack->top] = data;

    return OK;
}

int input_stack_arr(const int count, arrstack_r *stack)
{
    char c;

    for (int i = 0; i < count; i++)
    {
        if (scanf("%c", &c) != 1)
            return INPUT_ERR;

        if (push_arr(stack, c))
            return STACK_FULL_ERR;
    }

    getchar();
    return OK;
}

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

char pop_arr(arrstack_r *stack)
{
    if (is_empty_arr(stack))
        return STACK_POP_ERR;

    return stack->arr[stack->top--];
}

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
