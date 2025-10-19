#include "philo.h"

void    *phil_live(void *id)
{
    //(void)id;
    if (*(int *)id == 1)
        printf("let's eat\n");
    else
        printf("let's sleep\n");
    return (NULL);
}

void    join_threads(pthread_t *threads, int num_of_phil)
{
    int i;

    i = 0;
    while (i < num_of_phil)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}

void    create_threads(pthread_t *threads, int *ids, int num_of_phil)
{
    int i;

    i = 0;
    while (i < num_of_phil)
    {
        pthread_create(&threads[i], NULL, phil_live, &ids[i]);
        i++;
    }
}



void    create_ids(int *ids, int number_of_philosophers)
{
    int i;

    i = 0;
    while (i < number_of_philosophers)
    {
        ids[i] = i + 1;
        i++;
    }
}

/* static void init_threads(pthread_t *threads, int *ids, int num_of_philosphers)
{
    int i;

    i = 0;
    while (i < num_of_philosphers)
    {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, phil_live, &ids[i]);
        pthread_join(threads[i], NULL);
        i++;
    }
} */



/* void    init_variables(int *v1, int *v2, int *v3, int *v4, int *v5)
{
    *v1 = 0;
    *v2 = 0;
    *v3 = 0;
    *v4 = 0;
    *v5 = 0;
} */


int main(int argc, char *argv[])
{
    pthread_t   *threads;
    int         *ids;
    int         *args;

    if (!(args = parser(argc, argv, &threads, &ids)))
        return (1);
    create_ids(ids, args[0]);
    create_threads(threads, ids, args[0]);
    join_threads(threads, args[0]);
    return (0);
}