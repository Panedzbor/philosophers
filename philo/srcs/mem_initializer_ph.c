#include "../philo.h"

//static t_action define_start_action(int id);
static void     define_forks(t_curph *philosopher, int number_of_philosophers);
static void     define_death_time(t_curph *philosopher);

void    init_philosophers(t_curph philosophers[], t_philo *ph_struct, void *threads)
{
    int number_of_philosophers;
    int i;

    number_of_philosophers = ph_struct->args[0];
    i = 0;
    while (i < number_of_philosophers)
    {
        philosophers[i].id = i + 1;
        philosophers[i].meals = 0;
        philosophers[i].thread = &((pthread_t *)threads)[i];
        philosophers[i].next_action = EAT;
        philosophers[i].ph_struct = ph_struct;
        //philosophers[i].status = ALIVE;
        define_forks(&philosophers[i], number_of_philosophers);
        define_death_time(&philosophers[i]);
        pthread_mutex_init(&philosophers[i].ph_mutex, NULL);
        i++;
    }
}

/* static t_action define_start_action(int id)
{
    if (id % 2 == 0)
        return (EAT);
    return (SLEEP);
} */

static void define_forks(t_curph *philosopher, int number_of_philosophers)
{
    philosopher->rfork = philosopher->id - 1;
    philosopher->lfork = philosopher->id;
    if (philosopher->id == number_of_philosophers)
        philosopher->lfork = 0;
}

static void define_death_time(t_curph *philosopher)
{
    int time_to_die;

    time_to_die = philosopher->ph_struct->args[1];
    reset_death(&philosopher->death, time_to_die);
}