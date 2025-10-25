#include "philo.h"

void *mem_cleaner(void *mem[])
{
    int i;

    i = 0;
    while (i < D_PTRS)
    {
        free(mem[i]);
        i++;
    }
    return (NULL);
}