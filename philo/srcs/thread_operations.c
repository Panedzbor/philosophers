#include "../philo.h"

void    create_threads(t_curph philosophers[], int num_of_phil)
{
    pthread_t   *thread;
    int         i;
    
    i = 0;
    while (i < num_of_phil)
    {
        thread = philosophers[i].thread;
        pthread_create(&thread, NULL, phil_live, (void *)&philosophers[i]);
        i++;
    }
    pthread_create(&philosophers->ph_struct->death_check, NULL, death_checker, (void *)philosophers);
}