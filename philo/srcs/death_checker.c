#include "../philo.h"

static bool all_fed_up(t_curph philosophers[], int number_of_philosophers);
static void end_simulation(t_curph philosophers[]);

void *death_checker(void *phil_void)
{
    t_curph         *philosophers;
    int             number_of_philosophers;
    int             i;
    struct timeval  now;

    philosophers = (t_curph *)phil_void;
    number_of_philosophers = philosophers->ph_struct->args[0];
    while (!all_fed_up(philosophers, number_of_philosophers))
    {
        i = 0;
        while (i < number_of_philosophers)
        {
            gettimeofday(&now, NULL);
            if (timeval_cmp(now, philosophers[i].death) >= 0)
            {
                end_simulation(philosophers);
                printf("%04ld %d died\n", generate_timestamp(philosophers), philosophers->id);
                return (NULL);
            }
            i++;
        }
    }
    end_simulation(philosophers);
    printf("End of simulation: philosophers go partying 🥳\n");
    return (NULL);
}

static bool all_fed_up(t_curph philosophers[], int number_of_philosophers)
{
    int meals_to_eat;
    int i;

    if (philosophers->ph_struct->argc < 5)
        return (false);
    meals_to_eat = philosophers->ph_struct->args[4];
    i = 0;
    while (i < number_of_philosophers)
    {
        if (philosophers[i].meals < meals_to_eat)
            return (false);
        i++;
    }
    return (true);
}

static void end_simulation(t_curph philosophers[])
{
    philosophers->ph_struct->end_of_simulation = true;
    finish_threads(philosophers);
}
