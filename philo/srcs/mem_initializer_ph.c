/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_initializer_ph.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earutiun <earutiun@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:47:28 by earutiun          #+#    #+#             */
/*   Updated: 2025/11/15 17:47:31 by earutiun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	define_forks(t_curph *philosopher, int number_of_philosophers);
static void	define_death_time(t_curph *philosopher);

void	init_philosophers(
	t_curph philosophers[], t_philo *ph_struct, void *threads)
{
	int	number_of_philosophers;
	int	i;

	number_of_philosophers = ph_struct->args[0];
	i = 0;
	while (i < number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].meals = 0;
		philosophers[i].fed_up = false;
		philosophers[i].thread = &((pthread_t *)threads)[i];
		philosophers[i].ph_struct = ph_struct;
		philosophers[i].last_meal = ph_struct->start;
		philosophers[i].death = ph_struct->start;
		pthread_mutex_init(&philosophers[i].mutx_meals, NULL);
		pthread_mutex_init(&philosophers[i].mutx_death, NULL);
		pthread_mutex_init(&philosophers[i].mutx_last_meal, NULL);
		define_forks(&philosophers[i], number_of_philosophers);
		define_death_time(&philosophers[i]);
		i++;
	}
}

static void	define_forks(t_curph *philosopher, int number_of_philosophers)
{
	philosopher->rfork = philosopher->id - 1;
	philosopher->lfork = philosopher->id;
	if (philosopher->id == number_of_philosophers)
		philosopher->lfork = 0;
}

static void	define_death_time(t_curph *philosopher)
{
	int	time_to_die;

	time_to_die = philosopher->ph_struct->args[1];
	reset_death(&philosopher->death, time_to_die,
		&philosopher->mutx_death, philosopher);
}
