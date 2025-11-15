/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_initializer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:47:22 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/15 17:47:23 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_mem(void *mem[])
{
	int	i;

	i = 0;
	while (i < D_PTRS)
	{
		mem[i] = NULL;
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
