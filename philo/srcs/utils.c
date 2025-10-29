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

void reset_death(struct timeval *tv, int time_to_die)
{
    struct timeval now;
    
    gettimeofday(&now, NULL);
    tv->tv_sec = now.tv_sec + time_to_die / 1000;
    tv->tv_usec = now.tv_usec + (time_to_die % 1000) * 1000;
    if (tv->tv_usec >= 1000000) 
    {
        tv->tv_sec++;
        tv->tv_usec -= 1000000;
    }
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