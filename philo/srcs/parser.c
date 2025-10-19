#include "../philo.h"

static bool         is_correct_args_num(int argc);
static int          *validate_input(int argc, char *argv[]);
static pthread_t    *thalloc(int number_of_philosophers, int **ids, int **args);

int *parser(int argc, char *argv[], pthread_t **threads, int **ids)
{
    int *args;
    
    if (!is_correct_args_num(argc))
        return (NULL);
    if (!(args = validate_input(argc, argv)))
        return (NULL);
    if (!(*threads = thalloc(args[0], ids, &args)))
        return (NULL);
    return (args);
}

static bool is_correct_args_num(int argc)
{
    if (argc < 5 || argc > 6)
    {
        ft_putstr_fd("Error: Wrong number of arguments entered\n", STDERR_FILENO);
        return (0);
    }
    return (1);
}

static int    *validate_input(int argc, char *argv[])
{
    int *args;
    int i;
    int temp;

    args = (int *)malloc((argc - 1) * sizeof(int));
    if (!args)
    {
        ft_putstr_fd("Error during memory allocation\n", STDERR_FILENO);
        return (NULL);
    }
    i = 1;
    while (i < argc)
    {
        temp = ph_atoi(argv[i]);
        if (temp < 0)
        {
            ft_putstr_fd("Invalid input: negative values\n", STDERR_FILENO);
            free(args);
            return (NULL);
        }
        args[i - 1] = temp;
        i++;
    }
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

