#include "../philo.h"

void init_mem(void *mem[])
{
    int i;

    i = 0;
    while (i < D_PTRS)
    {
        mem[i] = NULL;
        i++;
    }
}

void    init_locks(int *forks, int number_of_philosophers)
{
    int i;

    i = 0;
    while (i < number_of_philosophers)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void    init_ids(int *ids, int number_of_philosophers)
{
    int i;

    i = 0;
    while (i < number_of_philosophers)
    {
        ids[i] = i + 1;
        i++;
    }
}

void    init_philosophers(t_curph philosophers[], t_philo *ph_struct)
{
    int number_of_philosophers;
    int i;

    number_of_philosophers = ph_struct->args[0];
    i = 0;
    while (i < number_of_philosophers)
    {
        philosophers[i].id = i + 1;
        philosophers[i].ph_struct = ph_struct;
        i++;
    }
}