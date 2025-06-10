#include "philo.h"

int main(int argc, char *argv[])
{
    pthread_t   *threads;
    int         *ids;
    int         *args;

    if (argc < 5 || argc > 6)
    {
        printf("Error: Wrong amount of arguments entered\n");
        return (0);
    }
    args = parse_args(argc, argv);
    if (!args)
        return (0);
    threads = phalloc(args[0], &ids, &args);
    if (!threads)
        return (0);
}

pthread_t   *phalloc(int number_of_philosophers, int **ids, int **args)
{
    pthread_t   *threads;
    int         *ids_temp;

    threads = (pthread_t *)malloc(number_of_philosophers * sizeof(pthread_t));
    if (!threads)
    {
        printf("Error: memory allocation for threads failed\n");
        free (*args);
        return (NULL);
    }
    ids_temp = (int *)malloc(number_of_philosophers * sizeof(int));
    if (!ids_temp)
    {
        printf("Error: memory allocation for ids failed\n");
        free (threads);
        free (*args);
        return (NULL);
    }
    *ids = ids_temp;
    ids_temp = NULL;
    return (threads);
}

int    *parse_args(int argc, char *argv[])
{
    int *args;
    int i;
    int temp;

    args = (int *)malloc((argc - 1) * sizeof(int));
    if (!args)
    {
        printf("Error during memory allocation\n");
        return (NULL);
    }
    i = 1;
    while (i <= argc)
    {
        temp = ph_atoi(argv[i]);
        if (temp < 0)
        {
            printf("Invalid input\n");
            free (args);
            return (NULL);
        }
        args[i - 1] = temp;
        i++;
    }
    return (args);
}



void    init_variables(int *v1, int *v2, int *v3, int *v4, int *v5)
{
    *v1 = 0;
    *v2 = 0;
    *v3 = 0;
    *v4 = 0;
    *v5 = 0;
}
