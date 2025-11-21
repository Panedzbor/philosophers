/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:46:49 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/15 17:46:52 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	death_check_mon(t_curph *phil,
				int number_of_philosophers, int *hungry);
static bool	hungry_check(t_curph *phil, int *hungry);

bool	death_check_ph(struct timeval tv, t_curph *phil)
{
	struct timeval	death;
	long long		d;
	long long		now;

	pthread_mutex_lock(&phil->mutx_death);
	death = phil->death;
	pthread_mutex_unlock(&phil->mutx_death);
	now = convert_timeval_ms(tv);
	d = convert_timeval_ms(death);
	if (now > d)
		return (false);
	return (true);
}

void	*death_monitor(void *phil_void)
{
	t_curph	*phil;
	int		number_of_philosophers;
	int		hungry;

	phil = (t_curph *)phil_void;
	number_of_philosophers = phil->ph_struct->args[0];
	while (!get_eos(phil->ph_struct))
	{
		hungry = 0;
		if (!death_check_mon(phil, number_of_philosophers, &hungry))
			return (NULL);
		if (!hungry_check(phil, &hungry))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static bool	death_check_mon(t_curph *phil, int number_of_philosophers,
							int *hungry)
{
	int				meals_to_end;
	struct timeval	death;
	struct timeval	now;
	int				i;

	meals_to_end = get_meals_to_end_val(phil);
	i = 0;
	while (i < number_of_philosophers && !get_eos(phil->ph_struct))
	{
		pthread_mutex_lock(&phil[i].mutx_death);
		death = phil[i].death;
		pthread_mutex_unlock(&phil[i].mutx_death);
		gettimeofday(&now, NULL);
		if (convert_timeval_ms(now) > convert_timeval_ms(death))
		{
			set_end_of_simulation(&phil[i]);
			mutex_print_prepare(now, DIE, &phil[i]);
			return (false);
		}
		if (meals_to_end < 0 || get_meals(&phil[i]) < meals_to_end)
			(*hungry)++;
		i++;
	}
	return (true);
}

static bool	hungry_check(t_curph *phil, int *hungry)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (!(*hungry))
	{
		set_end_of_simulation(&phil[0]);
		usleep(10000);
		mutex_print_prepare(now, END, phil);
		return (false);
	}
	return (true);
}
