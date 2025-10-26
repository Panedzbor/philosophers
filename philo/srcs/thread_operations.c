#include "../philo.h"

void    create_threads(t_curph philosophers[], int num_of_phil)
{
    pthread_t *threads;
    int i;
    
    threads = philosophers->ph_struct->threads;
    i = 0;
    while (i < num_of_phil)
    {
        pthread_create(&threads[i], NULL, phil_live, (void *)&philosophers[i]);
        i++;
    }
    pthread_create(&philosophers->ph_struct->death_check, NULL, death_checker, (void *)philosophers);
}

void    join_threads(t_philo ph_struct, int num_of_phil)
{
    int i;

    i = 0;
    while (i < num_of_phil)
    {
        pthread_join(ph_struct.threads[i], NULL);
        i++;
    }
    pthread_join(ph_struct.death_check, NULL);
}