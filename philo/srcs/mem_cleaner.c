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

void destroy_mutexes(t_curph *phil)
{
    int i;

    i = 0;
    while (i < phil->ph_struct->args[0])
    {
        pthread_mutex_destroy(&phil->ph_struct->mutexes[i]);
        i++;
    }
}