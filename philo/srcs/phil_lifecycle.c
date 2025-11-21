/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:48:08 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/15 17:48:10 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	phil_take_forks(t_curph *phil);
static bool	phil_eat(t_curph *phil);
static bool	phil_sleep(t_curph *phil);
static bool	phil_think(t_curph *phil);

void	*phil_live(void *phil_void)
{
	t_curph	*phil;
	int		time_to_eat;
	bool	forks_taken;
	bool	completed;

	phil = (t_curph *)phil_void;
	time_to_eat = phil->ph_struct->args[2];
	completed = false;
	if (phil->id % 2 == 0)
		usleep(convert_ms_us(time_to_eat / 2));
	while (!get_eos(phil->ph_struct))
	{
		forks_taken = phil_take_forks(phil);
		if (!get_eos(phil->ph_struct) && forks_taken)
			completed = phil_eat(phil);
		else if (forks_taken)
			putaway_forks(phil, forks_taken);
		if (!get_eos(phil->ph_struct) && completed)
			completed = phil_sleep(phil);
		if (!get_eos(phil->ph_struct) && completed)
			completed = phil_think(phil);
		if (!completed)
			break ;
	}
	return (NULL);
}

static bool	phil_take_forks(t_curph *phil)
{
	int				number_of_philosophers;
	struct timeval	now;

	number_of_philosophers = phil->ph_struct->args[0];
	pthread_mutex_lock(&phil->ph_struct->forks[phil->rfork]);
	gettimeofday(&now, NULL);
	if (death_check_ph(now, phil))
		mutex_print_prepare(now, FORK, phil);
	else
	{
		pthread_mutex_unlock(&phil->ph_struct->forks[phil->rfork]);
		return (false);
	}
	if (number_of_philosophers <= 1)
	{
		simulate_alone_phil(phil);
		pthread_mutex_unlock(&phil->ph_struct->forks[phil->rfork]);
		return (false);
	}
	pthread_mutex_lock(&phil->ph_struct->forks[phil->lfork]);
	return (true);
}

static bool	phil_eat(t_curph *phil)
{
	long			time_to_eat;
	long			time_to_die;
	struct timeval	meal_time;

	time_to_eat = phil->ph_struct->args[2];
	time_to_die = phil->ph_struct->args[1];
	gettimeofday(&meal_time, NULL);
	if (!death_check_ph(meal_time, phil))
	{
		putaway_forks(phil, true);
		return (false);
	}
	pthread_mutex_lock(&phil->mutx_last_meal);
	phil->last_meal = meal_time;
	pthread_mutex_unlock(&phil->mutx_last_meal);
	reset_death(&phil->death, time_to_die, &phil->mutx_death, phil);
	mutex_print_prepare(meal_time, EAT, phil);
	ph_sleep(time_to_eat);
	pthread_mutex_unlock(&phil->ph_struct->forks[phil->rfork]);
	pthread_mutex_unlock(&phil->ph_struct->forks[phil->lfork]);
	increment_meals(phil);
	return (true);
}

static bool	phil_sleep(t_curph *phil)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (death_check_ph(now, phil))
	{
		mutex_print_prepare(now, SLEEP, phil);
		ph_sleep(phil->ph_struct->args[3]);
		return (true);
	}
	return (false);
}

static bool	phil_think(t_curph *phil)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (death_check_ph(now, phil))
	{
		mutex_print_prepare(now, THINK, phil);
		return (true);
	}
	return (false);
}
