/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:47:11 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/15 17:47:13 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*mem_cleaner(void *mem[])
{
	int	i;

	i = 0;
	while (i < D_PTRS)
	{
		free(mem[i]);
		i++;
	}
	return (NULL);
}

void	destroy_mutexes(t_curph *phil)
{
	int	i;

	i = 0;
	while (i < phil->ph_struct->args[0])
	{
		pthread_mutex_destroy(&phil->ph_struct->forks[i]);
		pthread_mutex_destroy(&phil->mutx_meals);
		pthread_mutex_destroy(&phil->mutx_death);
		pthread_mutex_destroy(&phil->mutx_last_meal);
		i++;
	}
	pthread_mutex_destroy(&phil->ph_struct->eos);
	pthread_mutex_destroy(&phil->ph_struct->print);
}
