/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:18:22 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/21 18:18:24 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
