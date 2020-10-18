int64_t tact(void)
{
    int32_t h, l;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (h), "=r" (l)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    int64_t tacks = ((int64_t)h << 32) | l;

    return tacks;
}
