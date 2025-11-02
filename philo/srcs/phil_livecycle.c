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
    while ((meals_to_end < 0 || phil->meals < meals_to_end) 
            && phil->ph_struct->end_of_simulation == false)
    {
        if (phil->next_action == EAT)
        {
            if (phil_take_forks(phil))
                phil_eat(phil);
            else
                phil->ph_struct->end_of_simulation = true;
        }
        else if (phil->next_action == SLEEP)
            phil_sleep(phil);
        else if (phil->next_action == THINK)
            phil_think(phil);
    }
    return (NULL);
}

static int phil_take_forks(t_curph *phil)
{
    int number_of_philosophers;
    
    number_of_philosophers = phil->ph_struct->args[0];
    pthread_mutex_lock(&phil->ph_struct->mutexes[phil->lfork]);
    printf("%04ld %d has taken a fork\n", generate_timestamp(phil),phil->id);
    if (number_of_philosophers <= 1)
        return (0);
    pthread_mutex_lock(&phil->ph_struct->mutexes[phil->rfork]);
    return (1);
}

static void phil_eat(t_curph *phil)
{
    printf("%04ld %d is eating\n", generate_timestamp(phil), phil->id);
    reset_death(&phil->death, phil->ph_struct->args[1]);
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