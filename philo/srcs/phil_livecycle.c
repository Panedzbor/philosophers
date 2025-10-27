#include "../philo.h"

static void phil_take_forks(t_curph *phil);
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

static void phil_take_forks(t_curph *phil)
{
    pthread_mutex_lock(&phil->ph_struct->mutexes[phil->lfork]);
    printf("%04ld %d has taken a fork\n", generate_timestamp(phil),phil->id);
    pthread_mutex_lock(&phil->ph_struct->mutexes[phil->rfork]);
}

static void phil_eat(t_curph *phil)
{
    reset_death(&phil->death, phil->ph_struct->args[1]);
    printf("%04ld %d is eating\n", generate_timestamp(phil), phil->id);
    usleep(convert_ms_us(phil->ph_struct->args[2]));
    pthread_mutex_unlock(&phil->ph_struct->mutexes[phil->lfork]);
    pthread_mutex_unlock(&phil->ph_struct->mutexes[phil->rfork]);
    (phil->meals)++;
    phil->next_action = SLEEP;
}

static void phil_sleep(t_curph *phil)
{
    printf("%04ld %d is sleeping\n", generate_timestamp(phil), phil->id);
    usleep(convert_ms_us(phil->ph_struct->args[3]));
    phil->next_action = THINK;
}

static void phil_think(t_curph *phil)
{
    printf("%04ld %d is thinking\n", generate_timestamp(phil), phil->id);
    phil->next_action = EAT;
}