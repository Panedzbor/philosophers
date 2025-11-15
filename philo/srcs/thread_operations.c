#include "../philo.h"

void    create_threads(t_curph philosophers[], int num_of_phil)
{
    pthread_t   *thread;
    int         i;

    i = 0;
    while (i < num_of_phil)
    {
        thread = philosophers[i].thread;
        pthread_create(thread, NULL, phil_live, (void *)&philosophers[i]);
        i++;
    }
}

void finish_threads(t_curph phil[])
{
    int i;
    int number_of_philosophers;

    i = 0;
    number_of_philosophers = phil->ph_struct->args[0];
    while (i < number_of_philosophers)
    {
        pthread_join(*phil[i].thread, NULL);
        i++;
    }
}
