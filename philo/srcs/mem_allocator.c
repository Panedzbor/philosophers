#include "../philo.h"

static pthread_t       *alloc_threads(int number_of_philosophers, void *mem[]);
static pthread_mutex_t *alloc_mutexes(int number_of_philosophers, void *mem[]);
static int             *alloc_ids(int number_of_philosophers, void *mem[]);
static t_curph          *alloc_phils(int number_of_philosophers, void *mem[]);

t_curph *mem_allocator(int *args, t_philo ph_struct, void *mem[])
{
    pthread_t *threads;
    pthread_mutex_t *locks;
    int *ids;
    t_curph *philosophers;

    threads = ph_struct.threads;
    locks = ph_struct.mutexes;
    ids = ph_struct.ids;
    if (!(threads = alloc_threads(args[0], mem)))
        return (mem_cleaner(mem));
    if (!(locks = alloc_mutexes(args[0], mem)))
        return (mem_cleaner(mem));
    if (!(ids = alloc_ids(args[0], mem)))
        return (mem_cleaner(mem));
    if (!(philosophers = alloc_phils(args[0], mem)))
        return (mem_cleaner(mem));
    return (philosophers);
}

static pthread_t *alloc_threads(int number_of_philosophers, void *mem[])
{
    pthread_t *threads;
    
    threads = (pthread_t *)malloc(number_of_philosophers * sizeof(pthread_t));
    if (!threads)
    {
        ft_putstr_fd("Error: Memory allocation for threads failed\n", STDERR_FILENO);
        return (NULL);
    }
    mem[1] = (void *)threads;
    return (threads);
}

static pthread_mutex_t *alloc_mutexes(int number_of_philosophers, void *mem[])
{
    pthread_mutex_t *locks;

    locks = (pthread_mutex_t *)malloc(number_of_philosophers * sizeof(pthread_mutex_t));
    if (!locks)
    {
        ft_putstr_fd("Error: Memory allocation for mutexes failed\n", STDERR_FILENO);
        return (NULL);
    }
    mem[2] = (void *)locks;
    return (locks);
}

static int *alloc_ids(int number_of_philosophers, void *mem[])
{
    int *ids;
    
    ids = (int *)malloc(number_of_philosophers * sizeof(int));
    if (!ids)
    {
        ft_putstr_fd("Error: Memory allocation for ids failed\n", STDERR_FILENO);
        return (NULL);
    }
    mem[3] = (void *)ids;
    return (ids);
}

static t_curph *alloc_phils(int number_of_philosophers, void *mem[])
{
    t_curph *phils;
    
    phils = (t_curph *)malloc(number_of_philosophers * sizeof(t_curph));
    if (!phils)
    {
        ft_putstr_fd("Error: Memory allocation for philosophers failed\n", STDERR_FILENO);
        return (NULL);
    }
    mem[4] = (void *)phils;
    return (phils);
}