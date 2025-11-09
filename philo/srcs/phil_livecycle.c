#include "../philo.h"

static bool phil_take_forks(t_curph *phil);
static bool phil_eat(t_curph *phil);
static bool phil_sleep(t_curph *phil);
static bool phil_think(t_curph *phil);

void ph_sleep(long ms)
{
    const long slice_ms = 1;
    long slice_us = convert_ms_us(slice_ms);
    struct timeval start;
    struct timeval now;
    gettimeofday(&start, NULL);
    now = start;
    long diff;
    while ((diff = convert_timeval_ms(now) - convert_timeval_ms(start)) < ms)
    {
        usleep(slice_us);
        gettimeofday(&now, NULL);
    }
}

void    *phil_live(void *phil_void)
{
    t_curph *phil;
    int     meals_to_end;
    //bool dead;

    phil = (t_curph *)phil_void;
    meals_to_end = -1;
    if (phil->ph_struct->argc == 5)
        meals_to_end = phil->ph_struct->args[4];
    if (phil->id % 2 == 0)
        usleep(convert_ms_us(phil->ph_struct->args[2]/2));//refactor
    while ((meals_to_end < 0 || get_meals(phil) < meals_to_end) 
            && get_eos(phil->ph_struct) == false)
    {
        phil_take_forks(phil);
        if (!get_eos(phil->ph_struct))
            phil_eat(phil);
        if (!get_eos(phil->ph_struct))
            phil_sleep(phil);
        if (!get_eos(phil->ph_struct))
            phil_think(phil);
    }
    return (NULL);
}

static bool death_check(struct timeval tv, t_curph *phil)
{
    struct timeval death;

    pthread_mutex_lock(&phil->mutx_death);
    death = phil->death;
    pthread_mutex_unlock(&phil->mutx_death);
    long long now = convert_timeval_ms(tv);
    long long d = convert_timeval_ms(death);
    /* if (tv.tv_sec < death.tv_sec)
        return (true);
    else if (tv.tv_sec > death.tv_sec)
        return (false);
    if (tv.tv_usec < death.tv_usec)
        return (true);
    else if (tv.tv_usec > death.tv_usec)
        return (false); */
    if (now > d)
        return (false);
    return (true);
}

static bool phil_take_forks(t_curph *phil)//refactor
{
    int number_of_philosophers;
    int time_to_die;
    struct timeval now;
    
    number_of_philosophers = phil->ph_struct->args[0];
    time_to_die = phil->ph_struct->args[1];
    pthread_mutex_lock(&phil->ph_struct->forks[phil->rfork]);
    gettimeofday(&now, NULL);
    if (death_check(now, phil))
        mutex_print(now, FORK, phil);
    else
    {
        set_end_of_simulation(phil->ph_struct);
        //usleep()
        mutex_print(now, DIE, phil);
        pthread_mutex_unlock(&phil->ph_struct->forks[phil->rfork]);
        return (true);
    }
    if (number_of_philosophers <= 1)
    {
        usleep(convert_ms_us(time_to_die));
        mutex_print(now, DIE, phil);
        return (true);
    }
    pthread_mutex_lock(&phil->ph_struct->forks[phil->lfork]);
    return (false);
}

static bool phil_eat(t_curph *phil)
{
    long time_to_eat;
    struct timeval meal_time;
    
    time_to_eat = phil->ph_struct->args[2];
    gettimeofday(&meal_time, NULL);
    if (!death_check(meal_time, phil))
    {
        set_end_of_simulation(phil->ph_struct);
        //usleep?
        mutex_print(meal_time, DIE, phil);
        return (true);
    }
    pthread_mutex_lock(&phil->mutx_last_meal);
    phil->last_meal = meal_time;
    pthread_mutex_unlock(&phil->mutx_last_meal);
    reset_death(&phil->death, phil->ph_struct->args[1], &phil->mutx_death, phil);//reafactor
    mutex_print(meal_time, EAT, phil);
    //usleep(convert_ms_us(time_to_eat));
    ph_sleep(time_to_eat);
    pthread_mutex_unlock(&phil->ph_struct->forks[phil->rfork]);
    pthread_mutex_unlock(&phil->ph_struct->forks[phil->lfork]);
    increment_meals(phil);
    return (false);
}

static bool phil_sleep(t_curph *phil)
{
    struct timeval now;
    
    gettimeofday(&now, NULL);
    if (death_check(now, phil))
    {
        mutex_print(now, SLEEP, phil);
        //usleep(convert_ms_us(phil->ph_struct->args[3]));//refactor
        ph_sleep(phil->ph_struct->args[3]);
        return (false);
    }
    set_end_of_simulation(phil->ph_struct);
    //usleep()
    mutex_print(now, DIE, phil);
    return (true);
}

static bool phil_think(t_curph *phil)
{
    struct timeval now;

    gettimeofday(&now, NULL);
    if (death_check(now, phil))
    {
        mutex_print(now, THINK, phil);
        return (false);
    }
    set_end_of_simulation(phil->ph_struct);
    //usleep()
    mutex_print(now, DIE, phil);
    return (true);
}