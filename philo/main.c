#include "philo.h"

int main(int argc, char *argv[])
{
    t_philo ph_struct;
    t_curph *philosophers;
    void    *mem[D_PTRS];

    gettimeofday(&ph_struct.start, NULL);
    init_mem(mem);
    if (!(parser(argc, argv, mem, &ph_struct)))
        return (1);
    if (!(philosophers = mem_allocator(ph_struct.args, &ph_struct, mem)))
        return (2);
    init_locks(ph_struct.mutexes, ph_struct.args[0]);
    init_philosophers(philosophers, &ph_struct, mem[1]);
    create_threads(philosophers, ph_struct.args[0]);
    pthread_join(ph_struct.death_check, NULL);
    destroy_mutexes(philosophers);
    mem_cleaner(mem);
    return (0);
}

//testing