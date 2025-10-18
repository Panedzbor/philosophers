#include "../philo.h"

bool        is_correct_args_num(int argc, char *argv[]);
static int  *validate_input(int argc, char *argv[]);

int    *process_input(int argc, char *argv[])
{
    int *args;
    
    if (!is_correct_args_num(argc, argv))
        return (NULL);
    if (!(args = validate_input(argc, argv)))
        return (NULL);
    return (args);
}

bool is_correct_args_num(int argc, char *argv[])
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
            ft_outstr_fd("Invalid input: negative values\n", STDERR_FILENO);
            free(args);
            return (NULL);
        }
        args[i - 1] = temp;
        i++;
    }
    return (args);
}