#include "../philo.h"

static int phil_take_forks(t_curph *phil);
static void phil_eat(t_curph *phil);
static void phil_sleep(t_curph *phil);
static void phil_think(t_curph *phil);

void    *phil_live(void *phil_void)
{
    t_curph *phil;
    int     meals_to_end;

    phil = (t_curph *)phil_void;
    meals_to_end = -1;
    if (phil->ph_struct->argc == 5)
        meals_to_end = phil->ph_struct->args[4];
    if (phil->id % 2 == 0)
        usleep(200);
    while ((meals_to_end < 0 || get_meals(phil) < meals_to_end) 
            && get_eos(phil->ph_struct) == false)
    {
        if (phil_take_forks(phil))
            phil_eat(phil);
        else
            set_end_of_simulation(phil->ph_struct);
        phil_sleep(phil);
        phil_think(phil);
    }
    return (NULL);
}

static int phil_take_forks(t_curph *phil)
{
    int number_of_philosophers;
    
    number_of_philosophers = phil->ph_struct->args[0];
    pthread_mutex_lock(&phil->ph_struct->forks[phil->rfork]);
    mutex_print(FORK, phil);
    if (number_of_philosophers <= 1)
        return (0);
    pthread_mutex_lock(&phil->ph_struct->forks[phil->lfork]);
    return (1);
}

static void phil_eat(t_curph *phil)
{
    long time_to_eat;
    struct timeval meal_time;
    
    gettimeofday(&meal_time, NULL);
    time_to_eat = phil->ph_struct->args[2];
    pthread_mutex_lock(&phil->mutx_last_meal);
    phil->last_meal = meal_time;
    pthread_mutex_unlock(&phil->mutx_last_meal);
    reset_death(&phil->death, phil->ph_struct->args[1], &phil->mutx_death, phil);//reafactor
    mutex_print(EAT, phil);
    usleep(convert_ms_us(time_to_eat));
    pthread_mutex_unlock(&phil->ph_struct->forks[phil->rfork]);
    pthread_mutex_unlock(&phil->ph_struct->forks[phil->lfork]);
    increment_meals(phil);
}

static void phil_sleep(t_curph *phil)
{
    mutex_print(SLEEP, phil);
    usleep(convert_ms_us(phil->ph_struct->args[3]));
}

static void phil_think(t_curph *phil)
{
    mutex_print(THINK, phil);
}