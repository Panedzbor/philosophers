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

int	get_mte_value(t_curph *phil)
{
	int	meals_to_end;

	meals_to_end = -1;
	if (phil->ph_struct->argc == 5)
		meals_to_end = phil->ph_struct->args[4];
	return (meals_to_end);
}

void	*death_monitor(void *phil_void)
{
	t_curph			*phil;
	int             number_of_philosophers;
    int             i;
    struct timeval  death_vs_now[2];
	int				meals_to_end;
	int				hungry;

	phil = (t_curph *)phil_void;
	number_of_philosophers = phil->ph_struct->args[0];
	meals_to_end = get_mte_value(phil);
	while (!get_eos(phil->ph_struct))
	{
		hungry = 0;
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
			if (meals_to_end < 0 || get_meals(&phil[i]) < meals_to_end)
				hungry++;
			i++;
		}
		if (!hungry)
		{
			set_end_of_simulation(&phil[0]);
			usleep(10000);
			mutex_print_prepare(death_vs_now[0], END, phil);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
