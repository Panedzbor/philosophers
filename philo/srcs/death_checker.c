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

bool	death_check(struct timeval tv, t_curph *phil)
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
	t_curph			*phil;
	int             number_of_philosophers;
    int             i;
    struct timeval  death_vs_now[2];

	phil = (t_curph *)phil_void;
	number_of_philosophers = phil->ph_struct->args[0];
	while (!get_eos(phil->ph_struct))
	{
		i = 0;
		while (i < number_of_philosophers && !get_eos(phil->ph_struct))
		{
			pthread_mutex_lock(&phil[i].mutx_death);
			death_vs_now[1] = phil[i].death;
			pthread_mutex_unlock(&phil[i].mutx_death);
			gettimeofday(&death_vs_now[0], NULL);
			if (convert_timeval_ms(death_vs_now[0]) > convert_timeval_ms(death_vs_now[1]))//refactor!
			{
				set_end_of_simulation(&phil[i]);
				mutex_print_prepare(death_vs_now[0], DIE, &phil[i]);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
