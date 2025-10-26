#include "../philo.h"

void phil_take_forks(t_curph *phil);
void phil_eat(t_curph *phil);
void phil_sleep(t_curph *phil);
void phil_think(t_curph *phil);

void    *phil_live(void *phil_void)
{
    t_curph *phil;
    int meals_to_end;

    phil = (t_curph *)phil_void;
    meals_to_end = -1;
    if (phil->ph_struct->argc == 5)
        meals_to_end = phil->ph_struct->args[4];
    while ((meals_to_end < 0 || phil->meals < meals_to_end) 
            && phil->status == ALIVE)
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

long generate_timestamp(t_curph *phil)
{
    struct timeval tv;
    long dif_sec;
    long dif_us;
    long ms;

    gettimeofday(&tv, NULL);
    dif_sec = tv.tv_sec - phil->ph_struct->start.tv_sec;
    dif_us = tv.tv_usec - phil->ph_struct->start.tv_usec;
    ms = convert_sec_ms(dif_sec) + convert_us_ms(dif_us);
    return (ms); 
}

void phil_take_forks(t_curph *phil)
{
    pthread_mutex_lock(&phil->ph_struct->mutexes[phil->lfork]);
    printf("%04ld %d has taken a fork\n", generate_timestamp(phil),phil->id);
    pthread_mutex_lock(&phil->ph_struct->mutexes[phil->rfork]);
}

void reset_death(struct timeval *tv, int time_to_die)
{
    struct timeval now;
    
    gettimeofday(&now, NULL);
    tv->tv_sec = now.tv_sec + time_to_die / 1000;
    tv->tv_usec = now.tv_usec + (time_to_die % 1000) * 1000;
    if (tv->tv_usec >= 1000000) {  // Add overflow handling
        tv->tv_sec++;
        tv->tv_usec -= 1000000;
    }
}

void phil_eat(t_curph *phil)
{
    reset_death(&phil->death, phil->ph_struct->args[1]);
    printf("%04ld %d is eating\n", generate_timestamp(phil), phil->id);
    usleep(phil->ph_struct->args_us[1]);
    pthread_mutex_unlock(&phil->ph_struct->mutexes[phil->lfork]);
    pthread_mutex_unlock(&phil->ph_struct->mutexes[phil->rfork]);
    (phil->meals)++;
    phil->next_action = SLEEP;
}

void phil_sleep(t_curph *phil)
{
    printf("%04ld %d is sleeping\n", generate_timestamp(phil), phil->id);
    usleep(phil->ph_struct->args_us[2]);
    phil->next_action = THINK;
}

void phil_think(t_curph *phil)
{
    printf("%04ld %d is thinking\n", generate_timestamp(phil), phil->id);
    phil->next_action = EAT;
}