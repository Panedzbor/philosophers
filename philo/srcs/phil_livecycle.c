#include "../philo.h"

static int phil_take_forks(t_curph *phil);
static void phil_eat(t_curph *phil);
static void phil_sleep(t_curph *phil);
static void phil_think(t_curph *phil);

int get_meals(t_curph *phil)
{
    int meals;

    pthread_mutex_lock(&phil->ph_mutex);
    meals = phil->meals;
    pthread_mutex_unlock(&phil->ph_mutex);
    retrun (meals);
}

bool get_eos(t_philo *ph_struct)
{
    bool eos;

    pthread_mutex_lock(&ph_struct->eos);
    eos = ph_struct->end_of_simulation;
    pthread_mutex_unlock(&ph_struct->eos);
    return (eos);
}

void set_end_of_simulation(t_philo *ph_struct)
{
    pthread_mutex_lock(&ph_struct->eos);
    ph_struct->end_of_simulation = true;
    pthread_mutex_unlock(&ph_struct->eos);
}

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
        if (phil->next_action == EAT)//remove
        {
            if (phil_take_forks(phil))
                phil_eat(phil);
            else
                set_end_of_simulation(phil->ph_struct);
        }
        else if (phil->next_action == SLEEP)
            phil_sleep(phil);
        else if (phil->next_action == THINK)
            phil_think(phil);
    }
    return (NULL);
}

void mutex_print(t_print message_type, t_curph *phil)
{
    const char *string;

    if (message_type == FORK)
        string = "has taken a fork\n";
    else if (message_type == EATS)
        string = "is eating\n";
    else if (message_type == SLEEPS)
        string = "is sleeping\n";
    else if (message_type == THINKS)
        string = "is thinking\n";
    else if (message_type == DIE)
        string = "died\n";
    pthread_mutex_lock(&phil->ph_struct->print);
    if (message_type == END)
        printf("End of simulation: philosophers go partying 🥳\n");
    else
        printf("%04ld %d %s", generate_timestamp(phil), phil->id, string);
    pthread_mutex_unlock(&phil->ph_struct->print);
}

static int phil_take_forks(t_curph *phil)
{
    int number_of_philosophers;
    
    number_of_philosophers = phil->ph_struct->args[0];
    pthread_mutex_lock(&phil->ph_struct->forks[phil->lfork]);
    mutex_print(FORK, phil);
    //printf("%04ld %d has taken a fork\n", generate_timestamp(phil),phil->id);//mutex
    if (number_of_philosophers <= 1)
        return (0);
    pthread_mutex_lock(&phil->ph_struct->forks[phil->rfork]);
    return (1);
}

void increment_meals(t_curph *phil)
{
    pthread_mutex_lock(&phil->ph_mutex);
    (phil->meals)++;
    pthread_mutex_unlock(&phil->ph_mutex);
}

static void phil_eat(t_curph *phil)
{
    //printf("%04ld %d is eating\n", generate_timestamp(phil), phil->id);
    mutex_print(EATS, phil);
    reset_death(&phil->death, phil->ph_struct->args[1], &phil->ph_mutex);
    usleep(convert_ms_us(phil->ph_struct->args[2]));
    pthread_mutex_unlock(&phil->ph_struct->forks[phil->lfork]);
    pthread_mutex_unlock(&phil->ph_struct->forks[phil->rfork]);
    increment_meals(phil);
    phil->next_action = SLEEP;//remove
}

static void phil_sleep(t_curph *phil)
{
    //printf("%04ld %d is sleeping\n", generate_timestamp(phil), phil->id);
    mutex_print(SLEEPS, phil);
    usleep(convert_ms_us(phil->ph_struct->args[3]));
    phil->next_action = THINK;//remove
}

static void phil_think(t_curph *phil)
{
    //printf("%04ld %d is thinking\n", generate_timestamp(phil), phil->id);
    mutex_print(THINKS, phil);
    phil->next_action = EAT;//remove
}