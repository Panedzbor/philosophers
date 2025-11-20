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

long	generate_timestamp(t_curph *phil)
{
	struct timeval	tv;
	long			dif_sec;
	long			dif_us;
	long			ms;

	gettimeofday(&tv, NULL);
	dif_sec = tv.tv_sec - phil->ph_struct->start.tv_sec;
	dif_us = tv.tv_usec - phil->ph_struct->start.tv_usec;
	ms = convert_sec_ms(dif_sec) + convert_us_ms(dif_us);
	return (ms);
}

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

bool	all_fed_up(t_curph *phil, int id, int meals_to_end)
{
	t_curph			*first_phil;
	struct timeval	now;
	int				number_of_philosophers;
	int				i;

	first_phil = phil - (id - 1);
	number_of_philosophers = phil->ph_struct->args[0];
	i = 0;
	while (i < number_of_philosophers)
	{
		if (meals_to_end < 0 || get_meals(&first_phil[i]) < meals_to_end)
			return (false);
		i++;
	}
	set_end_of_simulation(phil);
	gettimeofday(&now, NULL);
	mutex_print_prepare(now, END, phil);
	return (true);
}

void	putaway_forks(t_curph *phil, bool forks_taken)
{
	if (!forks_taken)
		return ;
	pthread_mutex_unlock(&phil->ph_struct->forks[phil->sfork]);
	pthread_mutex_unlock(&phil->ph_struct->forks[phil->bfork]);
}
