#include "../philo.h"

static bool         is_correct_args_num(int argc);
static int          *validate_input(int argc, char *argv[], void *mem[]);

int parser(int argc, char *argv[], void *mem[], t_philo *ph_struct)
{
    if (!is_correct_args_num(argc))
        return (0);
    if (!(ph_struct->args = validate_input(argc, argv, mem)))
        return (0);
    ph_struct->argc = argc - 1;
    ph_struct->end_of_simulation = false;
    pthread_mutex_init(&ph_struct->eos, NULL);
    pthread_mutex_inin(&ph_struct->print, NULL);
    return (1);
}

static bool is_correct_args_num(int argc)
{
    if (argc < 5 || argc > 6)
    {
        ft_putstr_fd("Error: Wrong number of arguments entered\n", STDERR_FILENO);
        return (false);
    }
    return (true);
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
            ft_putstr_fd("Invalid input: negative or non-numeric values\n", 
                STDERR_FILENO);
            mem_cleaner(mem);
            return (NULL);
        }
        args[i++ - 1] = temp;
    }
    return (args);
}

