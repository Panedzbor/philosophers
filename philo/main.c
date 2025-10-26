#include "philo.h"

void    join_threads(t_philo ph_struct, int num_of_phil)
{
    int i;

    i = 0;
    while (i < num_of_phil)
    {
        pthread_join(ph_struct.threads[i], NULL);
        i++;
    }
    pthread_join(ph_struct.death_check, NULL);
}

void    create_threads(t_curph philosophers[], int num_of_phil)
{
    pthread_t *threads;
    int i;
    
    threads = philosophers->ph_struct->threads;
    i = 0;
    while (i < num_of_phil)
    {
        pthread_create(&threads[i], NULL, phil_live, (void *)&philosophers[i]);
        i++;
    }
    pthread_create(&philosophers->ph_struct->death_check, NULL, death_checker, (void *)philosophers);
}

int main(int argc, char *argv[])
{
    t_philo ph_struct;
    t_curph *philosophers;
    void *mem[D_PTRS];

    gettimeofday(&ph_struct.start, NULL);
    init_mem(mem);
    if (!(ph_struct.args = parser(argc, argv, mem)))
        return (1);
    convert_args_us(&ph_struct);
    if (!(philosophers = mem_allocator(ph_struct.args, &ph_struct, mem)))
        return (2);
    init_locks(ph_struct.mutexes, ph_struct.args[0]);
    init_ids(ph_struct.ids, ph_struct.args[0]); //? : is this needed?
    init_philosophers(philosophers, &ph_struct);
    create_threads(philosophers, ph_struct.args[0]);
    join_threads(ph_struct, ph_struct.args[0]);
    printf("finish\n");
    return (0);
}
