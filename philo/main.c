#include "philo.h"

void    *phil_live(void *phil)
{
    struct timeval now;
    struct timeval death;

    
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

void    create_threads(t_curph philosophers[], int num_of_phil)
{
    pthread_t *threads;
    int i;
    
    threads = philosophers[0].ph_struct->threads;
    i = 0;
    while (i < num_of_phil)
    {
        pthread_create(&threads[i], NULL, phil_live, (void *)&philosophers[i]);
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
    init_locks(ph_struct.mutexes, ph_struct.args[0]);
    init_ids(ph_struct.ids, ph_struct.args[0]); //? : is this needed?
    init_philosophers(philosophers, &ph_struct);
    create_threads(philosophers, ph_struct.args[0]);
    join_threads(threads, args[0]);
    
    return (0);
}
