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
