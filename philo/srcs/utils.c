#include "../philo.h"

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

void reset_death(struct timeval *tv, int time_to_die, pthread_mutex_t *death, t_curph *phil)
{
    struct timeval last_meal;
    
    //gettimeofday(&now, NULL);
    pthread_mutex_lock(&phil->mutx_last_meal);
    last_meal = phil->last_meal;
    pthread_mutex_unlock(&phil->mutx_last_meal);
    pthread_mutex_lock(death);
    tv->tv_sec = last_meal.tv_sec + time_to_die / 1000;//refactor?
    tv->tv_usec = last_meal.tv_usec + (time_to_die % 1000) * 1000;//?
    if (tv->tv_usec >= 1000000) 
    {
        tv->tv_sec++;
        tv->tv_usec -= 1000000;
    }
    pthread_mutex_unlock(death);
}

int timeval_cmp(struct timeval now, t_curph *phil)
{
    struct timeval death;

    pthread_mutex_lock(&phil->mutx_death);
    death = phil->death;
    pthread_mutex_unlock(&phil->mutx_death);
    if (now.tv_sec < death.tv_sec)
        return (-1);
    else if (now.tv_sec > death.tv_sec)
        return (1);
    if (now.tv_usec < death.tv_usec)
        return (-1);
    else if (now.tv_usec > death.tv_usec)
        return (1);
    return (0);
}