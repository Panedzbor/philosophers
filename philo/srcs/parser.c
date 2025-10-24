#include "../philo.h"

static bool         is_correct_args_num(int argc);
static int          *validate_input(int argc, char *argv[], void *mem[]);

int *parser(int argc, char *argv[], void *mem[])
{
    int *args;
    
    if (!is_correct_args_num(argc))
        return (NULL);
    if (!(args = validate_input(argc, argv, mem)))
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

static int    *validate_input(int argc, char *argv[], void *mem[])
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
    mem[0] = args;
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

