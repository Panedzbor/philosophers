#include "../philo.h"

static pthread_t    *thalloc(int number_of_philosophers, int **ids, int **args);
static void         init_threads(pthread_t *threads, int *ids, int num_of_philosphers);

int *parser(int argc, char *argv[], pthread_t **threads, int **ids)
{
    int *args;
    
    if (!(args = process_input(argc, argv)))
        return (NULL);
    if (!(*threads = thalloc(args[0], ids, &args)))
        return (NULL);
    init_threads(*threads, *ids, args[0]);
    return (args);
}

static pthread_t   *thalloc(int number_of_philosophers, int **ids, int **args)
{
    pthread_t   *threads;
    int         *ids_temp;

    threads = (pthread_t *)malloc(number_of_philosophers * sizeof(pthread_t));
    if (!threads)
    {
        ft_putstr_fd("Error: Memory allocation for threads failed\n", STDERR_FILENO);
        free(*args);
        return (NULL);
    }
    ids_temp = (int *)malloc(number_of_philosophers * sizeof(int));
    if (!ids_temp)
    {
        ft_putstr_fd("Error: Memory allocation for ids failed\n", STDERR_FILENO);
        free(threads);
        free(*args);
        return (NULL);
    }
    *ids = ids_temp;
    ids_temp = NULL;
    return (threads);
}

static void init_threads(pthread_t *threads, int *ids, int num_of_philosphers)
{
    int i;

    i = 0;
    while (i < num_of_philosphers)
    {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, phil_live, &ids[i]);
        pthread_join(threads[i], NULL);
        i++;
    }
}