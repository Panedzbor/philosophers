#include "../philo.h"

int get_meals(t_curph *phil)
{
    int meals;

    pthread_mutex_lock(&phil->ph_mutex);
    meals = phil->meals;
    pthread_mutex_unlock(&phil->ph_mutex);
    return (meals);
}

void increment_meals(t_curph *phil)
{
    pthread_mutex_lock(&phil->ph_mutex);
    (phil->meals)++;
    pthread_mutex_unlock(&phil->ph_mutex);
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

void mutex_print(t_print message_type, t_curph *phil)
{
    const char *string;

    if (message_type == FORK)
        string = "has taken a fork\n";
    else if (message_type == EAT)
        string = "is eating\n";
    else if (message_type == SLEEP)
        string = "is sleeping\n";
    else if (message_type == THINK)
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