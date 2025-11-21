/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:48:39 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/15 17:48:39 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	reset_death(struct timeval *tv, int time_to_die,
					pthread_mutex_t *death, t_curph *phil)
{
	struct timeval	last_meal;

	pthread_mutex_lock(&phil->mutx_last_meal);
	last_meal = phil->last_meal;
	pthread_mutex_unlock(&phil->mutx_last_meal);
	pthread_mutex_lock(death);
	tv->tv_sec = last_meal.tv_sec + convert_ms_sec(time_to_die);
	tv->tv_usec = last_meal.tv_usec + (time_to_die % 1000) * 1000;
	if (tv->tv_usec >= 1000000)
	{
		tv->tv_sec++;
		tv->tv_usec -= 1000000;
	}
	pthread_mutex_unlock(death);
}

void	simulate_alone_phil(t_curph *phil)
{
	int				time_to_die;
	struct timeval	now;

	time_to_die = phil->ph_struct->args[1];
	usleep(convert_ms_us(time_to_die));
	gettimeofday(&now, NULL);
	set_end_of_simulation(phil);
	mutex_print_prepare(now, DIE, phil);
}

void	putaway_forks(t_curph *phil, bool forks_taken)
{
	if (!forks_taken)
		return ;
	pthread_mutex_unlock(&phil->ph_struct->forks[phil->rfork]);
	pthread_mutex_unlock(&phil->ph_struct->forks[phil->lfork]);
}

void	increment_meals(t_curph *phil)
{
	pthread_mutex_lock(&phil->mutx_meals);
	(phil->meals)++;
	pthread_mutex_unlock(&phil->mutx_meals);
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
