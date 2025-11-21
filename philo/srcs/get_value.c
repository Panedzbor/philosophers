/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:18:12 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/21 18:18:14 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	get_eos(t_philo *ph_struct)
{
	bool	eos;

	pthread_mutex_lock(&ph_struct->eos);
	eos = ph_struct->end_of_simulation;
	pthread_mutex_unlock(&ph_struct->eos);
	return (eos);
}

int	get_meals(t_curph *phil)
{
	int	meals;

	pthread_mutex_lock(&phil->mutx_meals);
	meals = phil->meals;
	pthread_mutex_unlock(&phil->mutx_meals);
	return (meals);
}

int	get_meals_to_end_val(t_curph *phil)
{
	int	meals_to_end;

	meals_to_end = -1;
	if (phil->ph_struct->argc == 5)
		meals_to_end = phil->ph_struct->args[4];
	return (meals_to_end);
}
