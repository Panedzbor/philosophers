#include "../philo.h"

int	get_meals(t_curph *phil)
{
	int	meals;

	pthread_mutex_lock(&phil->mutx_meals);
	meals = phil->meals;
	pthread_mutex_unlock(&phil->mutx_meals);
	return (meals);
}

void	increment_meals(t_curph *phil)
{
	pthread_mutex_lock(&phil->mutx_meals);
	(phil->meals)++;
	pthread_mutex_unlock(&phil->mutx_meals);
}

bool	get_eos(t_philo *ph_struct)
{
	bool	eos;

	pthread_mutex_lock(&ph_struct->eos);
	eos = ph_struct->end_of_simulation;
	pthread_mutex_unlock(&ph_struct->eos);
	return (eos);
}

void	set_end_of_simulation(t_curph *phil)
{
	int	dead_id;

	pthread_mutex_lock(&phil->ph_struct->eos);
	phil->ph_struct->end_of_simulation = true;
	pthread_mutex_unlock(&phil->ph_struct->eos);
	pthread_mutex_lock(&phil->ph_struct->did);
	dead_id = phil->ph_struct->dead_id;
	pthread_mutex_unlock(&phil->ph_struct->did);
	if (!dead_id)
	{
		pthread_mutex_lock(&phil->ph_struct->did);
		phil->ph_struct->dead_id = phil->id;
		pthread_mutex_unlock(&phil->ph_struct->did);
	}
}

bool	check_id(t_curph *phil)
{
	int	dead_id;

	pthread_mutex_lock(&phil->ph_struct->did);
	dead_id = phil->ph_struct->dead_id;
	pthread_mutex_unlock(&phil->ph_struct->did);
	if (dead_id == phil->id)
		return (true);
	return (false);
}
