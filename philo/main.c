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
    
}

int    *parse_args(int argc, char *argv[])
{
    int *args;
    int i;

    args = (int *)malloc((argc - 1) * sizeof(int));
    if (!args)
    {
        printf("Error during memory allocation\n");
        return (NULL);
    }
    i = 1;
    while (i <= argc)
    {
        args[i - 1] = ft_atoi(argv[i]);
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
