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

void    init_locks(pthread_mutex_t *forks, int number_of_philosophers)
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

t_action define_start_action(int id)
{
    if (id % 2 == 0)
        return (EAT);
    return (SLEEP);
}

void define_forks(t_curph *philosopher, int number_of_philosophers)
{
    philosopher->rfork = philosopher->id - 1;
    philosopher->lfork = philosopher->id;
    if (philosopher->id == number_of_philosophers)
        philosopher->lfork = 0;
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
        define_forks(&philosophers[i], number_of_philosophers);
        philosophers[i].next_action = define_start_action(i + 1);
        philosophers[i].ph_struct = ph_struct;
        i++;
    }
}