#include "../philo.h"

/* bool check_death(t_curph *philosophers)
{

} */

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

void *death_checker(void *phil_void)
{
    t_curph *philosophers;
    int number_of_philosophers;
    int i;
    struct timeval now;

    philosophers = (t_curph *)phil_void;
    number_of_philosophers = philosophers->ph_struct->args[0];
    while (true) //game not finished
    {
        i = 0;
        while (i < number_of_philosophers)
        {
            gettimeofday(&now, NULL);
            if (now.tv_sec < philosophers[i].death.tv_sec || (now.tv_sec == philosophers[i].death.tv_sec 
                && now.tv_usec < philosophers[i].death.tv_usec))
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
