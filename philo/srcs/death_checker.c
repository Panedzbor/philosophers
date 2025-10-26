#include "../philo.h"

void detach_threads(pthread_t *threads, int number_of_philosophers)
{
    int i;
    
    i = 0;
    while (i < number_of_philosophers)
    {
        pthread_detach(threads[i]);
        i++;
    }
}

bool all_fed_up(t_curph philosophers[], int number_of_philosophers)
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

int timeval_cmp(struct timeval tv1, struct timeval tv2)
{
    if (tv1.tv_sec < tv2.tv_sec)
        return (-1);
    else if (tv1.tv_sec > tv2.tv_sec)
        return (1);
    if (tv1.tv_usec < tv2.tv_usec)
        return (-1);
    else if (tv1.tv_usec > tv2.tv_usec)
        return (1);
    return (0);
}

void *death_checker(void *phil_void)
{
    t_curph *philosophers;
    int number_of_philosophers;
    int i;
    struct timeval now;

    philosophers = (t_curph *)phil_void;
    number_of_philosophers = philosophers->ph_struct->args[0];
    while (!all_fed_up(philosophers, number_of_philosophers))
    {
        i = 0;
        while (i < number_of_philosophers)
        {
            gettimeofday(&now, NULL);
            if (timeval_cmp(now, philosophers->death) >= 0)
            {
                philosophers[i].status = DEAD;
                detach_threads(philosophers->ph_struct->threads, number_of_philosophers);
                return (NULL);
            }
            i++;
        }
    }
    return (NULL);
}
