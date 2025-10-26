#include "philo.h"

int main(int argc, char *argv[])
{
    t_philo ph_struct;
    t_curph *philosophers;
    void *mem[D_PTRS];

    gettimeofday(&ph_struct.start, NULL);
    init_mem(mem);
    if (!(parser(argc, argv, mem, &ph_struct)))
        return (1);
    convert_args_us(&ph_struct);
    if (!(philosophers = mem_allocator(ph_struct.args, &ph_struct, mem)))
        return (2);
    init_locks(ph_struct.mutexes, ph_struct.args[0]);
    //init_ids(ph_struct.ids, ph_struct.args[0]); //? : is this needed?
    init_philosophers(philosophers, &ph_struct);
    create_threads(philosophers, ph_struct.args[0]);
    join_threads(ph_struct, ph_struct.args[0]);
    printf("finish\n");
    return (0);
}
