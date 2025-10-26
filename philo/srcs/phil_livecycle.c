#include "../philo.h"

void phil_take_forks(t_curph *phil);
void phil_eat(t_curph *phil);
void phil_sleep(t_curph *phil);
void phil_think(t_curph *phil);

void    *phil_live(void *phil_void)
{
    t_curph *phil;

    phil = (t_curph *)phil_void;
    while (!phil->ph_struct->args[4] || phil->meals < phil->ph_struct->args[4]) // ?: 1 or until status is dead !: dereferencing index 4!
    {
        if (phil->next_action == EAT)
        {
            phil_take_forks(phil);
            phil_eat(phil);
        }
        else if (phil->next_action == SLEEP)
            phil_sleep(phil);
        else if (phil->next_action == THINK)
            phil_think(phil);
    }
    return (NULL);
}

void phil_take_forks(t_curph *phil)
{
    pthread_mutex_lock(&phil->ph_struct->mutexes[phil->lfork]);
    printf("%d has taken a fork\n", phil->id);
    pthread_mutex_lock(&phil->ph_struct->mutexes[phil->rfork]);
}

void reset_death(struct timeval *tv, int ms)
{
    tv->tv_sec = ms / 1000;
    tv->tv_usec = (ms % 1000) * 1000;
}

void phil_eat(t_curph *phil)
{
    printf("%d is eating\n", phil->id);
    usleep(phil->ph_struct->args_us[1]);
    pthread_mutex_unlock(&phil->ph_struct->mutexes[phil->lfork]);
    pthread_mutex_unlock(&phil->ph_struct->mutexes[phil->rfork]);
    reset_death(&phil->death, phil->ph_struct->args[1]);
    (phil->meals)++;
    phil->next_action = SLEEP;
}

void phil_sleep(t_curph *phil)
{
    printf("%d is sleeping\n", phil->id);
    usleep(phil->ph_struct->args_us[2]);
    phil->next_action = THINK;
}

void phil_think(t_curph *phil)
{
    printf("%d is thinking\n", phil->id);
    phil->next_action = EAT;
}