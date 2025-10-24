#include "philo.h"

void    *phil_live(void *id)
{
    
    return (NULL);
}

void    join_threads(pthread_t *threads, int num_of_phil)
{
    int i;

    i = 0;
    while (i < num_of_phil)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}

void    create_threads(void *arrs[], int num_of_phil)
{
    pthread_t *threads;
    int i;
    
    threads = (pthread_t *)arrs[0];
    i = 0;
    while (i < num_of_phil)
    {
        pthread_create(&threads[i], NULL, phil_live, &ids[i]);
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

int main(int argc, char *argv[])
{
    t_philo ph_struct;
    t_curph *philosophers;
    void *mem[D_PTRS];

    init_mem(mem);
    if (!(ph_struct.args = parser(argc, argv, mem)))
        return (1);
    if (!(philosophers = mem_allocator(ph_struct.args, ph_struct, mem)))
        return (2);
    init_locks(forks, args[0]);
    init_ids(ids, args[0]);
    create_threads(arrs, args[0]);
    join_threads(threads, args[0]);
    
    return (0);
}