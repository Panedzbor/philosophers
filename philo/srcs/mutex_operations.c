#include "../philo.h"

int get_meals(t_curph *phil)
{
    int meals;

    pthread_mutex_lock(&phil->mutx_meals);
    meals = phil->meals;
    pthread_mutex_unlock(&phil->mutx_meals);
    return (meals);
}

void increment_meals(t_curph *phil)
{
    pthread_mutex_lock(&phil->mutx_meals);
    (phil->meals)++;
    pthread_mutex_unlock(&phil->mutx_meals);
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

void mutex_print(struct timeval time_tv, t_print message_type, t_curph *phil)
{
    const char *string;
    long timestamp;
    long death_time;
    struct timeval dt;

    if (message_type == FORK)
        string = "has taken a fork";
    else if (message_type == EAT)
        string = "is eating";
    else if (message_type == SLEEP)
        string = "is sleeping";
    else if (message_type == THINK)
        string = "is thinking";
    else if (message_type == DIE)
        string = "died";
    //timestamp = generate_timestamp(phil);

    //test // or no?
    pthread_mutex_lock(&phil->mutx_death);
    dt = phil->death;
    pthread_mutex_unlock(&phil->mutx_death);
    death_time = convert_timeval_ms(dt) - convert_timeval_ms(phil->ph_struct->start);
    //test

    timestamp = convert_timeval_ms(time_tv) - convert_timeval_ms(phil->ph_struct->start);
    /* if (message_type == DIE)
        timestamp = death_time; */
    pthread_mutex_lock(&phil->ph_struct->print);
    if (message_type == END)
        printf("End of simulation: philosophers go partying 🥳\n");
    else/* {
        write(1, string, 5);
        write(1, "\n", 1);} */
        printf("%04ld %d %s | death time: %ld\n", timestamp, phil->id, string, death_time);
    pthread_mutex_unlock(&phil->ph_struct->print);
}
