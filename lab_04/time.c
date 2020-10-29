/*! \defgroup <main> (The Main module)
  @{
  */
/**
  * \file time.c
  * \brief File with the time code
  * \version 1.0
  * \date 23.10.2020
  @}
  */

#include "time.h"

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


/*!
 * \brief time_output - Comparison of stack.
 * \param *arr, *list - A pointer to a stack.
 */
void time_output(arrstack_r *arr, liststack_r *list, func_var max_)
{
    FILE *f = fopen("C:/msys64/home/Ira/tads/lab_04/in.txt", "r");
    int64_t s1, e1, s2, e2;

    arr = create_stack_arr(max_);
    input_stack_arr(max_, arr, 0, f);
    input_stack_list(max_, &list, max_, 0, f);
    s1 = tick();
    input_stack_arr(1, arr, 1, stdin);
    e1 = tick();

    s2 = tick();
    input_stack_list(1, &list, max_, 1, stdin);
    e2 = tick();

    printf("   Command: PUSH\n");
    printf("   what |   memory |     time |\n");
    printf("  array | %8d | %8d |\n",
           (sizeof(int)) * arr->capacity + sizeof(char *), (int)(e1 - s1));
    printf("   list | %8d | %8d |\n\n\n",
           (sizeof(char) + sizeof(int) + sizeof(liststack_r *)) * arr->capacity, (int)(e2 - s2));

    s1 = tick();
    pop_arr(arr);
    e1 = tick();

    arr_r *darr = create_array(max_ * max_);
    s2 = tick();
    pop_list(&list, darr);
    e2 = tick();

    printf("   Command: POP\n");
    printf("   what |   memory |     time |\n");
    printf("  array | %8d | %8d |\n",
           (sizeof(int)) * arr->capacity + sizeof(char *), (int)(e1 - s1));
    printf("   list | %8d | %8d |\n\n\n",
           (sizeof(char) + sizeof(int) + sizeof(liststack_r *)) * arr->capacity, (int)(e2 - s2));

    s1 = tick();
    check_brackets_arr(arr);
    e1 = tick();

    s2 = tick();
    check_brackets_list(list);
    e2 = tick();

    printf("   Command: CHECK\n");
    printf("   what |   memory |     time |\n");
    printf("  array | %8d | %8d |\n",
           (sizeof(int)) * arr->capacity + sizeof(char *), (int)(e1 - s1));
    printf("   list | %8d | %8d |\n\n\n",
           (sizeof(char) + sizeof(int) + sizeof(liststack_r *)) * arr->capacity, (int)(e1 - s1) * 3);
    fclose(f);
}
